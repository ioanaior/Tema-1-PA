#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("compresie.in");
ofstream g("compresie.out");

int suma_subsecventa(vector<int> v, int i, int j) {
    if (i == 0)
        return v[j];
    else
        return v[j] - v[i - 1];
}

int main() {
    // avem datele in ordinea: n, A, m, B
    vector<int> A, B;
    int n, m, x;
    f >> n;
    for (int i = 0; i < n; i++) {
        f >> x;
        A.push_back(x);
    }
    f >> m;
    for (int i = 0; i < m; i++) {
        f >> x;
        B.push_back(x);
    }

    // acum trebuie sa parcurgem A si B in paralel ca sa gasim primul set
    // de subsecvente care au sume egale

    // ne luam cate un contor pentru fiecare sir si vedem
    // cate subsecvente gasim pana ajungem la final

    int contor_a = 0, contor_b = 0, nr = 0, ok = 1, i, j;
    int suma_subsecventa_A, suma_subsecventa_B;
    while (contor_a <= n - 1 || contor_b <= m - 1) {
        suma_subsecventa_A = A[contor_a];
        suma_subsecventa_B = B[contor_b];
        // contoarele arata de unde ar trebui sa inceapa subsecventa curenta
        // cautam pozitia la care aceasta se termina
        // adica cautam primul set de subsecvente cu sumele egale
        i = contor_a;
        j = contor_b;
        while (suma_subsecventa_A != suma_subsecventa_B
        && i <= n - 1 && j <= m - 1) {
            while (i <= n - 1 && suma_subsecventa_A < suma_subsecventa_B) {
                i++;
                suma_subsecventa_A += A[i];
            }
            while (j <= m - 1 && suma_subsecventa_A > suma_subsecventa_B) {
                j++;
                suma_subsecventa_B += B[j];
            }
        }
        if (suma_subsecventa_A == suma_subsecventa_B) {
            nr++;
        } else {
            ok = 0;
            break;
        }
        contor_a = i + 1;
        contor_b = j + 1;
    }
    if (ok)
        g << nr;
    else
        g << -1;

    return 0;
}
