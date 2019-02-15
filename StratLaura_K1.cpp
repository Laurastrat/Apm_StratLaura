/*
Probleme :
(I) Arbore partial de cost minim intr-un NDG ponderat  - problema APM

Pseudocod :
- citeste G(X,U)
- sorteaza muchiile din G crescator dupa costuri
- pentru i=1 pana la n-1 executa
                                         - unificare i
                                        sf_executa

 Probleme :
 - cum reprezint setul arborilor disjuncti ?
 - cum execut unificarile ?

        * 1
     /       \
    / 1        \  1
   *2--------*3
  |       77    |
  | 1            | 1
  *4--------*5
           66

===================
[a] preparative :
1. citirea datelor de intrare
2. sortarea colectiei de muchii dupa costuri
     = >  STL ! <algorithm> , sort
[b] questions :

 - cum reprezint setul arborilor disjuncti ?
 - cum execut unificarile ?

 In modalitatea aleasa pentru rezolvare APM optam pentru
 algoritmul lui Kruskal

 (-) Setul arborilor disjuncti il reprezint cu ajutorul
unui vector Vin care aplic codificarea :

L[i]=j  inseamna ca nodul i apartine arborelui partial de cost minim j
Asadar la pasul initial ( inaintea sirului de unificari )
voi avea :

for(int i=1;i<=n;i++) L[i]=i;

adica :
in L ( prin codificarile practicate ) construiesc setul arborilor disjuncti
singleton ( fiecare nod i face parte dintr-un arbore i --- graful cu un singur
nod, faca nici o muchie il consider arbore )

Asadar algoritmul propus parcurge setul arborilor disjuncti
in cautarea primei muchii cu extremitati in arbori disjuncti
pentru a face unificarea.

exemplu G :

        * 1
     /       \
    / 1        \  1
   *2--------*3
  |       77    |
  | 1            | 1
  *4--------*5
           66

G ca o colectie de muchii sortate crescator dupa costul este :
5
        cost
1 2     1
1 3     1
2 4     1
3 5     1
4 5     66
2 3     77

L intial este

       -------------------------
L : | 1 | 2   | 3   | 4   |  5 |
      -------------------------
        1     2      3      4      5

 execut sirul celor n-1 unificari  cautand in L muchie de cost
 minim cu extremitati in arbori disjuncti
astfel :
parcurg sirul muchiilor ordonate dupa costuri
        - pentru muchie curenta (i,j) daca extremitatile sale in L
            sunt in arbori disjuncti atunci
                            - execut unificare ( nume nod extremitate "dreapta"
                                                il depun in arborele extremitatii "stangi"

OBS : evident sunt de practicat optimizari IMPORTANTE   !!!!

- citeste G(X,U)
- sorteaza muchiile din G crescator dupa costuri
- intializea L
- pentru i=1 pana la n-1 executa
                  pentru j=1 pana la m numarul de muchii executa
                          daca L[G[j][1]] !=L[G[j][2]]   atunci
                                      - afiseaza  G[j][1]  si G[j][2]
                                      -  pentru k=1 pana la n
                                            daca L[k]=L[G[j][2]] atunci L[k]=L[G[j][1]]


                                        sf_executa

*/

#include<fstream>
#include<iostream>
using namespace std;
int n, m=1;
int top;
int l[100];

typedef struct
{
    int x;
    int y;
    double cost;
}muchie;

muchie v[100];

ifstream fin("input.dat");
ofstream fout("output.dat");

int read_data()
{
    fin>>n;
    while(true)
    {
        fin>>v[m].x;
        fin>>v[m].y;
        fin>>v[m].cost;
        m++;
        if(fin.eof()) break;
    }
    m=m-2;
    for(int i=1;i<=n;i++)
        l[i]=i;
    fin.close();
    return 0;
}

int sort_data()
{
    int g=0;
    while(g==0)
    {
        g=1;
        for(int i=1;i<m;i++)
            if(v[i].cost>v[i+1].cost)
            {
                swap(v[i].cost,v[i+1].cost);
                swap(v[i].x,v[i+1].x);
                swap(v[i].y,v[i+1].y);
                g=0;
            }
    }
}

int arbori()
{
    int i=0;
    for(int j=1;j<=m;j++)
    {
        if(l[v[j].x]!=l[v[j].y])
        {
            cout<<v[j].x<<" "<<v[j].y<<endl;
            int z=l[v[j].y];
            i++;
            for(int k=1;k<=n;k++)
                if(l[k]==z)
                    l[k]=l[v[j].x];
        }
        if(i==n-1)
            break;
    }
}

int main()
{
    read_data();
    sort_data();
    arbori();
}
