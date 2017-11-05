#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "NumberFormatter.hpp"
#include "scanner.hpp"
#include "scanner-builder.hpp"

using namespace std;

namespace castle {
    class scanner_builder;
}

namespace DS      {
namespace CAS     {
namespace Numbers {

class NumberFormatterStandard : public NumberFormatter
{
public:
    NumberFormatterStandard(shared_ptr<NumberFactory> _factory,
                            shared_ptr<castle::scanner_builder> _sBuilder, unsigned int _sigFigs = 15)
                            : NumberFormatter(_factory), sBuilder(_sBuilder), maximumSigFigs(_sigFigs) {}
    virtual ~NumberFormatterStandard() { }

    virtual string  formatRealPart(const Number&);
    virtual Number* format(const string&);

    unsigned int getSigFigs(void) const;
    void setSigFigs(unsigned int _sigFigs) { maximumSigFigs = _sigFigs; }

protected:
    shared_ptr<castle::scanner_builder> sBuilder;
    unsigned int maximumSigFigs;

    void buildScanners(void);
    Numbers::Proxy::NumberP formatRealInteger(const string&);
    Numbers::Proxy::NumberP formatRealFloat(const string&);
    Numbers::Proxy::NumberP formatRealScientific(const string&);

    string formatRealDecimal(const Number& _number, unsigned int maxSigDigits);
    string formatRealScientific(const Number& _number, unsigned int maxSigDigits);

    vector<castle::scanner::ptr> scanners;
    vector<bool> optionalFlags;

    vector<castle::scanner::ptr> realScientificScanners;
    vector<bool> realScientificOptionalFlags;
    vector<castle::scanner::ptr> realFloatScanners;
    vector<bool> realFloatOptionalFlags;
};

} } }
