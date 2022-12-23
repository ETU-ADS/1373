#include <string>
#include <assert.h>
#include "Sort.h"

void unitTest()
{
    std::string str = "";
    assert(sort("2 + sin ( 5 + 3 ) * 8 + cos ( 9 * 7 )") == "2 5 3 + sin 8 * + 9 7 * cos + ");
    assert(sort("sin 3 - 1 / 2 * sin ( 3 ^ 2 - 2 )") == "3 sin 1 2 / 3 2 ^ 2 - sin * - ");
    assert(sort("3 + ( 9 * cos 6 + 3 ) * 6") == "3 9 6 cos * 3 + 6 * + ");
    assert(sort("( 2 + 3 ) * ( 4 + 9 )") == "2 3 + 4 9 + * ");
}