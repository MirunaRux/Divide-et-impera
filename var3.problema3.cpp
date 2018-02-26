#include <bits/stdc++.h>
using namespace std;

int merge(int arr[], int temp[], int left, int mid, int right);

///functie recursiva care sorteaza vectorul si returneaza numarul de inversiuni
int _mergeSort(int arr[], int temp[], int left, int right)
{
  int mid, inv_count = 0;
  if (right > left)
  {
    mid = (right + left)/2;

    /// numarul total de inversiuni = inversiuni_st + inverisuni_dr + inversiuni_dupa_merge
    inv_count  = _mergeSort(arr, temp, left, mid);

    inv_count += _mergeSort(arr, temp, mid+1, right);

    inv_count += merge(arr, temp, left, mid+1, right);
  }
  return inv_count;
}

///functie care uneste cele doua parti de vector sortate si retrneaza numarul de inversiuni semnificative
int merge(int arr[], int temp[], int left, int mid, int right)
{
  int i, j, k;
  int inv_count = 0;

  i = left; ///index pentru partea stanga
  j = mid;  ///index pentru partea dreapta
  k = left; ///index pentru vectorul rezultat
  while ((i <= mid - 1) && (j <= right))
  {
    if (arr[i] <= 2 * arr[j])
    {
      temp[k++] = arr[i++];
    }
    else
    {
      temp[k++] = arr[j++];

      inv_count += (mid - i); /// sunt mid-i inversiuni pentru ca parile sunt sortate
    }
  }

 ///copiez ce a mai ramas in partea stanga
  while (i <= mid - 1)
    temp[k++] = arr[i++];

  ///copiez ce a mai ramas in partea dreapta
  while (j <= right)
    temp[k++] = arr[j++];

  ///copiez inapoi in arr vectorul sortat
  for (i=left; i <= right; i++)
    arr[i] = temp[i];

  return inv_count;
}

int main(int argv, char** args)
{
  int arr[] = {4, 8, 11, 3, 5};

  int *temp = (int *)malloc(sizeof(int)*4);
  cout<<" Number of inversions are "<< _mergeSort(arr, temp, 0, 4)<<'\n';
  getchar();
  return 0;
}
