#include "CharMap.hpp"
#include "exprs.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {
namespace Render      {
namespace Infixs      {

unsigned int max(unsigned int i, unsigned int j)
{
    return i <= j ? j : i;
}
unsigned int min(unsigned int i, unsigned int j)
{
    return i >= j ? j : i;
}

CenteredCharMatrix& CenteredCharMatrix::operator+=(const CenteredCharMatrix& right)
{
    unsigned int newHeight, newYCenter;
    newYCenter = max(centerY, right.centerY);
    newHeight = newYCenter + max(ySize()-centerY, right.ySize()-right.centerY);
    CenteredCharMatrix newMap(xSize() + right.xSize(), newHeight);
    newMap.setYCenter(newYCenter);
    newMap.insertMatrix(*this, 0, newYCenter-centerY);
    newMap.insertMatrix(right, xSize(), newYCenter-right.centerY);
    return (*this = newMap);
}

CenteredCharMatrix CharMap::renderParenthesis(const CenteredCharMatrix& arg)
{
    if (arg.ySize() == 1)
    {
        CenteredCharMatrix result(arg.xSize()+2, 1, ' ');
        result.insertMatrix(arg, 1, 0);
        result[0][0] = '(';
        result[0][result.xSize()-1] = ')';
        return result;
    }
    CenteredCharMatrix result(arg.xSize()+2, arg.ySize()+2, ' ');
    result.insertMatrix(arg, 1, 1);
    result[0][0] = '/';
    result[0][result.xSize()-1] = '\\';
    result[result.ySize()-1][0] = '\\';
    result[result.ySize()-1][result.xSize()-1] = '/';
    for (unsigned int i = 1; i < result.ySize()-1; i++)
    {
        result[i][0] = '|';
        result[i][result.xSize()-1] = '|';
    }
    result.setYCenter(arg.yCenter()+1);
    return result;
}
CenteredCharMatrix CharMap::renderComma(const CenteredCharMatrix& leftArg, const CenteredCharMatrix& rightArg)
{
    CenteredCharMatrix cMap(leftArg);
    cMap += CenteredCharMatrix(", ");
    cMap += rightArg;
    return cMap;
}
CenteredCharMatrix CharMap::renderAdjacent(const CenteredCharMatrix& leftArg, const CenteredCharMatrix& rightArg)
{
    CenteredCharMatrix result(leftArg);
    result += rightArg;
    return result;
}
CenteredCharMatrix CharMap::renderString(const string& arg)
{
    return CenteredCharMatrix(arg);
}
CenteredCharMatrix CharMap::renderBinaryOp(const string& op, const CenteredCharMatrix& leftArg, const CenteredCharMatrix& rightArg, bool spaces)
{
    CenteredCharMatrix opMap(op);
    CenteredCharMatrix spaceMap(" ");
    CenteredCharMatrix result(leftArg);
    if (spaces)
        result += spaceMap;
    result += opMap;
    if (spaces)
        result += spaceMap;
    result += rightArg;
    return result;
}
CenteredCharMatrix CharMap::renderUnaryOp(const string& op, const CenteredCharMatrix& arg, bool leftRight)
{
    if (leftRight)
    {
        CenteredCharMatrix result(arg);
        CenteredCharMatrix opMap(op);
        result += opMap;
        return result;
    }
    else
    {
        CenteredCharMatrix result(op);
        result += arg;
        return result;
    }
}
CenteredCharMatrix CharMap::renderSuperscript(const CenteredCharMatrix& base, const CenteredCharMatrix& super)
{
    CenteredCharMatrix result(base.xSize() + super.xSize(), base.ySize() + super.ySize());
    result.insertMatrix(base, 0, super.ySize());
    result.insertMatrix(super, base.xSize(), 0);
    result.setYCenter(super.ySize()+base.yCenter());
    return result;
}
CenteredCharMatrix CharMap::renderFraction(const CenteredCharMatrix& top, const CenteredCharMatrix& bottom)
{
    unsigned int newWidth = max(top.xSize(), bottom.xSize()) + 2;
    CenteredCharMatrix result(newWidth, top.ySize() + bottom.ySize() + 1);
    result.insertMatrix(top, newWidth/2-top.xCenter(), 0);
    result.insertMatrix(bottom, newWidth/2-bottom.xCenter(), top.ySize()+1);
    for (unsigned int i = 0; i < newWidth; i++)
        result[top.ySize()][i] = '-';
    result.setYCenter(top.ySize());
    return result;
}


} /* namespace Infixs */
} /* namespace Render */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
