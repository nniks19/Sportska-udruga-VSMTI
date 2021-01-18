#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include "Osoba.h"
#include "Sport.h"
#include "Funkcija.h"
using namespace std;
class Clan
{
public:
	int m_nID;
	Clan(int id,vector<Sport*> Sport, vector<Funkcija*> Funkcija, int pc);
	~Clan();
	vector<Funkcija*>m_vFunkcija;
	vector<Sport*> m_vSport;
	int m_nPlaceneClanarine;
};

