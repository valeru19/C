#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для вывода массива на экран
void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size;
    printf("input array len: ");
    scanf("%d", &size);

    // Выделение памяти под массив
    int *arr = (int *)malloc(size * sizeof(int));

    // Инициализация генератора случайных чисел
    srand(time(0));

    // Заполнение массива случайными числами
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100; 
    }

    printf("original order:\n");
    // Вывод массива в исходном порядке
    printArray(arr, size);

    char *filename = "output.txt";
    // Открытие файла для записи
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("ERROR of opening input file\n");
        exit(EXIT_FAILURE);
    }

    // Запись массива в файл в обратном порядке
    for (int i = size - 1; i >= 0; i--) {
        fprintf(file, "%d ", arr[i]);
    }

    // Закрытие файла
    fclose(file);
    printf("written to '%s' in reversed order\n", filename);

    // Освобождение выделенной под массив памяти
    free(arr);
    return 0;
}
