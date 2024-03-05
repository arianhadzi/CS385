/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Arian Hadzibrahimi
 * Date        : 10/7/23
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> combinations;

    if(num_stairs == 0){
        return {{}};
    } else if(num_stairs == 1){
        return {{1}};
    } else if(num_stairs == 2){
        return {{1, 1}, {2}};
    } else{
        for(int i = 1; i <= 3; i++){
            if(num_stairs >= i){
                vector<vector<int>> temp_vector = get_ways(num_stairs - i);
                for(vector<int> vector : temp_vector){
                    vector.push_back(i);
                    combinations.push_back(temp_vector);
                }
            }
        }
        return combinations;
    }
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int num_ways = ways.size();
    cout << num_ways << " ways to climb " << cout << ways[0] << " stairs." << endl;

    int width = to_string(num_ways).length();

    for(int i = 0; i < num_ways; i++){
        cout << setw(width) << i + 1 << ". [";
        for(size_t j = 0; j < ways[i].size(); j++){
            cout << ways[i][j];
            if(j < ways[i].size() - 1){
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

}

int main(int argc, char * const argv[]) {
    int stairs;
    istringstream iss;

    if(argc != 2){
        cout << "Usage: " << argv[0] << "<number of stairs>" << endl;
        return 1;
   }
   
   iss.str(argv[1]);
   
   if( !(iss >> stairs) ){
    cout << "Error: Number of stairs must be a positive integer." << endl;
    return 1;
   } else if(stairs <= 0){
    cout << "Error: Number of stairs must be a positive integer." << endl;
    return 1;
   } else{
    vector<vector<int>> combinations = get_ways(stairs);
   }

    return 0;
}

