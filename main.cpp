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
void quickSort(float arr[], int low, int high) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
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
void ts(int i) {
	vector<float> v;
	string files[2] = { "dataset/smallIntsBigList.txt","dataset/randomBigList.txt" };
	ifstream test(files[i]);
	ofstream check("dataset/checkBIg.txt");
	float a;
	while (test >> a) { v.push_back(a); }
	vector<float> copy = v;
	auto st = high_resolution_clock::now();
	mergeSort(&v[0], 0, v.size() - 1);
	auto ft = high_resolution_clock::now();
	auto d = duration_cast<microseconds>(ft - st);
	cout << fixed << d.count() / 1000000.0 << "s merge\n";
	v = copy;
	auto st1 = high_resolution_clock::now();
	quickSort(&v[0], 0, v.size() - 1);
	auto ft1 = high_resolution_clock::now();
	auto d1 = duration_cast<microseconds>(ft1 - st1);
	cout << fixed << d1.count() / 1000000.0 << "s qck\n";
	v = copy;
	}

int main()
{
	int s;
	bool checks[5];
	bool k1 = false, k2 = false;
	cout << "Choose  what kind of data the alg should be compared over:\n1.Almost sorted data.\n2.Random data.\n";
	cin >> s;
	while (s != 3) {
		if (k1 && (s == 1) || k2 && (s == 2)) {
			cout << "Already added, enter a diff one or enter 3 to continue!\n";
			cin >> s;
		}
		else {
			switch (s) {
			case 1:
				k1 = true;
				break;
			case 2:
				k2 = true;
				break;
			}
			if (k1 && k2) break;
			cout << "To add more one more data type enter the corresponding number, to continue enter 3.\n";
			cin >> s;
		}
	}
	checks[0] = k1;
	checks[1] = k2;
	for (int i = 0; i < 5; i++) {
		if (checks[i]) tQS(i);
	}
	
}
