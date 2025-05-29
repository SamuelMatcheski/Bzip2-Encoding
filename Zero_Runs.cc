#include <string>
#include <sstream>

#include "Zero_Runs.h"

using namespace std;

string ZRencode(const string &s) {
    istringstream iss(s);
    ostringstream oss;
    int val;
    int numzeros = 0;
    while (iss >> val) {
        if (val == 0) {
            numzeros++;
        } else {
            if (numzeros > 0) {
                oss << 0 << " " << numzeros << " ";
                numzeros = 0;
            }
            oss << val << " ";
        }
    }
    if (numzeros > 0) {
        oss << 0 << " " << numzeros << " ";
        numzeros = 0;
    }
    return oss.str();
}

string ZRdecode(const string &s) {
    istringstream iss(s);
    ostringstream oss;
    int val;
    int numzeros = 0;
    while (iss >> val) {
        if (val == 0) {
            iss >> numzeros;
            for (int i = 0; i < numzeros; ++i) {oss << 0 << " ";}
        } else {
            oss << val << " ";
        }
    }
    return oss.str();
}
