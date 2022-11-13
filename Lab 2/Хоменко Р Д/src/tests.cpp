#include <assert.h>
#include "sort.h"
bool isEqual(int* arr1, int* arr2, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (arr1[i] != arr2[i])
            return 0;
    }
    return 1;
}

void unitTest()
{
    int arr1[97] = { -89,-64,-36,-96,-79,-52,-53,-36,-57,-97,-20,-95,-83,-27,-30,-36,-62,-56,-14,-14,-12,-1,-99,-18,-24,-60,-26,-71,-36,-89,-72,-58,-93,-99,-56,-43,-11,-69,-96,-35,-66,-88,-20,-20,-19,-36,-91,-50,-67,87,34,11,9,20,43,69,22,7,74,26,22,0,22,0,36,70,42,47,90,3,37,24,19,61,15,55,29,19,21,59,22,12,52,0,85,23,32,61,93,20,50,59,58,77,36,74,2 };
    int arr2[97] = { -99,-99,-97,-96,-96,-95,-93,-91,-89,-89,-88,-83,-79,-72,-71,-69,-67,-66,-64,-62,-60,-58,-57,-56,-56,-53,-52,-50,-43,-36,-36,-36,-36,-36,-35,-30,-27,-26,-24,-20,-20,-20,-19,-18,-14,-14,-12,-11,-1,0,0,0,2,3,7,9,11,12,15,19,19,20,20,21,22,22,22,22,23,24,26,29,32,34,36,36,37,42,43,47,50,52,55,58,59,59,61,61,69,70,74,74,77,85,87,90,93 };
    timSort(arr1, 97);
    assert(isEqual(arr1, arr2, 97));
    int arr11[64] = { -34,24,-33,14,47,-30,1,5,37,-34,40,2,-43,-24,36,-37,-9,5,14,17,-17,3,12,-17,-3,-24,17,25,-9,-20,47,31,-6,49,9,-50,48,-29,-19,-29,24,15,42,8,7,44,-43,8,-29,9,49,35,-7,-50,-28,-32,-22,45,-44,8,-46,26,-30,8 };
    int arr12[64] = { -50,-50,-46,-44,-43,-43,-37,-34,-34,-33,-32,-30,-30,-29,-29,-29,-28,-24,-24,-22,-20,-19,-17,-17,-9,-9,-7,-6,-3,1,2,3,5,5,7,8,8,8,8,9,9,12,14,14,15,17,17,24,24,25,26,31,35,36,37,40,42,44,45,47,47,48,49,49 };
    timSort(arr11, 64);
    assert(isEqual(arr11, arr12, 64));
}