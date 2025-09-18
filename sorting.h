#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#ifndef SORTING_VERBOSE
#define SORTING_VERBOSE 0
#endif

#if SORTING_VERBOSE
  #define DBG(x) do { x; } while(0)
#else
  #define DBG(x) do {} while(0)
#endif

/*
  Bubble Sort
  Compara pares adyacentes y los intercambia si están en orden incorrecto.
  En cada pasada, el mayor “burbujea” al final.
  Tiempo: O(n^2) prom/peor, O(n) mejor (casi ordenado). Espacio: O(1).
  Eficiente en listas pequeñas o casi ordenadas; ineficiente en grandes desordenadas.
*/
inline void bubbleSort(vector<int>& arr) {
  const int n = (int)arr.size();
  bool swapped;
  for (int i = 0; i < n; ++i) {
    swapped = false;
    for (int j = 0; j < n - 1 - i; ++j) {
      DBG(cout << "[Bubble] cmp " << arr[j] << " vs " << arr[j+1] << "\n");
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }
    if (!swapped) break; // corte temprano
  }
}

/*
  Selection Sort
  Selecciona el mínimo del subarreglo [i..n) y lo coloca en i (pocos intercambios).
  Tiempo: O(n^2) en todos los casos. Espacio: O(1).
  Útil cuando es caro escribir/intercambiar y barato comparar.
*/
inline void selectionSort(vector<int>& arr) {
  const int n = (int)arr.size();
  for (int i = 0; i < n; ++i) {
    int minIdx = i;
    for (int j = i + 1; j < n; ++j) {
      DBG(cout << "[Selection] ? " << arr[j] << " < " << arr[minIdx] << "\n");
      if (arr[j] < arr[minIdx]) minIdx = j;
    }
    if (minIdx != i) swap(arr[i], arr[minIdx]);
  }
}

/*
  Insertion Sort
  Construye una sublista ordenada a la izquierda; inserta cada elemento en su posición
  desplazando a la derecha a los mayores.
  Tiempo: O(n^2) prom/peor, O(n) mejor (casi ordenado). Espacio: O(1).
  Muy bueno en arreglos pequeños o casi ordenados; base común en híbridos.
*/
inline void insertionSort(vector<int>& arr) {
  const int n = (int)arr.size();
  for (int i = 1; i < n; ++i) {
    int key = arr[i], j = i - 1;
    DBG(cout << "[Insertion] key " << key << "\n");
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

/*
  Merge Sort (divide y vencerás)
  Divide en mitades, ordena cada mitad y fusiona ambas en orden.
  Tiempo: O(n log n) en todos los casos. Espacio: O(n) (buffer de fusión).
  Estable y con rendimiento garantizado, bueno en grandes volúmenes.
*/
namespace { // helpers de enlace interno para headers
  inline void __merge(vector<int>& arr, int left, int mid, int right) {
    const int n1 = mid - left + 1, n2 = right - mid;
    vector<int> L; L.reserve(n1);
    vector<int> R; R.reserve(n2);
    for (int i = 0; i < n1; ++i) L.push_back(arr[left + i]);
    for (int j = 0; j < n2; ++j) R.push_back(arr[mid + 1 + j]);
    int i = 0, j = 0, k = left;
    DBG(cout << "[Merge] [" << left << "," << mid << "] + ["
             << (mid+1) << "," << right << "]\n");
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
  }
}

inline void mergeSort(vector<int>& arr, int left, int right) {
  if (left >= right) return;
  int mid = left + (right - left) / 2;
  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);
  __merge(arr, left, mid, right);
}

/*
  Quick Sort
  Elige un pivote y particiona: menores a la izquierda, mayores a la derecha.
  Aquí se usa Lomuto con pivote en el último elemento.
  Tiempo: O(n log n) promedio; O(n^2) peor caso (por ejemplo, ya ordenado).
  Espacio: O(log n) promedio por recursión. Mejoras: pivote aleatorio o mediana-de-tres.
*/
namespace {
  inline int __partitionLomuto(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    DBG(cout << "[Quick] pv=" << pivot << " idx=" << high << "\n");
    int i = low - 1;
    for (int j = low; j < high; ++j) {
      if (arr[j] <= pivot) { ++i; swap(arr[i], arr[j]); }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
  }
}

inline void quickSort(vector<int>& arr, int low, int high) {
  if (low >= high) return;
  int p = __partitionLomuto(arr, low, high);
  quickSort(arr, low, p - 1);
  quickSort(arr, p + 1, high);
}

#endif // SORTING_H
