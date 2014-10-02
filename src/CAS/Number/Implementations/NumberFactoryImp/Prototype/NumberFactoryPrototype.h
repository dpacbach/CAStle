/*
 * NumberFactoryPrototype.h
 *
 *  Created on: Dec 30, 2012
 *      Author: davidsicilia
 */

#ifndef NUMBERFACTORYPROTOTYPE_H_
#define NUMBERFACTORYPROTOTYPE_H_

#include "../../../NumberFactory.h"

namespace DS {
namespace CAS {
namespace Numbers {

class NumberFactoryPrototype: public NumberFactory
{
public:
    NumberFactoryPrototype(const Number*);
    NumberFactoryPrototype(const Number&);
    NumberFactoryPrototype(const NumberFactoryPrototype&);
    virtual ~NumberFactoryPrototype();

    //NumberFactoryPrototype& operator=(const NumberFactoryPrototype&);

    virtual Number* number(double realPart, double imaginaryPart) const;
    virtual Number* PI(void) const;

protected:
    const Number* prototype;
};

} } }
#endif /* NUMBERFACTORYPROTOTYPE_H_ */
