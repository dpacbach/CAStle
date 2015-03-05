#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#include "shared_array.hpp"

using std::cout;
using std::endl;
using std::string;

template<typename T>
auto str(const T& data) {
    std::stringstream s;
    s << data;
    return s.str();
}

struct test {
    short x;
    short y;
    short z;
    short w;
};

int main(int argc, char* argv[])
{
    printf("sizeof(shared_array):  %lu\n", sizeof(DS::shared_array<int>));
    printf("sizeof(test):          %lu\n", sizeof(struct test));

    DS::shared_array<int>          sa1(1); 
    DS::shared_array<unsigned int> sa2(1); 
    DS::shared_array<int*>         sa3(1); 
    DS::shared_array<double>       sa8(1); 

    return 0;
}
