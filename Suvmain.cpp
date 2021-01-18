#include "Suvmain.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include "Osoba.h"
#include "Sport.h"
#include "Funkcija.h"
#include "Clan.h"
#include "tinyxml2.h"
#include "CppConsoleTable.hpp"
#include "algorithm"
#include <sstream>
using namespace tinyxml2;
using namespace std;
using ConsoleTable = samilton::ConsoleTable;
ConsoleTable table;
// Preuzeto sa https://github.com/DenisSamilton/CppConsoleTable
int Provjera = 1;
Suvmain::Suvmain()
{
}
void Suvmain::GlavniIzbornik()
{
    system("cls");
    int Odabir;
    string naziv;
    cout << "Glavni izbornik:" << endl;
    cout << "1. Pregled svih clanova" << endl;
    cout << "2. Dodavanje sportova" << endl;
    cout << "3. Dodavanje clanova" << endl;
    cout << "4. Azuriranje funkcija clanova" << endl;
    cout << "5. Brisanje clanova" << endl;
    cout << "6. Statistika" << endl;
    cout << "7. Izlaz iz glavnog izbornika " << endl;
    cout << "Upisite broj za odgovarajuci izbornik koji zelite pokrenuti : " << endl;
    cin >> Odabir;
    switch (Odabir)
    {
    case 1:
        system("cls");
        IspisiSveClanove();
        PovratakUIzbornik();
        break;
    case 2:
        system("cls");
        DodajSport();
        PovratakUIzbornik();
        break;
    case 3:
        system("cls");
        cout << "Dodavanje clanova " << endl;
        DodajClana();
        PovratakUIzbornik();
        break;
    case 4:
        system("cls");
        cout << "Azuriranje funkcija clanova :" << endl;
        AzurirajClana();
        PovratakUIzbornik();
        break;
    case 5:
        system("cls");
        cout << "Brisanje clanova :" << endl;
        ObrisiClana();
        PovratakUIzbornik();
        break;
    case 6:
        system("cls");
        cout << "Statistika :" << endl;
        Statistike();
        PovratakUIzbornik();
    case 7:
        system("cls");
        exit(0);
    }
}
struct sortiranje_prezimena_pa_imena
{
    inline bool operator() (const Osoba* const p1, const Osoba* const p2)
    {
        if (p1->m_sPrezime < p2->m_sPrezime)
            return true;
        else if (p1->m_sPrezime == p2->m_sPrezime && p1->m_sIme < p2->m_sIme)
            return true;
    } // Sortiranje po prezimenu pa po imenu
};
struct sortiranje_zastupljenosti_pa_imena
{
    inline bool operator() (const Sport* const p1, const Sport* const p2)
    {
        return(p1->UkupnaZastupljenost < p2->UkupnaZastupljenost);
    } // Sortiranje ukupnoj zastupljenosti
};
void Suvmain::IspisiSveClanove()
{
    m_vSport.clear();
    m_vFunkcija.clear();
    m_vOsobe.clear();
    m_vClanovi.clear();
    XMLDocument oXmlDocument;
    oXmlDocument.LoadFile("sportovi.xml");
    XMLElement* pRoot = oXmlDocument.FirstChildElement("dataset");
    XMLElement* pChild;
    //Ucitavanje sportova iz sportovi.xml u vektor m_vSport
    for (pChild = pRoot->FirstChildElement("Sport"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDSporta = pChild->Attribute("id");
        string NazivSporta = pChild->Attribute("nazivsporta");
        m_vSport.push_back(new Sport(IDSporta, NazivSporta));
    } 
    oXmlDocument.LoadFile("funkcije.xml");
    //Ucitavanje funkcija iz funkcije.xml u vektor m_vFunkcija
    for (pChild = pRoot->FirstChildElement("Funkcija"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDFunkcije = pChild->Attribute("id");
        string NazivFunkcije = pChild->Attribute("nazivfunkcije");
        m_vFunkcija.push_back(new Funkcija(IDFunkcije, NazivFunkcije));
    }
    oXmlDocument.LoadFile("clanovi.xml");
    // Ucitavanje clanova iz clanovi.xml u vektore m_vOsobe i m_vClanovi
    for (pChild = pRoot->FirstChildElement("Clan"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        int ID = atoi(pChild->Attribute("id"));
        string Prezime = pChild->Attribute("prezime");
        string Ime = pChild->Attribute("ime");
        string DatumRodenja = pChild->Attribute("datumrodenja");
        string Email = pChild->Attribute("email");
        vector<Sport*>m_vSportovi;
        vector<string>Rastavljac;
        string IDSport = pChild->Attribute("sport");
        stringstream ss_stream(IDSport);
        while (ss_stream.good())
        {
            string NoviString;
            getline(ss_stream, NoviString, ',');
            Rastavljac.push_back(NoviString);
        }
        for (int i = 0; i < Rastavljac.size(); i++)
        {
            for (int j = 0; j < m_vSport.size(); j++)
            {
                if (Rastavljac[i] == m_vSport[j]->m_sIDSporta)
                {
                    m_vSportovi.push_back(new Sport(m_vSport[j]->m_sIDSporta,m_vSport[j]->m_sImeSporta));
                }
            }
        }
        vector<Funkcija*>m_vFunkcije;
        vector<string>Rastavljacc;
        string IDFunkcije = pChild->Attribute("funkcije");
        stringstream s_stream(IDFunkcije);
        while (s_stream.good())
        {
            string NoviStringg;
            getline(s_stream, NoviStringg, ',');
            Rastavljacc.push_back(NoviStringg);
        }
        for (int i = 0; i < Rastavljacc.size(); i++)
        {
            for (int j = 0; j < m_vFunkcija.size(); j++)
            {
                if (Rastavljacc[i] == m_vFunkcija[j]->m_sIDFunkcije)
                {
                    m_vFunkcije.push_back(new Funkcija(m_vFunkcija[j]->m_sIDFunkcije, m_vFunkcija[j]->m_sImeFunkcije));
                }
            }
        }
        int PlaceneClanarine = atoi(pChild->Attribute("placeneclanarine"));
        m_vOsobe.push_back(new Osoba(ID, Prezime, Ime, DatumRodenja, Email));
        m_vClanovi.push_back(new Clan(ID,m_vSportovi, m_vFunkcije, PlaceneClanarine));
    }
    sort(m_vOsobe.begin(), m_vOsobe.end(), sortiranje_prezimena_pa_imena());
    // Tablicni ispis osoba sortiranih po prezimenu pa po imenu
    for (int i = 0; i < m_vOsobe.size(); i++)
    {
        for (int j = 0; j < m_vClanovi.size(); j++)
        {
            if (m_vOsobe[i]->m_nID == m_vClanovi[j]->m_nID)
            {
                int brojac = 0;
                table[0][0] = "R.br";
                table[0][1] = "ID";
                table[0][2] = "Prezime";
                table[0][3] = "Ime";
                table[0][4] = "Datum Rodenja";
                table[0][5] = "Email";
                table[0][6] = "Sport";
                table[0][7] = "Funkcije";
                table[0][8] = "Placene clanarine";
                table[Provjera][0] = Provjera;
                table[Provjera][1] = m_vOsobe[i]->m_nID;
                table[Provjera][2] = m_vOsobe[i]->m_sPrezime;
                table[Provjera][3] = m_vOsobe[i]->m_sIme;
                table[Provjera][4] = m_vOsobe[i]->m_sDatumRodenja;
                table[Provjera][5] = m_vOsobe[i]->m_sEmail;
                string ss = "";
                for (int k = 0; k < m_vClanovi[j]->m_vSport.size(); k++)
                {
                    ss += m_vClanovi[j]->m_vSport[k]->m_sImeSporta;
                    ss += ", ";
                }
                if (!ss.empty())
                {
                    ss.pop_back();
                    ss.pop_back();
                }
                table[Provjera][6] = ss;
                string s = "";
                for (int k = 0; k < m_vClanovi[j]->m_vFunkcija.size(); k++)
                {
                    s += m_vClanovi[j]->m_vFunkcija[k]->m_sImeFunkcije;
                    s += ", ";
                }
                if (!s.empty())
                {
                    s.pop_back();
                    s.pop_back();
                }
                table[Provjera][7] = s;
                table[Provjera][8] = m_vClanovi[j]->m_nPlaceneClanarine;
                if (Provjera == m_vClanovi.size())
                {
                    cout << table;
                    Provjera = 1;
                }
                else
                {
                    Provjera++;
                }
                brojac = brojac + 1;
            }
        }
    }
}
void Suvmain::DodajSport()
{
    m_vSport.clear();
    m_vFunkcija.clear();
    m_vOsobe.clear();
    m_vClanovi.clear();
    int RedniBroj;
    XMLDocument oXmlDocument;
    oXmlDocument.LoadFile("sportovi.xml");
    XMLElement* pRoot = oXmlDocument.FirstChildElement("dataset");
    XMLElement* pChild;
    //Ucitavanje sportova iz sportovi.xml u vektor m_vSport
    for (pChild = pRoot->FirstChildElement("Sport"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDSporta = pChild->Attribute("id");
        string NazivSporta = pChild->Attribute("nazivsporta");
        RedniBroj = atoi(pChild->Attribute("id"));
        m_vSport.push_back(new Sport(IDSporta, NazivSporta));
    }
    //Ispis svih sportova iz vektora m_vSport
    for (int i = 0; i < m_vSport.size(); i++)
    {
        cout << "ID Sporta : " << m_vSport[i]->m_sIDSporta << " || " << m_vSport[i]->m_sImeSporta << endl;
    }
    cout << "Unesite naziv sporta koji zelite dodati :";
    string naziv;
    cin >> naziv;
    // Provjera ako postoji sport sa tim nazivom
    for (int i = 0; i < m_vSport.size(); i++)
    {
        if (naziv == m_vSport[i]->m_sImeSporta)
        {
            cout << "Unesli ste sport koji vec postoji." << endl;
            PovratakUIzbornik();
            exit(0);
        }
    }
    RedniBroj = RedniBroj + 1;
    XMLElement* pElement = oXmlDocument.NewElement("Sport");
    pElement->SetAttribute("id", RedniBroj);
    pElement->SetAttribute("nazivsporta", naziv.c_str());
    pRoot->InsertEndChild(pElement);
    XMLError eResult = oXmlDocument.SaveFile("sportovi.xml");
}
void Suvmain::DodajClana()
{
    m_vSport.clear();
    m_vFunkcija.clear();
    m_vOsobe.clear();
    m_vClanovi.clear();
    XMLDocument oXmlDocument;
    oXmlDocument.LoadFile("sportovi.xml");
    XMLElement* pRoot = oXmlDocument.FirstChildElement("dataset");
    XMLElement* pChild;
    //Ucitavanje sportova iz sportovi.xml u vektor m_vSport
    for (pChild = pRoot->FirstChildElement("Sport"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDSporta = pChild->Attribute("id");
        string NazivSporta = pChild->Attribute("nazivsporta");
        m_vSport.push_back(new Sport(IDSporta, NazivSporta));
    }
    oXmlDocument.LoadFile("funkcije.xml");
    //Ucitavanje funkcija iz funkcije.xml u vektor m_vFunkcija
    for (pChild = pRoot->FirstChildElement("Funkcija"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDFunkcije = pChild->Attribute("id");
        string NazivFunkcije = pChild->Attribute("nazivfunkcije");
        m_vFunkcija.push_back(new Funkcija(IDFunkcije, NazivFunkcije));
    }
    oXmlDocument.LoadFile("clanovi.xml");
    // Ucitavanje clanova iz clanovi.xml u vektore m_vOsobe i m_vClanovi
    for (pChild = pRoot->FirstChildElement("Clan"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        int ID = atoi(pChild->Attribute("id"));
        string Prezime = pChild->Attribute("prezime");
        string Ime = pChild->Attribute("ime");
        string DatumRodenja = pChild->Attribute("datumrodenja");
        string Email = pChild->Attribute("email");
        vector<Sport*>m_vSportovi;
        vector<string>Rastavljac;
        string IDSport = pChild->Attribute("sport");
        stringstream ss_stream(IDSport);
        while (ss_stream.good())
        {
            string NoviString;
            getline(ss_stream, NoviString, ',');
            Rastavljac.push_back(NoviString);
        }
        for (int i = 0; i < Rastavljac.size(); i++)
        {
            for (int j = 0; j < m_vSport.size(); j++)
            {
                if (Rastavljac[i] == m_vSport[j]->m_sIDSporta)
                {
                    m_vSportovi.push_back(new Sport(m_vSport[j]->m_sIDSporta, m_vSport[j]->m_sImeSporta));
                }
            }
        }
        vector<Funkcija*>m_vFunkcije;
        vector<string>Rastavljacc;
        string IDFunkcije = pChild->Attribute("funkcije");
        stringstream s_stream(IDFunkcije);
        while (s_stream.good())
        {
            string NoviStringg;
            getline(s_stream, NoviStringg, ',');
            Rastavljacc.push_back(NoviStringg);
        }
        for (int i = 0; i < Rastavljacc.size(); i++)
        {
            for (int j = 0; j < m_vFunkcija.size(); j++)
            {
                if (Rastavljacc[i] == m_vFunkcija[j]->m_sIDFunkcije)
                {
                    m_vFunkcije.push_back(new Funkcija(m_vFunkcija[j]->m_sIDFunkcije, m_vFunkcija[j]->m_sImeFunkcije));
                }
            }
        }
        int PlaceneClanarine = atoi(pChild->Attribute("placeneclanarine"));
        m_vOsobe.push_back(new Osoba(ID, Prezime, Ime, DatumRodenja, Email));
        m_vClanovi.push_back(new Clan(ID, m_vSportovi, m_vFunkcije, PlaceneClanarine));
    }
    string Prezime, Ime, DatumRodenja, IDSport, IDFunkcije, Email;
    int ID, PlaceneClanarine;
    cout << "Unesite ID novog clana : " << endl;
    cin >> ID;
    // Provjera postoji li ID tog clana vec
    for (int i = 0; i < m_vClanovi.size(); i++)
    {
        if (ID == m_vClanovi[i]->m_nID)
        {
            cout << "ID Vec postoji, pokusajte ponovno!" << endl;
            PovratakUIzbornik();
            exit(0);
        }
    }
    system("cls");
    cout << "Unesite Prezime novog clana : " << endl;
    cin >> Prezime;
    system("cls");
    cout << "Unesite Ime novog clana : " << endl;
    cin >> Ime;
    system("cls");
    cout << "Unesite datum rodenja novog clana ( u obliku DD.M.YYYY ) : " << endl;
    cin >> DatumRodenja;
    system("cls");
    cout << "Unesite E-mail novog clana :" << endl;
    cin >> Email;
    system("cls");
    // Ispis svih clanova vektora m_vSport
    for (int i = 0; i < m_vSport.size(); i++)
    {
        cout << "ID Sporta : " << m_vSport[i]->m_sIDSporta << " || " << m_vSport[i]->m_sImeSporta << endl;
    }
    cout << "Unesite sa koliko sportova se clan bavi (ako se clan ne bavi sportom upisite 0)" << endl;
    int KolikoSportova;
    cin >> KolikoSportova;
    vector<string>vIDoviSportova;
    //Unos broja sportova koliko je korisnik unesao sa tipkovnice
    if (KolikoSportova > 0)
    {
        for (int i = 0; i < KolikoSportova; i++)
        {
            cout << "Unesite ID sporta kojim se clan bavi : " << endl;
            cin >> IDSport;
            vIDoviSportova.push_back(IDSport);
        }
    }
    //Ako je broj 0 spremi NULL (nista)
    else
    {
        KolikoSportova = NULL;
    }
    system("cls");
    //Ispis svih clanova funkcija vektora m_vFunkcija
    for (int i = 0; i < m_vFunkcija.size(); i++)
    {
        cout << "ID Funkcije : " << m_vFunkcija[i]->m_sIDFunkcije << " || " << m_vFunkcija[i]->m_sImeFunkcije << endl;
    }
    cout << "Unesite koliko funkcija ovaj clan ima (ako clan nema funkcije unesite 0)" << endl;
    int KolikoFunkcija;
    cin >> KolikoFunkcija;
    vector<string>vIDoviFunkcija;
    int brojacno = 0;
    int brojacio = 0;
    //Brojac koji broji koliko ljudi ima u nadzbornom i izvrsnom odboru
    for (int i = 0; i < m_vClanovi.size(); i++)
    {
        for (int j = 0; j < m_vClanovi[i]->m_vFunkcija.size(); j++)
        {
            if (m_vClanovi[i]->m_vFunkcija[j]->m_sIDFunkcije == "5")
            {
                brojacno = brojacno + 1;
            }
            if (m_vClanovi[i]->m_vFunkcija[j]->m_sIDFunkcije == "6")
            {
                brojacio = brojacio + 1;
            }
        }
    }
    //Spremanje ID-ova funkcija koji se unose tom clanu
    if (KolikoFunkcija > 0)
    {
        for (int i = 0; i < KolikoFunkcija; i++)
        {
            cout << "Unesite ID funkcije kojom se clan bavi: " << endl;
            cin >> IDFunkcije;
            if (IDFunkcije == "6")
            {
                if (brojacio == 5)
                {
                    cout << "Izvrsni odbor vec ima 5 clanova..." << endl;
                    exit(0);
                }
            }
            if (IDFunkcije == "5")
            {
                if (brojacno == 3)
                {
                    cout << "Nadzorni odbor vec ima 3 clana..." << endl;
                    exit(0);
                }
            }
            vIDoviFunkcija.push_back(IDFunkcije);
        }
    }
    //Ako je broj 0 spremi NULL (nista)
    else
    {
        KolikoFunkcija = NULL;
    }
    system("cls");
    cout << "Unesite zadnju godinu kada je clan platio clanarinu" << endl;
    cin >> PlaceneClanarine;
    system("cls");
    XMLDocument oXmlDoc;
    oXmlDoc.LoadFile("clanovi.xml");
    XMLElement* pRoot1 = oXmlDoc.FirstChildElement("dataset");
    XMLElement* pElement1 = oXmlDoc.NewElement("Clan");
    pElement1->SetAttribute("id", ID);
    pElement1->SetAttribute("prezime", Prezime.c_str());
    pElement1->SetAttribute("ime", Ime.c_str());
    pElement1->SetAttribute("datumrodenja", DatumRodenja.c_str());
    pElement1->SetAttribute("email", Email.c_str());
    IDSport = "";
    // Odvajanje zarezom
    for (int i = 0; i < vIDoviSportova.size(); i++)
    {
        IDSport += vIDoviSportova[i];
        IDSport += ",";
    }
    // Brisanje zareza sa kraja
    if (!IDSport.empty())
    {
        IDSport.pop_back();
    }
    pElement1->SetAttribute("sport", IDSport.c_str());
    IDFunkcije = "";
    // Odvajanje zarezom
    for (int i = 0; i < vIDoviFunkcija.size(); i++)
    {
        IDFunkcije += vIDoviFunkcija[i];
        IDFunkcije += ",";
    }
    // Brisanje zareza sa kraja
    if (!IDFunkcije.empty())
    {
        IDFunkcije.pop_back();
    }
    pElement1->SetAttribute("funkcije", IDFunkcije.c_str());
    pElement1->SetAttribute("placeneclanarine", PlaceneClanarine);
    pRoot1->InsertEndChild(pElement1);
    oXmlDoc.SaveFile("clanovi.xml");
}
void Suvmain::AzurirajClana()
{
    m_vSport.clear();
    m_vFunkcija.clear();
    m_vOsobe.clear();
    m_vClanovi.clear();
    int unos;
    string Email;
    XMLDocument oXmlDocument;
    oXmlDocument.LoadFile("sportovi.xml");
    XMLElement* pRoot = oXmlDocument.FirstChildElement("dataset");
    XMLElement* pChild;
    //Ucitavanje sportova iz sportovi.xml u vektor m_vSport
    for (pChild = pRoot->FirstChildElement("Sport"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDSporta = pChild->Attribute("id");
        string NazivSporta = pChild->Attribute("nazivsporta");
        m_vSport.push_back(new Sport(IDSporta, NazivSporta));
    }
    oXmlDocument.LoadFile("funkcije.xml");
    //Ucitavanje funkcija iz funkcije.xml u vektor m_vFunkcija
    for (pChild = pRoot->FirstChildElement("Funkcija"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDFunkcije = pChild->Attribute("id");
        string NazivFunkcije = pChild->Attribute("nazivfunkcije");
        m_vFunkcija.push_back(new Funkcija(IDFunkcije, NazivFunkcije));
    }
    oXmlDocument.LoadFile("clanovi.xml");
    // Ucitavanje clanova iz clanovi.xml u vektore m_vOsobe i m_vClanovi
    for (pChild = pRoot->FirstChildElement("Clan"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        int ID = atoi(pChild->Attribute("id"));
        string Prezime = pChild->Attribute("prezime");
        string Ime = pChild->Attribute("ime");
        string DatumRodenja = pChild->Attribute("datumrodenja");
        string Email = pChild->Attribute("email");
        vector<Sport*>m_vSportovi;
        vector<string>Rastavljac;
        string IDSport = pChild->Attribute("sport");
        stringstream ss_stream(IDSport);
        while (ss_stream.good())
        {
            string NoviString;
            getline(ss_stream, NoviString, ',');
            Rastavljac.push_back(NoviString);
        }
        for (int i = 0; i < Rastavljac.size(); i++)
        {
            for (int j = 0; j < m_vSport.size(); j++)
            {
                if (Rastavljac[i] == m_vSport[j]->m_sIDSporta)
                {
                    m_vSportovi.push_back(new Sport(m_vSport[j]->m_sIDSporta, m_vSport[j]->m_sImeSporta));
                }
            }
        }
        vector<Funkcija*>m_vFunkcije;
        vector<string>Rastavljacc;
        string IDFunkcije = pChild->Attribute("funkcije");
        stringstream s_stream(IDFunkcije);
        while (s_stream.good())
        {
            string NoviStringg;
            getline(s_stream, NoviStringg, ',');
            Rastavljacc.push_back(NoviStringg);
        }
        for (int i = 0; i < Rastavljacc.size(); i++)
        {
            for (int j = 0; j < m_vFunkcija.size(); j++)
            {
                if (Rastavljacc[i] == m_vFunkcija[j]->m_sIDFunkcije)
                {
                    m_vFunkcije.push_back(new Funkcija(m_vFunkcija[j]->m_sIDFunkcije, m_vFunkcija[j]->m_sImeFunkcije));
                }
            }
        }
        int PlaceneClanarine = atoi(pChild->Attribute("placeneclanarine"));
        m_vOsobe.push_back(new Osoba(ID, Prezime, Ime, DatumRodenja, Email));
        m_vClanovi.push_back(new Clan(ID, m_vSportovi, m_vFunkcije, PlaceneClanarine));
    }
    int brojacno = 0;
    int brojacio = 0;
    // Brojac koji broji koliko clanova ima u nadzornom a koliko u izvrsnom odboru
    for (int i = 0; i < m_vClanovi.size(); i++)
    {
        for (int j = 0; j < m_vClanovi[i]->m_vFunkcija.size(); j++)
        {
            if (m_vClanovi[i]->m_vFunkcija[j]->m_sIDFunkcije == "5")
            {
                brojacno = brojacno + 1;
            }
            if (m_vClanovi[i]->m_vFunkcija[j]->m_sIDFunkcije == "6")
            {
                brojacio = brojacio + 1;
            }
        }
    }
    IspisiSveClanove();
    cout << "Unesite ID clana kako bi mu promjenili podatak" << endl;
    cin >> unos;
    system("cls");
    IspisiSveClanove();
    int SmartVarijabla = 0;
    // Azuriranje podataka postojecem clanu
    for (int i = 0; i < m_vOsobe.size(); i++)
    {
        for (int j = 0; j < m_vClanovi.size(); j++)
        {
            if (unos == m_vClanovi[j]->m_nID && unos == m_vOsobe[i]->m_nID)
            {
                SmartVarijabla = 1;
                cout << "Koji podatak zelite odabranom clanu promjeniti?" << endl;
                cout << " 1. ID" << endl;
                cout << " 2. Prezime" << endl;
                cout << " 3. Ime" << endl;
                cout << " 4. Datum rodenja" << endl;
                cout << " 5. Email" << endl;
                cout << " 6. ID Sportova kojim se clan bavi (ponovni upis svih ID-ova)" << endl;
                cout << " 7. ID Funkcija koje clan ima (ponovni upis svih ID-ova)" << endl;
                cout << " 8. Godinu placanja zadnje clanarine" << endl;
                string Prezime, Ime, DatumRodenja, IDSport, IDFunkcije;
                int podatak, placenaclanarina;
                cin >> podatak;
                switch (podatak)
                {
                case 1:
                    system("cls");
                    IspisiSveClanove();
                    cout << "Unesite novi ID clana" << endl;
                    int ID;
                    cin >> ID;
                    if (ID == m_vOsobe[i]->m_nID)
                    {
                        cout << "ID Vec postoji, pokusajte ponovno!" << endl;
                        PovratakUIzbornik();
                        exit(0);
                    }
                    m_vOsobe[i]->m_nID = ID;
                    m_vClanovi[j]->m_nID = ID;
                    break;
                case 2:
                    system("cls");
                    IspisiSveClanove();
                    cout << "Unesite novo prezime clana" << endl;
                    cin >> Prezime;
                    m_vOsobe[i]->m_sPrezime = Prezime;
                    break;
                case 3:
                    system("cls");
                    IspisiSveClanove();
                    cout << "Unesite novo ime clana" << endl;
                    cin >> Ime;
                    m_vOsobe[i]->m_sIme = Ime;
                    break;
                case 4:
                    system("cls");
                    IspisiSveClanove();
                    cout << "Unesite novi datum rodenja clana u obliku DD.MM.YYYY" << endl;
                    cin >> DatumRodenja;
                    m_vOsobe[i]->m_sDatumRodenja = DatumRodenja;
                    break;
                case 5:
                    system("cls");
                    IspisiSveClanove();
                    cout << "Unesite novi e-mail" << endl;
                    cin >> Email;
                    m_vOsobe[i]->m_sEmail = Email;
                    break;
                case 6:
                    m_vClanovi[j]->m_vSport.clear();
                    system("cls");
                    IspisiSveClanove();
                    for (int i = 0; i < m_vSport.size(); i++)
                    {
                        cout << "ID Funkcije : " << m_vSport[i]->m_sIDSporta << " || " << m_vSport[i]->m_sImeSporta<< endl;
                    }
                    cout << "Unesite novi broj sportova sa kojima se clan bavi (ako se clan ne bavi sportom upisite 0)" << endl;
                    int KolikoSportova;
                    cin >> KolikoSportova;
                    m_vClanovi[j]->m_vSport.clear();
                    if (KolikoSportova > 0)
                    {
                        for (int k = 0; k < KolikoSportova; k++)
                        {
                            cout << "Unesite ID sporta kojim se clan bavi : " << endl;
                            cin >> IDSport;
                            m_vClanovi[j]->m_vSport.push_back(new Sport(IDSport, m_vSport[j]->m_sImeSporta));
                        }
                    }
                    else
                    {
                        KolikoSportova = NULL;
                    }
                    break;
                case 7:
                    m_vClanovi[j]->m_vFunkcija.clear();
                    system("cls");
                    IspisiSveClanove();
                    for (int i = 0; i < m_vFunkcija.size(); i++)
                    {
                        cout << "ID Funkcije : " << m_vFunkcija[i]->m_sIDFunkcije << " || " << m_vFunkcija[i]->m_sImeFunkcije << endl;
                    }
                    cout << "Unesite koliko funkcija ovaj clan ima (ako clan nema funkcije unesite 0)" << endl;
                    int KolikoFunkcija;
                    cin >> KolikoFunkcija;
                    m_vClanovi[j]->m_vFunkcija.clear();
                    if (KolikoFunkcija > 0)
                    {
                        for (int k = 0; k < KolikoFunkcija; k++)
                        {
                            cout << "Unesite ID funkcije kojom se clan bavi: " << endl;
                            cin >> IDFunkcije;
                            if (IDFunkcije == "6")
                            {
                                if (brojacio == 5)
                                {
                                    cout << "Izvrsni odbor vec ima 5 clanova..." << endl;
                                    PovratakUIzbornik();
                                    exit(0);
                                }
                            }
                            if (IDFunkcije == "5")
                            {
                                if (brojacno == 3)
                                {
                                    cout << "Nadzorni odbor vec ima 3 clana..." << endl;
                                    PovratakUIzbornik();
                                    exit(0);
                                }
                            }
                            if (brojacio != 5 && brojacno != 5)
                            {
                                m_vClanovi[j]->m_vFunkcija.push_back(new Funkcija(IDFunkcije, m_vFunkcija[j]->m_sImeFunkcije));
                            }
                        }
                    }
                    else
                    {
                        KolikoFunkcija = NULL;
                    }
                    break;
                case 8:
                    cout << "Unesite zadnju godinu placanja clanarine clanu " << endl;
                    cin >> placenaclanarina;
                    m_vClanovi[j]->m_nPlaceneClanarine = placenaclanarina;
                    break;
                }
            }
        }
    } 
    // Ako nismo pronasli clana vracamo se u glavni izbornik
    if (SmartVarijabla == 0)
    {
        cout << "Ne postoji clan sa navedenim ID-om" << endl;
        PovratakUIzbornik();
        exit(0);
    }
    oXmlDocument.LoadFile("clanovi.xml");
    XMLElement* pRoots = oXmlDocument.FirstChildElement("dataset");
    pRoots->DeleteChildren();
    XMLError eResult = oXmlDocument.SaveFile("clanovi.xml");
    XMLDocument oXmlDoc;
    oXmlDoc.LoadFile("clanovi.xml");
    XMLElement* pRoot1 = oXmlDoc.FirstChildElement("dataset");
    string IDSport, IDFunkcije;
    // Ako smo pronasli clana spremi azurirane vrijednosti u clanovi.xml
    if (SmartVarijabla == 1)
    {
        for (int i = 0; i < m_vOsobe.size(); i++)
        {
            for (int j = 0; j < m_vClanovi.size(); j++)
            {
                if (m_vClanovi[j]->m_nID == m_vOsobe[i]->m_nID)
                {
                    XMLElement* pElement1 = oXmlDoc.NewElement("Clan");
                    pElement1->SetAttribute("id", m_vOsobe[i]->m_nID);
                    pElement1->SetAttribute("prezime", m_vOsobe[i]->m_sPrezime.c_str());
                    pElement1->SetAttribute("ime", m_vOsobe[i]->m_sIme.c_str());
                    pElement1->SetAttribute("datumrodenja", m_vOsobe[i]->m_sDatumRodenja.c_str());
                    pElement1->SetAttribute("email", m_vOsobe[i]->m_sEmail.c_str());
                    IDSport = "";
                    for (int k = 0; k < m_vClanovi[j]->m_vSport.size(); k++)
                    {
                        IDSport += m_vClanovi[j]->m_vSport[k]->m_sIDSporta;
                        IDSport += ",";
                    }
                    if (!IDSport.empty())
                    {
                        IDSport.pop_back();
                    }
                    pElement1->SetAttribute("sport", IDSport.c_str());
                    IDFunkcije = "";
                    for (int k = 0; k < m_vClanovi[j]->m_vFunkcija.size(); k++)
                    {
                        IDFunkcije += m_vClanovi[j]->m_vFunkcija[k]->m_sIDFunkcije;
                        IDFunkcije += ",";
                    }
                    if (!IDFunkcije.empty())
                    {
                        IDFunkcije.pop_back();
                    }
                    pElement1->SetAttribute("funkcije", IDFunkcije.c_str());
                    pElement1->SetAttribute("placeneclanarine", m_vClanovi[j]->m_nPlaceneClanarine);
                    pRoot1->InsertEndChild(pElement1);
                }
            }
            oXmlDoc.SaveFile("clanovi.xml");
        }
    }
}
void Suvmain::ObrisiClana()
{
    m_vSport.clear();
    m_vFunkcija.clear();
    m_vOsobe.clear();
    m_vClanovi.clear();
    int unos;
    XMLDocument oXmlDocument;
    oXmlDocument.LoadFile("sportovi.xml");
    XMLElement* pRoot = oXmlDocument.FirstChildElement("dataset");
    XMLElement* pChild;
    //Ucitavanje sportova iz sportovi.xml u vektor m_vSport
    for (pChild = pRoot->FirstChildElement("Sport"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDSporta = pChild->Attribute("id");
        string NazivSporta = pChild->Attribute("nazivsporta");
        m_vSport.push_back(new Sport(IDSporta, NazivSporta));
    }
    oXmlDocument.LoadFile("funkcije.xml");
    //Ucitavanje funkcija iz funkcije.xml u vektor m_vFunkcija
    for (pChild = pRoot->FirstChildElement("Funkcija"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDFunkcije = pChild->Attribute("id");
        string NazivFunkcije = pChild->Attribute("nazivfunkcije");
        m_vFunkcija.push_back(new Funkcija(IDFunkcije, NazivFunkcije));
    }
    oXmlDocument.LoadFile("clanovi.xml");
    // Ucitavanje clanova iz clanovi.xml u vektore m_vOsobe i m_vClanovi
    for (pChild = pRoot->FirstChildElement("Clan"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        int ID = atoi(pChild->Attribute("id"));
        string Prezime = pChild->Attribute("prezime");
        string Ime = pChild->Attribute("ime");
        string DatumRodenja = pChild->Attribute("datumrodenja");
        string Email = pChild->Attribute("email");
        vector<Sport*>m_vSportovi;
        vector<string>Rastavljac;
        string IDSport = pChild->Attribute("sport");
        stringstream ss_stream(IDSport);
        while (ss_stream.good())
        {
            string NoviString;
            getline(ss_stream, NoviString, ',');
            Rastavljac.push_back(NoviString);
        }
        for (int i = 0; i < Rastavljac.size(); i++)
        {
            for (int j = 0; j < m_vSport.size(); j++)
            {
                if (Rastavljac[i] == m_vSport[j]->m_sIDSporta)
                {
                    m_vSportovi.push_back(new Sport(m_vSport[j]->m_sIDSporta, m_vSport[j]->m_sImeSporta));
                }
            }
        }
        vector<Funkcija*>m_vFunkcije;
        vector<string>Rastavljacc;
        string IDFunkcije = pChild->Attribute("funkcije");
        stringstream s_stream(IDFunkcije);
        while (s_stream.good())
        {
            string NoviStringg;
            getline(s_stream, NoviStringg, ',');
            Rastavljacc.push_back(NoviStringg);
        }
        for (int i = 0; i < Rastavljacc.size(); i++)
        {
            for (int j = 0; j < m_vFunkcija.size(); j++)
            {
                if (Rastavljacc[i] == m_vFunkcija[j]->m_sIDFunkcije)
                {
                    m_vFunkcije.push_back(new Funkcija(m_vFunkcija[j]->m_sIDFunkcije, m_vFunkcija[j]->m_sImeFunkcije));
                }
            }
        }
        int PlaceneClanarine = atoi(pChild->Attribute("placeneclanarine"));
        m_vOsobe.push_back(new Osoba(ID, Prezime, Ime, DatumRodenja, Email));
        m_vClanovi.push_back(new Clan(ID, m_vSportovi, m_vFunkcije, PlaceneClanarine));
    }
    // Tablicni ispis
    for (int x = 0; x < m_vOsobe.size(); x++)
    {
        for (int y = 0; y < m_vClanovi.size(); y++)
        {
            if (m_vOsobe[x]->m_nID == m_vClanovi[y]->m_nID)
            {
                int brojac = 0;
                table[0][0] = "R.br";
                table[0][1] = "ID";
                table[0][2] = "Prezime";
                table[0][3] = "Ime";
                table[0][4] = "Datum Rodenja";
                table[0][5] = "Email";
                table[0][6] = "Sport";
                table[0][7] = "Funkcije";
                table[0][8] = "Placene clanarine";
                table[Provjera][0] = Provjera;
                table[Provjera][1] = m_vOsobe[x]->m_nID;
                table[Provjera][2] = m_vOsobe[x]->m_sPrezime;
                table[Provjera][3] = m_vOsobe[x]->m_sIme;
                table[Provjera][4] = m_vOsobe[x]->m_sDatumRodenja;
                table[Provjera][5] = m_vOsobe[x]->m_sEmail;
                string ss = "";
                for (int z = 0; z < m_vClanovi[y]->m_vSport.size(); z++)
                {
                    ss += m_vClanovi[y]->m_vSport[z]->m_sImeSporta;
                    ss += ", ";
                }
                if (!ss.empty())
                {
                    ss.pop_back();
                    ss.pop_back();
                }
                table[Provjera][6] = ss;
                string s = "";
                for (int z = 0; z < m_vClanovi[y]->m_vFunkcija.size(); z++)
                {
                    s += m_vClanovi[y]->m_vFunkcija[z]->m_sImeFunkcije;
                    s += ", ";
                }
                if (!s.empty())
                {
                    s.pop_back();
                    s.pop_back();
                }
                table[Provjera][7] = s;
                table[Provjera][8] = m_vClanovi[y]->m_nPlaceneClanarine;
                if (Provjera == m_vClanovi.size())
                {
                    cout << table;
                        Provjera = 1;
                }
                else
                {
                    Provjera++;
                }
                brojac = brojac + 1;
            }
        }
    }
    cout << "Unesite ID Clana kojeg zelite obrisati : " << endl;
    cin >> unos;
    // Brisanje tog clana iz vektora m_vClanovi
    for (int i = 0; i < m_vClanovi.size(); i++)
    {
        if (unos == m_vClanovi[i]->m_nID)
        {
            m_vClanovi.pop_back();
        }
    }
    // Brisanje tog clana iz vektora m_vOsobe
    for (int i = 0; i < m_vOsobe.size(); i++)
    {
        if (unos == m_vOsobe[i]->m_nID)
        {
            m_vOsobe.pop_back();
        }
    }
    oXmlDocument.LoadFile("clanovi.xml");
    pRoot->DeleteChildren();
    XMLError eResult = oXmlDocument.SaveFile("clanovi.xml");
    XMLDocument oXmlDoc;
    oXmlDoc.LoadFile("clanovi.xml");
    XMLElement* pRoot1 = oXmlDoc.FirstChildElement("dataset");
    string IDSport, IDFunkcije;
    // Spremanje svih clanova u xml, bez obrisanog clana
    for (int i = 0; i < m_vOsobe.size(); i++)
    {
        for (int j = 0; j < m_vClanovi.size(); j++)
        {
            if (m_vOsobe[i]->m_nID == m_vClanovi[j]->m_nID)
            {
                XMLElement* pElement1 = oXmlDoc.NewElement("Clan");
                pElement1->SetAttribute("id", m_vOsobe[i]->m_nID);
                pElement1->SetAttribute("prezime", m_vOsobe[i]->m_sPrezime.c_str());
                pElement1->SetAttribute("ime", m_vOsobe[i]->m_sIme.c_str());
                pElement1->SetAttribute("datumrodenja", m_vOsobe[i]->m_sDatumRodenja.c_str());
                pElement1->SetAttribute("email", m_vOsobe[i]->m_sEmail.c_str());
                IDSport = "";
                for (int k = 0; k < m_vClanovi[j]->m_vSport.size(); k++)
                {
                    IDSport += m_vClanovi[j]->m_vSport[k]->m_sIDSporta;
                    IDSport += ",";
                }
                if (!IDSport.empty())
                {
                    IDSport.pop_back();
                }
                pElement1->SetAttribute("sport", IDSport.c_str());
                IDFunkcije = "";
                for (int k = 0; k < m_vClanovi[j]->m_vFunkcija.size(); k++)
                {
                    IDFunkcije += m_vClanovi[j]->m_vFunkcija[k]->m_sIDFunkcije;
                    IDFunkcije += ",";
                }
                if (!IDFunkcije.empty())
                {
                    IDFunkcije.pop_back();
                }
                pElement1->SetAttribute("funkcije", IDFunkcije.c_str());
                pElement1->SetAttribute("placeneclanarine", m_vClanovi[j]->m_nPlaceneClanarine);
                pRoot1->InsertEndChild(pElement1);
            }
        }
        oXmlDoc.SaveFile("clanovi.xml");
    }
}
void Suvmain::Statistike()
{
    m_vSport.clear();
    m_vFunkcija.clear();
    m_vOsobe.clear();
    m_vClanovi.clear();
    XMLDocument oXmlDocument;
    oXmlDocument.LoadFile("sportovi.xml");
    XMLElement* pRoot = oXmlDocument.FirstChildElement("dataset");
    XMLElement* pChild;
    //Ucitavanje sportova iz sportovi.xml u vektor m_vSport
    for (pChild = pRoot->FirstChildElement("Sport"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDSporta = pChild->Attribute("id");
        string NazivSporta = pChild->Attribute("nazivsporta");
        m_vSport.push_back(new Sport(IDSporta, NazivSporta));
    }
    oXmlDocument.LoadFile("funkcije.xml");
    //Ucitavanje funkcija iz funkcije.xml u vektor m_vFunkcija
    for (pChild = pRoot->FirstChildElement("Funkcija"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        string IDFunkcije = pChild->Attribute("id");
        string NazivFunkcije = pChild->Attribute("nazivfunkcije");
        m_vFunkcija.push_back(new Funkcija(IDFunkcije, NazivFunkcije));
    }
    oXmlDocument.LoadFile("clanovi.xml");
    // Ucitavanje clanova iz clanovi.xml u vektore m_vOsobe i m_vClanovi
    for (pChild = pRoot->FirstChildElement("Clan"); pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        int ID = atoi(pChild->Attribute("id"));
        string Prezime = pChild->Attribute("prezime");
        string Ime = pChild->Attribute("ime");
        string DatumRodenja = pChild->Attribute("datumrodenja");
        string Email = pChild->Attribute("email");
        vector<Sport*>m_vSportovi;
        vector<string>Rastavljac;
        string IDSport = pChild->Attribute("sport");
        stringstream ss_stream(IDSport);
        while (ss_stream.good())
        {
            string NoviString;
            getline(ss_stream, NoviString, ',');
            Rastavljac.push_back(NoviString);
        }
        for (int i = 0; i < Rastavljac.size(); i++)
        {
            for (int j = 0; j < m_vSport.size(); j++)
            {
                if (Rastavljac[i] == m_vSport[j]->m_sIDSporta)
                {
                    m_vSportovi.push_back(new Sport(m_vSport[j]->m_sIDSporta, m_vSport[j]->m_sImeSporta));
                }
            }
        }
        vector<Funkcija*>m_vFunkcije;
        vector<string>Rastavljacc;
        string IDFunkcije = pChild->Attribute("funkcije");
        stringstream s_stream(IDFunkcije);
        while (s_stream.good())
        {
            string NoviStringg;
            getline(s_stream, NoviStringg, ',');
            Rastavljacc.push_back(NoviStringg);
        }
        for (int i = 0; i < Rastavljacc.size(); i++)
        {
            for (int j = 0; j < m_vFunkcija.size(); j++)
            {
                if (Rastavljacc[i] == m_vFunkcija[j]->m_sIDFunkcije)
                {
                    m_vFunkcije.push_back(new Funkcija(m_vFunkcija[j]->m_sIDFunkcije, m_vFunkcija[j]->m_sImeFunkcije));
                }
            }
        }
        int PlaceneClanarine = atoi(pChild->Attribute("placeneclanarine"));
        m_vOsobe.push_back(new Osoba(ID, Prezime, Ime, DatumRodenja, Email));
        m_vClanovi.push_back(new Clan(ID, m_vSportovi, m_vFunkcije, PlaceneClanarine));
    }
    int brojac = 0;
    // Brojanje koliko clanova sportska udruga ima
    for (int i = 0; i < m_vClanovi.size(); i++)
    {
        brojac = brojac + 1;
    }
    cout << "Ukupni broj clanova sportske udruge je: " << brojac << endl;
    cout << "Unesite koliko je ukupno iznosila clanarina za tekucu godinu: ";
    int clanarina;
    cin >> clanarina;
    brojac = 0;
    // Zbrajanje koliko je puta clanarina placeno u tekucoj godini (2020)
    for (int i = 0; i < m_vClanovi.size(); i++)
    {
        if (m_vClanovi[i]->m_nPlaceneClanarine == 2020)
        {
            brojac = brojac + 1;
        }
    }
    int counter = 0;
    clanarina = clanarina * brojac;
    cout << "---------------------------------------" << endl;
    cout << "Kolicina kuna koja je prikupljena od clanarina: " << clanarina << endl;
    // Odredivanje koliko je koji sport zastupljen
    for (int i = 0; i < m_vSport.size(); i++)
    {
        for (int j = 0; j < m_vClanovi.size(); j++)
        {
            for (int k = 0; k < m_vClanovi[j]->m_vSport.size(); k++)
            {
                if (m_vSport[i]->m_sIDSporta == m_vClanovi[j]->m_vSport[k]->m_sIDSporta)
                {
                    counter = counter + 1;
                }
            }
        }
        m_vSport[i]->UkupnaZastupljenost = counter;
        counter = 0;
    }
    cout << "---------------------------------------" << endl;
    sort(m_vSport.begin(), m_vSport.end(), sortiranje_zastupljenosti_pa_imena());
    // Ispis clanova iz vektora m_vSport
    for (int i = 0; i < m_vSport.size(); i++)
    {
        cout << "Ime sporta: " << m_vSport[i]->m_sImeSporta << " | Broj clanova koji se bavi ovim sportom : " << m_vSport[i]->UkupnaZastupljenost << endl;
    }
    cout << "Najmanje zastupljen sport je : " << m_vSport[0]->m_sImeSporta << endl;
    cout << "Najvise zastupljen sport je : " << m_vSport[m_vSport.size() - 1]->m_sImeSporta << endl;
}
void Suvmain::PovratakUIzbornik()
{
    cout << "Kliknite enter za povratak u glavni izbornik" << endl;
    cin.ignore();
    cin.get();
    GlavniIzbornik();
}
Suvmain::~Suvmain()
{

}