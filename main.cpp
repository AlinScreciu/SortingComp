#include <algorithm> 
#include <chrono> 
#include <iostream> 
#include<vector>
#include <fstream>
#include <string>
using namespace std;
using namespace std::chrono;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1);
    vector<int> R(n2);


    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;


    int j = 0;

    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}
void quickSort(int arr[], int low, int high) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
    if (low < high)
    {

        int pi = partition(arr, low, high);


        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void bubbleSort(int arr[], int n)  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{ 
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}
void insertionSort(int arr[], int n) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
int main()
{

    vector<int> v;
    int a;
    string files[5] = { "Dataset/BigList.txt",
    "Dataset/GinormousList.txt",
    "Dataset/MediumList.txt",
    "Dataset/SmallIntSmallList.txt",
    "Dataset/smallList.txt" };
    for (int i = 0; i < 5; i++) {
        vector<int> v;
        ifstream temp(files[i]);
        float a;
        while (temp >> a) {
            v.push_back(a);
        }
        auto start1 = high_resolution_clock::now();
        quickSort(&v[0], 0, v.size() - 1);
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        cout << "Quick sort took " << duration1.count() / 1000000.0 << " seconds to sort" << files[i]<<"\n\n\n";
    }
    /* choose sorts and on what sets and if you want to avg results from more runs*/
/*vector<int> values(55000);
    vector<int> copyV(55000);
    auto f = []() -> int { return rand() % 100000; };
    static const int ITER = 100;
    generate(values.begin(), values.end(), f);
    copyV = values;
    double arr[ITER],arr1[ITER],arr2[ITER], arr3[ITER];
    for (int j = 0; j < ITER; j++) {
        auto start1 = high_resolution_clock::now();
        quickSort(&copyV[0], 0, copyV.size() - 1);
        auto stop1 = high_resolution_clock::now();
        copyV = values;
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        arr[j] = duration1.count()/1000000.0;

        auto start2 = high_resolution_clock::now();
        mergeSort(&copyV[0], 0, copyV.size() - 1);
        auto stop2 = high_resolution_clock::now();
        copyV = values;
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        arr1[j] = duration2.count() / 1000000.0;
        auto start3 = high_resolution_clock::now();
        insertionSort(&copyV[0], copyV.size() - 1);
        auto stop3 = high_resolution_clock::now();
        copyV = values;
        auto duration3 = duration_cast<microseconds>(stop3 - start3);
        arr2[j] = duration3.count() / 1000000.0;
        auto start4 = high_resolution_clock::now();
        bubbleSort(&copyV[0], copyV.size() - 1);
        auto stop4 = high_resolution_clock::now();
        copyV = values;
        auto duration4 = duration_cast<microseconds>(stop4 - start4);
        arr3[j] = duration4.count() / 1000000.0;
    }
    double s = 0;
    for (int j = 0; j < 10; j++) {
        s += arr[j];
    }
    cout << s/(sizeof(arr) / sizeof(*arr))<<" seconds avg of "<< (sizeof(arr) / sizeof(*arr))<<" quicksort runs \n";
    for (int j = 0; j < 10; j++) {
        s += arr1[j];
    }
    cout << s / (sizeof(arr1) / sizeof(*arr1)) << " seconds avg of " << (sizeof(arr1) / sizeof(*arr1)) << " merge runs \n";
    for (int j = 0; j < 10; j++) {
        s += arr1[j];
    }
    cout << s / (sizeof(arr2) / sizeof(*arr2)) << " seconds avg of " << (sizeof(arr2) / sizeof(*arr2)) << " inssrt runs \n";
    for (int j = 0; j < 10; j++) {
        s += arr1[j];
    }
    cout << s / (sizeof(arr3) / sizeof(*arr3)) << " seconds avg of " << (sizeof(arr3) / sizeof(*arr3)) << " bblsrt runs \n";
    return 0; */
}
