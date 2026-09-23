#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define EPS 1e-9

// Функция для освобождения памяти динамической матрицы
void free_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Выделение памяти под матрицу
double** create_matrix(int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
    }
    return matrix;
}

// Заполнение матрицы случайными целыми числами от 0 до 15
void fill_matrix_random(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 16; // случайное число от 0 до 15
        }
    }
}

// Вывод матрицы на экран
void print_matrix(double** matrix, int rows, int cols) {
    printf("\nСгенерированная матрица (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
			printf("%4.0f ", matrix[i][j]); // вывод без десятичных знаков
        }
        printf("\n");
    }
}

// Рекурсивный расчет детерминанта (определителя) квадратной подматрицы k x k
double determinant(double** matrix, int k) {
	if (k == 1) return matrix[0][0]; //детерминант 1x1 матрицы не существует.
	if (k == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];//рекурсивный расчет детерминанта для матрицы 2x2

    double det = 0;
    double** submatrix = create_matrix(k - 1, k - 1);

    for (int p = 0; p < k; p++) {
        int sub_i = 0;
        for (int i = 1; i < k; i++) {
            int sub_j = 0;
            for (int j = 0; j < k; j++) {
				if (j == p) continue; //пропускаем столбцы из-за представления первой строки методом Лапласа
                submatrix[sub_i][sub_j] = matrix[i][j];
                sub_j++;
            }
            sub_i++;
        }
        det += (p % 2 == 0 ? 1 : -1) * matrix[0][p] * determinant(submatrix, k - 1);//вот и он сам, ??
    }

    free_matrix(submatrix, k - 1);
    return det;
}

// Вывод всех ненулевых миноров порядка k и проверка, есть ли хотя бы один ненулевой
int print_and_check_nonzero_minors(double** matrix, int rows, int cols, int k) {
    printf("\n--- Поиск ненулевых миноров порядка %d ---\n", k);
    int found_count = 0;

    double** submatrix = create_matrix(k, k);

    // Полный перебор комбинаций k строк и k столбцов через битовые маски
	for (int r_mask = 0; r_mask < (1 << rows); r_mask++) { // пишем по битовой маске, столько сколько строк в матрице, выраженных в битовом виде, т.е. 2^n - закон комбинаторики, где  n - количество строк
        int r_count = 0;
		for (int i = 0; i < rows; i++) if (r_mask & (1 << i)) r_count++; // ищем строки с нужными k единицами в битовой маске, т.е. выбираем строки для миноров
        if (r_count != k) continue;

		for (int c_mask = 0; c_mask < (1 << cols); c_mask++) { // аналогично для столбцов
            int c_count = 0;
            for (int j = 0; j < cols; j++) if (c_mask & (1 << j)) c_count++;
            if (c_count != k) continue;

            // Извлечение подматрицы k x k
            int sub_i = 0;
            for (int i = 0; i < rows; i++) {
                if (r_mask & (1 << i)) {
                    int sub_j = 0;
                    for (int j = 0; j < cols; j++) {
                        if (c_mask & (1 << j)) {
                            submatrix[sub_i][sub_j] = matrix[i][j]; 
                            sub_j++;
                        }
                    }
                    sub_i++;
                }
            }

            double det = determinant(submatrix, k);
			if (fabs(det) > EPS) { // если детерминант ненулевой
                found_count++;
                printf("Минор #%d = %.0f (Строки: ", found_count, det);
                for (int i = 0; i < rows; i++) if (r_mask & (1 << i)) printf("%d ", i + 1);
                printf("| Столбцы: ");
                for (int j = 0; j < cols; j++) if (c_mask & (1 << j)) printf("%d ", j + 1);
                printf(")\n");
            }
        }
    }

    if (found_count == 0) {
        printf("Ненулевые миноры порядка %d ОТСУТСТВУЮТ (все равны 0).\n", k);
    }

    free_matrix(submatrix, k);
    return found_count; // возвращает количество найденных ненулевых миноров
}

// Определение ранга матрицы перебором миноров от максимального порядка к минимальному
int calculate_rank_by_minors(double** matrix, int rows, int cols) {
	int max_order = (rows < cols) ? rows : cols; // максимальный возможный порядок миноров

    // Проверяем порядки от наибольшего возможного до 1
	for (int k = max_order; k >= 1; k--) { // >= 1, так как минор 0-го порядка не имеет смысла, а k-- потому что мы ищем наибольший ненулевой минор
        int nonzero_count = print_and_check_nonzero_minors(matrix, rows, cols, k);

        // Если нашли хотя бы один ненулевой минор порядка k,
        // то ранг матрицы равен k!
        if (nonzero_count > 0) {
            return k;
        }
    }

    // Если даже миноры 1-го порядка все нулевые — матрица нулевая
    return 0;
}

int main() {
    // Инициализация генератора случайных чисел
	srand((unsigned int)time(NULL)); //time(NULL) возвращает текущее время в секундах с 1 января 1970 года, преобразованное в unsigned int для использования в srand

    int rows, cols;
    printf("Введите количество строк матрицы: ");
    scanf("%d", &rows);
    printf("Введите количество столбцов матрицы: ");
    scanf("%d", &cols);

    if (rows <= 0 || cols <= 0) {
        printf("Ошибка: размеры матрицы должны быть больше 0.\n");
        return 1;
    }

    double** matrix = create_matrix(rows, cols);

    // Заполнение случайными числами [0; 15] и вывод
    fill_matrix_random(matrix, rows, cols);
    print_matrix(matrix, rows, cols);

    printf("\n================ ОПРЕДЕЛЕНИЕ РАНГА ============\n");
    int rank = calculate_rank_by_minors(matrix, rows, cols);

    printf("\n================ ИТОГОВЫЙ РЕЗУЛЬТАТ ============\n");
    printf("Ранг матрицы равен: %d\n", rank);

    // Освобождение памяти
    free_matrix(matrix, rows);

    return 0;
}