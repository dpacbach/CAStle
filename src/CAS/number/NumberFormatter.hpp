/*
 * NumberFormatter.h
 *
 *  Created on: Dec 31, 2012
 *      Author: davidsicilia
 */

#ifndef NUMBERFORMATTER_H_
#define NUMBERFORMATTER_H_

#include <iostream>
#include <string>
#include <utility>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "Number.h"
#include "NumberFactory.h"

using namespace std;

namespace DS {
namespace CAS {
namespace Numbers {

class NumberFormatter : private boost::noncopyable
{
public:
    virtual ~NumberFormatter() { }

    virtual Number*              format(const string&) = 0;
    virtual pair<string, string> format(const Number& number)
    {
        pair<string,string> result;
        result.first = formatRealPart(number);
        result.second = formatImaginaryPart(number);
        return result;
    }

    virtual string formatRealPart(const Number&) = 0;
    virtual string formatImaginaryPart(const Number& number)
    {
        Number* temp = number.clone();
        temp->exchangeRealAndImaginary();
        string result = formatRealPart(*temp);
        delete temp;
        return result;
    }

    virtual pair<string, string> operator()(const Number& number)
    {
        return format(number);
    }
    virtual Number*                 operator()(const string& aString)
    {
        return format(aString);
    }

protected:
    NumberFormatter(boost::shared_ptr<NumberFactory> _factory) : factory(_factory) {}
    boost::shared_ptr<NumberFactory> factory;
};

} } }

#endif /* NUMBERFORMATTER_H_ */
