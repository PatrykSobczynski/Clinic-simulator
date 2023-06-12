#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cctype> // to upper case
#include <ctime> // time

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

    //cout << "Dodano pacjenta: " << pData.name << " " << pData.surname << endl;
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
        cout << "Nowy pacjent!" << endl;
        cout << "Czy chcesz dodać kolejnego pacjenta? (T/N)";
        addAnother = toupper(getch());
    } while (addAnother == 'T');
}

string currentDate() {
    // obecna data z komputera
    time_t dateNow = time(0);

    // objekt biblioteki ctime
    tm *ltm = localtime(&dateNow);

    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    // obiekt std::ostringstream o nazwie oss, pomaga stworzyc łańcuch znaków zawierający datę
    ostringstream oss;
    oss << year << "-" << month << "-" << day;

    return oss.str();
}

// Zapis do pliku
void saveToFile(tPointer first) {
    string fileName = currentDate() + ".txt";

    ofstream fileQueue(fileName.c_str());

    if(fileQueue.is_open()) {
        tPointer current = first;
        while (current != NULL) {
            fileQueue << "Imie: " << current->patientData.name << endl;
            fileQueue << "Nazwisko: " << current->patientData.surname << endl;
            fileQueue << "Rok urodzenia: " << current->patientData.birthDate.day
                << " " << current->patientData.birthDate.month
                << " " << current->patientData.birthDate.year;
            fileQueue << endl;

            current = current->next;
        }
        fileQueue.close();
    } else {
        cout << "Nie Udalo sie otworzyc pliku." << endl;
    }
}

// Odczyt z pliku
void readFromFile(tPointer* first, tPointer* last) {
    string fileName = currentDate() + ".txt";
    string text;
    ifstream fileQueue(fileName.c_str());

    tPatientData patient;

    while(getline(fileQueue, text)) {
        if (text.find("Imie: ") != string::npos) {
            patient.name = text.substr(6); // Odczytujemy imię
        } else if (text.find("Nazwisko: ") != string::npos) {
            patient.surname = text.substr(10); // Odczytujemy nazwisko
        } else if (text.find("Rok urodzenia: ") != string::npos) {
            stringstream dateStream(text.substr(15)); // Tworzymy strumień dla daty
            dateStream >> patient.birthDate.day >> patient.birthDate.month >> patient.birthDate.year; // Odczytujemy dzień, miesiąc i rok
            addToQueue(first, last, patient); // Dodajemy pacjenta do kolejki
        }
    }

    fileQueue.close();

}


// Menu
// Operator ** jest nazywany operatorem wskaźnika do wskaźnika
// i służy do operowania na wskaźnikach wielokrotnie pośrednich.
int menu(tElement **first, tElement **last) {

    *first = NULL;
    *last = NULL;

    readFromFile(first, last);

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
            saveToFile(*first);
            break;
        case '2':
            cout << "Opcja 2" << endl;
            displayPatientQueue(*first);
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
    cout << currentDate() << endl; // Dzisiejsza data
    menu(&first, &last); // Operator & służy do pobrania adresu zmiennej

    return 0;
}



