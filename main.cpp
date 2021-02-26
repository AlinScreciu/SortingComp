#include <algorithm>
#include <chrono>
#include <iostream>
#include<vector>
#include <fstream>
#include <string>
using namespace std;
using namespace std::chrono;

void swap(float* a, float* b)
{
	float t = *a;
	*a = *b;
	*b = t;
	//cout << *a <<" "<< *b << "\n";
}
int partition(float arr[], int low, int high)
{
	float pivot = arr[high];
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
void merge(float arr[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;
	vector<float> L(n1);
	vector<float> R(n2);

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
void mergeSort(float arr[], int l, int r) {
	if (l >= r) {
		return;
	}
	int m = l + (r - l) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);
	merge(arr, l, m, r);
}
void quickSort(float arr[], float low, float high) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	if (low < high)
	{
		float pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1.0);
		quickSort(arr, pi + 1.0, high);
	}
}
void bubbleSort(float arr[], int n)  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}
void insertionSort(float arr[], int n) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	int i, j;
	float key;
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
	vector<float> v;
	ifstream test("dataset/smallIntsBigList.txt");
	ofstream check("dataset/checkBIg.txt");
	float a;
	while (test >> a) { v.push_back(a); }
	auto st = high_resolution_clock::now();
	mergeSort(&v[0],0,v.size() - 1);
	auto ft = high_resolution_clock::now();
	auto d = duration_cast<microseconds>(ft - st);
	cout<<fixed<< d.count()/1000000.0<<" s";
	for (int i = 0; i < v.size(); i++) {
		check << v[i]<<"\n";
	}
}
