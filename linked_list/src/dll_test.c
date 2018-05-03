#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <gmodule.h>

void prettyPrint(GList* l) {
    GList *list = l;
    while (list != NULL){
        GList *next = list->next;
        printf("list data: %s\n", (char*)list->data);
        list = next;
    }
    printf("\n");
}

int main() {
    //instantiate list (NULL list is valid)
    GList *l = NULL;

    //appending elements to list. 
    l = g_list_append (l, "first");
    l = g_list_append (l, "second");
    l = g_list_append (l, "third");
    l = g_list_append (l, "fourth");
    l = g_list_append (l, "fifth");
    l = g_list_append (l, "seventh");
    l = g_list_append (l, "delete this");
    
    printf("appending items to list\n");
    prettyPrint(l);
    
    //insert element to list at position.
    l = g_list_insert (l, "sixth", 5);
    
    printf("insert sixth at position 5\n");
    prettyPrint(l);
    
    //get element at position
    GList *toDelete = g_list_nth (l, 7);
    
    printf("get element at position 7\n");
    printf("element: %s\n", (char*) (toDelete -> data));
    
    //remove position at element
    l = g_list_delete_link(l, toDelete);
    
    printf("remove element toDelete\n");
    prettyPrint(l);
    
    //get index position of element
    int position = g_list_index(l, "seventh");
    
    printf("The position of seventh is %d\n\n", position);
    
    printf("Current pos data: %s\n", (char*) (l->data));
    //get next
    l = l->next;
    printf("Next: Current pos data: %s\n", (char*) (l->data));
    //get prev
    l = l->prev;
    printf("Prev: Current pos data: %s\n", (char*) (l->data));
    /*l = l->prev;
    printf("%s\n", l->data);*/

    return 0;
}