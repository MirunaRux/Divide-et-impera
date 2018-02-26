#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <vector>
#include <iomanip>
using namespace std;

ifstream f("date.in");
ofstream g("date.out");

struct val
{
  float x; ///vectorul x
  float w; ///vectorul cu ponderi

}X;

int n, p; /// n - numarul de elemente din cei doi vectori

vector<val>v; ///structura care retine ambii vectori

void Pivot(int st, int dr, int&p) ///functie care calculeaza pivotul pentru functia de divide et impera
{
    p = dr; ///initial este pozitionat pe ultimul element
    int piv = v[dr].x; ///luam x-ul pivotului
    int ok = 0, ok2 = 0, minn = -1, maxx = -1;

    while(maxx <= minn)
    {
        ok = 0;
        ok2 = 0;

        for(int i = st;i < dr; i++) ///parcurgem vectorul x
            {
                if(v[i].x > piv && !ok) ///cand gasim o valoare > decat x-ul pivotului
                   {
                       maxx = i; /// ii retinem pozitia
                       ok = 1;
                   }
                if(ok)
                   break; ///si ne oprim din cautat
            }
        if(maxx == -1) ///daca nu am gasit o astfel de valoare iesim din while
            break;
        for(int i = dr - 1;i >= st; i--) ///altfel cautam in continuare o valoare < decat x-ul pivotului
            {
                if(v[i].x < piv && !ok2) ///daca am gasit
                    {
                        minn = i; ///ii retinem pozitia
                        ok2 = 1;
                    }
                if(ok2)
                   break; ///si ne oprim din cautat
            }
        if(minn == -1) ///daca nu am gasit o astfel de valoare iesim din while
           break;
        if(maxx <= minn) ///altfel daca valoarea > decat x-ul pivotului este <= valoarea mai < decat x-ul pivotului
           swap(v[minn], v[maxx]); ///le inversam
    }

    if(maxx > minn)
      {
          swap(v[dr], v[maxx]);
          p = maxx;
      }
}

 void rezolvare(int st, int dr)
{
    float sl = 0,sr = 0; ///sl = suma din stanga pivotului ; sr = suma din dreapta pivotului

    Pivot(st, dr, p); ///calculam pivotul

    for(int i = 0;i < p; i++) ///calculam suma ponderilor din stanga pivotului
        sl += v[i].w;

    if(p + 1 < n)
       for(int j = p + 1;j < n; j++) ///calculam suma ponderilor din dreapta pivotului
           sr += v[j].w;

    if(sl >= 0.5) ///daca suma din stanga este prea mare apelam functia pentru partea stanga
       rezolvare(st, p - 1);

    if(sr > 0.5) ///daca suma din dreapta este prea mare apelam functi pentru partea dreapta
       rezolvare(p + 1, dr);

    if(sl < 0.5 && sr <= 0.5) ///daca sumele sunt exact cat trebuie l-am aflat pe Xk
       g<<v[p].x;
}

int main()
{
    f>>n;

    for(int i = 0;i < n; i++) ///se citesc cei doi vectori
        {
            f>>X.x>>X.w;
            v.push_back(X);
        }

    rezolvare(0, n - 1);

    f.close();
    g.close();
    return 0;
}
