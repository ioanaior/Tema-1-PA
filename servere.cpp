#include <bits/stdc++.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("servere.in");
ofstream g("servere.out");

double putere_sistem(int N, vector<int> &P, vector<int> &C, double val) {
    double putere_min = numeric_limits<double>::max();
    for (int i = 0; i < N; i++) {
        // calculam puterea noua pentru sistemul curent
        double putere_new = P[i] - abs(C[i] - val);
        // actualizam minimul daca e necesar
        if (putere_new < putere_min) {
            putere_min = putere_new;
        }
    }
    return putere_min;
}

int main() {
    // avem datele in ordinea: N, P si C
    vector<int> P, C;
    int N, i, x;
    f >> N;
    for (i = 0; i < N; i++) {
        f >> x;
        P.push_back(x);
    }
    for (i = 0; i < N; i++) {
        f >> x;
        C.push_back(x);
    }

    // aplicam un fel de cautare binara
    // intre consumul minim si maxim
    double st = *min_element(C.begin(), C.end());
    double dr = *max_element(C.begin(), C.end());
    double m;
    double putere_sist_max = numeric_limits<double>::lowest();
    // ne oprim cand ajungem la aceeasi pozitie
    while (dr - st > 0.01) {
        m = (dr + st) / 2;

        // actualizam puterea maxima a sistemului in cazul
        // in care intalnim o valoare mai mare
        double putere_sist = putere_sistem(N, P, C, m);
        if (putere_sist > putere_sist_max) {
            putere_sist_max = putere_sist;
        }

        // ne uitam la valoarea vecinului din stanga (m - 0.01),
        // daca puterea sistemului e mai mare pentru valoarea
        // respectiva, ne mutam cu limita dreapta acolo
        double putere_sist_st = putere_sistem(N, P, C, m - 0.01);
        if (putere_sist_st > putere_sist)
            dr = m - 0.01;

        // altfel, mutam limita stanga
        else
            st = m + 0.01;
    }

    // afisam rezultatul obtinut cu o zecimala
    g << fixed << setprecision(1) << putere_sist_max << "\n";

    f.close();
    g.close();

    return 0;
}
