#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Структура для представления узла в стеке
struct Node {
    int data;            // Значение узла
    struct Node* next;   // Указатель на следующий узел
};

// Структура для представления стека
struct Stack {
    struct Node* top;   // Указатель на вершину стека
};

// Функция для создания нового узла с заданным значением
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error of getting memory for node\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Функция для создания нового стека
struct Stack* createStack() {
    struct Stack* newStack = (struct Stack*)malloc(sizeof(struct Stack));
    if (newStack == NULL) {
        printf("Error of getting memory for stack\n");
        exit(EXIT_FAILURE);
    }
    newStack->top = NULL;
    return newStack;
}

// Функция для добавления нового элемента в стек
void push(struct Stack* stack, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Функция для извлечения и удаления элемента из стека
int pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty, can't use pop\n");
        exit(EXIT_FAILURE);
    }
    struct Node* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

int main(int argc, char const *argv[]) {
    // Открытие файла для чтения
    FILE* file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error opening the file\n");
        return -1;
    }

    // Создание нового стека
    struct Stack* stack = createStack();

    char c;
    while ((c = fgetc(file)) != EOF) {
        if (isdigit(c)) {
            push(stack, c - '0');  // Преобразование символа в число и добавление в стек
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int operand2 = pop(stack);  // Извлечение двух операндов из стека
            int operand1 = pop(stack);

            // Выполнение операции в зависимости от символа
            switch (c) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
            }
        }
    }

    fclose(file);

    // Печать результата, если стек не пустой
    if (stack->top != NULL) {
        int result = pop(stack);
        printf("Result: %d\n", result);
    } else {
        printf("Error: Stack is empty\n");
    }

    // Освобождение памяти, выделенной под стек
    free(stack);

    return 0;
}
