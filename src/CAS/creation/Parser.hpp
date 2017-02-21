#pragma once

#include <string>
#include <vector>
#include "Tokenizer.hpp"
#include "Builder.hpp"
#include "NumberFormatter.hpp"

namespace DS { namespace Tokens {
    class ScannerBuilder;
} }

namespace DS          {
namespace CAS         {
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
        std::string getNodeName(void) const { return nodeName; }
        unsigned int getNumberOfChildren(void) const { return numberOfChildren; }
    private:
        type nodeType;
        std::string nodeName;
        unsigned int numberOfChildren;
    };
public:
    Parser(std::shared_ptr<Tokens::ScannerBuilder>, std::shared_ptr<Expressions::Builder>,
           std::shared_ptr<Numbers::NumberFormatter>, std::shared_ptr<Tokens::Tokenizer>);
    virtual ~Parser() {}

    ExprConstSP parse(const std::string&);
    ExprConstSP operator() (const std::string& aString) { return parse(aString); }

    std::string::const_iterator getStopLocation(void) const { return stopLocation; }

protected:
    virtual void buildScanners(std::vector<Tokens::Scanner::Ptr>&, std::shared_ptr<Tokens::ScannerBuilder>) = 0;
    virtual bool parseTokens(const std::vector<Token>&, std::vector<Command>&) = 0;
    virtual ExprConstSP buildExpression(const std::vector<Command>&);

    std::shared_ptr<Expressions::Builder>     eBuilder;
    std::shared_ptr<Numbers::NumberFormatter> nFormatter;
    std::shared_ptr<Tokens::ScannerBuilder>   sBuilder;
    std::shared_ptr<Tokens::Tokenizer>        tokenizer;

    std::string::const_iterator stopLocation;

private:
    std::vector<Tokens::Scanner::Ptr> scanners;
};

} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
