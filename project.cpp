#include <iostream>
#include <time.h>
#include <cmath>
using namespace std;
void disp(int *arr, int n) { for (int i = 1; i < n; i++)cout << arr[i] << "     "; cout << endl << endl; }
int selectionSort(int *arr, int size, int &comp) {
	int m = 0;
	for (int i = 1; i < size-1; i++) {
		m = i;
		for (int j = i + 1; j < size; j++) {
			comp++;
			if (arr[j] < arr[m]) m = j;
		}
		swap(arr[i], arr[m]);
	}
	return comp;
}

void merge(int *arr, int n, int a, int mid, int b, int &comp) {
	int *B = new int[n+1];
	for (int i = 1; i <= n; i++)B[i] = arr[i];
	int i = a, j = mid + 1, k = a;
	while (i <= mid && j <= b) {
		comp++;
		if (B[i] <= B[j]) { arr[k] = B[i]; i++; }
		else { arr[k] = B[j]; j++; } 
		k++;
	}
	while (i <= mid){
		arr[k] = B[i]; i++; k++;
	}
	while (j <= b) {
		arr[k] = B[j]; j++; k++;
	}
}

int mergeSort(int *arr, int size, int a, int b, int &comp) {
	if (a < b) {
		int mid = floor((a + b) / 2);
		mergeSort(arr, size, a, mid, comp);
		mergeSort(arr, size, mid + 1, b, comp);
		merge(arr, size, a, mid, b, comp);
	}
	return comp;
}

int partitionA(int *arr, int a, int b, int &comp) {
	int pivot = arr[a];
	int i = a, j = b;
	do {
		do { i++; comp++; } while (arr[i] < pivot);
		do { j--; comp++; } while (arr[j] > pivot);
		if (i < j)swap(arr[i], arr[j]);
	} while (i < j);
	arr[a] = arr[j];
	arr[j] = pivot;
	return j;
}

int quickSortA(int *arr, int a, int b, int &comp) {
	if (a < b) {
		int x = partitionA(arr, a, b + 1, comp);
		quickSortA(arr, a, x - 1, comp);
		quickSortA(arr, x + 1, b, comp);
	}
	return comp;
}
int partitionB(int *arr, int a, int b, int &comp) {

	int p = (a + b) / 2, pivot = arr[(a + b) / 2];
	int i = a, j = b;
	do {
		while (arr[i] < pivot) { i++; comp++; }
		while (arr[j] > pivot) { j--; comp++; }

		if (i < j)swap(arr[i], arr[j]);
	} while (i < j);
	return j;
}
int quickSortB(int *arr, int a, int b, int &comp) {

	if (a < b) {
		int x = partitionB(arr, a, b, comp);
		quickSortB(arr, a, x - 1, comp);
		quickSortB(arr, x + 1, b, comp);

	}
	return comp;
}
int RQuickSort(int *arr, int p, int r, int &comp) {
	
	if (p < r) {
		if ((r - p) > 5) { 
			int m = rand() % (r - p + 1) + p;  swap(arr[p], arr[m]); }  
		int q = partitionA(arr, p, r + 1, comp);  
		RQuickSort(arr, p, q - 1, comp);
		RQuickSort(arr, q + 1, r, comp);

	}
	return comp;
}

int main() {

	for (int i = 0; i < 6; i++) {
		int n, x;
		cout << "N = ";
		cin >> n;
		n++;
		int *arr;
		arr = new int[n];
		for (int i = 1; i < n; i++) arr[i] = i;
		int t = 0;
		srand(time(NULL));
		for (int i = 2; i < n; i++) {
			x = 1 + rand() % i;
			t = arr[i];
			arr[i] = arr[x];
			arr[x] = t;
		}

		int *select, *merge, *quick1, *quick2, *quick3;
		select = new int[n];
		merge = new int[n];
		quick1 = new int[n];
		quick2 = new int[n];
		quick3 = new int[n];

		for (int i = 0; i < n; i++) {
			select[i] = arr[i];
			merge[i] = arr[i];
			quick1[i] = arr[i];
			quick2[i] = arr[i];
			quick3[i] = arr[i];
		}

		int comp = 0;
		cout << "Selection sort: " << selectionSort(select, n, comp) << " comparisons\n";
		comp = 0;
		cout << "Merge sort: " << mergeSort(merge, n - 1, 1, n - 1, comp) << " comparisons\n";
		comp = 0;
		cout << "Quick sort(first): " << quickSortA(quick1, 1, n - 1, comp) << " comparisons\n";
		comp = 0;
		cout << "Quick sort(mid): " << quickSortB(quick2, 1, n - 1, comp) << " comparisons\n";
		comp = 0;
		cout << "Quick sort(random): " << RQuickSort(quick3, 1, n - 1, comp) << " comparisons\n";

		delete[] arr;
		delete[] select;
		delete[] merge;
		delete[] quick1;
		delete[] quick2;
		delete[] quick3;
	}

}