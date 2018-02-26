#include <iostream>
#include <float.h>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;

ifstream f("cmap.in");
ofstream g("cmap.out");

const int NMAX = 128000;

struct Punct
{
    int x, y;
};

bool cmpX(Punct a, Punct b) /// functie care compara doua puncte dupa abscisa
{
    return a.x < b.x;
}

bool cmpY(Punct a, Punct b) /// functie care compara doua puntcte dupa ordonata
{
    return a.y < b.y;
}

long double dist(Punct p1, Punct p2) /// functie care calculeaza distanta dintre doua puncte
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

long double distMin(Punct P[], int n) /// functie care calculeaza minimul dintre distante cu forta bruta atunci cand sunt 3 sau mai putine elemente
{
    long double min = FLT_MAX;
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

long double min(long double x, long double y) /// functie care calculeaza minimul dintre doua numere
{
    return (x < y)? x : y;
}

long double distMinBanda(Punct banda[], int n, long double d) /// functie care calculeaza distanta minima dintre doua puncte din banda de latime 2d
{ /// aflata in vecinatatea dreptei "divide"
  ///d = distanta minima dintre dist_min_st si dist_min_dr
    long double d_min = d;

    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n && (banda[j].y - banda[i].y) < d_min; ++j)
            if (dist(banda[i],banda[j]) < d_min)
                d_min = dist(banda[i], banda[j]);

    return d_min;
}

long double divImp(Punct Px[], Punct Py[], int n) /// functie care divizeaza vectorul si calculeaza dist_min_st si dist_min_dr
{
    if (n <= 3)
        return distMin(Px, n);

    int mij = n/2;
    Punct mijPunct = Px[mij];

    Punct Pyl[mij+1]; ///contine punctele din stanga punctului de mijloc
    Punct Pyr[n-mij-1]; ///consine punctele din dreapta punctului de mijloc

    int st = 0, dr = 0;
    for (int i = 0; i < n; i++)
        if (Py[i].x <= mijPunct.x)
            Pyl[st++] = Py[i];
        else
            Pyr[dr++] = Py[i];

    long double dminSt = divImp(Px, Pyl, mij);
    long double dminDr = divImp(Px + mij, Pyr, n-mij);

    long double d_min = min(dminSt, dminDr); /// apoi calculeaza minimul dintre ele

    Punct banda[n]; /// vector care retine punctele din banda
    int pb = 0; ///numar puncte banda
    for (int i = 0; i < n; i++)
        if (abs(Py[i].x - mijPunct.x) < d_min)
            banda[pb++] = Py[i];

    return min(d_min, distMinBanda(banda, pb, d_min)); /// se returneaza minimul final
}

int main()
{
    Punct P[NMAX];
    int n;

    f>>n;
    for(int i = 1;i <= n; i++)
        f>>P[i].x>>P[i].y;

    f.close();

    Punct Px[n];
    Punct Py[n];

    for (int i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }

    sort(Px, Px + n, cmpX);
    sort(Py, Py + n, cmpY);

    g<<fixed<<setprecision(6)<<divImp(Px, Py, n)<<'\n';

    g.close();

    return 0;
}
