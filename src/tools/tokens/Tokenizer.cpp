/*
 * Tokenizer.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: davidsicilia
 */

#include <stdexcept>
#include "Tokenizer.h"

namespace DS {
namespace Tokens {

Tokenizer::Tokenizer() {
    // TODO Auto-generated constructor stub

}

Tokenizer::~Tokenizer() {
    // TODO Auto-generated destructor stub
}

bool Tokenizer::tokenizePriority(const string& source, const vector<Scanner::Ptr>& scanners, vector<Token>& destination)
{
    if (scanners.empty())
        return true;
    Scanner::bounds currentBounds = Scanner::make_bounds(source.begin(), source.end());
    stopLocation = currentBounds.first;
    while (currentBounds.first != currentBounds.second)
    {
        int id = 0;
        vector<Scanner::Ptr>::const_iterator it;
        for (it = scanners.begin(); it != scanners.end(); ++it, ++id)
        {
            Scanner::bounds resultBounds = (*it)->scan(currentBounds);
            if (resultBounds.first == resultBounds.second)
                continue;
            else
            {
                string match(resultBounds.first, resultBounds.second);
                destination.push_back(Token(match, id));
                currentBounds.first = resultBounds.second;
                stopLocation = currentBounds.first;
                break;
            }
        }
        if (it == scanners.end())
            return false;
    }
    return true;
}

bool Tokenizer::tokenizeOrdered(const string& source, const vector<Scanner::Ptr>& scanners,
                                const vector<bool>& optionalFlags, vector<Token>& destination, bool dummies)
{

    if (scanners.empty())
    {
        destination.clear();
        return true;
    }
    if (scanners.size() != optionalFlags.size())
    {
        destination.clear();
        throw invalid_argument("optionalFlags.size() != scanners.size() in Tokenizer::tokenizeOrdered");
    }

    Scanner::bounds currentBounds = Scanner::make_bounds(source.begin(), source.end());
    stopLocation = currentBounds.first;
    int id = 0;
    vector<Scanner::Ptr>::const_iterator it;
    vector<bool>::const_iterator bIt = optionalFlags.begin();
    for (it = scanners.begin(); it != scanners.end(); ++it, ++id, ++bIt)
    {
        Scanner::bounds resultBounds = (*it)->scan(currentBounds);
        if (resultBounds.first == resultBounds.second)
        {
            if (*bIt)
            {
                if (dummies)
                    destination.push_back(Token("", id));
                continue;
            }
            else
                return false;
        }
        else
        {
            string match(resultBounds.first, resultBounds.second);
            destination.push_back(Token(match, id));
            currentBounds.first = resultBounds.second;
            stopLocation = currentBounds.first;
        }
    }
    if (currentBounds.first != currentBounds.second)
        return false;
    return true;
}

} /* namespace Token */
} /* namespace DS */
