#ifndef GRAPH_
#define GRAPH_
#define INFINITY 9999

typedef struct GRAPH_NODE_ *pnode;
typedef struct Dijkstra {
    pnode node;
    int weight;
    int tag;
    struct Dijkstra *next;
} dijkstra, *pdijkstra;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

// graph //
pnode build_graph_cmd(int num_of_nodes);

pnode getNode(int id, pnode *head);

void insertNodeA(pnode *head, int src);

void add_edge(pnode temp, int dest, int w, pnode *head);

void insert_node_cmd(pnode *head);

void free_edges(pnode pEdge);

void delete_node_cmd(pnode *head);

void delete_graph_cmd(pnode *head);

void print_graph(pnode head);

void delete_edge(pnode *head, int nodeId);

void TSP_cmd(pnode head);


// Dijkstra //
pdijkstra buildDijkstra(pnode start, int src);

void deletateDijkstra(pdijkstra dijkstra);

pdijkstra getPdijkstra(pdijkstra head, int id);

pdijkstra minVertical(pdijkstra head);

int shortsPath_cmd(pnode head, int src, int dest);

// TSP //
void deep_copy(int *fromArr, int *toArr, int arrLenght);

void swap(int *arr, int i, int j);

void calcPermot(int *arr, int arrLength);

void permotion(int start, int *arr, int arrLength);

void TSP_cmd(pnode head);

#endif
