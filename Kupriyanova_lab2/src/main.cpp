#include <iostream>
#include <cstdlib>
#include<ctime>
#include <vector>
#include <stack>
#include <functional>
#include <algorithm>
#include <cmath>



using namespace std;


// ARRAY
class Arr {
public:
    int* arr;
    int capacity;
    int minrun;
public:
    Arr(){};
    Arr(int arrSize)
    {
        arr = new int[arrSize];
        capacity = arrSize;
    };
    ~Arr(){delete[] arr;}

    void fillArray()
    {
        string n;
        for(int j=0; j<capacity; j++){
            cout<<"Insert int"<<"("<<capacity-j<<" remain): ";
            cin>>n;
            bool wrongType=false;
            for (int i=0; i<n.length(); i++)
            {
                if (isdigit(n[i]) == false)
                {
                    cout<< "number must be integer!"<<endl;
                    j--;
                    wrongType = true;
                    break;
                }
            }
            if(wrongType==false)
                arr[j] = stoi(n);
        }
    }

    void fillRandArray()
    {
        for(int j=0; j<capacity; j++)
            arr[j] = rand()%500+1;
    }

    void printArray()
    {
        cout<<"Array: ";
        for(int j=0; j<capacity; j++)
            cout<<arr[j]<<" ";
        cout<<endl;
        cout<<"Array size: "<<capacity<<endl;
    }

    void deleteElement(int i)
    {
        if (i<0 || i>=capacity)
            cout<<"Number is out of range!"<<endl;
        else{
            int *tempArr = new int[capacity-1];
            int k = 0;
            for(int j=0; j<capacity; j++)
            {
                if(j==i)
                    j++;
                tempArr[k]=arr[j];
                k++;
            }
        capacity--;

        arr = new int[capacity];
        for(int j=0; j<capacity; j++)
              arr[j] = tempArr[j];
        delete [] tempArr;
        }
    }

    void addElement(int i, int val)
    {
        if (i<0 || i>=capacity)
            cout<<"Number is out of range!"<<endl;
        else{
            int *tempArr = new int[capacity+1];
            int k = 0;
            for(int j=0; j<capacity; j++)
            {
                if(j==i)
                {
                    tempArr[k]=val;
                    k++;
                }
                tempArr[k]=arr[j];
                k++;
            }
        capacity++;

        arr = new int[capacity];
        for(int j=0; j<capacity; j++)
              arr[j] = tempArr[j];
        delete [] tempArr;
        }
    }
};

int GetMinrun(int n) //поиск минимального размера подмассива
	{
	    int r = 0;           
	    while (n >= 64) 
        {
	        r |= n & 1;
	        n >>= 1;
	    }
	    return n + r;
	}

void Showstack(stack<pair<int, int> > s) //вывод пар
{
    while (!s.empty()) 
    {
            cout << "("
         << s.top().first << ", "
         << s.top().second << ") ";
        s.pop();
    }

    cout << '\n';
}

Arr& merge(Arr& startArray, int start, int mid, int last) //слияние подмассивов с режимом галопа
{
        int* left = new int[mid-start];
        int* right = new int[last-mid];

        for (int i = 0; i < mid-start; i++)
        {
            left[i] = startArray.arr[start+i];
            //cout<<left[i]<<" ";
        }
        for (int i = 0; i < last-mid; i++)
        {
            right[i] = startArray.arr[mid+i];
            //cout<<right[i]<<" ";
            }

        int i=0;
        int j=0;
        int k = start;
        int gallopR = 0;
        int gallopL = 0;
        while (i < mid-start && j < last-mid)
            {
                if (gallopL!=7 && gallopR!=7)
                {
                    if (left[i] <= right[j])
                    {
                        startArray.arr[k] = left[i];
                        i++;
                        gallopL++;
                        gallopR = 0;
                    }
                    else
                    {
                        startArray.arr[k] = right[j];
                        j++;
                        gallopR++;
                        gallopL = 0;
                    }
                    k++;
                }
                else{
                    cout<<"ENTERING GALLOP MODE"<<endl;
                    bool gallopContinue = true;
                    int gallopI = 0;
                    if(gallopL==7){
                        gallopL = 0;
                        int gallopCount = i;
                        int gallopCountPrev = i;
                        while(gallopContinue==true ){
                            if(gallopCount>mid-start ){
                                gallopCount = mid-start;
                                if(left[gallopCount] > right[j]){
                                    gallopCount = gallopCountPrev;
                                }
                                gallopContinue = false;
                            }
                            else if(left[gallopCount] <= right[j]){
                                gallopCountPrev = gallopCount;
                                gallopCount+=2*pow(gallopI,2);
                                gallopI++;
                                //gallopCountPrev = gallopCount-2*pow(gallopI,2);
                            }
                            else{
                                gallopCount = gallopCountPrev;
                                gallopContinue = false;
                            }
                        }
                        //cout<<"GC 1 "<<i<<" "<<gallopCount<<" "<<startArray.arr[k]<<endl;
                        copy(left + i, left + gallopCount, startArray.arr + k);
                        k+=gallopCount-i;
                        i=gallopCount;
                    }
                    else if(gallopR==7){
                        gallopR = 0;
                        int gallopCount = j;
                        int gallopCountPrev = j;
                        while(gallopContinue==true ){
                            if(gallopCount>last-mid){
                                gallopCount = last-mid;
                                if(right[gallopCount] > left[i]){
                                    gallopCount = gallopCountPrev;
                                }
                                gallopContinue = false;
                            }
                            else if(right[gallopCount] <= left[i]){
                                gallopCountPrev = gallopCount;
                                gallopCount+=2*pow(gallopI,2);
                                gallopI++;
                                //gallopCountPrev = gallopCount-2*pow(gallopI,2);
                            }
                            else{
                                gallopCount = gallopCountPrev;
                                gallopContinue = false;
                            }
                        }
                        //cout<<"GC "<<j<<" "<<gallopCount<<" "<<startArray.arr[k]<<endl;
                        copy(right + j, right + gallopCount, startArray.arr + k);
                        k+=gallopCount-j;
                        j=gallopCount;
                    }
                }
            }

        while (i < mid-start)
        {
            startArray.arr[k] = left[i];
            k++;
            i++;
        }

        while (j < last-mid)
        {
            startArray.arr[k] = right[j];
            k++;
            j++;
        }
        startArray.printArray();

        return startArray;
}

