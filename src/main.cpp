#include "solutions/solution_07_15.hpp"
#include "utils.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
//    auto input = InputParser<int>().getVecInVec("./1818_50.ipt");

    vector<int> input = {1,2,3,4,5};

    cout << Solution_658().findClosestElements(input, 4, 3);

    return 0;
}