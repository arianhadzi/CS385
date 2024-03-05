/*******************************************************************************
 * Filename: state.cpp
 * Author  : Arian Hadzibrahimi
 * Version : 1.0
 * Date    : October 16, 2023
 * Description: Program that solves the water jug puzzle using breadth-first search
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

string nameOfJug(int i){
    if(i == 1 || i == 4){ return "A";}
    if(i == 2 || i == 5){ return "B";}
    if(i == 3 || i == 6){ return "C";}
}

int main(int argc, char * const argv[]) { 

    int capacities[3];
    int goals[3];

// Error checking arguments
    if(argc != 7){
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    for(int i = 1; i <= 6; i++){
        int currentJug;
        istringstream iss(argv[i]);
        if(!(iss >> currentJug) || (currentJug < 0) || (currentJug == 3 )){
            cerr << "Error: Invalid " << ((i <= 3) ? "capacity" : "goal") << " '" << argv[i] << "' for jug " << nameOfJug(i) << "." << endl;
            return 1;
        }
        if(i <= 3){
            capacities[i-1] = currentJug;
        }else{
            goals[i-4] = currentJug;
        }
    }

    for(int i = 0; i < 3; i++){
        if(goals[i] > capacities[i]){
            cerr << "Error: Goal cannot exceed capacity of jug " << nameOfJug(i+1) << "." << endl;
        }
    }


    State s(0, 0, 8, "Initial state.");
    cout << s.to_string() << endl;
    s.a += 3;
    s.c -= 3;
    cout << s.to_string() << endl;
    return 0;
}
