#pragma once

#include "Scanner.hpp"

namespace DS {
namespace Tokens {
namespace Scanners {

class Not: public DS::Tokens::Scanner
{
public:
    Not(Scanner::Ptr _repeated) : repeated(_repeated) {}
    virtual ~Not() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    Scanner::Ptr repeated;
};

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
