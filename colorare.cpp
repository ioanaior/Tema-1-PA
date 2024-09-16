#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

ifstream f("colorare.in");
ofstream g("colorare.out");

int mod = 1000000007;

// gasim o metoda mai eficienta de a calcula puterea (x^y)
long long int power(long long int x, long long int y) {
    long long int result = 1;
    while (y > 0) {
        // ridicand la patrat de fiecare data rezultatul partial, ajungem mai
        // repede la raspuns
        if (y % 2 == 1) {
            result = (result * x) % mod;
        }
        y /= 2;
        x = (x * x) % mod;
    }
    return result;
}

int main() {
    // citim datele din fisierul de intrare
    // se citeste K
    int K;
    f >> K;
    // si acum lista cu numarul si ordinea zonelor
    // hai sa le prelucram in timp ce le citim
    long long int nr_zone;
    char tip_zone_curente;
    char tip_zone_precedente = '-';
    long long int combinatii_totale = 1;
    // pentru fiecare dintre perechi
    for (int i = 1; i <= K; i++) {
        f >> nr_zone >> tip_zone_curente;
        // acum in functie de tipul de zona inmultim
        // cu numarul corespunzator
        // trebuie sa retinem undeva si tipul zonei precedente
        // in aflarea rezultatului ne bazam pe inmultiri:
        // vedem cate modalitati de colorare posibile sunt pentru
        // fiecare zona, avand in vedere culoarea anterior folosita,
        // care nu trebuie sa se repete
        // daca e primul bloc din zona curenta pe care il punem:
        if (tip_zone_precedente == '-') {
            if (tip_zone_curente == 'H')
                combinatii_totale = (combinatii_totale * 6) % mod;
            else
                combinatii_totale = (combinatii_totale * 3) % mod;
        // pentru restul primei zone:
        } else {
            if (tip_zone_precedente == 'H' && tip_zone_curente == 'H')
                combinatii_totale = (combinatii_totale * 3) % mod;
            if (tip_zone_precedente == 'H' && tip_zone_curente == 'V')
                combinatii_totale = (combinatii_totale * 1) % mod;
            if (tip_zone_precedente == 'V' && tip_zone_curente == 'H')
                combinatii_totale = (combinatii_totale * 2) % mod;
            if (tip_zone_precedente == 'V' && tip_zone_curente == 'V')
                combinatii_totale = (combinatii_totale * 2) % mod;
        }

        tip_zone_precedente = tip_zone_curente;
        // pentru restul zonei, trebuie luat in calcul tipul
        // blocului/blocurilor precedente:
        if (tip_zone_precedente == 'H' && tip_zone_curente == 'H')
            combinatii_totale = (combinatii_totale * power(3, nr_zone - 1))
            % mod;
        else if (tip_zone_precedente == 'H' && tip_zone_curente == 'V')
            combinatii_totale = (combinatii_totale * power(1, nr_zone - 1))
            % mod;
        else if (tip_zone_precedente == 'V' && tip_zone_curente == 'H')
            combinatii_totale = (combinatii_totale * power(2, nr_zone - 1))
            % mod;
        else if (tip_zone_precedente == 'V' && tip_zone_curente == 'V')
            combinatii_totale = (combinatii_totale * power(2, nr_zone - 1))
            % mod;
    }
    g << combinatii_totale % mod << endl;

    return 0;
}
