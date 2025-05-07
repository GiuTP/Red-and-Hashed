#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main(){
    struct tree *t;
    char op;
    int chave;

    /* inicializa a árvore */
    t = cria_arvore();

    /* leitura de operações */
    while (scanf(" %c %d ", &op, &chave) == 2){
        if (op == 'i'){
            if (insere_rb(t, chave) != 0)
                printf("Erro ao inserir chave %d\n", chave);     
        }
        if (op == 'r'){
            if (remove_rb(t, chave) != 0)
                printf("Chave %d não encontrada\n", chave);
        }
        
    }

    printTree(t->raiz, t->nil, 0);

    /* libera memória alocada para a árvore */
    destroi_arvore(t);
    
    return 0;
}