/*
 Given an array of integers, find and print the maximum number of integers you can select from the array such that the absolute difference between any two of the chosen integers is .
 
 Solution uses O(1) Space, O(N) Time
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

using vec = std::vector<int>;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int numVals;
    int solution = 0;
    cin >> numVals;
    vec frequency(100, 0);
    auto i = 0;
    int maxVal = 0;
    while (i < numVals){
        int pushVal;
        cin >> pushVal;
        maxVal = (pushVal > maxVal) ? pushVal : maxVal;
        frequency[pushVal]++;
        ++i;
    }
    for (i = 2; i <= maxVal; ++i){
        solution = max(solution, frequency[i] + frequency[i-1]);
    }
    return solution;
}

