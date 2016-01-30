#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include "Number.hpp"
#include "NumberFactory.hpp"

using namespace std;

namespace DS {
namespace CAS {
namespace Numbers {

class NumberFormatter
{
public:
    NumberFormatter(const NumberFormatter&)           = delete;
    NumberFormatter& operator=(const NumberFormatter&) = delete;

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
    NumberFormatter(shared_ptr<NumberFactory> _factory) : factory(_factory) {}
    shared_ptr<NumberFactory> factory;
};

} } }
