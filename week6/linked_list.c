/* 
 * Read in a list of names from stdin
 *
 * usage: names < infile
 * stdin: list of names, one per line
 * stdout: list of names, one per line
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// A structure for each node in linked list
struct listnode {
    char *name;
    struct listnode *next;
};

bool list_insert(struct listnode *headp, char *name);
struct listnode *listnode_new(char *name);

/***********************************************************/
int main()
{
    struct listnode head = { NULL, NULL }; // initializeempty list
    int n = 0;       // total number of names read

    // read strings from standard input
    while (!feof(stdin)) {
        char *name = NULL;
        size_t name_len = 0;
        getline(&name, &name_len, stdin);
        if (name != NULL) {
            if (list_insert(&head, name)) {
                n++;
            }
        }
    }

    printf("Read %d names:\n", n);

    for (struct listnode *node = head.next; node != NULL; node = node->next) {
        printf("%s\n", node->name);
    }

    // must free the list here (Valgrind will keep us honest)

    return 0;
}

// insert name at the head of the list
bool list_insert(struct listnode *headp, char *name)
{
    struct listnode *node = listnode_new(name);

    if (headp == NULL || node == NULL) {
        return false;
    } else {
        // insert the new node at head of the list
        node->next = headp->next;
        headp->next = node;
    }
    return true;
}

// allocate a new node with provided name
struct listnode *listnode_new(char *name)
{
    // allocate memory for the new node
    struct listnode *node = malloc(sizeof(struct listnode));

    if (node == NULL) {
        return NULL;
    } else {
        // initialize node contents
        node->next = NULL;
        node->name = name;
    }

    return node;
}
