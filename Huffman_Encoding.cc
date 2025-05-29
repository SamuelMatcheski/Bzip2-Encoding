#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iostream>

#include "Huffman_Encoding.h"

using namespace std;

struct Node {
    int val;
    int freq;
    Node* left;
    Node* right;
    Node(int val) : val(val) {}
    Node(int val, int freq) : val(val), freq(freq), left(nullptr), right(nullptr) {}
    Node(int val, int freq, Node* left, Node* right) : val(val), freq(freq), left(left), right(right) {}
    ~Node() {
        delete left;
        delete right;
    }
};

struct Compare {
    bool operator()(Node *l, Node *r) {
        if (l->freq == r->freq) return l->val > r->val;
        return l->freq > r->freq;
    }
};

// preorder tree serializer, -1 implying null child. Takes root and serializes it for storage
void serializeTrie(Node *p, vector<int> &vec) {
    if (p == nullptr) {
        vec.push_back(-1);
        return;
    }
    vec.push_back(p->val);
    serializeTrie(p->left, vec);
    serializeTrie(p->right, vec);
}

// preorder tree deserializer, -1 implying null child.  First call with vecID = 0.
//   Returns pointer to root of newly created trie.
Node *deserializeTrie(int &vecID, vector<int> &vec) {
    if (vec[vecID] == -1){
        vecID++;
        return nullptr;
    }
    
    Node* root = new Node(vec[vecID]);
    vecID++;
    
    root->left = deserializeTrie(vecID, vec);
    root->right = deserializeTrie(vecID, vec);
    
    return root;
}

// creates the huffman trie using the string s
//   Returns pointer to root of trie.
Node *createTrieFromString(const string &s) {
    //  1. Create a hashmap of all ints in s and their frequencies
    unordered_map<int, int> m; // <val, freq>
    istringstream iss(s);
    int vl;
    while (iss >> vl) {
        if (m.find(vl) != m.end()) {
            ++m[vl];
        } else {
            m[vl] = 1;
        }
    }
    //  2. Put all hashmap as nodes into a min-heap (min based on frequency)
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (const auto &pr : m) {
        Node *newNode = new Node(pr.first, pr.second);
        minHeap.push(newNode);
    }

    // If s only has one unique symbol, add a dummy node to force a binary tree or else we end up with a symbol with encoding: ""
    if (minHeap.size() == 1) {
        minHeap.push(new Node(-2, 0));
    }

    //  3. Combine lowest freq nodes until there is only one
    while (minHeap.size() > 1) {
        Node *n1 = minHeap.top();
        minHeap.pop();
        Node *n2 = minHeap.top();
        minHeap.pop();
        int combinedFreq = n1->freq + n2->freq;
        minHeap.push(new Node(-2, combinedFreq, n1, n2));
    }
    // now the top of the minHeap is the root of the trie, just return it
    return minHeap.top();
}

// goes through a trie and modifies a map: <leaf value, path to leaf> to help encoding
//   first call with path = ""
void trieToMap(const Node *n, unordered_map<int, string> &mp, string path) {
    if (!n) return;
    if (!n->left && !n->right) { // if the node is a leaf node, then we add pair
        mp[n->val] = path; // add pair
    }
    trieToMap(n->left, mp, path + "0");
    trieToMap(n->right, mp, path + "1");
}

// returns the encoded string and mutates vec to be the serialized Trie (pass vec as empty vector)
//   s is a string of ints separated by spaces. eg: s = "0 0 0 23 41"
string HUFFencode(const string &s, vector<int> &vec) {
    // creating the trie...
    Node *root = createTrieFromString(s);
    // need to have vec as the serialized trie
    serializeTrie(root, vec);
    // since we know all the values of s will be integers [0, 128) we can create a map for this trie for each char
    //   I'll do this by visiting each leaf of the tree, keeping track of code on way down, then adding code as a value for the given leaf's key 
    unordered_map<int, string> encodeMap;
    trieToMap(root, encodeMap, "");
    // now that we have the mapping, the actual encoding is quite easy
    int vl;
    istringstream iss(s);
    ostringstream oss;
    while (iss >> vl) {
        oss << encodeMap[vl];
    }
    // cleanup
    delete root;

    return oss.str();
}

string HUFFdecode(const string &s, vector<int> &serializedTrie) {
    // deserialize the trie
    int ogID = 0;
    Node *root = deserializeTrie(ogID, serializedTrie);

    if (!root) {
        cerr << "deserialized Trie is NULL" << endl; 
        return "";
    }

    // now we read from trie
    ostringstream oss;
    Node *curnode = root;
    for (char bit : s) {
    if (!curnode) {
        cerr << "Error: encountered invalid bit sequence (curnode is nullptr)." << endl;
        return "";
    }
    if (bit == '0') {
        curnode = curnode->left;
    } else if (bit == '1') {
        curnode = curnode->right;
    } else {
        cerr << "Error: unexpected character '" << bit << "' in bitstring." << endl;
        return "";
    }
    if (!curnode) {
        cerr << "Error: invalid bit path led to null node." << endl;
        return "";
    }
    if (!curnode->left && !curnode->right) {
        oss << curnode->val << " ";
        curnode = root;
    }
}
    delete root;
    return oss.str();
}

/*
// main function just for testing
int main() {
    string s = "97 102 0 1 115 3 103 3 109 0 2 5 0 2 116 1 ";
    vector<int> v;
    string es = HUFFencode(s, v);
    string ds = HUFFdecode(es, v);

    cout << s << endl;
    cout << es << endl;
    cout << ds << endl;
}
*/
