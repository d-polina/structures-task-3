// Дан текст. Группы символов, разделенные пробелами (одним или несколькими) и не содержащие пробелов внутри себя, 
// будем называть словами. Найти количество слов, начинающихся с буквы "t"

// 1 вариант. Хранение данных в виде односвязного списка. Реализовать удаление элементов и добавление в список

// Односвязный список

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char word;
    struct Node* next;
} Node;

void addNode(Node** head, char word) {
    Node* newNode = (Node*) malloc(sizeof(Node)); // создаем новый узел
    if (newNode != NULL) { // проверка на выделение памяти
        newNode->word = word;
        newNode->next = NULL;
        if (*head == NULL) { // если список пустой
            *head = newNode;
        } else {
            Node* temp = *head;
            while (temp->next != NULL) { // ищем последний узел в списке
                temp = temp->next;
            }
            temp->next = newNode;
        }
    } else {
        printf("Ошибка выделения памяти\n");
    }
    
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%c", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

void deleteNode(Node** head, char value) {
    Node* temp = *head;
    Node* prev = NULL;

    if (temp != NULL && temp->word == value) {// проверка не в начале ли списка элемент
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->word != value) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Элемент не найден\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
}


void countWordsStartingWithT(Node* head) {
    Node* temp = head;
    int count = 0;
    int isFirstChar = 1; 
    while (temp != NULL) {
        if (isFirstChar && (temp->word == 't' || temp->word == 'T')) {
            count++;
        }
        if (temp->word == ' ' || temp->word == '\n') {
            isFirstChar = 1; 
        } else {
            isFirstChar = 0;
        }
        temp = temp->next;
    }
    printf("%d \n", count);
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;
    char c;
    int choice;

    printf("\nВведите текст: \n");

    while ((c = getchar()) != '\n') {
        addNode(&head, c);
    }
    addNode(&head, ' ');

    printf("\nВведенный текст:\n");
    printList(head);

    do {
        printf("\n\tМеню:\n");
        printf("1. Добавить элемент списка\n");
        printf("2. Удалить элемент\n");
        printf("3. Напечатать текст\n");
        printf("4. Посчитать кол-во слов на букву 't'\n");
        printf("0. Выход\n");
        printf("\nВыберите опцию: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("\nВведите слово, чтобы добавить его в список: ");
                while ((c = getchar()) != '\n') { // считываем каждый символ ввода до символа новой строки
                    addNode(&head, c);
                }
                addNode(&head, ' ');

                printf("\nПолучившийся текст: ");
                printList(head);
                break;
            case 2:
                printf("Введите слово, чтобы удалить его из списка: ");
                while ((c = getchar()) != '\n') {
                    deleteNode(&head, c);
                }
                deleteNode(&head, ' ');

                printf("\nПолучившийся текст: ");
                printList(head);
                break;

            case 3:
                printf("\nПрямой порядок: \n");
                printList(head);
                break;
            case 4:
                printf("\nКоличество слов, начинающихся на 't': \n");
                countWordsStartingWithT(head);
                break;
            case 0:
                printf("\nЗавершение программы\n");
                freeList(head);
                break;
            default:
                printf("\nНеверная опция, выберите другую\n");
        }
    } while (choice != 0);

    return 0;
}
