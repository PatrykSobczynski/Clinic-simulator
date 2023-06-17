#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cctype> // to upper case
#include <ctime> // time
#include <queue> // kolejka

using namespace std;

typedef struct tDate {
    int year, month, day;
};

typedef enum tSex {
    man, woman
};

typedef struct tDoctorElement;
typedef struct tElement;

// Dane Lekarza
typedef struct tDoctorData {
    string surname, name, specialization;
};

// Element kolejki lekarzy
typedef struct tDoctorElement {
    tDoctorData doctorData;
    tDoctorElement* next;
};

// Dane Pacjenta
typedef struct tPatientData {
    string surname, name;
    tDate birthDate;
    tSex sex;
};

// Element kolejki pacjentów
typedef struct tElement {
    tPatientData patientData;
    tDoctorElement* doctor;
    tElement* next;
};

typedef tElement* tPointer;
typedef tDoctorElement* tDoctorPointer;


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

// Pokazuje dane lekarza
void showDoctor(tDoctorData data) {
    cout << "" << endl;
    cout << "Imie: " << data.name << endl;
    cout << "Nazwisko: " << data.surname << endl;
    cout << "Specjalizacja: " << data.specialization << endl;
}

// Wyœwietla kolejki pacjentów z podzia³em na lekarzy
void displayPatientQueueByDoctor(tPointer first, tDoctorPointer doctorQueue) {
    if (doctorQueue == NULL) {
        cout << "Kolejka lekarzy jest pusta" << endl;
    } else {
        cout << "Kolejki pacjentow: " << endl;
        int i = 1;
        tDoctorPointer currentDoctor = doctorQueue;
        while (currentDoctor != NULL) {
            cout << i << ". Lekarz: ";
            showDoctor(currentDoctor->doctorData);
            cout << "   Pacjenci: " << endl;
            cout << endl;
            int j = 1;
            tPointer currentPatient = first;
            while (currentPatient != NULL) {
                if (currentPatient->doctor == currentDoctor) {
                    cout << "   " << j << ". ";
                    showPatient(currentPatient->patientData);
                    j++;
                }
                currentPatient = currentPatient->next;
            }
            cout << endl;
            currentDoctor = currentDoctor->next;
            i++;
        }
    }
}

// Wyœwietla kolejke lekarzy
void displayDoctorQueue(tDoctorPointer first) {
    if (first == NULL) {
        cout << "Kolejka lekarzy jest pusta" << endl;
    } else {
        cout << "Kolejka lekarzy: " << endl;
        int i = 1;
        tDoctorPointer current = first;
        while (current != NULL) {
            cout << i << ". ";
            // Operator "->" jest u¿ywany, aby uzyskaæ dostêp do sk³adowych struktury
            // za pomoc¹ wskaŸnika na strukturê.
            showDoctor(current->doctorData);
            current = current->next;
            i++;
        }
    }
}

// Dodawanie do kolejki pacjentów
void addToPatientQueue(tPointer* f, tPointer* l, tPatientData pData, tDoctorPointer doctor) {

    tPointer current = *f;
    while (current != NULL) {
        if (current->patientData.name == pData.name &&
            current->patientData.surname == pData.surname &&
            current->patientData.birthDate.day == pData.birthDate.day &&
            current->patientData.birthDate.month == pData.birthDate.month &&
            current->patientData.birthDate.year == pData.birthDate.year) {
            // Pacjent ju¿ istnieje, zakoñcz funkcjê
            return;
        }
        current = current->next;
    }

    tPointer newPatient = new tElement;
    newPatient->patientData = pData;
    newPatient->doctor = doctor;
    newPatient->next = NULL;

    if (*l == NULL) {
        *f = newPatient;
        *l = newPatient;
    } else {
        (*l)->next = newPatient;
        *l = newPatient;
    }
}

// Dodawanie do kolejki lekarzy
void addToDoctorQueue(tDoctorPointer* f, tDoctorPointer* l, tDoctorData dData) {

    tDoctorPointer newDoctor = new tDoctorElement;
    newDoctor->doctorData = dData;
    newDoctor->next = NULL;

    if (*l == NULL) {
        *f = newDoctor;
        *l = newDoctor;
    } else {
        (*l)->next = newDoctor;
        *l = newDoctor;
    }
}

