#include <iostream>
#include <string>

// #include "BW_Transform.cc"

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
    // call correct functions...
    string s = "ABCDEFG";
    printString(s, 2);

    return 0;
}