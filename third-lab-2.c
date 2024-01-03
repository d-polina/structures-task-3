// Дан текст. Группы символов, разделенные пробелами (одним или несколькими) и не содержащие пробелов внутри себя, 
// будем называть словами. Найти количество слов, начинающихся с буквы "t"

// 2 вариант. Хранение данных в виде двусвязного списка. Реализовать удаление элементов и добавление в список. Реализовать вывод данных в обоих порядках

// Двусвязный список


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data[100];
    struct Node* prev;
    struct Node* next;
} Node;

Node* head = NULL;
Node* tail = NULL;

void addNode(char data[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void deleteNode(char data[]) {
    Node* current = head;
    int found = 0; 
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            found = 1; 
            if (current == head) {
                head = current->next;
                if (head != NULL) {
                    head->prev = NULL;
                }
            } else if (current == tail) {
                tail = current->prev;
                tail->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            break; 
        }
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

void printListBackward() {
    Node* current = tail;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->prev;
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
    tail = NULL;
}

int main() {
    char input[100];
    int choice;

    printf("\nВведите текст: ");
    fgets(input, 100, stdin); 
    char* token = strtok(input, " \n"); 
    while (token != NULL) {
        addNode(token);
        token = strtok(NULL, " \n"); 
    }
    printf("\nВведенный текст: \n");
    printListForward();

    do {
        printf("\n\tМеню:\n");
        printf("1. Добавить элемент списка\n");
        printf("2. Удалить элемент\n");
        printf("3. Напечатать текст с головы списка\n");
        printf("4. Напечатать текст с хвоста списка\n");
        printf("5. Посчитать кол-во слов на букву 't'\n");
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
                    addNode(token);
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
                printf("Обратный порядок: \n");
                printListBackward();
                break;
            case 5:
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