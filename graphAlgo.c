#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graphAlgo.h"

pdijkstra buildDijkstra(pnode start, int src);
void deletateDijkstra(pdijkstra dijkstra);
pdijkstra getPdijkstra(pdijkstra head, int id);
pdijkstra minVertical(pdijkstra head);
int shortsPath_cmd(pnode head, int src, int dest);

void deep_copy(int *fromArr, int *toArr, int arrLenght);
void swap(int *arr, int i, int j);
void calcPermot(int *arr, int arrLength);
void permotion(int start, int *arr, int arrLength);
void TSP_cmd(pnode head);


pnode build_graph_cmd(int num_of_nodes) {
    node *head = NULL;
    pnode newNode, temp = NULL;
    int i;
    head = (pnode)malloc(sizeof(node));
    if (head == NULL) {
        perror("malloc didnt work");
        exit(0);
    }
    head->node_num = 0;
    head->next = NULL;
    head->edges = NULL;
    temp = head;

    for (i = 1; i < num_of_nodes; i++) {
        newNode = (pnode)malloc(sizeof(node));
        if (newNode == NULL) {
            perror("malloc didnt work");
            exit(0);
        }
        newNode->node_num = i;
        newNode->next = NULL;
        newNode->edges = NULL;
        temp->next = newNode;
        temp = temp->next;
    }
    return head;
}

void delete_graph_cmd(pnode *head) {
    pnode tempNode = *head;
    while (tempNode != NULL) {
        pedge tempEdge = tempNode->edges;
        while (tempEdge != NULL) {
            pedge tempEdgefree = tempEdge;
            tempEdge = tempEdge->next;
            free(tempEdgefree);
        }
        node *tempFree = tempNode;
        tempNode = tempNode->next;
        free(tempFree);
    }
    free(tempNode);
}


pdijkstra buildDijkstra(pnode start, int src) {
    pdijkstra head = NULL;
    pdijkstra *index = &head;
    while (start != NULL) {
        (*index) = (pdijkstra)malloc(sizeof(dijkstra));
        if ((*index) == NULL) {
            perror("malloc didnt work");
            exit(0);
        }

        (*index)->node = start;
        if (start->node_num == src) {
            (*index)->weight = 0;
        }
        else {
            (*index)->weight = INFINITY;
        }
        (*index)->tag = 0;
        (*index)->next = NULL;
        index = &((*index)->next);
        start = start->next;
    }
    return head;
}

void deletateDijkstra(pdijkstra dijkstra) {
    while (dijkstra != NULL) {
        pdijkstra temp = dijkstra;
        dijkstra = dijkstra->next;
        free(temp);
    }
}

pdijkstra getPdijkstra(pdijkstra head, int id) {
    while (head != NULL) {
        if (head->node->node_num == id) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

pdijkstra minVertical(pdijkstra head) {
    pdijkstra ver = NULL;
    while (head != NULL) {
        if (!head->tag && head->weight < INFINITY && (ver == NULL || ver->weight < head->weight)) {
            ver = head;
        }
        head = head->next;
    }
    if (ver != NULL) {
        ver->tag = 1;
    }
    return ver;
}

int shortsPath_cmd(pnode head, int src, int dest) {
    pdijkstra dijkstraHead = buildDijkstra(head, src);
    pdijkstra u = minVertical(dijkstraHead);
    while (u != NULL) {
        pedge edgeIndex = u->node->edges;
        while (edgeIndex != NULL) {
            // relax
            pdijkstra v = getPdijkstra(dijkstraHead, edgeIndex->endpoint->node_num);
            int newDist = u->weight + edgeIndex->weight;
            if (v->weight > newDist) {
                v->weight = newDist;
            }
            edgeIndex = edgeIndex->next;
        }
        u = minVertical(dijkstraHead);
    }
    int distance = getPdijkstra(dijkstraHead, dest)->weight;
    if (distance == INFINITY) {
        distance = -1;
    }
    deletateDijkstra(dijkstraHead);
    return distance;
}



//*********TSP*********//
int weight;
int arrlenth;
pnode graph;

void deep_copy(int *fromArr, int *toArr, int arrLenght) {
    for (int i = 0; i < arrLenght; ++i) {
        toArr[i] = fromArr[i];
    }
}

void swap(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void calcPermot(int *arr, int arrLength) {
    int tempWeight = 0;
    for (int i = 0; i < arrLength - 1; ++i) {
        int distance = shortsPath_cmd(graph, arr[i], arr[i + 1]);
        if (distance == -1) {
            tempWeight = INFINITY;
            return;
        }
        tempWeight += distance;
    }
    if (tempWeight < weight) {
        weight = tempWeight;
    }
}

void permotion(int start, int *arr, int arrLength) {
    if (start == arrLength - 1) {
        calcPermot(arr, arrLength);
        return;
    }
    for (int i = start; i < arrLength; ++i) {
        int *arrCopy = (int *)(calloc(arrLength, sizeof(int)));
        deep_copy(arr, arrCopy, arrLength);
        swap(arrCopy, start, i);
        permotion(start + 1, arrCopy, arrLength);
        free(arrCopy);
    }
}
void TSP_cmd(pnode head) {
	weight = INFINITY;
	arrlenth = -1;
    graph = head;
    scanf("%d", &arrlenth);
    int *arr = (int *)(calloc(arrlenth, sizeof(int)));
    for (int i = 0; i < arrlenth; i++) {
        scanf("%d", &arr[i]);
    }
    // for (int i = 0; i < arrlenth; ++i)
    // {
    //      printf("%d , ", arr[i]);
    // }
    // printf("\n");
    int *arrCopy = (int *)(calloc(arrlenth, sizeof(int)));
    deep_copy(arr, arrCopy, arrlenth);
    // for (int i = 0; i < arrlenth; ++i)
    // {
    //     printf("%d , ", arr[i]);
    // }
    // printf("\n");
    permotion(0, arrCopy, arrlenth);
    free(arr);
    free(arrCopy);
    if (weight == INFINITY) {
        weight = -1;
    }
    printf("TSP shortest path: %d \n", weight);
}




void print_graph(pnode head) { // for self debug
    pnode tempNode = head;
    while (tempNode != NULL) {
        printf("Node: %d {", tempNode->node_num);
        pedge tempEdge = tempNode->edges;
        while (tempEdge != NULL) {
            printf("dest: %d weight: %d ", tempEdge->endpoint->node_num, tempEdge->weight);
            tempEdge = tempEdge->next;
        }
        printf("}");
        tempNode = tempNode->next;
    }
}
