#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

// takes a string s and two indexes into that string, if the cyclic shift starting at index id1
//   comes before that starting at id2 (lexicographically), returns true. Otherwise returns false
int CyclicShiftLessThan(const string &s, int id1, int id2) {
    // since we add terminal which comes before all others, no need to 'loop' as once one hits end it will be <
    while (id1 < s.length() && id2 < s.length()) {
        if (s[id1] < s[id2]) return true;
        if (s[id1] > s[id2]) return false;
        ++id1;
        ++id2;
    }
    cerr << "hit end of string when comparing. Should not occur. Did you remember to add terminal?" << endl;
    return false;
}

string BWencode(string &s) {
    s = s + '\0'; // need a terminal to work. '\0' is below all
    vector<int> startIDs(s.length());
    for (int i = 0; i < startIDs.size(); ++i) {
        startIDs[i] = i;
    }

    // sort startIDs based using the CyclicShiftLessThan function above
    sort(startIDs.begin(), startIDs.end(), [&](int id1, int id2) {
        return CyclicShiftLessThan(s, id1, id2);
    });

    // now startIDs is sorted based on the string substring of s starting at their ids
    //   what we want is last column of sorted cyclic shifts array, which is just the char one before
    //   the indices in startIDs (in same order)
    string encoded_s;
    for (int &i : startIDs) {
        if (i == 0) {
            encoded_s += s[s.length() - 1];
        } else {
            encoded_s += s[i - 1];
        }
    }

    return encoded_s;
}

// s must have '\0' somewhere in it
string BWdecode(string &s) {
    // check for no '\0' error
    int i = 0;
    while (i < s.length()) {
        if (s[i] == '\0') break;
        ++i;
    }
    if (i >= s.length()) {
        throw "no '\0' character in s";
    }
    // s = last col of sorted cyclic shifts array
    vector<pair<char, int>> A(s.length());
    for (int i = 0; i < s.length(); ++i) {
        A[i].first = s[i];
        A[i].second = i;
    }
    stable_sort(A.begin(), A.end(), [](const pair<char, int> &a, const pair<char, int> &b) {
        return a.first < b.first;
    });
    int j = 0;
    while (j < s.length()) {
        if (s[j] == '\0') break;
        ++j;
    }

    string decoded_s;
    char c;
    do {
        c = A[j].first;
        decoded_s += c;
        j = A[j].second;
    } while (c != '\0');

    return decoded_s;

}

int main() {
    string s = "alfeatsalfalfa";
    string es = BWencode(s);
    string ds;
    try {
        ds = BWdecode(es);
    } catch (...) {
        cerr << "no '\0' character in s. Decoding cannot be completed" << endl;
        return 1;
    }
    cout << "ORG: " << s << endl;
    cout << "ENC: " << es << endl;
    cout << "DEC: " << ds << endl;
}