# Tema-1-PA
Tema 1 Proiectarea Algoritmilor 2024
## **Problema 1 ~ SERVERE**

Rezolvarea problemei a durat 3-4 ore.

Pentru a rezolva aceasta problema, am utilizat o metoda de cautare binara pentru a determina cantitatea optima de curent care maximizeaza puterea minima posibila a unui server. Astfel, ne concentram pe gasirea unui echilibru intre alimentarea insuficienta si supraalimentarea serverelor, cautand sa minimalizam pierderea de putere de calcul.

### Functia `putere_sistem`:

> Aceasta functie returneaza puterea minima de calcul a sistemului pentru o anumita valoare de curent data. Functia itereaza prin fiecare server, ajustand puterea in functie de diferenta dintre curentul optim si cel aplicat, si pastreaza minimul acestor valori.

### Cautarea binara:

> Am implementat o cautare binara pentru a afla valoarea optima de curent intre valoarea minima si maxima a curentului consumat de servere. Ajustez intervalele in functie de rezultatele functiei putere_sistem pentru a maximiza puterea minima a sistemului.
Rezultatul este scris in fisierul servere.out, afisand puterea maxima a sistemului cu o precizie de o zecimala.

### Observatii si Complexiate:
> Cautarea binara e oprita cand diferenta dintre limitele de cautare ajunge mai mica decat 0.01, asigurand o precizie suficienta pentru majoritatea aplicatiilor practice, in timp ce limitam complexitatea computationala a solutiei.

> Complexitatea temporala a solutiei: <span style="color:green">**O(N*logN)**</span>.


## **Problema 2 ~ COLORARE**

Rezolvarea problemei a durat 3-4 ore.

Programul propus calculeaza numarul de combinatii posibile pentru colorarea tabloului conform regulilor specificate, folosind un algoritm eficient bazat pe procesarea secventiala a blocurilor de colorat si utilizand programarea dinamica pentru a optimiza calculul.

Incepem prin a citi numarul de zone
K in care tabloul poate fi impartit si apoi tipul si numarul de zone care pot fi colorate intr-un anumit mod (orizontal H sau vertical V).

### Functia `power`:
> Aceasta functie calculeaza x^y folosind metoda exponentierii rapide, care este esentiala pentru gestionarea numerelor mari si a operatiilor repetate in modul specificat.

### Calculul Combinatiilor:
> Programul calculeaza numarul total de combinatii posibile iterand prin fiecare zona, incepand cu prima si aplicand regulile de colorare. Se foloseste o variabila combinatii_totale pentru a stoca rezultatul partial si se ajusteaza acest numar bazat pe tipul zonei curente si precedente pentru a asigura ca regulile de adiacenta sunt respectate.

> La prima zona, codul seteaza combinatii_totale in functie de tipul zonei (orizontal 'H' sau vertical 'V').
Pentru fiecare zona care urmeaza, codul verifica tipul curent si tipul zonei anterioare si aplica logica specifica pentru a actualiza combinatii_totale.
Exista patru scenarii bazate pe combinatia tipurilor zonei curente si anterioare ('H' cu 'H', 'H' cu 'V', 'V' cu 'H', 'V' cu 'V'). Fiecare scenariu decide factorul de multiplicare initial.
De exemplu, daca tipul curent si anterior sunt ambele 'H', factorul de multiplicare initial este 3. Daca sunt diferite, factorul poate fi 1 sau 2, in functie de combinatie.
Dupa stabilirea factorului de multiplicare initial pentru prima unitate a zonei curente, se aplica functia power pentru a calcula numarul de combinatii posibile pentru restul unitatilor din zona.

### Observatii si Complexitate:
Avand in vedere ca K este numarul total de zone si presupunand ca in medie fiecare zona are un numar
M de unitati, complexitatea totala a sectiunii de calcul al combinatiilor poate fi aproximata ca
<span style="color:green">**O(K*logM)**</span>.


## **Problema 3 ~ COMPRESIE**

Rezolvarea problemei a durat ~5 ore.

Programul propus compara sirurile A si B pentru a verifica daca pot fi facute identice prin aplicarea operatiilor de comprimare. Procesul este efectuat prin parcurgerea in paralel a ambelor siruri si cautarea subsecventelor cu sume egale.

