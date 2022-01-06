#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graphAlgo.h"

pnode getNode(int id, pnode *head) {
    pnode temp = *head;

    while (temp != NULL) {
        if (temp->node_num == id) {
            return temp;
        }
        else {
            temp = temp->next;
        }
    }
    return NULL;
}

void insertNodeA(pnode *head, int src) {
    int dest;
    int weight;
    pnode temp = getNode(src, head);

    while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0) {
        if (isalpha(dest) || isalpha(weight)) {
            break;
        }
        add_edge(temp, dest, weight, head);
    }
}

void insert_node_cmd(pnode *head) {
    int src;
    scanf("%d", &src);
    int dest;
    int weight;
    pnode temp = getNode(src, head);

    if (temp == NULL) {
        pnode pGraphNode = *head;
        while (pGraphNode->next != NULL) {
            pGraphNode = pGraphNode->next;
        }

        pnode newNode = (pnode)(malloc(sizeof(node)));

        if (newNode == NULL) {
            perror("malloc didnt work");
            exit(0);
        }

        newNode->node_num = src;
        newNode->edges = NULL;
        newNode->next = NULL;
        pGraphNode->next = newNode;

        while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0) {
            if (isalpha(dest) || isalpha(weight)) {
                break;
            }
            add_edge(newNode, dest, weight, head);
        }
    }
    else {
        free_edges(temp);
        temp->edges = NULL;

        while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0) {
            if (isalpha(dest) || isalpha(weight)) {
                break;
            }
            add_edge(temp, dest, weight, head);
        }
    }
}

void delete_node_cmd(pnode *head) {
    int id = 0;
    scanf("%d", &id);
    delete_edge(head, id);
    pnode tempNode = *head;
    node *pNode = NULL;

    if (tempNode->node_num != id) {
        while (tempNode->next->node_num != id) {
            tempNode = tempNode->next;
        }
        pNode = tempNode->next;
        tempNode->next = tempNode->next->next;
        free_edges(pNode);
        free(pNode);
    }
    else {
        pNode = *head;
        *head = pNode->next;
        free_edges(pNode);
        free(pNode);
    }
}
