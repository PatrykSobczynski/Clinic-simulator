#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

typedef struct tDate{
    int year, month, day;
};

typedef enum tSex{
    man, woman
};

// Dane Pacjenta
typedef struct tPatientData{
    string surname, name;
    tDate birthDate;
    tSex sex;
};

typedef struct tElement tElement;

typedef struct tElement{
    tPatientData patientData;
    tElement* next;
};

typedef tElement* tPointer;


// Dodawanie do kolejki
addToQueue(tPointer *f, tPointer *l, tPatientData pData) {
    //tPointer tQue;
    // New w c++ działa podobnie jak malloc w c
    //tQue = new tElement(sizeof(*tElement));

}

showPatient(tPatientData data) {
    cout << "Nazwisko: " << data.surname;
}

tPatientData newPatient() {
    tPatientData data;

    cout << "Nazwisko: " << endl;
    cin >> data.surname;

    showPatient(data);
    return data;

}

// Dodawanie nowego pacjenta
addPatient(tPointer *f, tPointer *l) {
    cout << "Dodawanie nowego pacjenta: " << endl;
    addToQueue(&(*f), &(*l), newPatient());
}

// Menu
int menu(tPointer first, tPointer last) {


    char menuChoice;
    bool running = true;
    while(running) { // Dopóki running == true Menu będzie isę pokazywać

        cout << "Witaj w przychodni!" << endl;
        cout << "Menu:" << endl
        << "" << endl
        << "1. Zarejestruj nowa osobe" << endl
        << "2. Wyswietl liste zarejestrowanych osob" << endl
        << "3. Zakończ program" << endl;

    menuChoice = getch();
    switch(menuChoice) {
        case '1':
            cout << "Opcja 1" << endl;
            addPatient(&first, &last);
            break;
        case '2':
            cout << "Opcja 2" << endl;
            break;
        case '3':
            running = false;
            return 0;
            break;
        default: cout << "Wybierz poprawnie" << endl;
            break;
    }

    getch();
    system("CLS"); // Czyszczenie konsoli

    }

    return 0;

}

// MAIN
int main() {


    tPointer first, last;
    first = NULL;
    menu(first, last);

    return 0;
}




