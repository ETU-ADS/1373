#pragma once
#include <iostream>
#include <ctime>

#include "myStack.h"
#include "myVector.h"

int Minrun(int N) {
    int r = 0;          
    while (N >= 64) {
        r |= N & 1;
        N >>= 1;
    }
    return N + r;
};

struct RUN {
    int size;
    int indexBegin;
};

template <class T>
T min(T x, T y) {
    if (x < y) return x;
    else return y;
};

void ReverseArr(int* run, int size) {

    //std::cout << "\nReverse message -> input: ";
    //for (int i = 0; i < size; i++) {
    //    std::cout << run[i] << ' ';
    //}

    for (int i = 0; i < (size) / 2; i++) {
        run[i] = run[i] + run[(size - 1) - i];
        run[(size - 1) - i] = run[i] - run[(size - 1) - i];
        run[i] = run[i] - run[(size - 1) - i];
    }

    //std::cout << "\nReverse message -> output: ";
    //for (int i = 0; i < size; i++) {
    //    std::cout << run[i] << ' ';
    //}
}

void InsertSort(int* run, int size) {

    //std::cout << "\nInsertSort message -> input: ";
    //for (int i = 0; i < size; i++) {
    //    std::cout << run[i] << ' ';
    //}

    for (int i = 1; i < size; i++) {
        int key = run[i];
        int j = i - 1;
        while (j > -1 && run[j] > key) {
            run[j + 1] = run[j];
            j--;
        }
        run[j + 1] = key;
    }

    //std::cout << "\nInsertSort message -> output: ";
    //for (int i = 0; i < size; i++) {
    //    std::cout << run[i] << ' ';
    //}
}

void MergeSort(myVector<int>& datamass, int l_ptr, int size_l, int size_r) {

    int r_ptr = l_ptr + size_l;

    myVector<int> L_arr(size_l);
    myVector<int> R_arr(size_r);

    for (int i = 0; i < size_l; i++) {
        L_arr[i] = datamass[l_ptr + i];
    }

    //std::cout << "\nMerge message -> L_arr: ";
    //for (int i = 0; i < size_l; i++) {
    //    std::cout << L_arr[i] << ' ';
    //}

    for (int i = 0; i < size_r; i++) {
        R_arr[i] = datamass[r_ptr + i];
    }

    //std::cout << "\nMerge message -> R_arr: ";
    //for (int i = 0; i < size_r; i++) {
    //    std::cout << R_arr[i] << ' ';
    //}

    int x = 0, y = 0, i = l_ptr;

    int l_iterat = 0, r_iterat = 0;
    int maxIterat = 10; //const for switch oo Galloping mode
    int plusIteratL = 1, plusIteratR = 1;

    while (x + y < size_l + size_r) {
        if (L_arr[x] <= R_arr[y] && (x < size_l)) {
            datamass[i] = L_arr[x];
            i++; x++;

            // for Galloping Mode
            r_iterat = 0;
            plusIteratR = 1;

            l_iterat++;

            if (l_iterat > maxIterat) {
                while (L_arr[x + plusIteratL] <= R_arr[y] && x + plusIteratL < size_l && y < size_r) {
                    for (int j = x; j < x + plusIteratL; j++) {
                        datamass[i] = L_arr[j];
                        i++;
                    }
                    x += plusIteratL;
                    plusIteratL += 1;
                }
                l_iterat = 0;
                plusIteratL = 1;
            }
            // end for Galloping Mode
        }
        else if (y < size_r)
        {
            datamass[i] = R_arr[y];
            i++; y++;

            // for Galloping Mode
            l_iterat = 0;
            plusIteratL = 1;

            r_iterat++;

            if (r_iterat > maxIterat) {
                while (L_arr[x] > R_arr[y + plusIteratR] && y + plusIteratR < size_r && x < size_l) {
                    for (int j = y; j < y + plusIteratR; j++) {
                        datamass[i] = R_arr[j];
                        i++;
                    }
                    y += plusIteratR;
                    plusIteratR += 1;
                }
                r_iterat = 0;
                plusIteratR = 1;
            }
            // end for Galloping Mode
        }

        // copy if one of arrs is empty
        if (x >= size_l) {
            while (y < size_r) {
                datamass[i] = R_arr[y];
                i++;
                y++;
            }
        }

        if (y >= size_r) {
            while (x < size_l) {
                datamass[i] = L_arr[x];
                i++;
                x++;
            }
        }
        // end copy
    }
}

