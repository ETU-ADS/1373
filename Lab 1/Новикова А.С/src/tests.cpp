#include <cassert>
#include "sort.h"

void tests()
{
	assert(sort("cos 1 + 5 * (2 - 1)") == "1 cos 5 2 1 - * + ");
	assert(sort("( 1 + 1 ) * ( 2 - 2 ) ^ ( 3 / 3 )") == "1 1 + 2 2 - 3 3 / ^ * ");
	assert(sort("sin ^ 2 ( 4 * 2 ^ 2 ) + 5 - cos 2") == "sin 2 4 2 2 ^ * ^ 5 + 2 cos - ");
	assert(sort("+ - * ^ sin cos / * -") == "+ sin cos ^ * / * - - ");
	assert(sort("sin ( cos 1 - 9 ^ ( sin ^ 4 (3 * 2 / 3 ) ) )") == "1 cos 9 sin 4 3 2 * 3 / ^ ^ - sin ");
}