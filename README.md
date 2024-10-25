
# Tema 2 - PCLP
**Programarea calculatoarelor si limbajelor de programare**

* In acest program, am folosit functii pentru alocarea dinamica a memoriei unei
matrici, pentru eliberarea memoriei unei matrici, dar si pentru fiecare
caracter citit de la tastatura caruia ii corespunde o comanda specifica.
* In functia main, declaram doi vectori care vor retine dimeniunile pentru
fiecare matrice, unul de linii si unul de coloane. De asemenea, vom declara o
colectie de matrici. Pentru fiecare caracter citit va trebui sa executam o
comanda, astfel:

- Daca caracterul citit este L, vom realoca memorie pentru cei doi vectori care
retin dimensiunile matricelor, dar si pentru colectia de matrici, intrucat va
trebui sa incarcam matricea citita de la tastatura in memorie. Astfel, creste
numarul de matrici, k.

- Daca caracterul citit este D, atunci vom afisa cu ajutorul unei functii
ajutatoare dimeniunile matricei corespunzatoare indexului dat.

- Daca caracterul citit este P, atunci se afiseaza, cu ajutorul unei functii
ajutatoare, matricea corespunzatoare indexului dat. Pentru fiecare matrice din
colectie, avem acces la numarul sau de linii si de coloane prin intermediul
celor doi vectori in care stocam dimensiunile.

- Daca caracterul este C, apelam functia corespunzatoare pentru redimensionarea
matricei. Se citeste de la tastatura indexul pentru care dorim redimensionarea
matricei. Daca indexul dat este unul valid, atunci se citeste in continuare
numarul de linii dupa care se face redimensionarea. Ne vom folosi de un vector
care va retine indicii, caruia ii alocam memorie. Acelasi lucru se va face si
pentru coloana. Cu ajutorul unei matrici auxiliare vom retine elementele
cerute. Se selecteaza pentru fiecare linie si coloana in parte elementul dorit.
Vechea matrice se elibereaza si va primi valoarea auxiliarei.

- Daca caracterul este M, atunci cu ajutorul unei functii ajutatoare vom
calcula rezultatul inmultirii a doua matrici. Rezultatul inmultirii se retine
intr-o matrice alocata dinamica care va avea ca dimensiuni: numarul de linii
de la prima matrice si numarul de coloane de la cea de a doua matrice. Noile
dimensiuni se retin in vectorii corespunzatori. Rezulatul inmultirii se retine
la finalul colectiei de matrici, astfel vom creste numarul de matrici din
colectie.

- Daca caracterul este O, atunci ne folosim de doua functii. Vom calcula
prima data suma fiecarei matrici. Toate sumele vor fi retinute intr-un vector
caruia ii vom aloca memorie pentru a putea face posibila compararea lor. Daca
matricea dinainte are suma mai mare, se face interschimbarea. Vom interschimba,
de aseemenea, matricile corespunzatoare, dar si dimensiunile lor. Astfel se va
face o sortare crescatoare a matricilor in functie de sumele lor.

- Daca caracterul este T, ne folosim de o matrice auxiliara in care vom retine
transpusa matricei corespunzatoare indexului citit. Se construieste astfel
matricea auxiliara. La final, eliberam matricea veche, pentru a-i putea da
noua sa valoare, transpusa sa. Cand se calculeaza matricea transpusa, numarul
de linii va deveni numar de coloane, iar numarul de coloane va deveni numarul
de linii. Astfel, cu ajutorul unei functii de interschimabare a doi pointeri,
interschimbam cele doua dimensiuni.

- Daca caracterul este R, ne vom folosi de o functie de inmultire a matricilor
pentru ridicarea la putere in timp logaritmic. Astfel, vom retine prima data
intr-o matrice auxiliara matricea identica. In cazul in care puterea citita
este impara, vom inmulti matricea corespunzatoare cu matricea identica. In caz
contrar, matricea se va inmulti cu ea insasi.La fiecare pas, vom imparti
puterea data la 2. In final, se elibereaza matricea veche si ii atribuim
noua valoare.

- Daca caracterul este F, vom elibera prima data memoria pentru matricea pe
care dorim sa o eliminam din multime si vom modifica de asemenea vectorul de
 inii, de coloane, dar si colectia, deoarece toate matricile vor fi mutate,
in colectie, cu o pozitie. Vom scadea si numarul matricilor din colectie.

- Daca caracterul este Q, vom elibera fiecare matrice pentru fiecare indice,
dar si vectorii cu dimensiuni si colectia de matrici.

- Daca avem caracterul S, atunci cu ajutorul unei functii ajutatoare vom
calcula rezultatul inmultirii a doua matrici, folosind algorimtul lui Strassen.
Rezultatul inmultirii se retine intr-o matrice alocata dinamica careia ii
vom seta noile dimensiuni. Noile dimensiuni se retin in vectorii
corespunzatori. Rezulatul inmultirii se retine la finalul colectiei de matrici,
astfel vom creste numarul de matrici din colectie.
* Pentru algoritmul Strassen ne-am folosit de urmatoarele functii ajutatoare:
    - get_the_matrices1 care ajuta la determinarea celor 8 blocuri din
    matricile initiale, respectiv A11, A12, A21, A22, B11, B12, B21, B22.
    - add_matrix & dif_matrix care vor calcula suma, respectiv diferenta
    a doua matrici trasmise ca parametru.
    - getc11 & getc12 & getc21 & getc22 care sunt folosite pentru a obtine
    matricea finala (rezultatul inmultirii). Ne folosim de cele 4 blocuri
    calculate cu ajutorul formulelor.
    - allocate_matrices & allocate_matrices_sum care aloca memorie pentru cele
    8 blocuri de matrici extrase din matricile initiale. De asemenea, alocam
    memorie si pentru matricile auxliare necesare algortmului Strassen.
    - free_matrices_sum & free_matrices care elibereaza memoria matricelor
    alocate.
    - strassen: pentru aplicarea recursivă a algoritmului, calculam fiecare
    dintre cele 7 matrice auxiliare:
       - **P1 = (A11 + A22) * (B11 + B22)**
       - **P2 = (A21 + A22) * B11**
       - **P3 = A11 * (B12 - B22)**
       - **P4 = A22 * (B21 - B11)**
       - **P5 = (A11 + A12) * B22**
       - **P6 = (A21 - A11) * (B11 + B12)**
       - **P7 = (A12 - A22) * (B21 + B22)**
        - In final se determina cele 4 blocuri din matricea finala:
       - **C11 = P1 + P4 - P5 + P6**
       - **C12 = P3 + P5**
       - **C21 = P2 + P4**
       - **C22 = P1 - P2 + P3 + P6**
