#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>

using namespace std;

struct Osoba
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

int dodajOsobe(Osoba osoby[], int &iloscOsob)
{
    string imie, nazwisko, numerTelefonu, email, adres;

    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> imie;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> nazwisko;

    /*int i=0;
    while(i<iloscPrzyjaciol)
    {
        if ((dane[i].imie==imie)&&(dane[i].nazwisko==nazwisko))
        {
            cout<< "Twoj przyjaciel istnieje juz w ksiazce adresowej"<<endl;
            i=0;
            Sleep(1500);
            return iloscPrzyjaciol;
        }
        else
        {
            i++;
        }
    }*/                  //jeszcze przydatna funkcja sprawdzajaca czy taki kontakt juz istnieje

    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj email uzytkownika: ";
    cin >> email;
    cout << "Podaj adres uzytkownika: ";
    cin.sync();
    getline(cin, adres);

    int osobaId = iloscOsob + 1;

    osoby[iloscOsob].id = osobaId;
    osoby[iloscOsob].imie = imie;
    osoby[iloscOsob].nazwisko = nazwisko;
    osoby[iloscOsob].numerTelefonu = numerTelefonu;
    osoby[iloscOsob].email = email;
    osoby[iloscOsob].adres = adres;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good())
    {
        plik << osoby[iloscOsob].id << endl;
        plik << osoby[iloscOsob].imie << endl;
        plik << osoby[iloscOsob].nazwisko << endl;
        plik << osoby[iloscOsob].numerTelefonu << endl;
        plik << osoby[iloscOsob].email << endl;
        plik << osoby[iloscOsob].adres << endl;

        plik.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    iloscOsob++;
    return iloscOsob;
}

int wczytajOsobyZPliku (Osoba osoby[], int &iloscOsob)
{
    string imie, nazwisko, numerTelefonu, email, adres;
    fstream plik;
    string linia;
    int nrLinii = 1;
    int i = 0;

    plik.open("KsiazkaAdresowa.txt", ios::in);
    if (plik.good() == false)
    {
        cout<<"Plik nie istnieje!";
        exit(0);
    }
    while(getline(plik, linia))
    {
        switch(nrLinii)
        {
            case 1: osoby[i].id = atoi(linia.c_str());            break;
            case 2: osoby[i].imie  = linia;                       break;
            case 3: osoby[i].nazwisko = linia;                    break;
            case 4: osoby[i].numerTelefonu = linia;               break;
            case 5: osoby[i].email = linia;                       break;
            case 6: osoby[i].adres = linia;                       break;
        }
        nrLinii++;
        if (nrLinii%7 == 0)
        {
            iloscOsob++;
            nrLinii = 1;
            i++;
        }
    }
    plik.close();

    return iloscOsob;
}

void wyszukajPoImieniu(Osoba osoby[], int &iloscOsob)
{
    string wyszukiwaneImie;
    int iloscZnalezionychOsobODanymImieniu = 0;
    cout<<"Podaj imie wyszukiwanej osoby: "<<endl;
    cin>>wyszukiwaneImie;
    system("cls");

    for (int i = 0; i < iloscOsob; i++)
        {
            if (osoby[i].imie == wyszukiwaneImie)
            {
                cout << endl;
                cout << "ID: " << osoby[i].id << endl;
                cout << osoby[i].imie << " " << osoby[i].nazwisko << endl;
                cout << "Telefon: " << osoby[i].numerTelefonu << endl;
                cout << "Email: " << osoby[i].email << endl;
                cout << "Adres: " << osoby[i].adres << endl;
                cout << endl;
                iloscZnalezionychOsobODanymImieniu++;
            }
        }
    if (iloscZnalezionychOsobODanymImieniu == 0)
    {
        cout << "Nie ma zapisanych osob o takim imieniu"<<endl;
        Sleep(1500);
    }
    system("pause");
}

void wyszukajPoNazwisku(Osoba osoby[], int &iloscOsob)
{
    string wyszukiwaneNazwisko;
    int iloscZnalezionychOsobODanymNazwisku = 0;
    cout<<"Podaj nazwisko wyszukiwanej osoby: "<<endl;
    cin>>wyszukiwaneNazwisko;
    system("cls");

    for (int i = 0; i < iloscOsob; i++)
    {
        if (osoby[i].nazwisko == wyszukiwaneNazwisko)
        {
            cout << endl;
            cout << "ID: " << osoby[i].id << endl;
            cout << osoby[i].imie << " " << osoby[i].nazwisko << endl;
            cout << "Telefon: " << osoby[i].numerTelefonu << endl;
            cout << "Email: " << osoby[i].email << endl;
            cout << "Adres: " << osoby[i].adres << endl;
            cout << endl;
            iloscZnalezionychOsobODanymNazwisku++;
        }
    }
    if (iloscZnalezionychOsobODanymNazwisku == 0)
    {
        cout << "Nie ma zapisanych osob o takim nazwisku"<<endl;
        Sleep(1500);
    }
    system("pause");
}

int main()
{
    Osoba osoby[1000];
    string imie, nazwisko, numerTelefonu, email, adres;
    int iloscOsob = 0;
    iloscOsob = wczytajOsobyZPliku(osoby, iloscOsob);
    char wybor;

    while (true)
    {
        system("cls");
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyswietl kontakty" << endl;
        cout << "3. Wyszukaj po imieniu" << endl;
        cout << "4. Wyszukaj po nazwisku" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            iloscOsob = dodajOsobe(osoby, iloscOsob);
        }
        else if (wybor == '2')
        {
            system("cls");

            for (int i=0; i<iloscOsob; i++)
            {
            cout<<osoby[i].id<<endl;
            cout<<osoby[i].imie<<endl;
            cout<<osoby[i].nazwisko<<endl;
            cout<<osoby[i].numerTelefonu<<endl;
            cout<<osoby[i].email<<endl;
            cout<<osoby[i].adres<<endl;
            }
            getch();
        }
        else if (wybor == '3')
        {
            wyszukajPoImieniu(osoby, iloscOsob);
        }
        else if (wybor == '4')
        {
            wyszukajPoNazwisku(osoby, iloscOsob);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }
    return 0;
}
