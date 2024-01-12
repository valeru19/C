#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для представления элемента стека
struct stack
{
    char data;
    struct stack *next;
};

// Функция добавления элемента в стек (push)
void push(struct stack **top, char D)
{
    struct stack *q;
    q = (struct stack *)malloc(sizeof(struct stack));
    q->data = D;
    if (*top == NULL)
    {
        *top = q;
    }
    else
    {
        q->next = *top;
        *top = q;
    }
}

// Функция удаления элемента из стека (pop)
void pop(struct stack **top, char N)
{
    struct stack *q = *top;
    struct stack *prev = NULL;
    while (q != NULL)
    {
        if (q->data == N)
        {
            if (q == *top)
            {
                *top = q->next;
                free(q);
                q->data = '\0';
                q->next = NULL;
            }
            else
            {
                prev->next = q->next;
                free(q);
                q->data = '\0';
                q->next = NULL;
            }
        }
        prev = q;
        q = q->next;
    }
}

// Функция вывода элементов стека
void s_print(struct stack *top)
{
    struct stack *q = top;
    while (q)
    {
        if (q->data >= 10)
        {
            printf("%c", q->data);
            q = q->next;
        }
        else
        {
            printf("%c", q->data + '0');
            q = q->next;
        }
    }
    printf("\n");
}

// Функция инвертирования строки
char *reverse(const char *s)
{
    int len = strlen(s);
    char *rev = (char *)malloc((len + 1) * sizeof(char));
    for (int i = len - 1; i >= 0; i--)
    {
        rev[len - i - 1] = s[i];
    }
    rev[len] = '\0';
    return rev;
}

// Функция формирования обратной польской записи из стека
char *polskiString(struct stack *top)
{
    struct stack *q = top;
    char *str = (char *)malloc(sizeof(char));
    int size = 0;
    while (q)
    {
        if (q->data >= 10)
        {
            size++;
            str = (char *)realloc(str, size * sizeof(char));
            str[size - 1] = q->data;
            q = q->next;
        }
        else
        {
            size++;
            str = (char *)realloc(str, size * sizeof(char));
            str[size - 1] = q->data + '0';
            q = q->next;
        }
    }
    size++;
    str = (char *)realloc(str, size * sizeof(char));
    str[size - 1] = '\0';
    char *rev = reverse(str);
    free(str);
    return rev;
}

// Функция удаления последнего элемента из стека
void pop_back(struct stack **top)
{
    struct stack *q = *top;
    *top = q->next;
    free(q);
}

// Функция очистки стека
void clear(struct stack **top)
{
    struct stack *q;
    while (*top != NULL)
    {
        q = *top;
        *top = (*top)->next;
        free(q);
    }
}

// Функция переноса элементов из одного стека в другой
void pop_owerwrite(struct stack **top_old, struct stack **top_new)
{
    struct stack *q = *top_old;
    while (q)
    {
        push(top_new, q->data);
        q = q->next;
    }
}

// Проверка, является ли символ оператором
int is_op(char op)
{
    return op == '+' || op == '-' || op == '*' || op == '/';
}

// Определение приоритета оператора
int priority(char op)
{
    return op == '+' || op == '-' ? 1
                                   : op == '*' || op == '/' ? 2 : 0;
}

// Получение приоритета последнего элемента стека
int priority_last_element(struct stack **top)
{
    struct stack *q = *top;
    return priority(q->data);
}

// Функция преобразования инфиксной строки в обратную польскую запись
char *polskyString(const char *str)
{
    struct stack *number = NULL;
    struct stack *operation = NULL;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (isdigit(str[i]))
        {
            push(&number, str[i]);
        }
        else if (is_op(str[i]))
        {
            if (operation == NULL || priority_last_element(&operation) >= priority(str[i]))
            {
                pop_owerwrite(&operation, &number);
                clear(&operation);
                push(&operation, str[i]);
            }
            else
            {
                push(&operation, str[i]);
            }
        }
    }
    pop_owerwrite(&operation, &number);
    char *newString = polskiString(number);
    return newString;
}

// Выполнение арифметической операции
char arif_operation(char a, char b, char op)
{
    switch (op)
    {
    case '-':
        return (b - '0') - (a - '0') + '0';
        break;
    case '+':
        return (b - '0') + (a - '0') + '0';
        break;
    case '*':
        return (b - '0') * (a - '0') + '0';
        break;
    case '/':
        return (b - '0') / (a - '0') + '0';
        break;
    }
    return '0';
}

// Вычисление значения выражения в обратной польской записи
int calc(const char *str)
{
    struct stack *result = NULL;
    int len = strlen(str);
    for (int i = 0; i < len + 1; i++)
    {
        if (isdigit(str[i]))
        {
            int x = (int)str[i];
            push(&result, x);
        }
        else if (is_op(str[i]))
        {
            char a = result->data;
            pop_back(&result);
            char b = result->data;
            pop_back(&result);
            char res = arif_operation(a, b, str[i]);
            push(&result, res);
        }
    }
    int finish_result = result->data - '0';
    return finish_result;
}

// Тестирование кода
void test_code()
{
    struct stack *number = NULL;
    struct stack *operation = NULL;

    push(&number, '5');
    push(&number, '3');
    push(&operation, '+');
    push(&operation, '-');
    push(&operation, '*');
    s_print(operation);
    pop_owerwrite(&number, &operation);
    s_print(number);
    s_print(operation);
}

int main()
{
    test_code();
    return 0;
}
