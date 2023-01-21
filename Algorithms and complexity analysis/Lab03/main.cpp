#include <ctime>
#include "iostream"
#include "fstream"
#include "string"
#include "DataBase.h"

using namespace std;

void simulate(int fl, int n0, int P, float s, float a, float r) {
    // я не смог связать О для разных файлов, потому я просто поместил её в DataBase
    DataBase db(n0, fl);
    for (int i = 0; i < P; i++) {
        float rng = (rand() % 100) / 100.0;
        if (rng < s) {
            int id = rand() % 100000;
            db.search(id);
        }
        else if (rng < s + a)
            db.add();
        else {
            int id = rand() % 100000;
            db.remove(id);
        }
    }
    cout << db.O << endl;
}

int main() {
    srand(time(NULL));
    simulate(0, 10000, 100000, 0.2, 0.5, 0.3);
    simulate(1, 10000, 100000, 0.2, 0.5, 0.3);
    simulate(2, 10000, 100000, 0.2, 0.5, 0.3);
    simulate(0, 100000, 10000, 0.2, 0.5, 0.3);
    simulate(1, 100000, 10000, 0.2, 0.5, 0.3);
    simulate(2, 100000, 10000, 0.2, 0.5, 0.3);
    return 0;
}