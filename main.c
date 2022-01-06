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
    while (scanf("%c", &func) != EOF)
    {
        if (func == 'A')
        {
            delete_graph_cmd(head);
            // printf("enter num of verticals:\n");
            scanf("%d", &v);
            *head = build_graph_cmd(v);

            scanf("%c", &ch);

            while (scanf("%c", &ch) != 0)
            {
                if (ch == 'n')
                {
                    scanf("%d", &src);
                    insert_node_funcA_cmd(head, src);
                }
                else
                {
                    break;
                }
            }
            //print_graph(*head);
            func = ch;

            //printf("\nend A func\n");
        }
        if (func == 'B')
        {
            //printf("\nstart B FUNC\n");
            insert_node_cmd(head);
            //print_graph(*head);
            continue;
        }
        if (func == 'D')
        {
            // printf("\nstart D FUNC\n");
            delete_node_cmd(head);
            // print_graph(*head);
            continue;
        }
        if (func == 'S')
        {
            // printf("\nstart S FUNC\n");
            int src = -1, dest = -1;
            scanf("%d %d", &src, &dest);
            int dis = shortsPath_cmd(*head, src, dest);
            printf("Dijsktra shortest path: %d \n", dis);
            //print_graph(*head);
            continue;
        }
        if (func == 'T')
        {
            // printf("\nstart T FUNC\n");
            TSP_cmd(*head);
            // print_graph(*head);
            continue;
        }
    }
    delete_graph_cmd(head);
}
