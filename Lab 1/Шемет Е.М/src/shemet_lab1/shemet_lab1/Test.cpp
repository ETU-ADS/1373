#include <string>
#include <cassert>
#include "Sort.h"

void Test()
{
    assert(sort("23 * 3 + 10") == "23 3 * 10 + ");
    assert(sort("2 + sin ( 5 + 3 ) * 8 + cos ( 5 * 3 )") == "2 5 3 + sin 8 * + 5 3 * cos + ");
    assert(sort("( 5 - 3 ) * ( 9 - 8 )") == "5 3 - 9 8 - * ");
    assert(sort("sin 5 + 1 / 2 * cos ( 3 ^ 4 + 2 )") == "5 sin 1 2 / 3 4 ^ 2 + cos * + ");
    assert(sort("3 + ( 9 * cos 6 + 3 ) * 6") == "3 9 6 cos * 3 + 6 * + ");
}