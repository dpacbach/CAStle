#pragma once

#include <vector>
#include "Scanner.hpp"

namespace DS {
namespace Tokens {
namespace Scanners {

class OrList: public DS::Tokens::Scanner
{
public:
    OrList(const vector<Scanner::Ptr>&);
    virtual ~OrList() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    vector<Scanner::Ptr> theList;
};

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
