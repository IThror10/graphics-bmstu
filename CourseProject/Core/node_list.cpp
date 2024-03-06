#include "Core/node_list.h"
#include <malloc.h>

node_t list_init()
{
    node_t list;
    list.n = 0;
    list.next = nullptr;
    return list;
}

void free_list(node_t& list)
{
    node_t *node = list.next;
    list.next = nullptr;

    while (node)
    {
        node_t *tmp = node->next;
        free(node);
        node = tmp;
    }
}

status add_node(node_t *list, int n)
{
    status result = ok;

    if (list)
    {
        while (list->next)
            list = list->next;

        list->next = (node_t*) malloc(sizeof(node_t));
        if (list->next)
        {
            list->next->next = nullptr;
            list->next->n = n;
        }
        else
            result = memory_error;
    }
    return result;
}
