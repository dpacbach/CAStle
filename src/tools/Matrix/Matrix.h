/*
 * Matrix.h
 *
 *  Created on: Jan 10, 2013
 *      Author: davidsicilia
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

namespace DS {

template <class T>
class Matrix
{
public:
    Matrix(unsigned int, unsigned int, const T& init);
    Matrix(const Matrix<T>& m);
    virtual ~Matrix();

    virtual Matrix<T>& operator= (const Matrix<T>&);
    vector<T>& operator [] (const unsigned int row);
    const vector<T>& operator [] (const unsigned int row) const;

    void output(ostream& out) const;

    unsigned int height(void) const { return matrix.size(); }
    unsigned int width(void) const { return matrix[0].size(); }

protected:
    vector<vector<T> > matrix;
};


template<class T>
ostream& operator<< (ostream& out, const Matrix<T>& mat)
{
    mat.output(out);
    //mat.matrix.size();
    return out;
}

template<class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns, const T& init) : matrix(rows, vector<T>(columns, init))
{
    if (rows < 1 || columns < 1)
        throw invalid_argument("rows < 1 || columns < 1 in Matrix<T>::Matrix");
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& m)
{
    matrix = m.matrix;
}

template<class T>
Matrix<T>::~Matrix()
{

}

template<typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& aMatrix)
{
    matrix = aMatrix.matrix;
    return *this;
}

template<class T>
vector<T>& Matrix<T>::operator [] (const unsigned int row)
{
    if (row >= matrix.size())
    {
        // throw exception
    }

    return matrix[row];
}

template<class T>
const vector<T>& Matrix<T>::operator [] (const unsigned int row) const
{
    if (row >= matrix.size())
    {
        // throw exception
    }

    return matrix[row];
}

template<class T>
void Matrix<T>::output(ostream& out) const
{
    typename vector<vector<T> >::const_iterator rowIter = matrix.begin();

    for (; rowIter != matrix.end(); ++rowIter)
    {
        cout << endl;
        for (typename vector<T>::const_iterator colIter = (*rowIter).begin(); colIter != (*rowIter).end(); ++colIter)
        {
            out << *colIter << " ";
        }
    }
}

} /* namespace DS */
#endif /* MATRIX_H_ */