// Tworzenie nowego pacjenta
tPatientData newPatient(tDoctorPointer* df, tPointer* first, tPointer* last) {
    if (*df == NULL) {
        cout << "Musisz pierw dodac lekarzy!" << endl;
        exit(-1);
    }

    tPatientData data;

    cout << "" << endl;
    cout << "Imie: ";
    cin >> data.name;
    cout << "Nazwisko: ";
    cin >> data.surname;
    cout << "Data urodzenia (Dzien Miesiac Rok): ";
    cin >> data.birthDate.day >> data.birthDate.month >> data.birthDate.year;
    cout << "Do jakiego lekarza zapisac pacjenta? " << endl;
    displayDoctorQueue(*df);

    int doctorIndex;
    cout << "Wybierz numer lekarza: ";
    cin >> doctorIndex;

    tDoctorPointer currentDoctor = *df;
    for (int i = 1; i < doctorIndex; i++) {
        currentDoctor = currentDoctor->next;
        if (currentDoctor == NULL) {
            cout << "Nieprawidlowy numer lekarza!" << endl;
            exit(-1);
        }
    }

    addToPatientQueue(first, last, data, currentDoctor);

    return data;
}


// Tworzenie nowego lekarza
tDoctorData newDoctor() {

    tDoctorData data;

    cout << "" << endl;
    cout << "Imie: ";
    cin >> data.name;
    cout << "Nazwisko: ";
    cin >> data.surname;
    cout << "Specjalizacja: ";
    cin >> data.specialization;

    return data;
}

// Dodawanie nowego pacjenta
void addPatient(tPointer* f, tPointer* l, tDoctorPointer* df, tDoctorPointer* dl) {

    char addAnother;

    do {
        addToPatientQueue(f, l, newPatient(df, f, l), *df);
        cout << "Nowy pacjent!" << endl;
        cout << "Czy chcesz dodaæ kolejnego pacjenta? (T/N)";
        addAnother = toupper(getch());
    } while (addAnother == 'T');
}

// Dodawanie nowego lekarza
void addDoctor(tDoctorPointer* f, tDoctorPointer* l) {

    char addAnother;

    do {
        addToDoctorQueue(&(*f), &(*l), newDoctor());
        cout << "Nowy lekarz!" << endl;
        cout << "Czy chcesz dodaæ kolejnego lekarza? (T/N)";
        addAnother = toupper(getch());
    } while (addAnother == 'T');
}

string currentDate() {
    // obecna data z komputera
    time_t dateNow = time(0);

    // objekt biblioteki ctime
    tm* ltm = localtime(&dateNow);

    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    // obiekt std::ostringstream o nazwie oss, pomaga stworzyc ³añcuch znaków zawieraj¹cy datê
    ostringstream oss;
    oss << year << "-" << month << "-" << day;

    return oss.str();
}

// Zapis pacjentów do pliku
void savePatientsToFile(tPointer first) {
    string fileName = currentDate() + "_patients.txt";

    ofstream fileQueue(fileName.c_str());

    if (fileQueue.is_open()) {
        tPointer current = first;
        while (current != NULL) {
            fileQueue << "Imie: " << current->patientData.name << endl;
            fileQueue << "Nazwisko: " << current->patientData.surname << endl;
            fileQueue << "Rok urodzenia: " << current->patientData.birthDate.day
                      << " " << current->patientData.birthDate.month
                      << " " << current->patientData.birthDate.year << endl;
            fileQueue << "Lekarz: " << current->doctor->doctorData.name << " "
                      << current->doctor->doctorData.surname << endl;
            fileQueue << endl;

            current = current->next;
        }
        fileQueue.close();
        cout << "Pacjenci zostali zapisani do pliku." << endl;
    } else {
        cout << "Nie udalo sie otworzyc pliku." << endl;
    }
}

// Zapis lekarzy do pliku
void saveDoctorsToFile(tDoctorPointer first) {
    string fileName = currentDate() + "_doctors.txt";

    ofstream fileQueue(fileName.c_str());

    if (fileQueue.is_open()) {
        tDoctorPointer current = first;
        while (current != NULL) {
            fileQueue << "Imie: " << current->doctorData.name << endl;
            fileQueue << "Nazwisko: " << current->doctorData.surname << endl;
            fileQueue << "Specjalizacja: " << current->doctorData.specialization << endl;
            fileQueue << endl;

            current = current->next;
        }
        fileQueue.close();
    } else {
        cout << "Nie Udalo sie otworzyc pliku." << endl;
    }
}

