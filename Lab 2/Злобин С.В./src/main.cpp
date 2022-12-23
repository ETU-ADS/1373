#include <iostream>
#include "MyVector.h"
#include "MyStack.h"
#include "MyRun.h"
#include <ctime>

using namespace std;

void insertion_sort(MyVector& arr, MyRun run) {
    int j;
    for (int i = run.begin+1; i < run.size+run.begin; i++) {
        j = i - 1;
        while ((j >= run.begin) && (arr[j] > arr[j + 1])) {
            arr.swap(j, j+1);
            j--;
        }
    }
}

int minrun_length(int n){
    int flag = 0;
    while (n >= 64) {
        flag |= n & 1;
        n >>= 1;
    }
    return n + flag;
}

void reverse_run(MyVector& arr, MyRun run) {
    int i = run.begin;
    int k = run.size + run.begin - 1;
    while ((i - k != 0) && (k - i != -1)) {
        arr.swap(i, k);
        i++;
        k--;
    }
}

void merge(MyVector& arr, MyRun run1, MyRun run2) {
    MyVector tmp;
    int i = run1.begin, k = run2.begin;
    int galop_i = 0, galop_k = 0, coeff=8;
    while ((i < run1.size+run1.begin) && (k < run2.size+run2.begin)) {
        if ((galop_i < coeff) && (galop_k < coeff)) {
            if (arr[i] <= arr[k]) {
                tmp.push_back(arr[i]);
                i++;
                galop_i++;
                galop_k = 0;
            }
            else {
                tmp.push_back(arr[k]);
                k++;
                galop_k++;
                galop_i = 0;
            }
        }
        else {
            int jump=1;
            int gal_in=0;
            if ((galop_i >= coeff)&&(arr[i]<=arr[k])) {
                gal_in = i;
                while ((gal_in + jump < run1.size + run1.begin) && (arr[gal_in + jump] <= arr[k])) {
                    gal_in += jump;
                    jump *= 2;
                }
                if (arr[run1.size + run1.begin - 1] <= arr[k]) {
                    gal_in = run1.size + run1.begin - 1;
                }
                else {
                    int l=gal_in, r, mid=0;
                    bool flag = false;

                    if (gal_in + jump < run1.size + run1.begin) {
                        r = gal_in + jump;
                    }
                    else {
                        r = run1.size + run1.begin - 1;
                    }
                    while ((l <= r) && (!flag)) {
                        mid = (l + r) / 2;
                        if ((arr[mid] <= arr[k]) && (arr[mid + 1] > arr[k])) flag = true;
                        if (arr[mid] > arr[k]) r = mid - 1;
                        else l = mid + 1;
                    }
                    if (flag) gal_in = mid;
                }
                while (i <= gal_in) {
                    tmp.push_back(arr[i]);
                    i++;
                }                
                galop_i = 0;
            }
            else galop_i = 0;
            if ((galop_k >= coeff) && (arr[k] <= arr[i])) {
                gal_in = k;
                while ((gal_in + jump < run2.size + run2.begin) && (arr[gal_in + jump] <= arr[i])) {
                    gal_in += jump;
                    jump *= 2;
                }
                if (arr[run2.size+run2.begin - 1] <= arr[i]){
                    gal_in = run2.size+run2.begin - 1;
                }
                else {
                    int l = gal_in, r, mid;
                    bool flag = false;

                    if (gal_in + jump < run2.size + run2.begin){
                        r = gal_in + jump;
                    }
                    else {
                        r = run2.size + run2.begin - 1;
                    }
                    while ((l <= r) && (!flag)) {
                        mid = (l + r) / 2;
                        if ((arr[mid] <= arr[i]) && (arr[mid + 1] > arr[i])) flag = true;
                        if (arr[mid] > arr[i]) r = mid - 1;
                        else l = mid + 1;
                    }
                    if (flag) gal_in = mid;
                }
                while (k <= gal_in) {
                    tmp.push_back(arr[k]);
                    k++;
                }
                galop_k = 0;
            }
            else galop_k = 0;
        }
    }

    while (i < run1.size+run1.begin) {
        tmp.push_back(arr[i]);
        i++;
    }
    while (k < run2.size+run2.begin) {
        tmp.push_back(arr[k]);
        k++;
    }

    int p = 0;
    for (int j = run2.begin; j < run1.begin + run1.size; j++) {
        arr[j] = tmp[p];
        p++;
    }
}

