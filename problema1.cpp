#include <iostream>

using namespace std;

int cauta(int v[], int low, int high) ///functie de caurate binara in vector
{
    if(high >= low)
    {
        int mid = (low + high)/2; ///luam jumatatea

        if(mid == v[mid]) ///daca elementul din mijloc indeplineste cerinta il returnam
           return mid;

        if(mid > v[mid]) ///altfel
            return cauta(v, (mid + 1), high);   ///cautam in dreapta cand indicele > valoarea
        else
            return cauta(v, low, (mid -1));     ///cautam in stanga cand indicele < valoarea
    }

    return -1;   ///returneaza -1 daca nu exista
}

int main()
{
    int n,v[50];
    cout<<"n= ";
    cin>>n;

    for(int i = 0;i < n; i++)
        cin>>v[i];

    cout<<endl;

    cout<<cauta(v, 0, n-1);

    return 0;
}
