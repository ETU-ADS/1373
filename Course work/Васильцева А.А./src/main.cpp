#include <iostream>
#include <fstream>
#include <string>

#include "myList.h"
#include "myVector.h"

myVector<int> dsuVec(50);

struct EDGE_ {
    int vert1;
    int vert2;
    int value;
};

struct NAMEVERT_ {
    std::string name = "";
    int num;
};

void initDSU() {
    for (int i = 0; i < 50; i++) {
        dsuVec[i] = i;
    }
}

int findComponent(int x)
{
    if (dsuVec[x] == x) return x;
    return dsuVec[x] = findComponent(dsuVec[x]);
}

bool unitComponent(int x, int y) {
    int a = findComponent(x), b = findComponent(y);

    if (a == b) {
        return false;
    }
    else {
        dsuVec[a] = b;
        return true;
    }
}

void addAndSort(myVector<EDGE_>& vec, EDGE_ elem) { // insert sort
    vec.addToTheEnd(elem);
    int indx = vec.sizeVector() - 2;
    while (indx > -1 && vec[indx].value > elem.value) {
        vec[indx + 1] = vec[indx];
        indx--;
    }
    vec[indx + 1] = elem;
}

int main() {

    setlocale(0,"");
    int MAXvert = 50;
    initDSU();
    std::ifstream DATA("test2.txt");

    std::string data_vertice_line;
    // get vertice's names
    getline(DATA, data_vertice_line);
    int num_vertice = 0;
    myVector<NAMEVERT_> vertNameVector;
    for (int i = 0; i < MAXvert; i++) {
        int space_pos = data_vertice_line.find(" ");
        if (space_pos == -1) {
            NAMEVERT_ temp;
            temp.name = "";
            temp.name.append(data_vertice_line, 0, data_vertice_line.size());
            temp.num = num_vertice;
            vertNameVector.addToTheEnd(temp);
            num_vertice++;
            break;
        }
        if (data_vertice_line.size()) {
            NAMEVERT_ temp;
            temp.name = "";
            temp.name.append(data_vertice_line, 0, space_pos);
            temp.num = num_vertice;
            vertNameVector.addToTheEnd(temp);
            num_vertice++;

            data_vertice_line.erase(0, space_pos + 1);
        }
    }
    //for (int i = 0; i < vertNameVector.sizeVector(); i++) {
    //    std::cout << vertNameVector[i].name << " ";
    //}
    //std::cout << '\n';

    myVector<EDGE_> vertEdgeVec;
    int vertice_value;
    for (int i = 0; i < num_vertice; i++) {
        for (int j = 0; j < num_vertice; j++) {
            if (!DATA.eof()) {
                DATA >> vertice_value;
                if (vertice_value != 0) {
                    EDGE_ temp;
                    temp.vert1 = i;
                    temp.vert2 = j;
                    temp.value = vertice_value;
                    addAndSort(vertEdgeVec, temp);
                }
            }
        }
    }

    int name1, name2; int sum = 0;
    for (int i = 0; i < vertEdgeVec.sizeVector(); i++) {
        name1 = vertEdgeVec[i].vert1;
        name2 = vertEdgeVec[i].vert2;
        if (findComponent(name1) != findComponent(name2)) {
            unitComponent(name1, name2);
            std::cout << vertNameVector[vertEdgeVec[i].vert1].name <<
                ' ' << vertNameVector[vertEdgeVec[i].vert2].name << " | "
                << vertEdgeVec[i].value << std::endl;
            sum += vertEdgeVec[i].value;
        }
    }
    std::cout << "Your min sum: " << sum << std::endl;
}
