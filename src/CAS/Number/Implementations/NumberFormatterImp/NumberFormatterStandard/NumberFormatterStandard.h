/*
 * NumberFormatterStandard.h
 *
 *  Created on: Dec 31, 2012
 *      Author: davidsicilia
 */

#ifndef NUMBERFORMATTERSTANDARD_H_
#define NUMBERFORMATTERSTANDARD_H_

#include <iostream>
#include <vector>
#include "../../../../../Utilities/TokenProcessor/TokenProcessors.h"
#include "../../../NumberFormatter.h"

using namespace std;

namespace DS {
namespace CAS {
namespace Numbers {

class NumberFormatterStandard: public NumberFormatter
{
public:
    NumberFormatterStandard(boost::shared_ptr<NumberFactory> _factory,
                            boost::shared_ptr<DS::Tokens::ScannerBuilder> _sBuilder, unsigned int _sigFigs = 15)
                            : NumberFormatter(_factory), sBuilder(_sBuilder), maximumSigFigs(_sigFigs) {}
    virtual ~NumberFormatterStandard() { }

    virtual string  formatRealPart(const Number&);
    virtual Number* format(const string&);

    unsigned int getSigFigs(void) const;
    void setSigFigs(unsigned int _sigFigs) { maximumSigFigs = _sigFigs; }

protected:
    boost::shared_ptr<DS::Tokens::ScannerBuilder> sBuilder;
    unsigned int maximumSigFigs;

    void buildScanners(void);
    Numbers::Proxy::NumberP formatRealInteger(const string&);
    Numbers::Proxy::NumberP formatRealFloat(const string&);
    Numbers::Proxy::NumberP formatRealScientific(const string&);

    string formatRealDecimal(const Number& _number, unsigned int maxSigDigits);
    string formatRealScientific(const Number& _number, unsigned int maxSigDigits);

    vector<DS::Tokens::Scanner::Ptr> scanners;
    vector<bool> optionalFlags;

    vector<DS::Tokens::Scanner::Ptr> realScientificScanners;
    vector<bool> realScientificOptionalFlags;
    vector<DS::Tokens::Scanner::Ptr> realFloatScanners;
    vector<bool> realFloatOptionalFlags;
};

} } }

#endif /* NUMBERFORMATTERSTANDARD_H_ */
