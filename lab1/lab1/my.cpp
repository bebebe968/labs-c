#include <stdio.h>
#include <math.h>


    double get_nth_term(double a1, double d, int n) {
    return a1 + (n - 1) * d;
}
    double an = get_nth_term(a1, d, n);
    double sum = ((a1 + an) / 2.0) * n;

int main() {

    double a1, d;
    int n;



    printf("a1 =");
    
    printf("d =");
    
    printf("n =");
   


    while (n <= 0) {
        printf("Error! n must be greater than 0.\n");
        printf("n =");
        
    }
    printf("a%d = %lf\n", n, get_nth_term(a1, d, n));

    

    printf("\n--- Результаты анализа ---\n");

    // 1. Определение характера прогрессии по разности d
    if (d > 0) {
        printf("1. Прогрессия является строго возрастающей.\n");
    }
    else if (d < 0) {
        printf("1. Прогрессия является строго убывающей.\n");
    }
    else {
        printf("1. Прогрессия является постоянной.\n");
    }

    // 2. Анализ знака найденного n-го члена
    if (an > 0) {
        printf("2. Элемент a%d является положительным числом.\n", n);
    }
    else if (an < 0) {
        printf("2. Элемент a%d является отрицательным числом.\n", n);
    }
    else {
        printf("2. Элемент a%d равен нулю.\n", n);
    }

    // 3. Проверка изменения знака между первым и n-м членами
    if ((a1 > 0 && an < 0) || (a1 < 0 && an > 0)) {
        printf("3. Прогрессия пересекает ноль (a1 и a%d имеют разные знаки).\n", n);
    }
    else if (a1 == 0 || an == 0) {
        printf("3. Один из граничных членов (a1 или a%d) равен нулю.\n", n);
    }
    else {
        printf("3. Элементы a1 и a%d имеют одинаковый знак.\n", n);
    }

    // 4. Оценка величины суммы первых n членов
    printf("Сумма первых %d членов (S%d) = %lf\n", n, n, sum);
    if (sum > 100.0) {
        printf("4. Сумма S%d превышает порог 100.\n", n);
    }
    else if (sum < 0.0) {
        printf("4. Сумма S%d отрицательна.\n", n);
    }
    else if (sum == 0.0) {
        printf("4. Сумма S%d равна точно нулю.\n", n);
    }
    else {
        printf("4. Сумма S%d находится в диапазоне от 0 до 100 (включительно).\n", n);
    }

    return 0;
}