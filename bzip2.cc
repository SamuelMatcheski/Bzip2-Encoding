#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "BW_Transform.h"
#include "MTF_Transform.h"
#include "Zero_Runs.h"
#include "Huffman_Encoding.h"

using namespace std;

/*
void printString(string &s, int id) {
    if (s.length() == 0) {
        cout << endl; 
        return;
    }
    if (id < 0 || id >= s.length()) {
        cout << "invalid index" << endl;
        return;
    }
    cout << s[id];
    int pos = id;
    ++pos;
    while (pos != id) {
        if (pos >= s.length()) {
            pos = 0;
        } else {
            cout << s[pos];
            ++pos;
        }
    }
    cout << endl;
}
*/

// necessary to get rid of non ASCII characters
string sanitize(const string& input) {
    bool invalidChar = false;
    string result;
    for (unsigned char c : input) {
        if (c <= 127) result += c;
        else invalidChar = true;
    }
    if (invalidChar) cerr << "WARNING: there are non-ascii character(s) included included in your text that will not be stored" << endl;
    return result;
}

int main(int argc, char* argv[]) {
    // handle cmd
    string cmdArgHelp = "-e to encode\n-d to decode";
    if (argc == 1 || argc > 2) {
        cout << "Enter exactly one command line argument:\n" << cmdArgHelp << endl;
        return 0;
    }
    string cmd = argv[1];
    if (cmd != "-e" && cmd != "-d") {
        cout << "Incorrect command line argument:\n" << cmdArgHelp << endl;
        return 0;
    }

    
    // now we have to see if we are encoding or decoding
    if (cmd == "-e") {
        // read in the string - preserve all spacings
        string input;
        string line;
        while (getline(cin, line)) {
            input += line + '\n';
        }
        // get rid of non-ascii chars
        input = sanitize(input);
        // Encode!
        vector<int> v;
        string es1 = BWencode(input);
        string es2 = MTFencode(es1);
        string es3 = ZRencode(es2);
        string es4 = HUFFencode(es3, v);

        // compression info to cerr
        cerr << "8-bit ASCII converted to Binary with compression ratio of: ";
        int compression = (es4.length() * 10000 / (8 * input.length())); // in 10000s
        cerr << compression / 100 << "." << compression % 100 << "%" << endl;

        // now we output the encoded string and the trie
        // cout << "===CODE===" << endl;
        cout << es4 << endl;
        // cout << "===TRIE===" << endl;
        for (int i : v) cout << i << ' ';
        cout << endl;
    }

    if (cmd == "-d") {
        // read in what we need
        string bitstring;
        string trie;
        if(!getline(cin, bitstring)){
            cout << "A: Expected at least two lines of text" << endl;
            return 0;
        }
        if(!getline(cin, trie)) {
            cout << "B: Expected at least two lines of text" << endl;
            return 0;
        }
        istringstream iss(trie);
        vector<int> trieVec;
        int val;
        while (iss >> val) trieVec.push_back(val);

        // now we actually decode
        string ds4 = HUFFdecode(bitstring, trieVec);
        string ds3 = ZRdecode(ds4);
        string ds2 = MTFdecode(ds3);
        string ds1 = BWdecode(ds2);
        // AT END OF DECODING, REMEMBER TO REMOVE THE NULL CHAR! OR ELSE ORIGINAL WILL BE SLIGHLTY DIFFERENT (and remove extra newline)
        ds1.erase(remove(ds1.begin(), ds1.end(), '\0'), ds1.end());
        if (!ds1.empty()) ds1.pop_back();

        cout << ds1 << endl;
    }

    
    /*
    string s = "alfeatsalfalfa";
    string es1 = BWencode(s);
    string es2 = MTFencode(es1);
    string es3 = ZRencode(es2);
    vector<int> v;
    string es4 = HUFFencode(es3, v);
    string ds4 = HUFFdecode(es4, v);
    string ds3 = ZRdecode(ds4);
    string ds2 = MTFdecode(ds3);
    string ds1 = BWdecode(ds2);

    cout << "ogS: " << s << endl;
    cout << "es1: " << es1 << endl;
    cout << "es2: " << es2 << endl;
    cout << "es3: " << es3 << endl;
    cout << "es4: " << es4 << endl;
    cout << "ds4: " << ds4 << endl;
    cout << "ds3: " << ds3 << endl;
    cout << "ds2: " << ds2 << endl;
    cout << "ds1: " << ds1 << endl;
    */
    return 0;
}