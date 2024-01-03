// Дан текст. Группы символов, разделенные пробелами (одним или несколькими) и не содержащие пробелов внутри себя, 
// будем называть словами. Найти количество слов, начинающихся с буквы "t"

// 1 вариант. Хранение данных в виде односвязного списка. Реализовать удаление элементов и добавление в список

// Односвязный список
// реализация через массивы

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data[100];
    // char data;
    struct Node* next;
} Node;

Node* head = NULL;

void addNode(Node** head_ref, char new_data[]) {
// void addNode(Node** head_ref, char new_data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    Node* last = *head_ref;
    strcpy(new_node->data, new_data);
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void deleteNode(char data[]) {
    Node* current = head;
    Node* prev = NULL;
    int found = 0; 
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            found = 1; 
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            break; 
        }
        prev = current;
        current = current->next;
    }
    if (!found) {
        printf("Слово \"%s\" не было найдено в списке\n", data);
    }
}

void printListForward() {
    Node* current = head;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

void countWordsStartingWithT() {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        if (current->data[0] == 't') {
            count++;
        }
        current = current->next;
    }
    printf("%d \n", count);
}

void freeList(){
    Node* current = head;
    Node* next;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}


int main() {
    char input[100];
    int choice;

    printf("\nВведите текст: ");
    fgets(input, 100, stdin); 
    char* token = strtok(input, " \n"); 
    while (token != NULL) {
        addNode(&head, token);
        token = strtok(NULL, " \n"); 
    }
    char token;
    while((token = getchar()) != '\n'){
        addNode(&token, input);
    }

    printf("\nВведенный текст: \n");
    printListForward();

    do {
        printf("\n\tМеню:\n");
        printf("1. Добавить элемент списка\n");
        printf("2. Удалить элемент\n");
        printf("3. Напечатать текст\n");
        printf("4. Посчитать кол-во слов на букву 't'\n");
        printf("0. Выход\n");
        printf("\nВыберите опцию: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите слово, чтобы добавить его в список: ");
                getchar(); 
                fgets(input, 50, stdin); 

                char* token = strtok(input, " \n"); 
                while (token != NULL) {
                    addNode(&head, token);
                    token = strtok(NULL, " \n"); 
                }

                printf("\nПолучившийся текст: ");
                printListForward();
                break;
            case 2:
                printf("Введите слово, чтобы удалить его из списка: ");
                getchar(); 
                fgets(input, 50, stdin); 
                input[strcspn(input, "\n")] = 0; 
                deleteNode(input);

                printf("\nПолучившийся текст: ");
                printListForward();
                break;
            case 3:
                printf("Прямой порядок: \n");
                printListForward();
                break;
            case 4:
                printf("Количество слов, начинающихся на 't': \n");
                countWordsStartingWithT();
                break;
            case 0:
                printf("Завершение программы\n");
                freeList();
                break;
            default:
                printf("Неверная опция, выберите другую\n");
        }
    } while (choice != 0);

    return 0;
}