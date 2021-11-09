#include <iostream>
#include <windows.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

vector <Uzytkownik> rejestracja(vector <Uzytkownik> uzytkownicy)
{
    Uzytkownik nowyUzytkownik;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nowyUzytkownik.nazwa;
    int i = 0;
    while(i<uzytkownicy.size())
    {
         if(uzytkownicy[i].nazwa == nowyUzytkownik.nazwa)
         {
             cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika";
             cin >> nowyUzytkownik.nazwa;
             i =0;
         }
         else
         {
             i++;
         }

    }
    cout << "Podaj haslo: ";
    cin >> nowyUzytkownik.haslo;

    if(uzytkownicy.size()==0)
    {
        nowyUzytkownik.id =1;
    }
    else
    {
        nowyUzytkownik.id = uzytkownicy[uzytkownicy.size()-1].id+1;
    }
    uzytkownicy.push_back(nowyUzytkownik);
    cout<<"Konto zalozone"<<endl;
    Sleep(1000);
    return uzytkownicy;

}

int logowanie(vector <Uzytkownik> uzytkownicy)
{
    string nazwa, haslo;
    cout<<"Podaj nazwe: ";
    cin>>nazwa;
    int i = 0;
    while(i<uzytkownicy.size())
    {
         if(uzytkownicy[i].nazwa == nazwa)
         {
                for(int proba =0; proba < 3; proba++)
                {
                    cout <<"Podaj haslo. Pozostalo prob "<<3-proba <<": "; ;
                    cin>>haslo;
                    if(uzytkownicy[i].haslo == haslo)
                    {
                        cout<<"Zalogowales sie."<<endl;
                        Sleep(1000);
                        return uzytkownicy[i].id;

                    }
                }
                cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<<endl;
                Sleep(3000);
                return 0;
         }
         i++;

    }
    cout<<"Nie ma uzytkownika z takim logiem" <<endl;
    Sleep(2000);
    return 0;
}

vector <Uzytkownik> zmianaHasla(vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout <<"Podaj nowe haslo: ";
    cin>>haslo;
    for(int i = 0; i < uzytkownicy.size(); i++)
    {
        if(uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout <<"Haslo zostalo zmienieone" <<endl;
            Sleep(1500);
        }
    }
    return uzytkownicy;
}

void zapiszUzytkownikaWpliku(vector <Uzytkownik> uzytkownicy)
{
    fstream plikTekstowy;
    plikTekstowy.open("Uzytkownicy.txt", ios::out);
    if(plikTekstowy.good()==true)
    {
        for(int i =0; i<uzytkownicy.size(); i++)
        {
            plikTekstowy<<uzytkownicy[i].id<<"|";
            plikTekstowy<<uzytkownicy[i].nazwa<<"|";
            plikTekstowy<<uzytkownicy[i].haslo<<endl;
        }
        plikTekstowy.close();

    }
    else
    {
        cout<<"Nie mozna zapisac do pliku!"<<endl;
        plikTekstowy.close();
    }
}

Uzytkownik pobierzDaneZlinii(string liniaUzytkownika)
{
    Uzytkownik daneUzytkownika;

    vector <string> rozdzieloneElementy;

    stringstream pobierz(liniaUzytkownika);

    string elementy;

    while(getline(pobierz, elementy,'|'))
    {
        rozdzieloneElementy.push_back(elementy);
    }

    istringstream (rozdzieloneElementy[0]) >> daneUzytkownika.id;
    daneUzytkownika.nazwa = rozdzieloneElementy[1];
    daneUzytkownika.haslo =rozdzieloneElementy[2];

    return daneUzytkownika;
}

vector <Uzytkownik> wczytajUzytkownikowZpliku()
{
    fstream listaUzytkownikow;
    listaUzytkownikow.open("Uzytkownicy.txt", ios::in);
    string liniaJednegoUzytkownika;
    vector <Uzytkownik> odczytaniUzytkownicy;
    if(listaUzytkownikow.good()==true)
    {
        while(getline(listaUzytkownikow,liniaJednegoUzytkownika))
        {
            odczytaniUzytkownicy.push_back(pobierzDaneZlinii(liniaJednegoUzytkownika));
        }
        listaUzytkownikow.close();
    }
    return odczytaniUzytkownicy;
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    //int iloscUzytkownikow = 0;
    char wybor;
    uzytkownicy = wczytajUzytkownikowZpliku();
    while(1)
    {
        if(idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cin >> wybor;

            if(wybor == '1')
            {
                uzytkownicy = rejestracja(uzytkownicy);
            }
            else if(wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            }
            else if(wybor == '9')
            {
                zapiszUzytkownikaWpliku(uzytkownicy);
                exit(0);
            }
        }
        else
        {
            system("cls");
            cout<<"1. Zmiana hasla"<<endl;
            cout<<"2. Wylogowanie"<<endl;
            cin >> wybor;

            if(wybor == '1')
            {
                uzytkownicy = zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            }
            else if(wybor == '2')
            {
                idZalogowanegoUzytkownika = 0;
            }
        }
    }

    return 0;
}
