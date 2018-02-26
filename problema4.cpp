#include <iostream>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <iomanip>


using namespace std;

ifstream f("cmap.in");
ofstream g("cmap.out");

struct Punct
{
    int x, y;
};

/// sortarea punctelor dupa coordonata x
int compareX(const void* a, const void* b)
{
    Punct *p1 = (Punct *)a,  *p2 = (Punct *)b;
    return (p1->x - p2->x);
}
/// sortarea punctelor dupa coordonata y
int compareY(const void* a, const void* b)
{
    Punct *p1 = (Punct *)a,   *p2 = (Punct *)b;
    return (p1->y - p2->y);
}

/// functie ce afla distanta dintre puncte
float dist(Punct p1, Punct p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) );
}

/// o functie ce returneaza cea mai mica distanta dintre 2 pct
float bruteForce(Punct P[], int n)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

float min(float x, float y)
{
    return (x < y)? x : y;
}

///functie ce gaseste distanta dintre punctele retinute in vectorul strip[]
/// Aceasta functie pare ca are complexitatea O(n^2), dar este O(n) deoarece bucla se repeta de maxim 6 ori
float stripClosest(Punct strip[], int size, float d)
{
    float min = d;  /// Initializam distanta minima cu d

    qsort(strip, size, sizeof(Punct), compareY); ///sortam dupa y

    ///luam toate punctele unul cate unul si le incercam pana cand diferenta dintre coordonatele y este mai mica decat d
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}

/// Fct recursiva pt a afla cea mai mica distanta. P contine toate punctele sortate dupa x
float closestUtil(Punct P[], int n)
{
    /// Daca sunt 2 sau 3 puncte folosim fct speciala
    if (n <= 3)
        return bruteForce(P, n);

    int mid = n/2;           /// aflam mijlocul
    Punct midPoint = P[mid];

    ///consideram linia verticala ce trege prin pct din mijloc
    ///retinem in dl cea mai mica distanta din stanga mijlocului si in dr cea mai mica distanta din dreapta
    float dl = closestUtil(P, mid);
    float dr = closestUtil(P + mid, n-mid);

    float d = min(dl, dr);      /// luam cea mai mica valoare dintre dl si dr

    ///construim un vector de puncte strip[] ce contine punctele apropiate de linia ce trece prin mijloc (pct cu o distanta mai mica decat d)
    Punct strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip[j] = P[i], j++;

    return min(d, stripClosest(strip, j, d) );   ///returneaza minimul dintre d si cea mai mica distanta dintre punctele din strip[]
}

float closest(Punct P[], int n)
{
    qsort(P, n, sizeof(Punct), compareX);

    return closestUtil(P, n);
}

int main()
{
    long n;
    f >> n;
    Punct P[n];
    for (int i = 0; i < n; i++)
    {
        f >> P[i].x;
        f >> P[i].y;

    }
    g<< fixed <<setprecision(6)<<closest(P, n);
    f.close();
    g.close();
    return 0;
}
