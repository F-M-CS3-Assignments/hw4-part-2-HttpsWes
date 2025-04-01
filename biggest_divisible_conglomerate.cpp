#include "bdc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Converts a vector of integers into a formatted string for clean output
string vec_to_string(vector<int> v) {
    if (v.empty()) return "[]";
    string str = "[";
    for (size_t i = 0; i < v.size(); i++) {
        str += to_string(v[i]);
        if (i < v.size() - 1) str += ", ";
    }
    str += "]";
    return str;
}

// Returns the largest divisible subset from the input vector
// For any two elements a and b in the subset, a % b == 0 or b % a == 0
vector<int> biggest_divisible_conglomerate(vector<int> input) {
    if (input.size() <= 1) return input;

    //Sorted the list in ascending order 
    sort(input.begin(), input.end());

    //Filtered out any zero values, since 0 isn't divisible and breaks modulus logic
    auto zeroIt = find(input.begin(), input.end(), 0);
    if (zeroIt != input.end()) {
        input.erase(remove(input.begin(), input.end(), 0), input.end());
    }

    //Created a list of chains, one for each index
    vector<vector<int>> chains(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        chains[i] = {input[i]};  // Start each chain with the single element
    }

    //Built up each chain by checking divisibility backwards using a nested for loop
    for (size_t i = 0; i < input.size(); i++) {
        for (size_t j = i + 1; j < input.size(); j++) {
            if (input[j] % input[i] == 0 && chains[i].size() >= chains[j].size()) {
                chains[j] = {input[j]};
                for (int k : chains[i]) {
                    chains[j].push_back(k);
                }
            }
        }
    }

    //Found the longest chain (the biggest valid conglomerate)
    size_t maxIndex = 0;
    for (size_t i = 1; i < chains.size(); i++) {
        if (chains[i].size() > chains[maxIndex].size()) {
            maxIndex = i;
        }
    }

    //Final result in ascending order for readability
    vector<int> result = chains[maxIndex];
    sort(result.begin(), result.end());
    return result;
}

// Time Complexity: O(n^2)
// - The algorithm uses two nested loops over the input vector of size n
// - In the worst case, for each element, it may scan all previous elements

// Time Complexity of recursive version: O(2^n)
// - The recursive implementation explores all possible subsets,
//   making it infeasible for large inputs


// Summary:
// - The DP (dynamic programming) version is way faster for big inputs.
// - Instead of trying everything like the recursive version, it builds up answers smartly using memory.