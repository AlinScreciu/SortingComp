#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
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
void heapify(float arr[], int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i) {
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
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
void heapSort(float arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}
void ts(int i) {
	string smb[3] = { "Small size","Medium size","Big size" };
	int checker = 3;
	vector<float> v;
	string files[7][4] = {
	{"almostSortedSmallList","almostSortedMediumList","almostSortedBigList","Almost sorted"} // almost 1 
	,{"randomSmallList","randomMediumList","randomBigList","Random" } // random 2 
	,{"halfSortedSmallList","halfSortedMediumList","halfSortedBigList","Half sorted"} // half 3 
	,{"invertedSortedSmallList","invertedSortedMediumList","invertedSortedBigList","Reverse Sorted" } // reverse sorted 4
	,{"sortedSmallList","sortedMediumList","sortedBigList","Sorted" } // sorted 5
	,{"smallFloatsBigList","smallIntsBigList","Small numbers"}  // small numbers 6
	, { "WARNINGRequiresThreadripperList","pureRandomGinormousList","Big lists" } }; // big 7

	if (i == 6 || i == 5) checker = 2;
	vector<float> copy = v;
	for (int j = 0; j < checker; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st = high_resolution_clock::now();
		mergeSort(&v[0], 0, v.size() - 1);
		auto ft = high_resolution_clock::now();
		auto d = duration_cast<microseconds>(ft - st);
		if (j == 0 ) cout << files[i][checker]<<":\n\n";
		if (checker == 3) cout << fixed << "merge: " << d.count() / 1000000.0 << "s for " << smb[j] << endl;
		else cout << fixed << "merge: " << d.count() / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		v = copy;
		}
	for (int j = 0; j < checker ; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st1 = high_resolution_clock::now();
		quickSort(&v[0], 0, v.size() - 1);
		auto ft1 = high_resolution_clock::now();
		auto d1 = duration_cast<microseconds>(ft1 - st1);
		/*if (j == 0) cout << files[i][checker] << "\n";*/
		if (checker == 3) cout << fixed << "quick: " << d1.count() / 1000000.0 << "s for " << smb[j] << endl;
		else cout << fixed << "quick: " << d1.count() / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		v = copy;
	}
	for (int j = 0; j < checker; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st1 = high_resolution_clock::now();
		insertionSort(&v[0],  v.size() - 1);
		auto ft1 = high_resolution_clock::now();
		auto d1 = duration_cast<microseconds>(ft1 - st1);
		/*if (j == 0) cout << files[i][checker] << "\n";*/
		if (checker == 3) cout << fixed << "ins: " << d1.count() / 1000000.0 << "s for " << smb[j] << endl;
		else cout << fixed << "ins: " << d1.count() / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		v = copy;
	}
	for (int j = 0; j < checker; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st1 = high_resolution_clock::now();
		bubbleSort(&v[0], v.size() - 1);
		auto ft1 = high_resolution_clock::now();
		auto d1 = duration_cast<microseconds>(ft1 - st1);
		/*if (j == 0) cout << files[i][checker] << "\n";*/
		if (checker == 3) cout << fixed << "bubble: " << d1.count() / 1000000.0 << "s for " << smb[j] << endl;
		else cout << fixed << "bubble: " << d1.count() / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		v = copy;
	}
	for (int j = 0; j < checker; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st1 = high_resolution_clock::now();
		heapSort(&v[0], v.size() - 1);
		auto ft1 = high_resolution_clock::now();
		auto d1 = duration_cast<microseconds>(ft1 - st1);
		/*if (j == 0) cout << files[i][checker] << "\n";*/
		if (checker == 3) cout << fixed << "Heap: " << d1.count() / 1000000.0 << "s for " << smb[j] << endl;
		else cout << fixed << "Heap: " << d1.count() / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		v = copy;
	}
	cout << "\n\n";
	
	}

int main()
	{
		int s,safe=1;
		
		while (safe == 1) {
			bool checks[7];
			bool k1 = false, k2 = false, k3 = false, k4 = false, k5 = false, k6 = false, k7 = false;

			cout << "Choose  what kind of data the alg should be compared over: \n1.Almost sorted data.\n2.Random data.\n\
3.Half sorted data\n4.Reverse sorted  data.\n5.Sorted data.\n6.Small numbers.\n7.Lots of data!! warning for bubble and ins sort!\n";
			cin >> s;
			while (s != 8) {
				if (k1 && (s == 1) || k2 && (s == 2) || k3 && (s == 3) || k4 && (s == 4)
					|| k5 && (s == 5) || k6 && (s == 6) || k7 && (s == 7)) {
					cout << "Already added, enter a diff one or enter 8 to continue!\n";
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
					case 3:
						k3 = true;
						break;
					case 4:
						k4 = true;
						break;
					case 5:
						k5 = true;
						break;
					case 6:
						k6 = true;
						break;
					case 7:
						k7 = true;
						break;
					}
					if (k1 && k2 && k3 && k4 && k5 && k6 && k7) break;
					cout << "To add more one more data type enter the corresponding number, to continue enter 8.\n";
					cin >> s;
				}
			}
			cout << "\n\n\n";
			checks[0] = k1;
			checks[1] = k2;
			checks[2] = k3;
			checks[3] = k4;
			checks[4] = k5;
			checks[5] = k6;
			checks[6] = k7;
			for (int i = 0; i < 7; i++) {
				if (checks[i]) ts(i);
			}
			cout << "Enter 1 to sort the algs on diff data, or 0 to exit.\n";
			cin >> safe;
		}
	}
