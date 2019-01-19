#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Dict{
    char *description;
    char *data;

    struct Dict * next;
} Dict_t;

int empty(Dict_t * head){

    if (head == NULL){
        return 1;
    }
    return 0;
}   

Dict_t* addElementHead(Dict_t * head, char* word){
    Dict_t * new = malloc(sizeof(Dict_t));

    strcpy(new->data, word);
    new->next = head;

    head = new;
    return head;
}

void addElementTail(Dict_t * head, char* word){

    Dict_t *currentNode = head;
    while(currentNode != NULL && currentNode->next != NULL){
        currentNode = currentNode->next;
    }

    currentNode->next = malloc(sizeof(Dict_t));

    strcpy(currentNode->next->data, word);
    printf("ok");

    currentNode->next->next = NULL;
}

void print_list(Dict_t * head) {
    Dict_t * current = head;

    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

void main(void){

    Dict_t * head = NULL;

    empty(head);

    head = addElementHead(head, "A");
    print_list(head);

    addElementTail(head, "B");
    printf("%s\n",head->next->data);
}