void mergeArr(stack<pair<int, int>> s, Arr startArray) 
{
    while(s.size()>=2)
    {
        pair<int, int> X = s.top();
        s.pop();
        pair<int, int> Y = s.top();
        s.pop();
        if (s.empty())
        {
            startArray = merge(startArray, 0, X.second, X.second+Y.second);
            break;
        }
        if ((s.top().second > X.second + Y.second && Y.second > X.second))
            break;

        else
        {
            if (X.second <= s.top().second)
            {
                cout<<"X = X+Y"<<endl;
                startArray = merge(startArray, 0, X.second, X.second+Y.second);
                s.push({0,X.second+Y.second});
            }
            else
            {
                pair<int, int> Z = s.top();
                s.pop();
                cout<<"Z = Z+Y"<<endl;
                startArray = merge(startArray, X.second, X.second+Y.second, X.second+Y.second+Z.second);
                s.push({X.second,Y.second+Z.second});
                s.push({0,X.second});
            }
        }

    startArray.printArray();
    Showstack(s);

    }

}


void findRun(Arr startArray) //поиск подпоследоательностей
{
    int pointer = 0;
    int runSize = 0;
    vector<int> numberOfRun;

    while(pointer<=startArray.capacity-1)
    {
        runSize = pointer+1;

        if(startArray.arr[runSize-1]>startArray.arr[runSize])
        {
            while(runSize<startArray.capacity-1 &&startArray.arr[runSize]>startArray.arr[runSize+1])
                runSize+=1;
        }
        else{
            while(runSize<startArray.capacity-1 && startArray.arr[runSize]<=startArray.arr[runSize+1])
                runSize+=1;
        }
        runSize+=1;

        if(startArray.capacity-runSize<startArray.minrun){
            runSize+=startArray.capacity-runSize;
        }

        cout<<"r: "<<runSize<<endl;

        if(runSize-pointer<startArray.minrun)
        {
            if((startArray.minrun -(runSize-pointer)+runSize)>=startArray.capacity || runSize==startArray.capacity)
                runSize = startArray.capacity;
            else
                runSize = startArray.minrun -(runSize-pointer)+runSize;
        }

        cout<<"r: "<<runSize<<endl;
        cout<<"p: "<<pointer<<endl;
        numberOfRun.push_back(runSize-pointer);
        cout<<"Num of run: "<<numberOfRun.size()<<endl;
        cout<<runSize-pointer<<endl;
        pointer = runSize;

    }
    if(numberOfRun.at(numberOfRun.size()-1)< startArray.minrun)
    {
        numberOfRun.at(numberOfRun.size()-2)+=numberOfRun.at(numberOfRun.size()-1);
        numberOfRun.erase(numberOfRun.begin()+numberOfRun.size()-1);
    }

    for (int i=0; i<numberOfRun.size();i++)
        cout << numberOfRun.at(i) << ' ';

    pointer = 0;
    stack<pair<int, int>> s;
    for (int i=0; i<numberOfRun.size();i++)
    {
        pair<int, int> p(pointer, numberOfRun.at(i));
        s.push(p);
        for(int k=pointer+1;k<numberOfRun.at(i)+pointer;k++) //сортировка вставками
        {
            for(int l=k;l>pointer && startArray.arr[l-1]>startArray.arr[l];l--)
                swap(startArray.arr[l-1],startArray.arr[l]);
        }

        startArray.printArray();

        pointer +=numberOfRun.at(i);
    }



    cout<<"\n Sorted arrays:"<<endl;
    startArray.printArray();

    Showstack(s);

    stack<pair<int, int>> t_s;
    pair<int, int> t_p;
    while (s.size() != 0)
    {
      t_p = s.top();
      s.pop();
      t_s.push(t_p);
    }

    s = t_s;
    Showstack(s);

    startArray.printArray();

    mergeArr(s, startArray);



    cout<<"end"<<endl;
    int y=0;
    cin>>y;

}

void algorythm (Arr startArray)
{
    startArray.printArray();
    startArray.minrun = GetMinrun(startArray.capacity);
    cout<<"MINRUN: "<<startArray.minrun<<endl;
    findRun(startArray);
    cout<<"End"<<endl;
    int y=0;
    cin>>y;

}



int interface()
{
    system("cls");

    int arrSize;
    cout<<"Input size of Array"<<endl;
    cin>>arrSize;
    Arr arr(arrSize);
    int func;
    string n;
    while(func != 4)
    {
        cout<<"\n1 - input elements manualy\n2 - input random elements\n3 - Timesort\n4 - exit"<<endl;
        cin>>func;
        system("cls");
        switch(func)
        {
        case 1:
            arr.fillArray();
            arr.printArray();
            break;
        case 2:
            arr.fillRandArray();
            arr.printArray();
            break;
        case 3:
            algorythm(arr);
            break;
        }
    }
}


int main()
{
    srand(time(NULL));
    interface();
    return 0;
}
