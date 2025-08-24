#include <csignal>
#include <future> // добавлено
#include <iostream>
#include <ostream>
#include <string>
#include <thread> // добавлено

static bool make_thread = true;  // как в примере 28.7
static const int THRESH = 10000; // порог для запуска потока

void merge(int *arr, int l, int m, int r) {

  std::cout << "Вошли в слияние с отрезком от " << l << " до " << r
            << " m = " << m << std::endl;
  int nl = m - l + 1;
  int nr = r - m;
  std::cout << "диапазон от " << nl << " до " << nr << std::endl;

  for (int i = l; i <= r; ++i)
    std::cout << arr[i] << ", ";
  std::cout << std::endl;
  std::cout << std::endl;

  // создаем временные массивы
  int left[nl], right[nr];

  // копируем данные во временные массивы
  for (int i = 0; i < nl; i++)
    left[i] = arr[l + i];
  for (int j = 0; j < nr; j++)
    right[j] = arr[m + 1 + j];

  int i = 0, j = 0;
  int k = l; // начало левой части

  while (i < nl && j < nr) {
    // записываем минимальные элементы обратно во входной массив

    if (left[i] <= right[j]) {
      arr[k] = left[i];
      i++;
    } else {
      arr[k] = right[j];
      j++;
    }
    k++;
  }
  // записываем оставшиеся элементы левой части

  while (i < nl) {
    arr[k] = left[i];
    i++;
    k++;
  }
  // записываем оставшиеся элементы правой части
  while (j < nr) {
    arr[k] = right[j];
    j++;
    k++;
  }
}

// Рекурсивная сортировка
void mergeSort(int *arr, int l, int r, std::string str) {
  if (l >= r) {
    std::cout << "выход из рекурсии. " << str << std::endl;
    return;
  }

  int m = l + (r - l) / 2;

  std::cout << "Вошли с отрезком от " << l << " до " << r << " m = " << m
            << ", " << str << std::endl;
  for (int i = l; i <= r; ++i)
    std::cout << arr[i] << ", ";

  std::cout << std::endl;
  std::cout << std::endl;

  const int len = r - l + 1;

  if (make_thread && len > THRESH) {
    // одну половину — асинхронно, вторую — в текущем потоке
    auto fut = std::async(std::launch::async, [arr, l, m] {
      mergeSort(arr, l, m, "left");
    });                                // синхронизация строго через future
    mergeSort(arr, m + 1, r, "right"); // работаем параллельно
    fut.get();                         // ждём завершения перед merge
  } else {
    // оба вызова последовательно
    mergeSort(arr, l, m, "left");
    mergeSort(arr, m + 1, r, "right");
  }

  merge(arr, l, m, r);
}

int main() {
  int arr[]{6, 3, 8, 5, 2, 7, 4, 1};

  std::cout << "Исходный массив" << std::endl;
  for (int i = 0; i < 8; ++i)
    std::cout << arr[i] << ", ";
  std::cout << std::endl;
  std::cout << std::endl;

  mergeSort(arr, 0, 7, "full");

  std::cout << "отсортированный массив" << std::endl;
  for (int i = 0; i < 8; ++i)
    std::cout << arr[i] << ", ";

  std::cout << std::endl;

  return 0;
}