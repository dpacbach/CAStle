#include <cstdlib>
#include <iostream>
#include <chrono>

#include "BaseArray.h"
#include "Integer.h"
#include "Float.h"

auto task(unsigned long count) -> void
{
    for (auto i = 0; i < count; ++i) {
        // Some task
        auto j = 1 + 1;
    }
}

auto main(int argc, char* argv[]) -> int
{
    auto count = (unsigned long)(100000);
    if (argc > 1)
        count = atol(argv[1]);

    auto start = std::chrono::steady_clock::now();
    task(count);
    auto end  = std::chrono::steady_clock::now();
    auto diff = end-start;
    std::cout << std::chrono::duration<double, milli>(diff).count() << "ms";
    std::cout << " (" << count << ")" << std::endl;
    return 0;
}