### Functia `suma_subsecventa`:
> Aceasta calculeaza suma unei subsecvente date dintr-un sir, utilizand o metoda de precalcul pentru a eficientiza operatiile de adunare repetata.

### Procesarea Sirurilor
> Se parcurge fiecare sir, comparand subsecventele pentru a gasi sume egale. Se folosesc doua contoare pentru a mentine pozitiile curente in fiecare sir si se incearca extinderea subsecventelor pana cand sumele subsecventelor sunt egale. Daca sumele se egalizeaza, se trece la urmatoarea subsecventa; daca nu, procesul se incheie cu un rezultat negativ.
Dupa terminarea procesarii, se scrie in fisierul `compresie.out` numarul de subsecvente egale gasite, sau -1 daca nu este posibil sa se egalizeze sirurile.

### Observatii si Complexitate:
> In cel mai nefavorabil caz, fiecare extindere a subsecventelor ar putea necesita parcurgerea completa a ambelor siruri, daca subsecventele sunt mereu neechilibrate in suma pana aproape de finalul sirurilor. Acest lucru poate duce la o complexitate de <span style="color:green">**O(n*m)**</span>.


## **Problema 4 ~ CRIPTAT**

Rezolvarea problemei a durat ~5 ore.

Programul analizeaza o lista de cuvinte si incearca sa construiasca cea mai lunga parola posibila care respecta conditiile de litera dominanta.

Cuvintele sunt citite din fisier si stocate intr-un vector. Se identifica literele unice din toate cuvintele (cunoastem din enunt ca acestea sunt maxim 8).
Cuvintele sunt sortate descrescator dupa procentul de aparitie al fiecarei litere si dupa lungime, pentru a maximiza sansele ca litera sa devina dominanta in parola finala.

### Construirea Parolei
> Se incearca construirea parolei pentru fiecare litera identificata, adaugand cuvinte unul cate unul si verificand daca adaugarea respectivului cuvant mentine litera ca fiind dominanta. Daca un cuvant 'strica' procentul necesar, este omis. Lungimea maxima a parolei este actualizata pentru fiecare litera testata, selectandu-se valoarea maxima obtinuta.

### Observatii si Complexitate:
> Complexiatea este cel mai mult influentata de sortarea cuvintelor, care se executa pentru fiecare litera din 'alfabetul' obtinut => <span style="color:green">**O(N*logN)**</span>.


## **Problema 5 ~ OFERTA**

Rezolvarea problemei a durat ~ 2 zile (mai mult subpunctul b :))) ).

Solutia se bazeaza pe programare dinamica pentru a calcula costul minim de achizitie, analizand posibilitatile de grupare a produselor.

### Subpunctul a)
> Se utilizeaza un vector dp unde dp[i] reprezinta costul minim pentru primele i produse.
Se examineaza fiecare produs individual si se calculeaza costurile pentru gruparea a doua si trei produse adiacente, aplicand reducerile specifice.
Fiecare pozitie dp[i] este calculata pe baza costului produselor anterioare si a reducerilor aplicabile pentru grupari.
Ultima valoare din vectorul dp indica costul minim pentru toate produsele.

### Subpunctul b)

> Se extinde vectorul dp la o matrice pentru a stoca pana la K costuri unice pentru primele i produse.
Se combina costurile pentru diferite grupari si se mentin cele mai mici K valori unice (in ordine crescatoare) pentru fiecare set de produse.
Pentru a obtine cele K cele mai mici sume, se utilizeaza o functie de interclasare care combina sumele din diferite grupari si elimina duplicatele.
Valoarea din pozitia [N-1][K-1] a matricei indica al K-lea cel mai mic cost, daca exista; altfel, se returneaza -1 daca nu exista suficiente sume unice.

### Observatii si Complexitate:
> Subpunctul a): <span style="color:green">**O(N)**</span>, unde N este numarul de produse, deoarece fiecare produs este procesat o singura data.
>
> Subpunctul b): <span style="color:green">**O(N*K)**</span>, deoarece fiecare dintre cele N produse poate contribui la formarea a pana la K sume unice prin interclasare.
