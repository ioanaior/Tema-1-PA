#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

ifstream f("oferta.in");
ofstream g("oferta.out");

double min3(double a, double b, double c) {
    return min(a, min(b, c));
}

int discount3(int a, int b, int c) {
    return min(a, min(b, c));
}

double discount2(int a, int b) {
    return (float)min(a, b) / 2;
}

// functie care interclaseaza cei 3 vectori de sume cu eliminarea duplicatelor
vector<double> interclasare(const vector<double> &v1, const vector<double> &v2,
const vector<double> &v3, int K) {
    vector<double> rezultat;
    size_t i = 0, j = 0, k = 0;
    // pentru a evita duplicatele
    double last_added = std::numeric_limits<double>::quiet_NaN();

    while (rezultat.size() < K &&
    (i < v1.size() || j < v2.size() || k < v3.size())) {
        double min_val = numeric_limits<double>::infinity();

        if (i < v1.size())
            min_val = min(min_val, v1[i]);
        if (j < v2.size())
            min_val = min(min_val, v2[j]);
        if (k < v3.size())
            min_val = min(min_val, v3[k]);

        if (min_val != last_added) {
            rezultat.push_back(min_val);
            last_added = min_val;
        }

        if (i < v1.size() && v1[i] == min_val)
            i++;
        else if (j < v2.size() && v2[j] == min_val)
            j++;
        else if (k < v3.size() && v3[k] == min_val)
            k++;
    }

    return rezultat;
}

int main() {
    // citim datele de intrare: N, K si vectorul de preturi ale produselor
    int N, K, i, j;
    f >> N >> K;
    vector<int> prices;
    prices.reserve(N);

    // daca suntem in cazul subpunctului a)
    if (K == 1) {
        // am vectorul de preturi ale produselor
        // si trebuie sa vedem care ar fi cea mai buna varianta de a combina
        // produsele astfel incat sa platim cat mai putin

        // aici putem aplica un DP clasic
        // dp[i] va retine cel mai mic pret posibil care se poate plati pentru
        // primele i produse
        vector<double> dp;
        int price;

        for (i = 0; i < N; i++) {
            f >> price;
            prices.push_back(price);
            // verificam pozitia produsului
            if (i == 0) {
                dp.push_back(prices[0]);
            } else {
                if (i == 1) {
                    // cel mai mic pret platit pentru primele 2 produse
                    dp.push_back(prices[0] + prices[1] -
                    discount2(prices[0], prices[1]));
                } else {
                    // vedem care ar fi suma minima platita pentru
                    // primele i produse
                    // produsul curent incercam sa il punem fie singur,
                    // fie in grupa de 2 sau de 3 cu produsele precedente
                    dp.push_back(min3(dp[i - 1] + prices[i],
                                      dp[i - 2] + prices[i - 1] + prices[i] -
                                      discount2(prices[i - 1], prices[i]),
                                      dp[i - 3] + prices[i - 2] + prices[i - 1]
                                      + prices[i] - discount3(prices[i - 2],
                                      prices[i - 1], prices[i])));
                }
            }
        }
        g << fixed << setprecision(1) << dp[N - 1];
    } else {
        // ar trebui sa aplicam un fel de 'Rucsac' (tot DP)
        // o matrice cu N linii si (maxim) K coloane
        // la linia i retinem primele (maxim) K sume care se pot obtine din
        // primele i produse in ordine crescatoare
        // pentru i = 0 si i = 1 avem cazuri particulare:
        vector<vector<double>> dp(N, vector<double>(K, 0));
        int price;

        vector<double> sums1, sums2, sums3;
        for (i = 0; i < N; i++) {
            f >> price;
            prices.push_back(price);
            if (i == 0) {
                dp[i][0] = prices[0];
            } else {
                if (i == 1) {
                    dp[i][0] = prices[0] + prices[1]
                    - discount2(prices[0], prices[1]);
                    dp[i][1] = prices[0] + prices[1];
                } else {
                    // pentru celelalte cazuri:
                    // avem cei 3 pasi anteriori de care ne folosim
                    // fiecare pas ne-a generat un vector de sume posibile
                    // acestea sunt ordonate crescator

                    sums1.clear();
                    sums2.clear();
                    sums3.clear();

                    // elementele vectorului de la pasul i-1 vor fi
                    // completate cu pretul i
                    // asta o sa fie de fapt sums1
                    int pos = 0;
                    while (dp[i - 1][pos] != 0 && sums1.size() < K) {
                        sums1.push_back(dp[i - 1][pos] + prices[i]);
                        pos++;
                    }

                    // elementele vectorului de la pasul i-2 vor fi
                    // completate cu pretul celor 2 produse - discount2
                    // asta o sa fie de fapt sums2
                    pos = 0;
                    double value_added = prices[i] + prices[i - 1]
                    - discount2(prices[i], prices[i - 1]);
                    while (dp[i - 2][pos] != 0 && sums2.size() < K) {
                        sums2.push_back(dp[i - 2][pos] + value_added);
                        pos++;
                    }

                    // elementele vectorului de la pasul i-3 vor fi
                    // completate cu pretul celor 3 produse - discount3
                    // asta o sa fie de fapt sums3
                    pos = 0;
                    value_added = prices[i] + prices[i - 1] + prices[i - 2]
                    - discount3(prices[i], prices[i - 1], prices[i - 2]);
                    if (i >= 3) {
                        while (dp[i - 3][pos] != 0 && sums3.size() < K) {
                            sums3.push_back(dp[i - 3][pos] + value_added);
                            pos++;
                        }
                    } else {
                        sums3.push_back(value_added);
                    }

                    // interclasam vectorii cu eliminarea duplicatelor
                    dp[i] = interclasare(sums1, sums2, sums3, K);
                }
            }
        }
        // daca valoarea din coltul dreapta-jos nu a fost inca setata,
        // inseamna ca NU avem cel putin K sume diferite posibile
        if (dp[N - 1][K - 1] == 0)
            g << -1;
        else
            // altfel, afisam rezultatul
            g << fixed << setprecision(1) << dp[N - 1][K - 1];
    }

    return 0;
}
