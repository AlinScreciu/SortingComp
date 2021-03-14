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
void countSort(vector<float> &arr)
{
	float max = *max_element(arr.begin(), arr.end());
	float min = *min_element(arr.begin(), arr.end());
	int range = max - min + 1;

	vector<float> count(range), output(arr.size());
	for (int i = 0; i < arr.size(); i++)
		count[arr[i] - min]++;

	for (int i = 1; i < count.size(); i++)
		count[i] += count[i - 1];

	for (int i = arr.size() - 1; i >= 0; i--) {
		output[count[arr[i] - min] - 1] = arr[i];
		count[arr[i] - min]--;
	}

	for (int i = 0; i < arr.size(); i++)
		arr[i] = output[i];
}
vector<float> t;
void ts(int i) {
	// i = 1 qs = 16, ins = 25 ,every time bbl = 20
	int checker = 25, qs = 16, bbl =20,ins=20;
	
	
	vector<float> v;
	string files[7][25] = {
	{"10ALMOSTSORTED", "30ALMOSTSORTED", "50ALMOSTSORTED", "70ALMOSTSORTED", "90ALMOSTSORTED", "100ALMOSTSORTED", "300ALMOSTSORTED", "500ALMOSTSORTED", "700ALMOSTSORTED", "900ALMOSTSORTED", "1000ALMOSTSORTED", "3000ALMOSTSORTED", "5000ALMOSTSORTED", "7000ALMOSTSORTED", "9000ALMOSTSORTED", "10000ALMOSTSORTED", "30000ALMOSTSORTED", "50000ALMOSTSORTED", "70000ALMOSTSORTED", "90000ALMOSTSORTED", "100000ALMOSTSORTED", "300000ALMOSTSORTED", "500000ALMOSTSORTED", "700000ALMOSTSORTED", "900000ALMOSTSORTED"} // almost 1
	,{"10RANDOMFLOAT", "30RANDOMFLOAT", "50RANDOMFLOAT", "70RANDOMFLOAT", "90RANDOMFLOAT", "100RANDOMFLOAT", "300RANDOMFLOAT", "500RANDOMFLOAT", "700RANDOMFLOAT", "900RANDOMFLOAT", "1000RANDOMFLOAT", "3000RANDOMFLOAT", "5000RANDOMFLOAT", "7000RANDOMFLOAT", "9000RANDOMFLOAT", "10000RANDOMFLOAT", "30000RANDOMFLOAT", "50000RANDOMFLOAT", "70000RANDOMFLOAT", "90000RANDOMFLOAT", "100000RANDOMFLOAT", "300000RANDOMFLOAT", "500000RANDOMFLOAT", "700000RANDOMFLOAT", "900000RANDOMFLOAT"} // random 2
	,{"10HALFSORTED", "30HALFSORTED", "50HALFSORTED", "70HALFSORTED", "90HALFSORTED", "100HALFSORTED", "300HALFSORTED", "500HALFSORTED", "700HALFSORTED", "900HALFSORTED", "1000HALFSORTED", "3000HALFSORTED", "5000HALFSORTED", "7000HALFSORTED", "9000HALFSORTED", "10000HALFSORTED", "30000HALFSORTED", "50000HALFSORTED", "70000HALFSORTED", "90000HALFSORTED", "100000HALFSORTED", "300000HALFSORTED", "500000HALFSORTED", "700000HALFSORTED", "900000HALFSORTED"} // half 3
	,{"10REVERSESORTED", "30REVERSESORTED", "50REVERSESORTED", "70REVERSESORTED", "90REVERSESORTED", "100REVERSESORTED", "300REVERSESORTED", "500REVERSESORTED", "700REVERSESORTED", "900REVERSESORTED", "1000REVERSESORTED", "3000REVERSESORTED", "5000REVERSESORTED", "7000REVERSESORTED", "9000REVERSESORTED", "10000REVERSESORTED", "30000REVERSESORTED", "50000REVERSESORTED", "70000REVERSESORTED", "90000REVERSESORTED", "100000REVERSESORTED", "300000REVERSESORTED", "500000REVERSESORTED", "700000REVERSESORTED", "900000REVERSESORTED"} // reverse sorted 4
	,{"10SORTED", "30SORTED", "50SORTED", "70SORTED", "90SORTED", "100SORTED", "300SORTED", "500SORTED", "700SORTED", "900SORTED", "1000SORTED", "3000SORTED", "5000SORTED", "7000SORTED", "9000SORTED", "10000SORTED", "30000SORTED", "50000SORTED", "70000SORTED", "90000SORTED", "100000SORTED", "300000SORTED", "500000SORTED", "700000SORTED", "900000SORTED"} // sorted 5
	,{"10SMALLRANDOMINT", "30SMALLRANDOMINT", "50SMALLRANDOMINT", "70SMALLRANDOMINT", "90SMALLRANDOMINT", "100SMALLRANDOMINT", "300SMALLRANDOMINT", "500SMALLRANDOMINT", "700SMALLRANDOMINT", "900SMALLRANDOMINT", "1000SMALLRANDOMINT", "3000SMALLRANDOMINT", "5000SMALLRANDOMINT", "7000SMALLRANDOMINT", "9000SMALLRANDOMINT", "10000SMALLRANDOMINT", "30000SMALLRANDOMINT", "50000SMALLRANDOMINT", "70000SMALLRANDOMINT", "90000SMALLRANDOMINT", "100000SMALLRANDOMINT", "300000SMALLRANDOMINT", "500000SMALLRANDOMINT", "700000SMALLRANDOMINT", "900000SMALLRANDOMINT"}  // small numbers 6
	};
 	for (int j = 0; j < checker; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st = steady_clock::now();
		mergeSort(&v[0], 0, v.size() - 1);
		auto ft = steady_clock::now();
		auto d = duration_cast<microseconds>(ft - st);
		cout << fixed << "merge: " << d.count() / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		v.clear();
		}
	for (int j = 0; j < qs ; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st1 = steady_clock::now();
		quickSort(&v[0], 0, v.size() - 1);
		auto ft1 = steady_clock::now();
		auto d1 = duration_cast<microseconds>(ft1 - st1);
		cout << fixed << "quick: " << d1.count() / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		v.clear();
	}
	for (int j = 0; j < checker; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st1 = steady_clock::now();
		heapSort(&v[0], v.size() - 1);
		auto ft1 = steady_clock::now();
		auto d1 = duration_cast<microseconds>(ft1 - st1);
		cout << fixed << "Heap: " << d1.count() / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		v.clear();
	}
	for (int j = 0; j < checker; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st1 = steady_clock::now();
		countSort(v);
		auto ft1 = steady_clock::now();
		auto d1 = duration_cast<microseconds>(ft1 - st1);
		auto st2 = steady_clock::now();
		/*insertionSort(&v[0], v.size() - 1);
		auto ft2 = steady_clock::now();
		auto d2 = duration_cast<microseconds>(ft2 - st2);*/
		cout << fixed << "counting: " << (d1.count()/*+d2.count()*/) / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		t = v;
		v.clear();
	}
	for (int j = 0; j < ins; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st1 = steady_clock::now();
		insertionSort(&v[0],  v.size() - 1);
		auto ft1 = steady_clock::now();
		auto d1 = duration_cast<microseconds>(ft1 - st1);
		cout << fixed << "ins: " << d1.count() / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		v.clear();
	}
	for (int j = 0; j < bbl; j++) {
		ifstream test("dataset/" + files[i][j] + ".txt");
		float a;
		while (test >> a) { v.push_back(a); }
		auto st1 = steady_clock::now();
		bubbleSort(&v[0], v.size() - 1);
		auto ft1 = steady_clock::now();
		auto d1 = duration_cast<microseconds>(ft1 - st1);
		cout << fixed << "bubble: " << d1.count() / 1000000.0 << "s for " << files[i][j] << endl;
		cout << "----------------------------------------------------------------\n";
		v.clear();
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
3.Half sorted data\n4.Reverse sorted  data.\n5.Sorted data.\n6.Small numbers.\n";
			cin >> s;
			while (s != 7) {
				if (k1 && (s == 1) || k2 && (s == 2) || k3 && (s == 3) || k4 && (s == 4)
					|| k5 && (s == 5) || k6 && (s == 6)) {
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
					
					}
					if (k1 && k2 && k3 && k4 && k5 && k6) break;
					cout << "To add more one more data type enter the corresponding number, to continue enter 7.\n";
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
			for (int i = 0; i < 7; i++) {
				if (checks[i]) ts(i);
			}
			cout << "Enter 1 to sort the algs on diff data, or 0 to exit.\n";
			cin >> safe;
		}
		for (int i = 0; i < t.size(); i++) {
			cout << t[i] << "\n";
		}
	}
