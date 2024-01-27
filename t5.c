#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Структура для представления элемента стека
struct StackNode {
    double data;
    struct StackNode* next;
};

// Структура для представления стека
struct Stack {
    struct StackNode* top;
};

// Функция для инициализации стека
void initializeStack(struct Stack* stack) {
    stack->top = NULL;
}

// Функция для проверки, пуст ли стек
int isStackEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

// Функция для добавления значения в стек
void push(struct Stack* stack, double value) {
    // Создаем новый узел
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        // Обработка ошибки выделения памяти
        printf("Ошибка: Не удалось выделить память для нового элемента стека\n");
        exit(EXIT_FAILURE);
    }

    // Заполняем новый узел данными
    newNode->data = value;
    newNode->next = stack->top;

    // Обновляем указатель на верхний элемент стека
    stack->top = newNode;
}

// Функция для извлечения значения из стека
double pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        // Обработка ошибки: стек пуст
        printf("Ошибка: Стек пуст, невозможно выполнить извлечение\n");
        exit(EXIT_FAILURE);
    }

    // Получаем значение верхнего элемента стека
    double value = stack->top->data;

    // Удаляем верхний элемент и обновляем указатель на верхний элемент
    struct StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);

    return value;
}

// Функция для вычисления значения постфиксного выражения
double evaluatePostfixExpression(FILE* inputFile) {
    struct Stack operandStack;
    initializeStack(&operandStack);

    char buffer[100];
    while (fscanf(inputFile, "%s", buffer) != EOF) {
        if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[1]))) {
            // Если текущий токен - число, добавляем его в стек
            double operand = atof(buffer);
            push(&operandStack, operand);
        } else {
            // Если текущий токен - оператор, выполняем соответствующую операцию
            double operand2 = pop(&operandStack);
            double operand1 = pop(&operandStack);

            switch (buffer[0]) {
                case '+':
                    push(&operandStack, operand1 + operand2);
                    break;
                case '-':
                    push(&operandStack, operand1 - operand2);
                    break;
                case '*':
                    push(&operandStack, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 != 0) {
                        push(&operandStack, operand1 / operand2);
                    } else {
                        // Обработка ошибки: деление на ноль
                        printf("Ошибка: Деление на ноль\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                default:
                    // Обработка ошибки: неизвестный оператор
                    printf("Ошибка: Неизвестный оператор\n");
                    exit(EXIT_FAILURE);
            }
        }
    }

    // Получаем результат из верхнего элемента стека
    double result = pop(&operandStack);

    // Проверяем, что стек пуст после вычислений
    if (!isStackEmpty(&operandStack)) {
        // Обработка ошибки: остались элементы в стеке
        printf("Ошибка: Некорректное выражение\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        // Обработка ошибки: не удалось открыть файл
        printf("Ошибка: Не удалось открыть файл\n");
        return 1;
    }

    double result = evaluatePostfixExpression(inputFile);

    printf("Результат вычислений: %lf\n", result);

    fclose(inputFile);

    return 0;
}
