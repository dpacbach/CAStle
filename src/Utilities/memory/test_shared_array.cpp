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

void do_basic_test()
{
    cout << "===> Test constructor:" << endl;
    DS::shared_array<int>          sa1(1); 
    DS::shared_array<int>          sa2(1); 

    cout << "===> Test move assignment:" << endl;
    DS::shared_array<int>          sa3(1);
    sa3 = std::move(sa1); 
    DS::shared_array<int>          sa4(1);
    sa4 = std::move(sa3); 
    DS::shared_array<int>          sa5(1);
    sa5 = std::move(sa2); 

    sa2 = std::move(sa1 = std::move(sa2 = std::move(sa5)));

    cout << "===> Test copy constructor:" << endl;
    DS::shared_array<int>          sa6(sa1);
    DS::shared_array<int>          sa7(sa2);
    DS::shared_array<int>          sa8(sa4);

    sa6 = sa7 = sa8;

    cout << "===> Test copy assignment:" << endl;
    DS::shared_array<int>          sa9(1);
    sa9 = std::move(sa6); 
    DS::shared_array<int>          sa10(1);
    sa10 = std::move(sa9); 
    DS::shared_array<int>          sa11(1);
    sa11 = std::move(sa8); 

    sa2 = std::move(sa1 = std::move(sa2 = std::move(sa5)));

    cout << "===> Test destructor:" << endl;
}

DS::shared_array<int> make_shared_array(size_t size)
{
    auto sa1 = DS::shared_array<int>(size);
    sa1[1] = 2;
    return sa1;
}

int main(int argc, char* argv[])
{
    printf("sizeof(shared_array):  %lu\n", sizeof(DS::shared_array<int>));

    auto sa = make_shared_array(20);
    do_basic_test();

    return 0;
}
