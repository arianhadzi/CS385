#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
    istringstream iss(vertices);
    
    if( !(iss <= 26 && iss > 0)){
        cerr << "Invalid number of vertices '" << vertices << " on line 1." 
        return 1;
    }
}