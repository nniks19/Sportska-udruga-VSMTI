#include "Tajnik.h"
#include "Osoba.h"
#include "Predsjednik.h"
#include "PodPredsjednik.h"
#include "Clan.h"
#include "Funkcija.h"
#include "Likvidator.h"
#include "Sport.h"
#include "Suvmain.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include "tinyxml2.h"
#include "algorithm"
#include <sstream>
using namespace tinyxml2;
using namespace std;
int main()
{
    Suvmain* clan = new Suvmain();
    clan->GlavniIzbornik();
}
// ID 10 Hajba Marko - predsjednik, nadzorni odbor, izvrsni odbor
// ID 20 Heði Ivan - podpredsjednik, nadzorni odbor, izvrsni odbor
// ID 1 Stankovic Stanko - Likvidator, nadzorni odbor, izvrsni odbor
// ID 7 Modriæ Benjamin - Tajnik - nije platio clanarinu 2 godine, izvrsni odbor
// ID 2 Petrovic Petar - Clan - ali u izvrsnom odboru

// Nadzorni Odbor: 10,20,1
// Izvrsni Odbor: 10,20,1,7,2
