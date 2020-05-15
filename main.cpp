#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#define ID 34

using namespace std;

int f()
{
    static int i = 0;
    i++;
    return i;
}

int g()
{
    const int j = ID;
    return j;
}

class farmacie
{
protected:
    int index;
    int id_lant;

public:
    farmacie()
    {
        this->index = f();
        this->id_lant = g();
    }

    farmacie(farmacie&);

    virtual void afisare(ostream &out) = 0;
    friend ostream& operator<<(ostream &out, farmacie& farmacie_obj);

    farmacie& operator=(farmacie& farmacie_obj);

    ~farmacie()
    {
        this->index = 0;
        this->id_lant = 0;
    }
};

farmacie::farmacie(farmacie &farmacie_obj)
{
    this->index = farmacie_obj.index;
    this->id_lant = farmacie_obj.id_lant;
}

farmacie& farmacie::operator=(farmacie& farmacie_obj)
{
    index = farmacie_obj.index;
    id_lant = farmacie_obj.id_lant;
}

class farmacie_fizica:public farmacie
{
private:
    string denumire;
    int nr_angajati;
    float profit_lunar[12];

public:
    farmacie_fizica()
    {
        this->nr_angajati = 0;
        for(int i = 0; i < 12; i++)
        {
            this->profit_lunar[i] = 0;
        }
    }

    farmacie_fizica(farmacie_fizica&);

    void citire(istream &in);
    void afisare(ostream &out);

    friend istream& operator>>(istream &in, farmacie& farmacie_obj);
    friend ostream& operator<<(ostream &out, farmacie& farmacie_obj);

    farmacie_fizica& operator=(farmacie_fizica& ff_obj);

    ~farmacie_fizica()
    {
        this->denumire.clear();
        this->nr_angajati = 0;
        for(int i = 0; i < 12; i++)
        {
            this->profit_lunar[i] = 0;
        }
    }
};

farmacie_fizica::farmacie_fizica(farmacie_fizica &ff_obj)
{
    this->denumire = ff_obj.denumire;
    this->nr_angajati = ff_obj.nr_angajati;
    for(int i = 0; i < 12; i++)
    {
        this->profit_lunar[i] = ff_obj.profit_lunar[i];
    }
}

farmacie_fizica& farmacie_fizica::operator=(farmacie_fizica& ff_obj)
{
    denumire = ff_obj.denumire;
    nr_angajati = ff_obj.nr_angajati;
    for(int i = 0; i < 12; i++)
        profit_lunar[i] = ff_obj.profit_lunar[i];
}

void farmacie_fizica::citire(istream &in)
{
    cout << "Denumire: ";
    in >> this->denumire;
    cout << "Nr. angajati: ";
    in >> this->nr_angajati;
}

istream& operator>>(istream& in, farmacie_fizica& ff_obj)
{
    ff_obj.citire(in);
    return in;
}

void farmacie_fizica::afisare(ostream &out)
{
    out << this->denumire;
    out << " ";
    out << nr_angajati;
    out << "\n";
}

ostream& operator<<(ostream& out, farmacie_fizica& ff_obj)
{
    ff_obj.afisare(out);
    return out;
}

class farmacie_online:public farmacie
{
private:
    string web;
    int nr_vizitatori;
    float discount;

public:
    farmacie_online()
    {
        this->nr_vizitatori = 0;
        this->discount = 0;
    }

    farmacie_online(int nr_viz, float disc)
    {
        this->nr_vizitatori = nr_viz;
        this->discount = disc;
    }

    farmacie_online(farmacie_online&);

    void citire(istream &in);
    void afisare(ostream &out);

    friend istream& operator>>(istream &in, farmacie& farmacie_obj);
    friend ostream& operator<<(ostream &out, farmacie& farmacie_obj);
    farmacie_online& operator=(farmacie_online& fo_obj);

    ~farmacie_online()
    {
        this->web.clear();
        this->nr_vizitatori = 0;
        this->discount = 0;
    }
};

