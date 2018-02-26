#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

ifstream f("date.in");
ofstream g("date.out");

int t = 1, x, y;

int nr_mat() ///functie care calculeaza 2^n
{
    int n, s = 1;

    f>>n>>x>>y; ///2^n - latura matricei; x si y - coordonatele gaurii din matrice

    for(int i = 1;i <= n; i++)
        s = s * 2;

    return s; ///returneaza latura matricei
}

int s = nr_mat(), p = s;
int v[200][200]; ///matricea

void Piesa( int a, int b, int latx, int laty)
{
    if(a <= latx && b <= laty && v[latx + 1][laty] == 0 && v[latx][laty + 1] == 0 && v[latx + 1][laty + 1] == 0)
        {
            ///    ___
            ///       |
            ///       |
            v[latx + 1][laty] = t;
            v[latx][laty + 1] = t;
            v[latx + 1][laty + 1] = t;
        }
    else
        if(a <= latx && b > laty && v[latx + 1][laty] == 0 && v[latx][laty] == 0 && v[latx + 1][laty + 1] == 0)
            {
                ///       |
                ///       |
                ///    ---
                v[latx][laty] = t;
                v[latx + 1][laty] = t;
                v[latx + 1][laty + 1] = t;
            }
    else
        if(a > latx && b > laty && v[latx + 1][laty] == 0 && v[latx][laty + 1] == 0 && v[latx][laty] == 0)
            {
                ///    |
                ///    |
                ///     ---
                v[latx][laty] = t;
                v[latx + 1][laty] = t;
                v[latx][laty + 1] = t;
            }
    else
        if(a > latx && b <= laty && v[latx][laty] == 0 && v[latx][laty + 1] == 0 && v[latx + 1][laty + 1] == 0)
            {
                ///    ___
                ///   |
                ///   |
                v[latx][laty] = t;
                v[latx][laty + 1] = t;
                v[latx + 1][laty + 1] = t;
            }
     t++;
}

void rezolvare( int a, int b, int latx, int laty, int dim)
{
    Piesa(a, b, latx, laty);

    dim = dim / 2;

    if(dim > 1 && a <= latx && b <= laty)
        {
            rezolvare(a, b, latx - dim / 2, laty - dim / 2, dim);
            rezolvare(latx, laty + 1, latx - dim / 2, laty + dim / 2, dim);
            rezolvare(latx + 1, laty, latx + dim / 2, laty - dim / 2, dim);
            rezolvare(latx + 1, laty + 1, latx + dim / 2, laty + dim / 2, dim);
        }

    if(dim > 1 && a <= latx && b > laty)
        {
            rezolvare(latx, laty, latx - dim / 2, laty - dim / 2, dim);
            rezolvare(a, b, latx - dim / 2, laty + dim / 2, dim);
            rezolvare(latx + 1, laty, latx + dim / 2, laty - dim / 2, dim);
            rezolvare(latx + 1, laty + 1, latx + dim / 2, laty + dim / 2, dim);
        }

    if(dim > 1 && a > latx && b > laty)
        {
            rezolvare(latx, laty, latx - dim / 2, laty - dim / 2, dim);
            rezolvare(latx, laty + 1, latx - dim / 2, laty + dim / 2, dim);
            rezolvare(latx + 1, laty, latx + dim / 2, laty - dim / 2, dim);
            rezolvare(a, b, latx + dim / 2, laty + dim / 2, dim);
        }

    if(dim > 1 && a > latx && b <= laty)
        {
            rezolvare(latx, laty, latx - dim / 2, laty - dim / 2, dim);
            rezolvare(latx + 1, laty, latx - dim / 2, laty + dim / 2, dim);
            rezolvare(a, b, latx + dim / 2, laty - dim / 2, dim);
            rezolvare(latx + 1, laty + 1, latx + dim / 2, laty + dim / 2, dim);
        }
}

int main()
{
    int n;

    rezolvare(x, y, s / 2,s / 2, s); ///se acopera matricea cu piese

    v[x][y] = 0; ///gaura in matrice e reprezentata de un 0

    for(int i = 1;i <= s; i++) ///afisarea matricei acoperite de piese
        {
            for(int j = 1;j <= s; j++)
                g<<v[i][j]<<" ";
            g<<endl;
        }

    f.close();
    g.close();

    return 0;
}
