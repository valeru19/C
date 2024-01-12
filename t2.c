#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для вывода массива чисел типа float на экран
void printArray(float *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

// Функция для записи массива чисел типа float в файл
void writeArrayToFile(float *arr, int size, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("ERROR of opening input file\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%f\n", arr[i]);
    }
    fclose(file);
}

// Функция для сравнения двух чисел типа float (используется в qsort)
int compareFloats(const void *a, const void *b) {
    float diff = *(float *)a - *(float *)b;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

int main() {
    int size;
    printf("input array len: ");
    scanf("%d", &size);

    // Выделение памяти под массив чисел типа float
    float *arr = (float *)malloc(size * sizeof(float));

    // Инициализация генератора случайных чисел
    srand(time(0));

    // Заполнение массива случайными числами от 0 до 1
    for (int i = 0; i < size; i++) {
        arr[i] = (float)rand() / RAND_MAX;
    }

    printf("array of random nums:\n");
    // Вывод исходного массива на экран
    printArray(arr, size);

    // Сортировка массива чисел типа float в порядке возрастания
    qsort(arr, size, sizeof(float), compareFloats);

    const char *filename = "output.txt";
    // Запись отсортированного массива в файл
    writeArrayToFile(arr, size, filename);

    printf("written to '%s' sorted\n", filename);

    // Освобождение выделенной памяти под массив
    free(arr);
    return 0;
}
