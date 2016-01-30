#pragma once

#include "ScannerBuilder.hpp"

namespace DS {
namespace Tokens {
namespace ScannerBuilders {

class Simple: public DS::Tokens::ScannerBuilder
{
public:
    Simple();
    virtual ~Simple();

    virtual void charString(const string&);
    virtual void notted(void);
    virtual void repeat(void);
    virtual void orList(unsigned int);
    virtual void optionalList(unsigned int);
};

} /* namespace ScannerBuilders */
} /* namespace Tokens */
} /* namespace DS */
