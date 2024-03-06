#ifndef NODE_LIST_H
#define NODE_LIST_H

#include "model/inc/status.h"

struct node_t
{
    int n;
    node_t *next;
};

node_t list_init();
void free_list(node_t &list);
status add_node(node_t *node, int n);

#endif // NODE_LIST_H
