/*******************************************************************************
 * Filename: waterjugpuzzle.cpp
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
#include <algorithm>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    
    // String representation of state in tuple form.
    string to_string() const{
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

vector<State> performPour(State& current, int capA, int capB, int capC){
    vector<State> newStates;
    string directions;
    
    // Pour from C to A
    int pourCA = min(current.c, capA - current.a); // Amnt. of water that can be poured from src to dst
    if (pourCA > 0) {
        directions = "Pour " + to_string(pourCA) + " gallons from C to A.";
        newStates.push_back(State(current.a + pourCA, current.b, current.c - pourCA, directions));
    }

    // Pour from B to A
    int pourBA = min(current.b, capA - current.a);
    if (pourBA > 0) {
        directions = "Pour " + to_string(pourBA) + " gallons from B to A.";
        newStates.push_back(State(current.a + pourBA, current.b - pourBA, current.c, directions));
    }

    // Pour from C to B
    int pourCB = min(current.c, capB - current.b);
    if (pourCB > 0) {
        directions = "Pour " + to_string(pourCB) + " gallons from C to B.";
        newStates.push_back(State(current.a, current.b + pourCB, current.c - pourCB, directions));
    }

    // Pour from A to B
    int pourAB = min(current.a, capB - current.b);
    if (pourAB > 0) {
        directions = "Pour " + to_string(pourAB) + " gallons from A to B.";
        newStates.push_back(State(current.a - pourAB, current.b + pourAB, current.c, directions));
    }

    // Pour from B to C
    int pourBC = min(current.b, capC - current.c);
    if (pourBC > 0) {
        directions = "Pour " + to_string(pourBC) + " gallons from B to C.";
        newStates.push_back(State(current.a, current.b - pourBC, current.c + pourBC, directions));
    }

    // Pour from A to C
    int pourAC = min(current.a, capC - current.c);
    if (pourAC > 0) {
        directions = "Pour " + to_string(pourAC) + " gallons from A to C.";
        newStates.push_back(State(current.a - pourAC, current.b, current.c + pourAC, directions));
    }

    return newStates;
}

string backTrackedSolution(const State& goal){
    vector<string> steps;
    const State* currentState = &goal;

    // Backtrack from the goal state to the initial state
    while ((*currentState).parent != nullptr) {
        steps.push_back((*currentState).directions);
        currentState = (*currentState).parent;
    }

    // Add the initial state
    steps.push_back((*currentState).directions);

    // Reverse the steps since we collected them backwards
    reverse(steps.begin(), steps.end());

    // Join the steps into a single string
    ostringstream oss;
    for (const string& step : steps) {
        oss << step << " " << (*currentState).to_string() << endl;
        // Update currentState to point to its parent for the next iteration
        if ((*currentState).parent != nullptr) {
            currentState = (*currentState).parent;
        }
    }

    return oss.str();
} 


string bfs(int capA, int capB, int capC, int goalA, int goalB, int goalC){

    queue<State> pours;
    bool** visited = new bool*[capA + 1];
    for(int i = 0; i <= capA; i++){
        visited[i] = new bool[capB + 1];
        fill(visited[i], visited[i] + capB + 1, false);
    }

    State initialState(0,0, capC, "Initial state.");
    pours.push(initialState);

    vector<State*> allocated;  // Keep track of allocated State objects

    while(!pours.empty()){ // While pours queue is not empty
        State current = pours.front(); 
        pours.pop();

        if(current.a == goalA && current.b == goalB && current.c == goalC){
            for(int i = 0; i <= capA; i++){
                delete [] visited[i];
            }
            delete [] visited;

            for(State* state : allocated){
                delete state;
            }
            return backTrackedSolution(current);
        }

        if(visited[current.a][current.b]){
            continue;
        }
        visited[current.a][current.b] = true;

        vector<State> newStates = performPour(current, capA, capB, capC);

        for(State& newState : newStates){
            if(!visited[newState.a][newState.b]){
                State* newStatePtr = new State(current);
                newState.parent = newStatePtr;
                allocated.push_back(newStatePtr);  // Keep track of this allocation
                pours.push(newState);
            }
        }
    }

    for(int i = 0; i <= capA; i++){
        delete [] visited[i];
    }
    delete [] visited;

    for (State* state : allocated){
        delete state;
    }


    return "No solution.";
}



string nameOfJug(int i){
    if(i == 1 || i == 4){ return "A";}
    if(i == 2 || i == 5){ return "B";}
    if(i == 3 || i == 6){ return "C";}
    return "";
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
        if(!(iss >> currentJug) || (currentJug < 0)){
            cerr << "Error: Invalid " << ((i <= 3) ? "capacity" : "goal") << " '" << argv[i] << "' for jug " << nameOfJug(i) << "." << endl;
            return 1;
        }

        if(i <= 3 && currentJug == 0){
            cerr << "Error: Invalid capacity '0' for jug " << nameOfJug(i) << "." << endl;
            return 1;
        } else{
            if(i <= 3){
                capacities[i-1] = currentJug;
            } else{
                goals[i-4] = currentJug;
            }
        }
    }

    for(int i = 0; i < 3; i++){
        if(goals[i] > capacities[i]){
            cerr << "Error: Goal cannot exceed capacity of jug " << nameOfJug(i+1) << "." << endl;
            return 1;
        }
    }

    if(goals[0] + goals[1] + goals[2] != capacities[2]){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }


    string result = bfs(capacities[0], capacities[1], capacities[2], goals[0], goals[1], goals[2]);
    cout << result << endl;
    return 0;
}
