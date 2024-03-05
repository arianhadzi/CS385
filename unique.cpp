/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Arian Hadzibrahimi
 * Date        : 9/30/23
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      :  I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    int n = size.length();
    for(int i = 0; i < n; i++){
        if(!(islower(s[i]))){
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    unsigned int setter, vector = 0;
    int n = s.length();
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only.  Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.

    for(int i = 0; i < n; i++){
        setter = 1 << (s[i] - 'a');
        if((setter & vector) > 0){
            return false;
        }
        vector |= setter;
    }
    return true;

}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    istringstream iss;
    string s;

    if(argc != 1){
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }

    iss.str(argv[1]);
    (iss >> s);
    if(!(is_all_lowercase(s))){
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if(all_unique_letters(s)){
        cerr << "All letters are unique." << endl;
        return 1;
    } else{
         cout << "Duplicate letters found." << endl;
         return 0;
    }

    

    return 0;
}
