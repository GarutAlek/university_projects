#pragma once
#include <string>

using namespace std;

struct Record {
    int id;
    string str;
    Record() {
        id = rand() % 10000;
        str = "";
        str += (char)(65 + rand() % 20);
        str += (char)(65 + rand() % 20);
        str += (char)(65 + rand() % 20);
    }
};

struct binary_handler {
    int res;
    bool found;
    binary_handler(int res, bool found) {
        this->res = res;
        this->found = found;
    }
};

class DataBase
{
    const int MaxCount = 1000000;
    Record** array_of_pointers = new Record * [MaxCount];
    int count = 0;
public:
    bool sorted = false;
    int O = 0;

    DataBase(int n0, int fl);
    void gen(int n);
    int search(int id);
    void add();
    void remove(int id);
    void bubbleSort();
    int partition(int start, int end);
    void quickSort(int start, int end);
    void simulate(int fl, int n0, int P, float s, float a, float r);
    binary_handler binary_search(int id);
};

