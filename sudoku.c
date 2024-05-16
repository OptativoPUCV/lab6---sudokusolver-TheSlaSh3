#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}
/*2.Cree la función int is_valid(Node * n), para validar si un estado/nodo es válido (cumple con las restricciones del problema). Debe validar que:

No se repitan números en las filas
No se repitan números en las columnas
No se repitan números en las submatrices de 3x3
Si el estado es válido la función retorna 1, si no lo es retorna 0.*/
int is_valid(Node *n) {
    int row_check[9][9] = {0};
    int col_check[9][9] = {0};
    int box_check[9][9] = {0};

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                num--;  // Decrementar num para usarlo como índice (0-8)

                // Verificar filas
                if (row_check[i][num]) {
                    return 0;
                }
                row_check[i][num] = 1;

                // Verificar columnas
                if (col_check[j][num]) {
                    return 0;
                }
                col_check[j][num] = 1;

                // Verificar submatrices de 3x3
                int box_index = (i / 3) * 3 + (j / 3);
                if (box_check[box_index][num]) {
                    return 0;
                }
                box_check[box_index][num] = 1;
            }
        }
    }

    return 1;
}

/*
1.Cree una función que a partir de un nodo genere una lista con los nodos adyacentes:

Recuerde que los nodos adyacentes son generados aplicando las acciones al estado actual.
*/
List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(n->sudo[i][j]==0)
            {
                Node* adj=copy(n);
                adj->sudo[i][j]=1;
                pushBack(list,adj);
            }
        }
    }
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/