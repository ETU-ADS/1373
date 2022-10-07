#include <iostream>
#include <string>
#include "listFunctions.h"
#include "stackFunctions.h"
#include "taskFunctions.h"
using namespace std;

int main(int argc, char* argv[])
{
    cout << "\nType your array: ";
    string arr;
    getline(cin, arr);
    cout << endl;
    int L = strLen(arr);

    bool checking = 1;
    dataVerification(arr, L, checking); // �������� ��������� ������

    sortingStation(arr, L, checking); // �������� ������������� �������

    return 0;
}
