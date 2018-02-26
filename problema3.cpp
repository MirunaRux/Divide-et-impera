#include <iostream>
#include <vector>
#include <climits>

using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int N1 = nums1.size(); ///dimensiunea primului vector
    int N2 = nums2.size(); ///dimensiunea celui de-al doilea vector

    if (N1 < N2) return findMedianSortedArrays(nums2, nums1);	/// Ne asiguram ca al doilea vector e mai scurt

    int low = 0, high = N2 * 2; ///capetele vectorului interclasat
    while (low <= high)
     {
        int mid2 = (low + high) / 2;   /// Taietura 2
        int mid1 = N1 + N2 - mid2;  /// Calculam Taietura 1

        double L1 = (mid1 == 0) ? INT_MIN : nums1[(mid1-1)/2]; ///indicele elementului din stanga primei taieturi
        double L2 = (mid2 == 0) ? INT_MIN : nums2[(mid2-1)/2]; ///indicele elementului din stanga celei de-a doua taieturi
        double R1 = (mid1 == N1 * 2) ? INT_MAX : nums1[(mid1)/2]; ///indicele elementului din dreapta primei taieturi
        double R2 = (mid2 == N2 * 2) ? INT_MAX : nums2[(mid2)/2]; ///indicele elementului din dreapta celei de-a doua taieturi

        if (L1 > R2) low = mid2 + 1;		/// partea din stg a lui A1 prea mare; mutam prima taietura la stanga (a doua taietura la dreapta)
        else if (L2 > R1) high = mid2 - 1;	/// partea din stg a lui A2 prea mare; mutam a doua taietura la stanga.
        else return (max(L1,L2) + min(R1, R2)) / 2;	///altfel taietura este corecta
    }
    return -1;
}

int main()
{
    int N1, N2, x;
    vector<int> A1; ///primul vector
    vector<int> A2; ///al doilea vector

    cin>>N1; ///citim primul vector
    for(int i = 0;i < N1; i++)
    {
      cin>>x;
      A1.push_back(x);
    }

    cin>>N2; ///citim al doilea vector
    for(int i = 0;i < N2; i++)
    {
      cin>>x;
      A2.push_back(x);
    }

    cout<<"Mediana:"<<findMedianSortedArrays(A1, A2); ///afisam mediana

    return 0;
}*/
