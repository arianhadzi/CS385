/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Arian Hadzibrahimi
 * Version : 1.0
 * Date    : September 7, 2023
 * Description: Computes the square root of a double using Newton's method.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;
//method to compute the square root using Newton's method
double sqrt(double num, double epsilon = pow(10.0, -7.0)){
    double lastGuess = num;
    double nextGuess = (lastGuess + num/lastGuess)/2;

    //if value is less than 0 return nan
    if(num < 0){
        return numeric_limits<double>::quiet_NaN();
    } 
    //if value is equal to 0 or 1 return itself respectively 
    if(num == 0 || num == 1){
        return num;
    } 
    
    //while loop that continues to calculate the square root until the difference
    //between guesses is less than or equal to the epsilon
    while((abs(lastGuess - nextGuess)) >= epsilon){
        lastGuess = nextGuess;
        nextGuess = (lastGuess + num/lastGuess)/2;

    }

    return nextGuess;


}

int main(int argc, char* argv[]){
    double n, epsilon;
    istringstream iss;

    if(argc < 2 || argc > 3){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }

    

    iss.str(argv[1]);
	if(!(iss >> n)){
		cerr << "Error: Value argument must be a double." << endl; 
		return 1;
	}
    
    iss.clear();
    if(argc == 3){
        iss.str(argv[2]);
        if(!(iss >> epsilon) || epsilon <= 0.0){
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        } 
    } else{
        epsilon = pow(10.0, -7.0);
    }
    
    cout << fixed << setprecision(8) << sqrt(n, epsilon) << endl;
    

    return 0;
}