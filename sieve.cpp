/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Arian Hadzibrahimi
 * Date        : 9/14/23
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

    // Finds the width of the max prime value and how many primes
    // can fit on a row
    const int max_prime_width = num_digits(max_prime_),
              primes_per_row = 80 / (max_prime_width + 1);

    // primeCount will keep track of how many primes are shown and will be used
    // to know when to start a new line

    int primeCount = 0;
    for(int i = 2; i <= limit_; i++){
        if(is_prime_[i]){
            cout << setw(max_prime_width) << i << " ";
            primeCount++
        }
        if(primeCount == primes_per_row){
            cout << endl;
            primeCount = 0;
        }
    }
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.

    // From indices 2 to limit
    for(int i = 2; i <= limit_; i++){
        // Initializes each index as T
        is_prime_[i] == true;
    }
    for(int i = 2; i <= sqrt(limit_); i++){
        if(is_prime_[i]){
            for(int j = i*i; j <= limit_; j += i)
                is_prime_[j] = false;
        }
    }

}

// Computes the number of digits in a given integer, will be used for setw()
int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int digits = 0;
    while(num > 0){
        digits++;
        num = num/10;
    }
    return digits;
    return 0;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    // TODO: write code that uses your class to produce the desired output.

    PrimesSieve sieve(limit);
    sieve.display_primes();
    
    return 0;
}
