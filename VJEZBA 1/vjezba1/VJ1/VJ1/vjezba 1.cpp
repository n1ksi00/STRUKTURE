#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    char ime[50];
    char prezime[50];
    float bodovi;
};

int main() {

    ifstream datoteka("studenti.txt");

    if (!datoteka.is_open()) {
        cout << "Greska kod otvaranja datoteke!" << endl;
        return 1;
    }

   
 int n;

    Student* studenti = new Student[n];

    float max_br_bodova = 0;

    for (int i = 0; i < n; i++) {
        datoteka >> studenti[i].ime >> studenti[i].prezime >> studenti[i].bodovi;

        if (studenti[i].bodovi > max_br_bodova) {
            max_br_bodova = studenti[i].bodovi;
        }
    }

    datoteka.close();

    cout << "Ime\t\tPrezime\t\tApsolutni\tRelativni" << endl;
    cout << "---------------------------------------------------------" << endl;

    for (int i = 0; i < n; i++) {

        float relativni_br_bodova = (studenti[i].bodovi / max_br_bodova) * 100;

        cout << studenti[i].ime << "\t\t"
            << studenti[i].prezime << "\t\t"
            << studenti[i].bodovi << "\t\t"
            << relativni_br_bodova << "%" << endl;
    }

    delete[] studenti;

    return 0;
}