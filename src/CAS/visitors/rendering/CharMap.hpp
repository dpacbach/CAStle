#pragma once

#include <stdexcept>
#include <memory>
#include "matrix/Matrix.hpp"
#include "InfixRender.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {
namespace Visitors    {
namespace Render      {
namespace Infixs      {

class CenteredCharMatrix
{
public:
    CenteredCharMatrix() : matrix(1, 1, ' '), centerX(0), centerY(0) {}
    CenteredCharMatrix(unsigned int xSize, unsigned int ySize, char fill = ' ') : matrix(ySize,xSize, fill),
                                                                                  centerX(xSize/2), centerY(ySize/2) {}
    CenteredCharMatrix(const string& str) : matrix(1, str.length(), ' '), centerX(str.length()/2), centerY(0)
    {
        for (unsigned int i = 0; i < str.length(); i++)
            matrix[0][i] = str[i];
    }
    ~CenteredCharMatrix() {}

    CenteredCharMatrix& operator+=(const CenteredCharMatrix& right);

    char at(unsigned int x, unsigned int y) const { return matrix[y][x]; }
    vector<string> vectorOfStrings(void) const
    {
        string filler(xSize(), ' ');
        vector<string> result(matrix.height(), filler);
        for (unsigned int i = 0; i < ySize(); i++)
            for (unsigned int j = 0; j < xSize(); j++)
                result[i][j] = matrix[i][j];
        return result;
    }
    void set(char c, unsigned int x, unsigned int y)
    {
        if (x >= xSize() || y >= ySize())
            throw invalid_argument("coords out of bounds in CenteredCharMatrix::set()");
        matrix[y][x] = c;
    }

    void insertMatrix(const CenteredCharMatrix& _matrix, unsigned int x, unsigned int y)
    {
        for (unsigned int _y = 0; _y < _matrix.ySize(); _y++)
            for (unsigned int _x = 0; _x < _matrix.xSize(); _x++)
                set(_matrix[_y][_x], _x + x, _y + y);
    }

    vector<char>& operator[] (unsigned int i) { return matrix[i]; }
    const vector<char>& operator[] (unsigned int i) const { return matrix[i]; }

    unsigned int xCenter(void) const { return centerX; }
    unsigned int yCenter(void) const { return centerY; }
    void setXCenter(unsigned int center) { centerX = center; }
    void setYCenter(unsigned int center) { centerY = center; }
    unsigned int xSize(void) const { return matrix.width(); }
    unsigned int ySize(void) const { return matrix.height(); }

    ostream& output(ostream& out) const
    {
        vector<string> resultMap = vectorOfStrings();
        for (vector<string>::iterator it = resultMap.begin(); it != resultMap.end(); ++it)
        {
            out << *it;
            if (it+1 != resultMap.end())
                out << endl;
        }
        return out;
    }

protected:
    Matrix<char> matrix;
    unsigned int centerX, centerY;
};

class CharMap: public DS::CAS::Expressions::Visitors::Render::Infix<CenteredCharMatrix>
{
public:
    CharMap(std::shared_ptr<Numbers::NumberFormatter> formatter) : Infix<CenteredCharMatrix>(formatter) {}
    virtual ~CharMap() {}

protected:
    bool noParenthesisInDivision(void) const { return true; }
    bool noParenthesisInExponent(void) const { return true; }
    bool parenthesisInNegateDivision(void) const { return true; }

    virtual CenteredCharMatrix renderParenthesis(const CenteredCharMatrix& arg);
    virtual CenteredCharMatrix renderComma(const CenteredCharMatrix& leftArg, const CenteredCharMatrix& rightArg);
    virtual CenteredCharMatrix renderAdjacent(const CenteredCharMatrix& leftArg, const CenteredCharMatrix& rightArg);
    virtual CenteredCharMatrix renderString(const string& arg);
    virtual CenteredCharMatrix renderBinaryOp(const string& op, const CenteredCharMatrix& leftArg, const CenteredCharMatrix& rightArg, bool spaces);
    virtual CenteredCharMatrix renderUnaryOp(const string& op, const CenteredCharMatrix& arg, bool leftRight);
    virtual CenteredCharMatrix renderSuperscript(const CenteredCharMatrix& base, const CenteredCharMatrix& super);
    virtual CenteredCharMatrix renderFraction(const CenteredCharMatrix& top, const CenteredCharMatrix& bottom);
};

} /* namespace Infixs */
} /* namespace Render */
} /* namespace Visitors */
} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */
