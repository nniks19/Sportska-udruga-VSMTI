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
Clan::Clan(int id, vector<Sport*>Sport, vector<Funkcija*>Funkcija, int pc)
{
	m_nID = id;
	m_vSport = Sport;
	m_vFunkcija = Funkcija;
	m_nPlaceneClanarine = pc;
}
Clan::~Clan()
{
}
