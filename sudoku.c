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

int is_valid(Node *n) {
    int row_check[9][9] = {0};
    int col_check[9][9] = {0};
    int box_check[9][9] = {0};

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                num--;  // Decrementar num 

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

List* get_adj_nodes(Node* n) {
    List* list = createList();
    int row, col;

    // Encontrar la primera casilla vacía
    int found = 0;
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (n->sudo[row][col] == 0) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    // Si no hay celdas vacías, retornamos la lista vacía
    if (!found) {
        return list;
    }

    // Generar nuevos nodos cambiando la casilla vacía por los valores 1-9
    for (int num = 1; num <= 9; num++) {
        Node* newNode = copy(n);
        if (newNode == NULL) {
            // Manejar el error de asignación de memoria
            clean(list);
            return NULL;
        }
        newNode->sudo[row][col] = num;

        // Solo agregar el nodo si es válido
        if (is_valid(newNode)) {
            pushBack(list, newNode);
        } else {
            free(newNode);
        }
    }

    return list;
}

int is_final(Node *n) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont) {
    if (!initial) return NULL;

    Stack* stack = createStack();
    push(stack, initial);

    while (!is_empty(stack)) {
        Node* node = (Node*) top(stack);
        pop(stack);

        (*cont)++;

        if (is_final(node)) {
            clean(stack);
            free(stack);
            return node;
        }

        List* neighbors = get_adj_nodes(node);

        for (Node* neighbor = (Node*) first(neighbors); neighbor != NULL; neighbor = (Node*) next(neighbors)) {
            push(stack, neighbor);
        }

        clean(neighbors);
        free(neighbors);

        free(node);  // Liberar la memoria usada por el nodo
    }

    clean(stack);
    free(stack);
    return NULL;
}




int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}