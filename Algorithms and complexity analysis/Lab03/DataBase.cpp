#include "DataBase.h"
#include <iostream>
#include <string>

DataBase::DataBase(int n0, int fl) {
    gen(n0);
    sorted = fl == 1 || fl == 2;
    if (sorted) {
        if (fl == 1)
            bubbleSort();
        if (fl == 2)
            quickSort(0, count - 1);
    }
}

void DataBase::gen(int n) {
    for (int i = count; i < n + count; i++) {
        array_of_pointers[i] = new Record();
    }
    count += n;
}

binary_handler DataBase::binary_search(int id) {
    bool found = false;
    int left = 0;
    int right = count - 1;
    int now = -1;

    while ((left <= right) && (found != true)) {
        O++;
        now = (left + right) / 2;
        if (array_of_pointers[now]->id == id)
            found = true;
        if (array_of_pointers[now]->id > id)
            right = now - 1;
        else
            left = now + 1;
    }
    return binary_handler(now, found);
}

int DataBase::search(int id) {
    if (sorted) {
        binary_handler res = binary_search(id);
        if (res.found)
            return res.res;
    }
    else {
        for (int i = 0; i < count; i++) {
            O++;
            if (array_of_pointers[i]->id == id)
                return i;
        }
    }
    return -1;
}

void DataBase::add() {
    if (sorted) {
        Record r = Record();
        int pos = binary_search(r.id).res;
        for (int i = count; i > pos; i--) {
            O++;
            array_of_pointers[i] = array_of_pointers[i - 1]; // смещаем все элементы, правее нужной €чейки, на 1 вправо
        }
        array_of_pointers[pos] = &r;
        count++;
        O++;
    }
    else {
        array_of_pointers[count] = new Record();
        count++;
        O++;
    }
}

void DataBase::remove(int id) {
    int pos = search(id);
    // нет смысла ставить if (sorted) поскольку он и так есть в search()
    if (pos != -1) {
        // помещаем на место бывшего элемента те что правее него
        // если элемент в конце массива то ничего не делаем, он просто дальше не будет учитыватьс€ программой
        for (int i = pos; i < count - 1; i++) {
            array_of_pointers[i] = array_of_pointers[i + 1];
            O++;
        }
        count--;
    }
}

void DataBase::bubbleSort() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            O++;
            if (array_of_pointers[j] > array_of_pointers[j + 1]) {
                swap(array_of_pointers[j], array_of_pointers[j + 1]);
            }
        }
    }
}

// € вз€л эти функции с первой ссылки гугла, так что у других может быть такой же код :)
int DataBase::partition(int start, int end) {
    int pivot = array_of_pointers[start]->id;

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        O++;
        if (array_of_pointers[i]->id <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(array_of_pointers[pivotIndex], array_of_pointers[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {
        O++;
        while (array_of_pointers[i]->id <= pivot) {
            i++;
        }

        while (array_of_pointers[j]->id > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(array_of_pointers[i++], array_of_pointers[j--]);
            //O++;
        }
    }

    return pivotIndex;
}

void DataBase::quickSort(int start, int end) {
    // base case
    if (start >= end) {
        sorted = true;
        return;
    }

    // partitioning the array
    int p = partition(start, end);

    // Sorting the left part
    quickSort(start, p - 1);

    // Sorting the right part
    quickSort(p + 1, end);
}

