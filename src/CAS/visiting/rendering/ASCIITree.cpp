#include "ASCIITree.hpp"
#include "AllBasic.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {
namespace Render      {

void prependSpaces(vector<string>& vec) { }

bool ASCIITree::handleNode(const string& name, const Expression& exp)
{
    string padding;
    for (unsigned int k = 0; k < name.length()/2; k++)
        padding += " ";
    unsigned int numberOfChildren = exp.numberOfChildren();
    vector<string> result;
    for (unsigned int i = 0; i < numberOfChildren; i++)
    {
        vector<string> child = getPop(childResults);

        for (unsigned int j = 0; j < child.size(); j++)
        {
            if (i == 0 && j == 0)
                child[0] = "\\---" + child[0];
            else if (j == 0)
                child[0] = "|---" + child[0];
            else if (i != 0)
                child[j] = "|   " + child[j];
            else
                child[j] = "    " + child[j];
            child[j] = padding + child[j];
        }
        result.insert(result.begin(), child.begin(), child.end());
        result.insert(result.begin(), padding + "|   ");
    }

    result.insert(result.begin(), name);

    childResults.push(result);

    return true;
}

Expressions::Visitor* ASCIITree::create(void) const
{
    return new ASCIITree(formatter);
}
Expressions::Visitor* ASCIITree::clone(void)  const
{
    ASCIITree *result = new ASCIITree(formatter);
    result->childResults = childResults;
    return result;
}
void ASCIITree::reset(void)
{
    while (!childResults.empty())
        childResults.pop();
}

bool ASCIITree::visitAdd(const Add& exp)
{
    string signs = "(";
    bool foundNegative = false;
    for (unsigned int i = 0; i < exp.numberOfChildren(); i++)
    {
        Sign sign = exp.getSignForChild(i);
        if (sign == n)
        {
            foundNegative = true;
            signs += "-";
        }
        else
            signs += "+";
    }
    signs += ")";
    string resultName = "Add";
    if (foundNegative)
        resultName += signs;
    return handleNode(resultName, exp);
}
bool ASCIITree::visitDivide(const Divide& exp)
{
    return handleNode("Divide", exp);
}
bool ASCIITree::visitFactorial(const Factorial& exp)
{
    return handleNode("Factorial", exp);
}
bool ASCIITree::visitLiteral(const Literal& exp)
{
    pair<string,string> result = formatter->format(exp.getNumber());
    string numberString = result.first + "+" + result.second + "i";
    return handleNode(" " + numberString, exp);
}
bool ASCIITree::visitModulus(const Modulus& exp)
{
    return handleNode("Modulus", exp);
}
bool ASCIITree::visitMultiply(const Multiply& exp)
{
    return handleNode("Multiply", exp);
}
bool ASCIITree::visitNegate(const Negate& exp)
{
    return handleNode("Negate", exp);
}
bool ASCIITree::visitPower(const Power& exp)
{
    return handleNode("Power", exp);
}
bool ASCIITree::visitSymbol(const Symbol& exp)
{
    return handleNode(exp.getName(), exp);
}

} /* namespace Render */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
