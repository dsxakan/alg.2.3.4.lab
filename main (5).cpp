#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

// Функция для проверки упорядоченности массива
bool isSorted(const vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Сортировка Шелла
void shellSort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Пирамидальная сортировка
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Сортировка Хоара (QuickSort)
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; ++j) {
            if (arr[j] < pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);

        int pivotIndex = i + 1;

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    const int arraySize = 100000;
    vector<int> arrShell(arraySize);
    vector<int> arrHeap(arraySize);
    vector<int> arrQuick(arraySize);

    // Заполнение массивов случайными числами
    for (int i = 0; i < arraySize; ++i) {
        arrShell[i] = arrHeap[i] = arrQuick[i] = rand();
    }

    // Сортировка Шелла
    auto start = high_resolution_clock::now();
    shellSort(arrShell);
    auto stop = high_resolution_clock::now();
    auto durationShell = duration_cast<milliseconds>(stop - start);
    cout << "Shell Sort Time: " << durationShell.count() << " milliseconds" << endl;
    cout << "Is Sorted: " << isSorted(arrShell) << endl;

    // Пирамидальная сортировка
    start = high_resolution_clock::now();
    heapSort(arrHeap);
    stop = high_resolution_clock::now();
    auto durationHeap = duration_cast<milliseconds>(stop - start);
    cout << "Heap Sort Time: " << durationHeap.count() << " milliseconds" << endl;
    cout << "Is Sorted: " << isSorted(arrHeap) << endl;

    // Сортировка Хоара
    start = high_resolution_clock::now();
    quickSort(arrQuick, 0, arraySize - 1);
    stop = high_resolution_clock::now();
    auto durationQuick = duration_cast<milliseconds>(stop - start);
    cout << "Quick Sort Time: " << durationQuick.count() << " milliseconds" << endl;
    cout << "Is Sorted: " << isSorted(arrQuick) << endl;

    return 0;
}
