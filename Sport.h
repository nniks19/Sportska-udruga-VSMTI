#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
using namespace std;
class Sport
{
public:
	string m_sIDSporta;
	string m_sImeSporta;
	int UkupnaZastupljenost;
	Sport(string ids, string ims);
	~Sport();
};

