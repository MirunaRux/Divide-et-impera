#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int st, dr, k = 0;

vector<string> v;

ifstream f("date.in");
ofstream g("date.out");

struct nod
{
   string valoare;
    nod * stanga;
    nod * dreapta;
};

int ok = 1;

nod *inserare() ///parcurgerea in preordine si crearea arborelui
{
    nod*p = NULL;
    string x;

    if(f>>x)
    {
        p = new nod;
        p->valoare = x;
        cout<<x<<" ";
        p->stanga = inserare();
        p->dreapta = inserare();
    }
    return p;
}

void RSD (nod*prim) ///parcurgerea in preordine si verificarea daca este arbore binar de cautare sau nu
{
    if(prim != NULL)
     {
         if(prim->stanga != NULL && prim->dreapta != NULL) ///daca exista ambii fii
            if(!(prim->stanga->valoare < prim->valoare && prim->dreapta->valoare > prim->valoare)) ///fiu stanga > tata > fiu dreapta ca sa fie arb binar de caut.
               ok = 0;
         RSD(prim->stanga);
         RSD(prim->dreapta);
     }
}

int main()
{
    nod*r = new nod; ///radacina

    r = inserare(); ///creem arborele

    RSD(r); ///parcurgemdin radacina si verificam daca e binar de cautare sau nu

    if(!ok)
       g<"nu";
    else
       g<<"da";

    f.close();

    g.close();

    return 0;
}
