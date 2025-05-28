#include <string>
#include <vector>
#include <algorithm>

#include "MTF_Transform.h"

using namespace std;

int indexOfChar(const vector<char> &vec, char target) {
    auto it = find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        return static_cast<int>(it - vec.begin());
    } else {
        return -1;
    }
}

void mtf(vector<char> &dict, int id) {
    if (id <= 0 || id >= dict.size()) return;
    char value = dict[id];
    for (int i = id; i > 0; --i) {
        dict[i] = dict[i - 1];
    }
    dict[0] = value;

}

string MTFencode(string &s) {
    // initialize the dict
    vector<char> dict(128);
    for (int i = 0; i < 128; ++i) {
        dict[i] = static_cast<char>(i);
    }
    // do the MTF
    char c;
    int id;
    string es;
    for (int i = 0; i < s.length(); ++i) {
        c = s[i];
        id = indexOfChar(dict, c);
        mtf(dict, id);
        es.append(to_string(id));
        es.append(" ");
    }
    return es;
}
