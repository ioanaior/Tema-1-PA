#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

ifstream f("criptat.in");
ofstream g("criptat.out");

// functie care numara de cate ori apare caracterul ch in word
int times_found(const string &word, char ch) {
    int nr = 0;
    for (char letter : word) {
        if (letter == ch)
            nr++;
    }
    return nr;
}

// functie care calculeaza procentul caracterului ch in word
float percent(int count, int totalLength) {
    return static_cast<float>(count) / totalLength;
}

// functie comparator pentru sortarea cuvintelor
bool compare_words(const string &a, const string &b, char ch) {
    float percent_a = percent(times_found(a, ch), a.length());
    float percent_b = percent(times_found(b, ch), b.length());

    // descrescator dupa procent
    if (percent_a != percent_b)
        return percent_a > percent_b;

    // si mai apoi descrescator dupa lungime
    return a.length() > b.length();
}

// functie care sorteaza cuvintele
void sort_words(vector<string> &words, char ch) {
    sort(words.begin(), words.end(), [&](const string &a, const string &b)
         { return compare_words(a, b, ch); });
}

// functie care selecteaza caraterele care apar in words (unice, maxim 8)
string find_alphabet(const vector<string> words) {
    string alphabet;
    for (const string word : words) {
        for (char letter : word) {
            if (alphabet.find(letter) == string::npos)
                alphabet += letter;
        }
    }
    return alphabet;
}

int main() {
    int N, maxlen = 0;
    f >> N;
    vector<string> words(N);

    for (int i = 0; i < N; i++) {
        f >> words[i];
        cout << words[i] << endl;
    }

    // extragem 'alfabetul' pentru cuvintele citite (maxim 8 litere)
    string alphabet = find_alphabet(words);
    // pentru fiecare litera care apare, repetam acelasi proces
    // si la final vom selecta valoarea maxima rezultata
    for (char ch : alphabet) {
        // sortam cuvintele in functie de procentul aparitiei literei curente
        sort_words(words, ch);
        int times_found_passwd = 0, len_passwd = 0;

        for (const string &word : words) {
            times_found_passwd += times_found(word, ch);
            len_passwd += word.length();
            // daca intalnim un cuvant care ne 'strica' procentul,
            // il eliminam si trecem mai departe
            if (percent(times_found_passwd, len_passwd) <= 0.5) {
                len_passwd -= word.length();
                times_found_passwd -= times_found(word, ch);
            }
        }

        maxlen = max(maxlen, len_passwd);
    }

    g << maxlen;

    return 0;
}
