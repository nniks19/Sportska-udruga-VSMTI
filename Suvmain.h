#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include "Osoba.h"
#include "Sport.h"
#include "Funkcija.h"
#include "Clan.h"
using namespace std;
class Suvmain
{
public:
	vector<Funkcija*>m_vFunkcija;
	vector<Sport*> m_vSport;
	vector<Osoba*>m_vOsobe;
	vector<Clan*>m_vClanovi;
	Suvmain();
	~Suvmain();
	void GlavniIzbornik();
	void Statistike();
	void IspisiSveClanove();
	void DodajSport();
	void DodajClana();
	void AzurirajClana();
	void ObrisiClana();
	void PovratakUIzbornik();
};

