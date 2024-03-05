#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std; 

int max(int m, int n){
	return m > n ? m : n;
}

int main (int argc, char* argv[]){
	int n, m; 
	istringstream iss; 
	
	if(argc !=3){
		cerr << "Usage: " << argv[0] << "<int> <int>" << endl; 
		return 1;
	}
	
	iss.str(argv[1]);
	if(!(iss >> m)){
		cerr << "Err: first command line argument must be an int" << endl; 
		return 1;
	}

	iss.clear();
	iss.str(argv[2]);
	if(!(iss >> n)){
		cerr << "Err: second command line argument must be an int" << endl; 
		return 1;
	}

	cout << "m is :" << m << endl;
	cout << "n is :" << n << endl;
	cout << "max(" << m << ", " << n <<") is :" << max(m, n) << endl;
	return 0;
	
}