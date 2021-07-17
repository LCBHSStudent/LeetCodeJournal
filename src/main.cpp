#include "solutions/solution_07_17.hpp"
#include "utils.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    for (int i = 0; i < 10000000; i++) {
        Foo foo;
        Foo::TestFoo(foo);
        cout << endl;
    }

    return 0;
}