void readPatientsFromFile(tPointer* first, tPointer* last, tDoctorPointer doctorQueue) {
    string fileName = currentDate() + "_patients.txt";
    ifstream fileQueue(fileName.c_str());

    if (!fileQueue) {
        cout << "Nie udalo sie otworzyc pliku." << endl;
        return;
    }

    tPatientData patient;
    string line;

    while (getline(fileQueue, line)) {
        if (line.find("Imie: ") != string::npos) {
            patient.name = line.substr(6);
        } else if (line.find("Nazwisko: ") != string::npos) {
            patient.surname = line.substr(10);
        } else if (line.find("Rok urodzenia: ") != string::npos) {
            getline(fileQueue, line);
            stringstream dateStream(line.substr(15));
            dateStream >> patient.birthDate.day >> patient.birthDate.month >> patient.birthDate.year;
        } else if(line.find("Lekarz: ") != string::npos) {
            getline(fileQueue, line);
            string doctorName = line.substr(8);
            tDoctorPointer currentDoctor = doctorQueue;
            bool doctorFound = false;

            while (currentDoctor != NULL) {
                if (currentDoctor->doctorData.name == doctorName) {
                    addToPatientQueue(first, last, patient, currentDoctor);
                    doctorFound = true;
                       break;
                }
                currentDoctor = currentDoctor->next;
            }

            if (!doctorFound) {
                cout << "Nie znaleziono lekarza o nazwie: " << doctorName << endl;
            }
        }
    }

    fileQueue.close();
    cout << "Pacjenci zostali odczytani z pliku." << endl;
}
// Odczyt lekarzy z pliku
void readDoctorsFromFile(tDoctorPointer* first, tDoctorPointer* last) {
    string fileName = currentDate() + "_doctors.txt";
    string text;
    ifstream fileQueue(fileName.c_str());

    tDoctorData doctor;

    while (getline(fileQueue, text)) {
        if (text.find("Imie: ") != string::npos) {
            doctor.name = text.substr(6); // Odczytujemy imiê
        } else if (text.find("Nazwisko: ") != string::npos) {
            doctor.surname = text.substr(10); // Odczytujemy nazwisko
        } else if (text.find("Specjalizacja: ") != string::npos) {
            doctor.specialization = text.substr(15); // Odczytujemy specjalizacjê
            addToDoctorQueue(first, last, doctor); // Dodajemy lekarza do kolejki
        }
    }

    fileQueue.close();
}

// Menu
void menu(tPointer* f, tPointer* l, tDoctorPointer* df, tDoctorPointer* dl) {
    char choice;

    do {
        system("cls");
        cout << "----- Przychodnia -----" << endl;
        cout << "1. Dodaj pacjenta" << endl;
        cout << "2. Dodaj lekarza" << endl;
        cout << "3. Wyswietl kolejki pacjentow" << endl;
        cout << "4. Wyswietl kolejke lekarzy" << endl;
        cout << "5. Zapisz pacjentow do pliku" << endl;
        cout << "6. Zapisz lekarzy do pliku" << endl;
        cout << "7. Odczytaj pacjentow z pliku" << endl;
        cout << "8. Odczytaj lekarzy z pliku" << endl;
        cout << "0. Wyjscie" << endl;
        cout << "" << endl;
        cout << "Wybierz opcje: ";
        cin >> choice;

        switch (choice) {
            case '1':
                addPatient(f, l, df, dl);
                break;
            case '2':
                addDoctor(df, dl);
                break;
            case '3':
                displayPatientQueueByDoctor(*f, *df);
                break;
            case '4':
                displayDoctorQueue(*df);
                break;
            case '5':
                savePatientsToFile(*f);
                break;
            case '6':
                saveDoctorsToFile(*df);
                break;
            case '7':
                readPatientsFromFile(f, l, *df);
                break;
            case '8':
                readDoctorsFromFile(df, dl);
                break;
            case '0':
                break;
            default:
                cout << "Nieprawidlowa opcja!" << endl;
                break;
        }

        cout << endl;
        system("pause");

    } while (choice != '0');
}

int main() {
    tPointer firstPatient = NULL;
    tPointer lastPatient = NULL;
    tDoctorPointer firstDoctor = NULL;
    tDoctorPointer lastDoctor = NULL;

    menu(&firstPatient, &lastPatient, &firstDoctor, &lastDoctor);

    return 0;
}
