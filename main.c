#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "graphAlgo.h"

int main()
{
    pnode temp = NULL;
    pnode *head = &temp;
    char func;
    char ch;
    int v = 0;
    int src = 0;

    while (scanf("%c", &func) != EOF) {
        if (func == 'A') {
            delete_graph_cmd(head);

            scanf("%d", &v);
            *head = build_graph_cmd(v);

            scanf("%c", &ch);

            while (scanf("%c", &ch) != 0) {
                if (ch == 'n') {
                    scanf("%d", &src);
                    insertNodeA(head, src);
                }
                else {
                    break;
                }
            }
            func = ch;
        }

        if (func == 'B') {
            insert_node_cmd(head);
            continue;
        }

        if (func == 'D') {
            delete_node_cmd(head);
            continue;
        }

        if (func == 'S') {
            int src = -1, dest = -1;
            scanf("%d %d", &src, &dest);
            int dis = shortsPath_cmd(*head, src, dest);
            printf("Dijsktra shortest path: %d \n", dis);
            continue;
        }

        if (func == 'T') {
            TSP_cmd(*head);
            continue;
        }
    }
    delete_graph_cmd(head);
}
