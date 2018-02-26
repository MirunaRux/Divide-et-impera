#include <iostream>
#include <fstream>
#include <limits.h>
using namespace std;

fstream f("date.in", ios :: in);

const int NMAX = 100;

int a[NMAX];
int n;
int varf;

void citire()
{
    f>>n;

    for(int i = 1;i <= n; i++)
    {
       f>>a[i];
    }

    f.close();
}

int determinare(int st, int dr)
{
    int piv = (st + dr)/2; ///se ia "mijlocul"

    if(a[piv] > a[piv + 1] && a[piv] > a[piv - 1]) ///daca valoarea lui este mai mare decat vecinii
        return a[piv]; ///inseamna ca este varful
    else
    if(st =< 1 || dr >= n) ///altfel daca s-a iesit din vector returneaza -1
        return -1;
    else
    if(a[piv] > a[piv + 1] && a[piv] < a[piv - 1]) ///altfel daca valoarea "mijlocului" este > vecinul din dr, dar < decat vecinul din stg
        return determinare(st, piv - 1); ///apelam functia pentru partea din stanga a pivotului
    else
    if(a[piv] < a[piv + 1] && a[piv] > a[piv - 1]) ///altfel daca valoarea"mijlocului" este < vecinul din dr, dar > decat vecinul din stg
    return determinare(piv + 1, dr); ///apelam functia pentru partea din dreapta pivotului

}

int main()
{
    citire();

    cout<<determinare(1, n)<<'\n';

    return 0;
}
