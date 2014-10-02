/*
 * Templates.h
 *
 *  Created on: Jan 22, 2013
 *      Author: davidsicilia
 */

#ifndef TEMPLATES_H_
#define TEMPLATES_H_

#include <stack>

template <typename T>
T getPop(std::stack<T>& aStack)
{
    T result = aStack.top();
    aStack.pop();
    return result;
}

template <typename T>
void clearStack(std::stack<T>& aStack)
{
    while (!aStack.empty())
        aStack.pop();
}

#endif /* TEMPLATES_H_ */
