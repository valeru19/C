#include <stdio.h>
#include <stdlib.h>
#define MAX_NAME_LENGTH 100

// Структура для представления продукта
typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
} Product;

// Функция сравнения цен для использования в qsort
int comparePrices(const void *a, const void *b) {
    const Product *productA = (const Product *)a;
    const Product *productB = (const Product *)b;

    if (productA->price < productB->price) {
        return -1;
    } else if (productA->price > productB->price) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char *inputFile = "input.txt";
    char *outputFile = "output.txt";
    FILE *file = fopen(inputFile, "r");
    if (file == NULL) {
        printf("error\n");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);

    // Выделение памяти под массив продуктов
    Product *products = (Product *)malloc(size * sizeof(Product));

    // Чтение данных о продуктах из файла
    for (int i = 0; i < size; i++) {
        // Считывание строки целиком, включая пробелы
        fgets(products[i].name, MAX_NAME_LENGTH, file);
        fscanf(file, "%f", &products[i].price);
    }
    fclose(file);

    printf("before:\n");
    // Вывод информации о продуктах до сортировки
    for (int i = 0; i < size; i++) {
        printf("product: %s, price: %.2f\n", products[i].name, products[i].price);
    }

    // Сортировка продуктов по цене
    qsort(products, size, sizeof(Product), comparePrices);

    printf("after:\n");
    // Вывод отсортированной информации о продуктах
    for (int i = 0; i < size; i++) {
        printf("product: %s, price: %.2f\n", products[i].name, products[i].price);
    }

    FILE *file2 = fopen(outputFile, "w");
    if (file2 == NULL) {
        printf("error \n");
        return 1;
    }

    // Запись отсортированного списка продуктов в файл
    for (int i = 0; i < size; i++) {
        fprintf(file2, "product: %s, price: %.2f\n", products[i].name, products[i].price);
    }

    fclose(file2);
    printf("sorted written to '%s'.\n", outputFile);

    // Освобождение выделенной памяти
    free(products);
    return 0;
}
