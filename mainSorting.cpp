#include "sorting.h"
#include <random>

static void printVec(const vector<int>& v, const char* label) {
  cout << label << " [";
  for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i];
    if (i + 1 < v.size()) cout << " ";
  }
  cout << "]\n";
}

int main() {
  // Generar vector aleatorio de 10–15 elementos en [-50, 50]
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> n_dist(10, 15);
  uniform_int_distribution<int> val_dist(-50, 50);

  int n = n_dist(gen);
  vector<int> original(n);
  for (int& x : original) x = val_dist(gen);

  printVec(original, "Arreglo original:");

  // Baseline con std::sort para comparar
  vector<int> baseline = original;
  sort(baseline.begin(), baseline.end());

  vector<pair<const char*, void(*)(vector<int>&)>> tests;

  tests.push_back({"Bubble Sort",    +[](vector<int>& a){ bubbleSort(a); }});
  tests.push_back({"Selection Sort", +[](vector<int>& a){ selectionSort(a); }});
  tests.push_back({"Insertion Sort", +[](vector<int>& a){ insertionSort(a); }});
  tests.push_back({"Merge Sort",     +[](vector<int>& a){ if(!a.empty()) mergeSort(a, 0, (int)a.size()-1); }});
  tests.push_back({"Quick Sort",     +[](vector<int>& a){ if(!a.empty()) quickSort(a, 0, (int)a.size()-1); }});

  bool all_ok = true;

  for (auto& [name, func] : tests) {
    vector<int> arr = original;
    cout << "\n== " << name << " ==\n";
    printVec(arr, "Antes:   ");
    func(arr); // in-place
    printVec(arr, "Despues: ");
    bool ok = (arr == baseline);
    cout << "Resultado " << (ok ? "OK" : "INCORRECTO") << "\n";
    all_ok = all_ok && ok;
  }

  cout << "\nComparacion final: "
       << (all_ok ? "Todos los algoritmos producen el mismo arreglo ordenado."
                  : "Al menos un algoritmo no coincidió con el resultado esperado.")
       << "\n";

  return all_ok ? 0 : 1;
}
