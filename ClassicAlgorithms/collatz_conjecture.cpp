/*
 * =========================================================
 *       Filename:  collatz_conjecture.cpp
 *    Description:  Start with a number n > 1. Find the number of 
 *    steps it takes to reach one using the following process: 
 *    If n is even, divide it by 2. If n is odd, multiply it by 3 and add 1
 *
 * =========================================================
 */
#include <iostream>
using namespace std;
unsigned int step = 0;
void conjecture(unsigned int n);
int main(){
    unsigned int a = 3;
    conjecture(a);
    cout<< "step of "<< a <<" is "<< step <<endl;
    return 0;
}


void conjecture(unsigned int n){
    if(n == 1)
        return;
    else{
        ++step;
        if(n % 2 == 0)
            conjecture(n/2);
        else
            conjecture(3*n + 1);
    }
}
