#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    char *description;
    char *data;

    struct Node *next;
} Node;

struct Node *head = NULL;

void print_list(void)
{
    int list_index = 0;
    struct Node *current = head;

    while(current)
    {
        printf("Element N° %d\nWord: %s\nDescription: %s\n\n", list_index, current->data, current->description);
        current = current->next;
        list_index++;
    }
}

void freeList(void)
{
    struct Node* node = head;
    struct Node* tmp = 0;

    while(node) 
    {
        tmp = node->next;
        free(node->data);
        free(node->description);
        free(node);
        node = tmp;
    }
}

int empty(void)
{
    if (head)
    {
        return 0;
    }
    return 1;
}   

struct Node* nodeAlloc(struct Node *node, char *word, char *description)
{
    if ((node->data = malloc(strlen(word) + 1)) == NULL)
    {
        printf("Malloc Failed.\n");
        exit(EXIT_FAILURE);   
    }

    if ((node->description = malloc(strlen(description) + 1)) == NULL)
    {
        printf("Malloc Failed.\n");
        exit(EXIT_FAILURE);   
    }

    strcpy(node->data, word);
    strcpy(node->description, description);

    return node;
}

void addElementHead(char* word, char* description)
{
    struct Node *new = malloc(sizeof(struct Node));
    if (new == NULL)
    {
        printf("Malloc Failed.\n");
        exit(EXIT_FAILURE);
    }
    new = nodeAlloc(new, word, description);

    new->next = head;
    head = new;
}

void addElementTail(char* word, char* description)
{
    struct Node *currentNode = head;
    if (empty())
    {
        addElementHead(word, description);
        return;
    }

    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL)
    {
        printf("Malloc Failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node = nodeAlloc(new_node, word, description);

    while(currentNode->next)
    {
        currentNode = currentNode->next;
    }
    
    currentNode->next = new_node;
    new_node->next = NULL;
}

void add_element_w_index(char *word, char *description, int index)
{
    if (index < 0)
    {
        printf("Invalid index. Must be > 0\n");
        return;
    }

    struct Node *currentNode = head;
    struct Node *new_node = malloc(sizeof(struct Node));

    if (new_node == NULL)
    {
        printf("Malloc Failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node = nodeAlloc(new_node, word, description);

    if (index == 0)
    {
        addElementHead(word, description);
        return;
    }
    else
    {
        while((currentNode && currentNode->next) && index != 1)
        {
            currentNode = currentNode->next;
            index--;
        }

        if (index != 1)
        {
            printf("Index out of the list\n");
            free(new_node->data);
            free(new_node->description);
            free(new_node);
            return;
        }

        new_node->next = currentNode->next;
        currentNode->next = new_node;
    }
}

void pop_element_head(void)
{
    if (empty())
    {
        printf("List already empty\n");
    }
    else
    {
        struct Node *tmp;
        tmp = head;

        head = head->next;

        free(tmp->data);
        free(tmp->description);
        free(tmp);
    }
}

void pop_element_tail(void)
{
    struct Node *current_node = head;
    struct Node *previous_node;

    if (empty())
    {
        printf("List already empty\n");   
    }
    else
    {
        if (head->next == NULL)
        {
            pop_element_head();
            return;
        }

        while(current_node->next)
        {
            previous_node = current_node;
            current_node = current_node->next;
        }

        free(current_node->data);
        free(current_node->description);
        free(current_node);
        previous_node->next = NULL;
    }  
}

void pop_element_w_index(int index)
{
    struct Node *previous_node;
    struct Node *current_node = head;

    if (empty())
    {
        printf("List already empty\n");
    }
    else
    {
        if (index == 0)
        {
            pop_element_head();
            return;
        }

        while (current_node->next && index != 0)
        {
            previous_node = current_node;
            current_node = current_node->next;
            index--;
        }

        if (index != 0)
        {
            printf("Index out of range\n");
            return;
        }

        previous_node->next = current_node->next;

        free(current_node->data);
        free(current_node->description);
        free(current_node);
    }
}

void pop_element_w_name(char* name)
{
    int done = 1;
    struct Node *previous_node;
    struct Node *current_node = head;

    if (empty())
    {
        printf("List already empty\n");
    }
    else
    {   
        while (current_node->next && done)
        {
            if (!strcmp(name, current_node->data))
            {
                done = 0;
            }
            else
            {
                previous_node = current_node;
                current_node = current_node->next;
            }
        }

        if (done == 0)
        {
            previous_node->next = current_node->next;

            free(current_node->data);
            free(current_node->description);
            free(current_node);
        }
        else
        {
            printf("Word not foud\n");
        }
    }
}

void find_description(char* name)
{
    struct Node *current_node = head;

    if (empty())
    {
        printf("List already empty\n");
    }
    else
    {   
        while (current_node->next)
        {
            if (!strcmp(name, current_node->data))
            {
                printf("The description of %s is %s\n", current_node->data, current_node->description);
                return;
            }
            else
            {
                current_node = current_node->next;
            }
        }
        printf("Word not found\n");
    }
}

void main(void)
{
    if (empty())
    {
        printf("Empty\n");
    }

    addElementHead("1", "DESCRIPTION");
    addElementTail("2", "DESCRIPTION");
    addElementTail("4", "DESCRIPTION");
    add_element_w_index("3", "description", 2);
    addElementTail("5", "DESCRIPTION");

    find_description("3");

    print_list();
    printf("-------------------------------------\n");
    
    freeList();
}