void Timsort(myVector<int>& datamass, int N) {

    //std::cout << "\nTeamSort massage -> input: ";
    //for (int i = 0; i < N; i++) {
    //    std::cout << datamass[i] << ' ';
    //}

    myStack<RUN> runStack;
    RUN run;

    int minrun = Minrun(N);
    //std::cout << "\nTeamSort message -> minrun: " << minrun;
    run.indexBegin = 0;
    run.size = 1;

    for (int i = 1; i < N; ) {
        //std::cout << "\nTeamSort message -> i: " << i;
        if (datamass[i - 1] <= datamass[i]) {
            while (1) {
                if (datamass[i - 1] <= datamass[i] && i < N) {
                    run.size++;
                    i++;
                }
                else {
                    if (run.size < minrun) {
                        while (run.size < minrun && i < N) {
                            run.size++;
                            i++;
                        }
                        InsertSort(&datamass[run.indexBegin], run.size);
                    }

                    runStack.push(run);
                    run.indexBegin = i;
                    run.size = 1;
                    i++;
                    break;
                }
            }
            //std::cout << "\nTeamSort message -> if <= i: " << i;
        }

        if (datamass[i - 1] > datamass[i]) {
            while (1) {
                if (datamass[i - 1] > datamass[i] && i < N) {
                    run.size++;
                    i++;
                }
                else {
                    ReverseArr(&datamass[run.indexBegin], run.size);

                    if (run.size < minrun) {
                        while (run.size < minrun && i < N) {
                            run.size++;
                            i++;
                        }
                        InsertSort(&datamass[run.indexBegin], run.size);

                    }

                    runStack.push(run);
                    run.indexBegin = i;
                    run.size = 1;
                    i++;
                    break;
                }
            }
            //std::cout << "\nTeamSort message -> if > i: " << i;
        }
    }

    //std::cout << "\nTeamSort massage -> stack: ";
    //for (int i = 0; i < N; i++) {
    //    std::cout << datamass[i] << ' ';
    //}

    //while (!runStack.isEmpty()) {

    //    RUN X, Y, Z;
    //    X = runStack.peak();
    //    runStack.pop();
    //    //std::cout << "\nrunSrack massage -> X: ";
    //    //for (int i = X.indexBegin; i < X.indexBegin + X.size; i++) {
    //    //    std::cout << datamass[i] << ' ';
    //    //}

    //    if (runStack.isEmpty()) { break; }

    //    Y = runStack.peak();
    //    runStack.pop();
    //    //std::cout << "\nrunSrack massage -> Y: ";
    //    //for (int i = Y.indexBegin; i < Y.indexBegin + Y.size; i++) {
    //    //    std::cout << datamass[i] << ' ';
    //    //}

    //    if (Y.size >= X.size || runStack.isEmpty()) {
    //        MergeSort(datamass, Y.indexBegin, Y.size, X.size);
    //        X.indexBegin = min(X.indexBegin, Y.indexBegin);
    //        X.size = X.size + Y.size;
    //        runStack.push(X);
    //    }
    //    else {
    //        Z = runStack.peak();
    //        runStack.pop();

    //        if (1);
    //        MergeSort(datamass, Z.indexBegin, Z.size, Y.size);
    //        Y.indexBegin = min(Y.indexBegin, Z.indexBegin);
    //        Y.size = Y.size + Z.size;

    //        runStack.push(Y);
    //        runStack.push(X);
    //    }
    //}

    //    //std::cout << "\nrunSrack massage -> new X: ";
    //    //for (int i = X.indexBegin; i < X.indexBegin + X.size; i++) {
    //    //    std::cout << datamass[i] << ' ';
    //    //}
    //}

    RUN X, Y, Z;

    X.size = 0;
    Y.size = 0;
    Z.size = 0;

    int balanSize = 0;

    X = runStack.peak();
    runStack.pop();
    balanSize++;

    while (!runStack.isEmpty()) {

        if (!runStack.isEmpty() && Y.size == 0) {
            Y = runStack.peak();
            runStack.pop();

            balanSize++;
        }

        if (!runStack.isEmpty() && Z.size == 0) {
            Z = runStack.peak();
            runStack.pop();

            balanSize++;
        }

        while ((X.size >= Y.size || Z.size <= X.size + Y.size) && balanSize > 1) {
            if (balanSize >= 2 && X.size >= Y.size) {
                MergeSort(datamass, Y.indexBegin, Y.size, X.size);
                X.indexBegin = min(X.indexBegin, Y.indexBegin);
                X.size = X.size + Y.size;

                if (Z.size != 0) {
                    Y = Z;
                }
                else break;

                balanSize--;

                if (!runStack.isEmpty()) {
                    Z = runStack.peak();
                    runStack.pop();

                    balanSize++;
                }
            }

            if (balanSize >= 3 && Z.size <= X.size + Y.size) {

                if (X.size <= Z.size) {
                    MergeSort(datamass, Y.indexBegin, Y.size, X.size);
                    X.indexBegin = min(X.indexBegin, Y.indexBegin);
                    X.size = X.size + Y.size;

                    Y = Z;
                    Z.size = 0;

                    balanSize--;

                    if (!runStack.isEmpty()) {
                        Z = runStack.peak();
                        runStack.pop();

                        balanSize++;
                    }
                }
                else
                {
                    MergeSort(datamass, Z.indexBegin, Z.size, Y.size);
                    Y.indexBegin = min(Y.indexBegin, Z.indexBegin);
                    Y.size = Y.size + Z.size;
                    Z.size = 0;

                    balanSize--;

                    if (!runStack.isEmpty()) {
                        Z = runStack.peak();
                        runStack.pop();

                        balanSize++;
                    }
                }
            }
        }
    }

    //std::cout << "\nTeamSort massage -> output: ";
    //int prevElement = -1;
    //for (int i = 0; i < N; i++) {
    //    int y = datamass[i];
    //    if (prevElement > y) {
    //        std::cout << "\nTeamSort massage -> ERROR: UNCORRECT PROCESS";
    //        break;
    //    }
    //    else
    //        prevElement = datamass[i];

    //    std::cout << datamass[i] << ' ';
    //}
}