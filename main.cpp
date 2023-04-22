#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cctype> // to upper case

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

// Pokazuje dane pacjenta
void showPatient(tPatientData data) {
    cout << "" << endl;
    cout << "Imie: " << data.name << endl;
    cout << "Nazwisko: " << data.surname << endl;
    cout << "Rok Urodzenia: "
        << data.birthDate.day << " "
        << data.birthDate.month << " "
        << data.birthDate.year << endl;
}

// Wyświetla kolejke pacjentów
void displayPatientQueue(tPointer first) {
    if (first == NULL) {
        cout << "Kolejka jest pusta" << endl;
    } else {
        cout << "Kolejka: " << endl;
        int i = 1;
        tPointer current = first;
        while (current != NULL) {
            cout << i << ". ";
            // Operator "->" jest używany, aby uzyskać dostęp do składowych struktury
            // za pomocą wskaźnika na strukturę.
            showPatient(current->patientData);
            current = current->next;
            i++;
        }
    }
}

// Dodawanie do kolejki
void addToQueue(tPointer* f, tPointer* l, tPatientData pData) {

    tPointer newPatient = new tElement;
    newPatient->patientData = pData;
    newPatient->next = NULL;

    if(*l == NULL) {
        *f = newPatient;
        *l = newPatient;
    } else {
        (*l)->next = newPatient;
        *l = newPatient;
    }

    cout << "Dodano pacjenta: " << pData.name << " " << pData.surname << endl;
}

// Tworzenie nowego pacjenta
tPatientData newPatient() {

    tPatientData data;

    cout << "" << endl;
    cout << "Imie: ";
    cin >> data.name;
    cout << "Nazwisko: ";
    cin >> data.surname;
    cout << "Data urodzenia (Dzien Miesiac Rok): ";
    cin >> data.birthDate.day >> data.birthDate.month >> data.birthDate.year;

    return data;
}

// Dodawanie nowego pacjenta
void addPatient(tPointer *f, tPointer *l) {

    char addAnother;

    do {
        addToQueue(&(*f), &(*l), newPatient());
        cout << "Czy chcesz dodać kolejnego pacjenta? (T/N)";
        addAnother = toupper(getch());
    } while (addAnother == 'T');
}

// Menu
// Operator ** jest nazywany operatorem wskaźnika do wskaźnika
// i służy do operowania na wskaźnikach wielokrotnie pośrednich.
int menu(tElement **first, tElement **last) {

    *first = NULL;
    *last = NULL;

    char menuChoice;
    bool running = true;
    while(running) { // Dopóki running == true Menu bêdzie isê pokazywaæ

        cout << "Witaj w przychodni!" << endl;
        cout << "Menu:" << endl
        << "" << endl
        << "1. Zarejestruj nowa osobe" << endl
        << "2. Wyswietl liste zarejestrowanych osob" << endl
        << "3. Wyświetl aktualną kolejke" << endl
        << "4. Zakoncz program" << endl;

    menuChoice = getch();
    switch(menuChoice) {
        case '1':
            cout << "Opcja 1" << endl;
            addPatient(first, last);
            break;
        case '2':
            cout << "Opcja 2" << endl;
            break;
        case '3':
            cout << "Kolejka" << endl;
            displayPatientQueue(*first);
            break;
        case '4':
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
    menu(&first, &last); // Operator & służy do pobrania adresu zmiennej

    return 0;
}





