#include "solutions/solution_07_22+.hpp"
#include "utils.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    auto&& input = InputParser<int>().getVecInVec("./1743_exp.ipt");
    cout << Solution_1743().restoreArray(input);

    return 0;
}