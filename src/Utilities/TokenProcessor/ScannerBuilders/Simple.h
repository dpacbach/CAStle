/*
 * Simple.h
 *
 *  Created on: Feb 10, 2013
 *      Author: davidsicilia
 */

#ifndef SCANNERBUILDERSIMPLE_H_
#define SCANNERBUILDERSIMPLE_H_

#include "../ScannerBuilder.h"

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
#endif /* SIMPLE_H_ */
