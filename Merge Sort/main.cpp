#include <iostream>
#include <vector>
#include <thread>
using namespace std;

void merge(int arr[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1], R[n2];

	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	int i = 0, j = 0;
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

void mergeSort(int arr[],int l,int r){
	if(l>=r){
		return;
	}
	int m = (l+r-1)/2;
	thread t1(mergeSort,arr,l,m);
	thread t2(mergeSort,arr,m+1,r);
	t1.join();
	t2.join();
	merge(arr,l,m,r);
}

void printArray(int A[], int size)
{
	for (int i = 0; i < size; i++)
		cout << A[i] << " ";
}
vector<int*> readArray() {
    FILE *input = fopen("input.txt","r");
    int* arr;
    int size;
    while(!feof(input)) {
        fscanf(input,"%d\n", &size);
        arr = (int*)malloc(4*size);
        for(int i = 0; i < size; i++) {
            fscanf(input,"%d ", &arr[i]);
        }
    }
    fclose(input);
    vector <int*> data;
    data.push_back(arr);
    data.push_back(&size);
    return data;
}

int main()
{
    vector <int*> data = readArray();
	int *arr = data[0];
	int arr_size = *data[1];

	cout << "Given array is \n";
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	cout << "\nSorted array is \n";
	printArray(arr, arr_size);
	return 0;
}
