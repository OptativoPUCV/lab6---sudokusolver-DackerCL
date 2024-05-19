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

int is_valid(Node* n){
   int filas[9][9] = {0};
   int columnas[9][9] = {0};
   int submatrices[9][9] = {0};
   int x,y;
   for(x=0;x<9;x++){
      for(y=0;y<9;y++){
         int numero = n->sudo[x][y];
         if(numero!=0){
            int submatriz = (x/3)*3 + y/3;
            if(filas[x][numero-1] == 1 || columnas[y][numero-1] == 1 || submatrices[submatriz][numero-1] == 1){
               return 0;
            }
            filas[x][numero-1] = 1;
            columnas[y][numero-1] = 1;
            submatrices[submatriz][numero-1] = 1;
            
         }
      }
   }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();

   int fila =-1;
   int columna =-1;
   int x,y;
   for(x=0;x<9;x++){
      for(y=0;y<9;y++){
         if(n->sudo[x][y]==0){
            fila = x;
            columna = y;
            break;
         }
      }
      if(fila !=-1){
         break;
      }
   }
   if(fila == -1 && columna == -1){
      return list;
   }
   for(x=0;x<9;x++){
      Node* new_node = copy(n);
      new_node->sudo[fila][columna] = x + 1;
      if(is_valid(new_node)){
         pushBack(list,new_node);
      }else{
         free(new_node);
      }
   }
    return list;
}


int is_final(Node* n){
   for(int x = 0; x < 9; x++){
      for(int y = 0; y < 9; y++){
         if(n->sudo[x][y] == 0){
            return 0;
         }
      }
   }
    return 1;
}



Node* DFS(Node* initial, int* cont){
   Stack *stack = createStack();
   push(stack, initial);
   *cont = 0;

   while(!is_empty(stack)){
      Node* n = top(stack);
      pop(stack);
      (*cont)++;
      if(is_final(n)){
         while(is_empty(stack)){
            Node *aux = top(stack);
            pop(stack);
            free(aux);
         }
         free(stack);
         return n;
      }


      List *adj = get_adj_nodes(n);
      Node *aux = first(adj);
      while(aux){
         push(stack, aux);
         aux = next(adj);
      }
      free(n);
      free(adj);
   }
   free(stack);
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