/*
 * Token.h
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

using namespace std;

namespace DS {

class Token
{
public:
    Token(const string& aString, const int _id) : tokenString(aString), id(_id) {}
    ~Token() {}

    Token(const Token& _token) { tokenString = _token.tokenString; id = _token.id; }
    Token& operator= (const Token& _token) { tokenString = _token.tokenString; id = _token.id; return *this; }

    const string& getString(void) const { return tokenString; }
    const int getId(void) const { return id; }

protected:
    string tokenString;
    int id;
};

} /* namespace DS */
#endif /* TOKEN_H_ */