farmacie_online::farmacie_online(farmacie_online &fo_obj)
{
    this->web = fo_obj.web;
    this->nr_vizitatori = fo_obj.nr_vizitatori;
    this->discount = fo_obj.discount;
}

farmacie_online& farmacie_online::operator=(farmacie_online& fo_obj)
{
    web = fo_obj.web;
    nr_vizitatori = fo_obj.nr_vizitatori;
    discount = fo_obj.discount;
}

void farmacie_online::citire(istream &in)
{
    cout << "Site-ul web: ";
    in >> this->web;
    cout << "Nr. vizitatori: ";
    in >> this->nr_vizitatori;
    cout << "Discount: ";
    in >> this->discount;
}

istream& operator>>(istream& in, farmacie_online& fo_obj)
{
    fo_obj.citire(in);
    return in;
}

void farmacie_online::afisare(ostream &out)
{
    out << this->web;
    out << " ";
    out << nr_vizitatori;
    out << "\n";
}

ostream& operator<<(ostream& out, farmacie_online& fo_obj)
{
    fo_obj.afisare(out);
    return out;
}

template <class T>
class GestionareFarmacii
{
protected:
    vector <T> lista_farmacii;

public:
    friend GestionareFarmacii<T>& operator+=(GestionareFarmacii<T>& gf_obj, farmacie_online& fo_obj)
    {
        gf_obj.lista_farmacii.push_back(fo_obj);
        return gf_obj;
    }
};

void menu_output()
{
    cout << "\nSilaghi Tudor-Adrian - 211 - Tema 6 - Farmacie: \n";
    cout << "\n\t MENIU:";
    cout << "\n===========================================\n\n";

    cout << "1. Citeste numarul de farmacii din lantul respectiv." << endl;
    cout << "2. Citeste farmaciile." << endl;
    cout << "3. Afiseaza farmaciile." << endl;
    cout << "4. Adauga o farmacie online." << endl;
    cout << "5. Afiseaza nr. total de vizitatori ai farmaciilor online." << endl;
    cout << "0. Iesire." << endl;
    /**Observatie: Mai intai citim nr. de farmacii, apoi citim date despre ele,
                iar abia apoi putem apasa tastele 3, 4 sau 5. */
}

void menu()
{
    int option = 0;
    GestionareFarmacii<farmacie> gf;
    farmacie_fizica *ff_obj = new farmacie_fizica;
    farmacie_online *fo_obj = new farmacie_online;
    int nr_farmacii = 0, i;
    string tip_farmacie;        //va fi "fizica" sau "online"

    do
    {
        menu_output();

        cout << "\nIntroduceti numarul actiunii: ";
        cin >> option;

        if (option == 1)
        {
            if(nr_farmacii > 0)
            {
                cout << "\nNu putem modifica nr. de farmacii de la tastatura ";
                cout << "(doar programul o poate face, adaugand eventual o farmacie online)";
            }
            else
            {
                cout << "Citeste numarul de farmacii: ";
                cin >> nr_farmacii;
            }
        } else if (option == 2)
        {
            for(i = 1; i <= nr_farmacii; i++)
            {
                cout << "Tipul farmaciei: ";
                cin >> tip_farmacie;
                try
                {
                    if(tip_farmacie == "fizica")
                    {
                        cin >> *ff_obj;
                    }
                    else if(tip_farmacie == "online")
                    {
                        cin >> *fo_obj;
                    }
                    else throw 1;
                }
                catch(bad_alloc var)
                {
                    cout << "Eroare!\n";
                    exit(EXIT_FAILURE);
                }
                catch(int e)
                {
                    cout << "Farmaciile sunt doar fizice sau online.";
                }
            }
        } else if (option == 0)
        {
            cout << "\nEXIT!\n";
        } else
        {
            cout << "\nSelectie invalida\n";
        }
        cout << "\n";
        system("pause");
        system("cls");
    }
    while(option != 0);

}

int main()
{
    menu();

    return 0;
}
