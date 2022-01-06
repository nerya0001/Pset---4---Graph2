#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graphAlgo.h"

void add_edge(pnode temp, int dest, int w, pnode *head) {
    if (temp->edges == NULL) {
        temp->edges = (pedge)malloc(sizeof(edge));
        if (temp->edges == NULL) {
            perror("malloc didnt work");
            exit(0);
        }

        temp->edges->weight = w;
        temp->edges->next = NULL;
        node *D = getNode(dest, head);
        temp->edges->endpoint = &(*D);
    }
    else {
        pedge pe = temp->edges;
        while (pe->next != NULL) {
            pe = pe->next;
        }
        pe->next = (pedge)malloc(sizeof(edge));
        if (pe->next == NULL) {
            perror("malloc didnt work");
            exit(0);
        }
        pe->next->next = NULL;
        pe->next->weight = w;
        node *D = getNode(dest, head);
        pe->next->endpoint = &(*D);
    }
}

void free_edges(pnode pEdge) {
    if (pEdge->edges != NULL) {
        pedge temp = pEdge->edges;

        while (temp != NULL) {
            pedge pe = NULL;
            pe = temp;
            temp = temp->next;
            free(pe);
        }
    }
    else {
        free(pEdge->edges);
    }
}

void delete_edge(pnode *head, int nodeId) {
    pnode tempNode = *head;

    while (tempNode != NULL) {
        if (tempNode->node_num != nodeId && tempNode->edges != NULL) {

            if (tempNode->edges->endpoint->node_num != nodeId) {
                pedge tempEdge = tempNode->edges;

                while (tempEdge->next != NULL) {
                    if (tempEdge->next->endpoint->node_num == nodeId) {
                        pedge pe = tempEdge->next;
                        tempEdge->next = tempEdge->next->next;
                        free(pe);
                        break;
                    }
                    tempEdge = tempEdge->next;
                }
            }
            else {
                if (tempNode->edges->next == NULL) {
                    pedge pe = tempNode->edges;
                    tempNode->edges = NULL;
                    free(pe);
                }
                else {
                    pedge pe = tempNode->edges;
                    tempNode->edges = pe->next;
                    free(pe);
                }
            }
        }
        tempNode = tempNode->next;
    }
}
