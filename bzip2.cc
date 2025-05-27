#include <iostream>
#include <string>

#include "BW_Transform.h"

using namespace std;

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
    
    // BWT main helper
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
    // end of BWT main helper

    return 0;
}