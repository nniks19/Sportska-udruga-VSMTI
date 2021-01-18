#include "Osoba.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
using namespace std;
Osoba::Osoba(int id, string p, string i, string dr, string e)
{
	m_nID = id;
	m_sPrezime = p;
	m_sIme = i;
	m_sDatumRodenja = dr;
	m_sEmail = e;
}
Osoba::~Osoba()
{
}