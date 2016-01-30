#pragma once

#include "Scanner.hpp"

namespace DS {
namespace Tokens {
namespace Scanners {

class Repeat: public DS::Tokens::Scanner
{
public:
    Repeat(Scanner::Ptr _repeated) : repeated(_repeated) {}
    virtual ~Repeat() {}

    virtual Scanner::bounds scan(Scanner::bounds);

protected:
    Scanner::Ptr repeated;
};

} /* namespace Scanners */
} /* namespace Tokens */
} /* namespace DS */
