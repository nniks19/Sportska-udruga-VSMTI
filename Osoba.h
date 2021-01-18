#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
using namespace std;
class Osoba
{
public:
	int m_nID;
	string m_sPrezime;
	string m_sIme;
	string m_sDatumRodenja;
	string m_sEmail;
	Osoba(int id, string p, string i, string dr, string e);
	~Osoba();
};
