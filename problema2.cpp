#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("date.in.txt");
ofstream g("date.out.txt");

struct nod
{
    int data;
    nod *stg,*dr;
};

nod* newNode(int nr) ///functie care returneaza un nod cu informatia nr
{
    nod *aux=new nod;
    aux->stg=aux->dr=NULL;
    aux->data=nr;
    return aux;
}

void preOrdine(nod *root) ///parcurgerea arborelui in preordine RSD
{
    if(root)
    {
        g<<root->data<<" ";
        preOrdine(root->stg);
        preOrdine(root->dr);
    }

}
void inOrdine(nod *root) ///parcurgerea arborelui in inordine SRD
{
    if(root)
    {
        inOrdine(root->stg);
        g<<root->data<<" ";
        inOrdine(root->dr);
     }
}
void postOrdine(nod *root) ///parcurgerea arborelui in postordine SDR
{
    if(root)
    {
        postOrdine(root->stg);
        postOrdine(root->dr);
        g<<root->data<<" ";
    }
}
nod* Build_Tree(vector<int> &inord, vector<int> &postord,vector <int> &poz, int inordStart, int inordEnd, int &pIndex, bool &valid)
{ ///functie care construieste arborele

    if(!valid) ///daca nu e valid returneaza NULL
        return NULL;

    if(inordStart > inordEnd) /// daca pozitia de start > pozitia de final returneaza NULL
        return NULL;

    nod *node = newNode(postord[pIndex]); ///creeaza un nou nod - ultimul nod din parcurgerea in postordine = radacina arborelui mare

    pIndex--;

    if(inordStart == inordEnd)
        return node;

    int index=poz[node->data]; ///identific radacina in parcurgerea in inoridine si ii retin pozitia

    if(index>=inordStart && index<=inordEnd)
    {
        node->dr=Build_Tree(inord,postord,poz,index+1,inordEnd,pIndex,valid); ///apelez functia pentru subarborele stang in inordine
        node->stg=Build_Tree(inord,postord,poz,inordStart,index-1,pIndex,valid); ///apelez functia pentru subarborele drept in inordine
        return node; /// returnez radacina daca arborele e valid
    }
    else
    {
        valid=0;
        return NULL;
    }
}
 void checkTree(nod* root, int& nr, int n)
 {
    if(root)
    {
        nr++;
        checkTree(root->stg,nr,n);
        checkTree(root->dr,nr,n);
    }
 }
int main()
{
    int n, x, pIndex, nr = 0;

    vector<int> inord, postord; ///parcurgerile

    bool valid = 1; ///verifica daca arborele format este valid sau nu

    nod *root; ///radacina arborelui

    f>>n; ///numarul de noduri

    vector<int> poz(n,0); ///vector de pozitii ale nodurilor arborelui in parcurgerea in inordine

    for(int i = 0;i < n; i++) ///se citeste parcurgerea in postordine
    {
        f>>x;
        postord.push_back(x);
    }
    for(int i = 0;i < n; i++) ///se citeste parcurgerea in inordine
    {
        f>>x;
        inord.push_back(x);
        poz[x] = i; ///si pentru fiecare nod se retine pozitia in parcurgere
    }

    pIndex = n - 1;

    root = Build_Tree(inord, postord, poz, 0, n - 1, pIndex, valid); ///se creaza arborele

    if(valid) ///se verifica daca e valid
    { ///se afiseaza parcurgerile
        preOrdine(root);
        g<<endl;
        inOrdine(root);
        g<<endl;
        postOrdine(root);
    }

    else g<<"nu";

    return 0;
}
