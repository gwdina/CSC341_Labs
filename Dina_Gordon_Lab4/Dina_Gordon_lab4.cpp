#include <stdlib.h>
#include <stdio.h>
#include <iostream>



using namespace std;


int __mulsi3(int a, int b){
    int sum = 0; //the sum

    //if b is negative then will break, this if statement switches the signs 
    if (b < 0) {
    b = -b; 
    a = -a; //the function is fine with a negative a and not b
    }
    

    while(b != 0) {

        if(b & 1)
        {
            sum += a;//a added to sum
        }
    

        //add shift algorithms 
        a = a << 1; // a will keep increasing n times depending on b
        b = b >> 1; // b will go to 0
    }

    return sum; //return sum
}

int __divsi3(int a, int b){
    bool negative = false;
    
    if (a < 0){ // if a is negative then make it not negative
        a = -a;
        negative = true; //condition to if need quotient needs to turn negative
    }
    if (b < 0){// if b is negative then make it not negative
        b = -b;
        if (negative){  // if both are negative then switch negative back to false
            negative = false;
        }
        negative = true; //condition to if need quotient needs to turn negative
    }
    int quotient = a; 
    int remainder = 0; // upper half 
    quotient <<= 1;

    for (int i = 0; i < 32; i++) {
        remainder = remainder - b; // Perfrom trial subtraction

        if (remainder >= 0){
            { 
        
            remainder <<= 1; // shift upper half to the left
            if (quotient < 0) {
        
            remainder |= 1; // so set lower bit of remainder
            }
            quotient <<= 1; // shift lower half 
            quotient = quotient | 1; // set low order bit of quotient to 1
        }
        }
        if (remainder < 0) {
        
            remainder = remainder + b; // restore the orginal vaule
            remainder <<= 1; // shift upper half to the left

            if (quotient < 0) {
        
                remainder |= 1; // set lower bit of remainder
            }
            quotient <<= 1; // shift lower half 
            quotient = quotient & 0xFFFFFFFE; // set low order bit of quotient to 0
        }
        
    }
    if (negative){
        return -quotient;
    }
    return quotient; 
}

int main(){

    cout << __mulsi3(13, 25) << endl;

    //cout << __divsi3(-10, -2);
    
    
    return 0;
}
