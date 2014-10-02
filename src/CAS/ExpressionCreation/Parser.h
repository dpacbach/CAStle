/*
 * Parser.h
 *
 *  Created on: Feb 11, 2013
 *      Author: davidsicilia
 */

#ifndef EXPPARSER_H_
#define EXPPARSER_H_

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "../../Utilities/TokenProcessor/TokenProcessors.h"
#include "../Expression/Builder.h"
#include "../Number/Numbers.h"

using namespace std;

namespace DS {
namespace CAS {
namespace Expressions {

class Parser
{
protected:
    struct Command
    {
    public:
        typedef enum { literal, symbol } type;
        Command(type _nodeType, string _nodeName, unsigned int _numberOfChildren)
            : nodeType(_nodeType), nodeName(_nodeName), numberOfChildren(_numberOfChildren) {}
        type getNodeType(void) const { return nodeType; }
        string getNodeName(void) const { return nodeName; }
        unsigned int getNumberOfChildren(void) const { return numberOfChildren; }
    private:
        type nodeType;
        string nodeName;
        unsigned int numberOfChildren;
    };
public:
    Parser(boost::shared_ptr<Tokens::ScannerBuilder>, boost::shared_ptr<Expressions::Builder>,
           boost::shared_ptr<Numbers::NumberFormatter>, boost::shared_ptr<Tokens::Tokenizer>);
    virtual ~Parser() {}

    Expression::Ptr parse(const string&);
    Expression::Ptr operator() (const string& aString) { return parse(aString); }

    string::const_iterator getStopLocation(void) const { return stopLocation; }

protected:
    virtual void buildScanners(vector<Tokens::Scanner::Ptr>&, boost::shared_ptr<Tokens::ScannerBuilder>) = 0;
    virtual bool parseTokens(const vector<Token>&, vector<Command>&) = 0;
    virtual Expression::Ptr buildExpression(const vector<Command>&);

    boost::shared_ptr<Expressions::Builder>     eBuilder;
    boost::shared_ptr<Numbers::NumberFormatter> nFormatter;
    boost::shared_ptr<Tokens::ScannerBuilder>     sBuilder;
    boost::shared_ptr<Tokens::Tokenizer>         tokenizer;
    string::const_iterator stopLocation;

private:
    vector<Tokens::Scanner::Ptr> scanners;
};

} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
#endif /* PARSER_H_ */