void timsort(MyVector& arr) {
    int minrun = minrun_length(arr.size);
    
    MyStack stack;
    MyRun run;

    int i = 1;
    int num = 0;
    bool shortfall = false;
    
    while (i <= arr.size) {
        if (i < arr.size) {
            shortfall = false;
            if (arr[i - 1] <= arr[i]) {
                run.begin = i - 1;
                run.size++;
                run.size++;
                i++;
                while ((i < arr.size) && (arr[i - 1] <= arr[i])) {
                    run.size++;
                    i++;
                }
                while ((i < arr.size) && (run.size < minrun)) {
                    run.size++;
                    i++;
                    if (!shortfall) shortfall = true;
                }
                i++;
                if (shortfall) insertion_sort(arr, run);
                num++;
            }
            else {
                run.begin = i - 1;
                run.size++;
                run.size++;
                i++;
                while ((i < arr.size) && (arr[i - 1] > arr[i])) {
                    run.size++;
                    i++;
                }
                while ((i < arr.size) && (run.size < minrun)) {
                    run.size++;
                    i++;
                    if (!shortfall) shortfall = true;
                }
                i++;
                if (shortfall) insertion_sort(arr, run);
                else reverse_run(arr, run);
                num++;
            }
            stack.push(run);
        }
        else {
            run = stack.peak();
            run.size++;
            stack.pop();
            stack.push(run);
            insertion_sort(arr, run);
            i++;
        }

        MyRun X, Y, Z;

        if (stack.size >= 2) {
            X = stack.peak();
            Y = stack.peak(1);
        }

        while ((stack.size >= 2) && ((X.size >= Y.size)|| (stack.size >= 3) && (Z.size <= Y.size + X.size))) {
            while ((stack.size >= 2) && (X.size >= Y.size)) {
                merge(arr, X, Y);
                run.size = X.size + Y.size;
                run.begin = Y.begin;
                stack.pop();
                stack.pop();
                stack.push(run);
                if (stack.size >= 2) { X = stack.peak(); Y = stack.peak(1); }
            }

            if (stack.size >= 3) Z = stack.peak(2);

            while ((stack.size >= 3) && (Z.size <= Y.size + X.size)) {
                if (X.size >= Z.size) {
                    merge(arr, Y, Z);
                    run.size = Y.size + Z.size;
                    run.begin = Z.begin;
                    stack.pop(1);
                    stack.pop(1);
                    stack.push(run, 1);
                }
                else {
                    merge(arr, X, Y);
                    run.size = X.size + Y.size;
                    run.begin = Y.begin;
                    stack.pop();
                    stack.pop();
                    stack.push(run);
                }
                if (stack.size >= 3) { X = stack.peak(); Y = stack.peak(1); Z = stack.peak(2); }
            }

            if (stack.size >= 2) {
                X = stack.peak();
                Y = stack.peak(1);
            }
            if (stack.size >= 3) Z = stack.peak(2);
        }
        run.size = 0;
        run.begin = 0; 
    }

    while (stack.size > 1) {
        merge(arr, stack.peak(), stack.peak(1));
        run.size = stack.peak().size + stack.peak(1).size;
        run.begin = stack.peak(1).begin;
        stack.pop();
        stack.pop();
        stack.push(run);
    }
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter the elements: ";

    int a;
    MyVector arr;
    
    for (int i = 0; i < n; i++) {
        cin >> a;
        arr.push_back(a);
    }

    timsort(arr);
    cout << "\n\n\n";
    arr.print_data();
}