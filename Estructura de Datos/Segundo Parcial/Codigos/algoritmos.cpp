#include <iostream>
using namespace std;

/* ===========================
   1. BUBBLE SORT
   =========================== */
void bubbleSort(int A[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (A[j] > A[j + 1])
                swap(A[j], A[j + 1]);
}

/* ===========================
   2. SELECTION SORT
   =========================== */
void selectionSort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (A[j] < A[minIdx])
                minIdx = j;
        swap(A[i], A[minIdx]);
    }
}

/* ===========================
   3. INSERTION SORT
   =========================== */
void insertionSort(int A[], int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

/* ===========================
   4. SHELL SORT
   =========================== */
void shellSort(int A[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int temp = A[i];
            int j = i;
            while (j >= gap && A[j - gap] > temp) {
                A[j] = A[j - gap];
                j -= gap;
            }
            A[j] = temp;
        }
}

/* ===========================
   5. MERGE SORT
   =========================== */
void merge(int A[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = A[l + i];
    for (int i = 0; i < n2; i++) R[i] = A[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
        A[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int A[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(A, l, m);
        mergeSort(A, m + 1, r);
        merge(A, l, m, r);
    }
}

/* ===========================
   6. QUICK SORT
   =========================== */
int partitionQS(int A[], int low, int high) {
    int pivot = A[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
        if (A[j] < pivot)
            swap(A[++i], A[j]);

    swap(A[i + 1], A[high]);
    return i + 1;
}

void quickSort(int A[], int low, int high) {
    if (low < high) {
        int p = partitionQS(A, low, high);
        quickSort(A, low, p - 1);
        quickSort(A, p + 1, high);
    }
}

/* ===========================
   7. HEAP SORT
   =========================== */
void heapify(int A[], int n, int i) {
    int largest = i, l = 2*i + 1, r = 2*i + 2;

    if (l < n && A[l] > A[largest]) largest = l;
    if (r < n && A[r] > A[largest]) largest = r;

    if (largest != i) {
        swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

void heapSort(int A[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(A, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(A[0], A[i]);
        heapify(A, i, 0);
    }
}

/* ===========================
   8. COUNTING SORT
   =========================== */
void countingSort(int A[], int n, int maxVal) {
    int *C = new int[maxVal + 1]();
    int *B = new int[n];

    for (int i = 0; i < n; i++) C[A[i]]++;
    for (int i = 1; i <= maxVal; i++) C[i] += C[i - 1];
    for (int i = n - 1; i >= 0; i--)
        B[--C[A[i]]] = A[i];

    for (int i = 0; i < n; i++) A[i] = B[i];

    delete[] C;
    delete[] B;
}

/* ===========================
   9. RADIX SORT
   =========================== */
int getMax(int A[], int n) {
    int mx = A[0];
    for (int i = 1; i < n; i++)
        if (A[i] > mx) mx = A[i];
    return mx;
}

void countSortExp(int A[], int n, int exp) {
    int B[n], C[10] = {0};

    for (int i = 0; i < n; i++) C[(A[i]/exp)%10]++;
    for (int i = 1; i < 10; i++) C[i] += C[i - 1];
    for (int i = n - 1; i >= 0; i--)
        B[--C[(A[i]/exp)%10]] = A[i];

    for (int i = 0; i < n; i++) A[i] = B[i];
}

void radixSort(int A[], int n) {
    int m = getMax(A, n);
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSortExp(A, n, exp);
}

/* ===========================
   FUNCIONES DE UTILIDAD
   =========================== */
void printArray(int A[], int n) {
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

/* ===========================
   MAIN
   =========================== */
int main() {
    int A[] = {8, 5, 2, 9, 1, 3, 7};
    int n = sizeof(A)/sizeof(A[0]);

    cout << "Array original: ";
    printArray(A, n);

    // Cambia el sort aquí:
    quickSort(A, 0, n - 1);

    cout << "Array ordenado: ";
    printArray(A, n);

    return 0;
}
