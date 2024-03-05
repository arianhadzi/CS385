#include <iostream>

using namespace std;

int mystery3(int x, int y){
   int s, c;
   s = x ^ y; 
   c = x & y;

   while (c != 0){
    c = c << 1;
    x = s;
    y = c; 
    s = x ^ y;
    c = x & y;
   }
   return s;
}

int main(void){
    cout << mystery3(5, 7) << endl;
    cout << mystery3(2, 8) << endl;

}