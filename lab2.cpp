#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для сортировки массива по возрастанию (метод пузырька)
void sortAscending(double arr[], int n) {
    for (int i = 0; i < n - 1; i++) {    //двигатель кода
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];   //сосуд для временного хранения 
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Введите количество элементов массива (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Ошибка: неверное количество элементов.\n");
        return 1;
    }

    double arr[n];

    printf("Введите %d вещественных элементов массива:\n", n);
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%lf", &arr[i]);
    }

    // 1. Подсчет количества отрицательных элементов
    int negativeCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            negativeCount++;
        }
    }

    // Поиск индекса минимального по модулю элемента
    int minAbsIndex = 0;
    for (int i = 1; i < n; i++) {
        if (fabs(arr[i]) < fabs(arr[minAbsIndex])) {  //fabs - модуль для double
            minAbsIndex = i;
        }
    }

    // 2. Вычисление суммы модулей элементов, расположенных после минимального по модулю
    double sumAfterMinAbs = 0;
    for (int i = minAbsIndex + 1; i < n; i++) {
        sumAfterMinAbs += fabs(arr[i]);
    }

    // Вывод промежуточных результатов
    printf("\n--- Результаты расчетов ---\n");
    printf("1) Количество отрицательных элементов: %d\n", negativeCount);
    printf("Минимальный по модулю элемент: arr[%d] = %.2lf\n", minAbsIndex, arr[minAbsIndex]);
    printf("2) Сумма модулей элементов после минимального по модулю: %.2lf\n", sumAfterMinAbs);

    // Замена всех отрицательных элементов их квадратами
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            arr[i] = arr[i] * arr[i];
        }
    }

    // Упорядочивание элементов массива по возрастанию
    sortAscending(arr, n);

    // Вывод преобразованного массива
    printf("\n--- Массив после возведения отрицательных элементов в квадрат и сортировки ---\n");
    for (int i = 0; i < n; i++) {
        printf("%.2lf ", arr[i]);
    }
    printf("\n");

    return 0;
}