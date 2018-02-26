#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void divideEtImpera(int x, int y, int l, int &pas, int a, int b, int &rez)
{
    if(l == 0) return; ///l este latura patratelului

    if (l == 1) ///daca este 1
    {
        pas++; ///adaugam o valoare in patratel (valorile vor fi consecutive in parcurgere)
        if(x == a && y == b) ///verificam daca este pozitia pe care o cautam
        {
            rez = pas; ///daca da, ii retinem valoarea
            return;
        }
    }
    else ///altfel pentru patratele cu latura >= 2
    {
        divideEtImpera(x, y, l / 2, pas, a, b, rez); ///primul cadran
        divideEtImpera(x, y + l / 2, l / 2, pas, a, b, rez); ///al doilea cadran
        divideEtImpera(x + l / 2, y, l / 2, pas, a, b, rez); ///al treilea cadran
        divideEtImpera(x + l / 2, y + l / 2, l / 2, pas, a, b, rez); ///al patrulea cadran
        ///patratul de latura l se imparte in 4 patratele mai mici, iar originea patratului este in stanga sus
    }
}

int main()
{
    int p, n, k, x, y, r, p2;

    fstream fin("z.in", ios :: in);
    fstream fout("z.out", ios :: out);

    fin >> n >> k; ///k - nr de patratele din care vrem sa aflam valoarea
    p2 = 1 << n; ///p2 = 2 ^ n

    for(int i = 1; i <= k; i++) /// se citesc coordonatele celor k patratele
    {
        fin >> x >> y;
        p = 0;
        divideEtImpera(1, 1, p2, p, x, y, r); ///se parcurge recursiv in forma de Z matricea fara a fi memorata pentru a gasi valoarea de pe poz (x,y)
        fout << r << endl; ///si se afiseaza valoarea gasita
    }

    fin.close();
    fout.close();

    return 0;
}
