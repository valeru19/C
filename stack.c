#include <stdlib.h>
#include <stdio.h>

// Структура для представления узла (элемента) стека
struct Node_tag{
    int value;               // Значение узла
    struct Node_tag *next;   // Ссылка на следующий узел
};

// Структура для представления стека
struct Stack{
    struct Node_tag *head;    // Указатель на вершину стека
    int size;                 // Текущий размер стека
};

// Функция для добавления элемента в стек (push)
void push(struct Stack *stack, int value, int maxsize){
    if (stack->size >= maxsize) {
        perror("overflow");    // Обработка переполнения стека
    } else {
        // Выделение памяти под новый узел
        struct Node_tag *in = malloc(sizeof(struct Node_tag));
        // Инициализация нового узла
        in->next = stack->head; 
        in->value = value;
        // Обновление указателя на вершину стека
        stack->head = in;
        // Увеличение размера стека
        stack->size++;
    }	
}

// Функция для создания нового стека
struct Stack* createStack() {
    // Выделение памяти под стек
    struct Stack* newStack = (struct Stack*)malloc(sizeof(struct Stack));
    if (newStack == NULL) {
        perror("memory allocation failed"); // Обработка ошибки выделения памяти
    } else {
        // Инициализация нового стека
        newStack->head = NULL;
        newStack->size = 0;
        return newStack;
    }	
}

// Функция для удаления и возврата верхнего элемента из стека (pop)
int pop(struct Stack *stack){
    if (stack->head == NULL) { 
        perror("empty");  // Обработка попытки извлечь элемент из пустого стека
    } else {
        // Сохранение указателя на верхний узел
        struct Node_tag *out = stack->head;
        // Обновление указателя на вершину стека
        stack->head = stack->head->next; 
        // Получение значения удаляемого узла
        int value = out->value;
        // Освобождение памяти, занятой удаляемым узлом
        free(out);
        return value;
    }	
}

// Функция для получения значения верхнего элемента без его удаления (peek)
int peek(const struct Stack *stack){
    if (stack->head == NULL) {
        perror("empty");  // Обработка попытки получения значения из пустого стека
    }else{
        // Возврат значения верхнего узла стека
        return stack->head->value;
    }
}
