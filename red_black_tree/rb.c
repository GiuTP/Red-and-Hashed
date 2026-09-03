#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

#define BLACK 0
#define RED 1

struct tree *cria_arvore(){
    struct tree *t;

    if (!(t = malloc(sizeof(struct tree))))
        return NULL;
    
    if (!(t->nil = malloc(sizeof(struct no))))
        return NULL;
    
    /* Os ponteiros do sentinela são ele próprio e sua cor é preta */
    t->nil->color = BLACK;
    t->nil->dir = t->nil;
    t->nil->esq = t->nil;
    t->nil->pai = t->nil;

    /* A raiz é o sentinela quando a árvore não possui nós */
    t->raiz = t->nil;

    return t;
}

struct no *cria_no(int chave, struct no *nil){
    struct no *novo;

    if (!(novo = malloc(sizeof (struct no))))
        return NULL;
    
    /* Nós criados sempre são vermelhos */
    novo->chave = chave;
    novo->color = RED;

    novo->dir = nil;
    novo->esq = nil;
    novo->pai = nil;

    novo->valor = NULL;

    return novo;
}

void rotation_left(struct tree *t, struct no *n){
    struct no *aux;

    /* a base (y) é o filho da direita nessa rotação */
    aux = n->dir;

    /* novo filho direito de n */
    n->dir = aux->esq;

    /* se a subarvore esquerda de aux não é vazia */
    /* se for vazia, o sentinela t.nil não precisa de pai */
    if (aux->esq != t->nil)
        aux->esq->pai = n;

    /* atualiza o pai de aux */
    aux->pai = n->pai;
    
    if (n->pai == t->nil)         
        t->raiz = aux;             /* n é a raiz da árvore */
    else if (n->pai->esq == n)   
        n->pai->esq = aux;         /* n é filho da esquerda */ 
    else
        n->pai->dir = aux;         /* n é filho da direita */

    /* ponteiros que faltaram */
    aux->esq = n;
    n->pai = aux; 
}

void rotation_right(struct tree *t, struct no *n){
    struct no *aux;

    /* a base (aux) é o filho da esquerda nessa rotação */
    aux = n->esq;

    /* novo filho esquerdo de n */
    n->esq = aux->dir;

    /* se a subarvore direita de aux não é vazia */
    /* se for vazia, o sentinela t.nil não precisa de pai */
    if (aux->dir != t->nil)
        aux->dir->pai = n;
    
    /* atualiza o pai de aux */
    aux->pai = n->pai;

    if (n->pai == t->nil)
        t->raiz = aux;             /* n é a raiz da árvore */
    else if(n->pai->esq == n)
        n->pai->esq = aux;         /* n é filho da esquerda */ 
    else
        n->pai->dir = aux;         /* n é filho da direita */
    
    /* ponteiros que faltaram */
    aux->dir = n;
    n->pai = aux;
}

int insere_bst(struct tree *t, struct no *n){
    struct no *aux, *pai;

    if (!(t) || !(n))
        return -1;

    aux = t->raiz;
    pai = t->nil;

    while (aux != t->nil){
        pai = aux;
        if (n->chave <= aux->chave)
            aux = aux->esq;
        else
            aux = aux->dir;
    }

    /* atualizado o ponteiro pai de n */
    n->pai = pai;

    /* atualiza o ponteiro do filho do pai de n */
    if (pai == t->nil)
        t->raiz = n;
    else if (n->chave <= pai->chave)
        pai->esq = n;
    else
        pai->dir = n;

    return 0;
}

void insere_fixup_rb(struct tree *t, struct no *n){
    struct no *aux;

    while (n->pai != t->nil && n->pai->color == RED){
        /* pai de n é filho da esquerda do avô de n */
        if (n->pai == n->pai->pai->esq){
            aux = n->pai->pai->dir;     /* aux é o tio de n */
            
            /* Caso 1: o tio (aux) de n é vermelho */
            /* Esse caso que faz o loop continuar */
            if ((aux != t->nil) && (aux->color == RED)){
                n->pai->color = BLACK;
                aux->color = BLACK;
                n->pai->pai->color = RED;
                n = n->pai->pai;
            }
            else{
                /* Caso 2: o tio (aux) de n é preto e n é um filho à direita */
                if (n == n->pai->dir){
                    n = n->pai;           /* n vira o seu pai */
                    rotation_left(t, n);  /* após rotação, n volta a ser filho do seu pai */

                }
                /* Caso 3: o tio (aux) de n é preto e n é um filho à esquerda */
                n->pai->color = BLACK;    
                n->pai->pai->color = RED;
                rotation_right(t, n->pai->pai); /* após rotação, estrutura ficou certa */
            }
        }

        /* caso simétrico */
        else{
            aux = n->pai->pai->esq;

            if ((aux != t->nil) && (aux->color == RED)){
                n->pai->color = BLACK;
                aux->color = BLACK;
                n->pai->pai->color = RED;
                n = n->pai->pai;
            }
            else{
                if (n == n->pai->esq){
                    n = n->pai;
                    rotation_right(t, n);
                }
                n->pai->color = BLACK;
                n->pai->pai->color = RED;
                rotation_left(t, n->pai->pai);
            }
        }
    }
    /* Por fim, raiz deve ser sempre preta */
    t->raiz->color = BLACK;
}

int insere_rb(struct tree *t, int chave){
    struct no *novo;

    if (!(novo = cria_no(chave, t->nil)))
        return -2;
    
    if (insere_bst(t, novo) != 0){
        free(novo);
        return -1;
    }

    insere_fixup_rb(t, novo);

    return 0;
}

void transplant_rb(struct tree *t, struct no *u, struct no *v){
    if (u->pai == t->nil)
        t->raiz = v;
    else if (u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;
    
    v->pai = u->pai;
}

struct no *find_max(struct tree *t, struct no *n){
    if (n->dir == t->nil)
        return n;
    
    return find_max(t, n->dir);
}

struct no *busca(struct tree *t, struct no *n, int chave){
    if (n == t->nil || n->chave == chave)
        return n;
    
    if (chave < n->chave)
        return busca(t, n->esq, chave);
    
    return busca(t, n->dir, chave);
}

struct no *remove_no(struct tree *t, struct no *n){
    struct no *x, *y;
    int y_cor_original;

    y = n;
    y_cor_original = y->color;

    /* Casos onde n tem apenas um filho */
    if (n->esq == t->nil){
        x = n->dir;
        transplant_rb(t, n, n->dir);
    }
    else if(n->dir == t->nil){
        x = n->esq;
        transplant_rb(t, n, n->esq);
    }

    /* Caso onde n tem dois filhos */
    else{
        y = find_max(t, n->esq);    /* É pego o antecessor de n */
        y_cor_original = y->color;
        x = y->esq;

        if (y != n->esq){
            transplant_rb(t, y, y->esq);
            y->esq = n->esq;
            y->esq->pai = y;
        }
        else
            x->pai = y;

        transplant_rb(t, n, y);
        y->dir = n->dir;
        y->dir->pai = y;
        y->color = n->color;
    }
    if (y_cor_original == BLACK)
        return x;
    
    return NULL;
}

void remove_fixup_rb(struct tree *t, struct no *n){
    struct no *aux;

    while (n != t->raiz && n->color == BLACK){
        /* n é filho da esquerda */
        if (n == n->pai->esq){

            /* aux é o irmão de n */
            aux = n->pai->dir;

            /* Caso 1: irmão de n (aux) é vermelho */
            if (aux->color == RED){
                aux->color = BLACK;         /* colore o irmão de n como preto */
                n->pai->color = RED;        /* colore o pai de n como vermelho */
                rotation_left(t, n->pai);   /* rotaciona para esquerda o pai de n */
                aux = n->pai->dir;          /* aux recebe o novo irmão de n */
            }

            /* Apenas esse caso faz o laço se repetir */
            /* Caso 2: irmão de n (aux) é preto e tem dois filhos pretos */
            if (aux->esq->color == BLACK && aux->dir->color == BLACK){
                aux->color = RED;
                n = n->pai;
            }
            else{
                /* Caso 3: irmão de n (aux) é preto e o filho direito de 
                    aux é preto e o filho esquerdo de aux é vermelho */
                if (aux->dir->color == BLACK){
                    aux->esq->color = BLACK;
                    aux->color = RED;
                    rotation_right(t, aux);
                    aux = n->pai->dir;
                }

                /* Caso 4: o irmão de n (aux) é preto e o filho direito de aux é vermelho */
                aux->color = n->pai->color;
                n->pai->color = BLACK;
                aux->dir->color = BLACK;
                rotation_left(t, n->pai);
                n = t->raiz;
            }
        }
        /* Caso simétrico */
        /* n é filho da direita */
        else{
            /* aux é o irmão de n */
            aux = n->pai->esq;

            /* Caso 1: irmão de n (aux) é vermelho */
            if (aux->color == RED){
                aux->color = BLACK;
                n->pai->color = RED;
                rotation_right(t, n->pai);
                aux = n->pai->esq;
            }

            /* Apenas esse caso faz o laço se repetir */
            /* Caso 2: irmão de n (aux) é preto e tem dois filhos pretos */
            if (aux->dir->color == BLACK && aux->esq->color == BLACK){
                aux->color = RED;
                n = n->pai;
            }
            else{
                /* Caso 3: irmão de n (aux) é preto e o filho esquerdo de 
                    aux é preto e o filho direito de aux é vermelho */
                if (aux->esq->color == BLACK){
                    aux->dir->color = BLACK;
                    aux->color = RED;
                    rotation_left(t, aux);
                    aux = n->pai->esq;
                }

                /* Caso 4: o irmão de n (aux) é preto e o filho esquerdo de aux é vermelho */
                aux->color = n->pai->color;
                n->pai->color = BLACK;
                aux->esq->color = BLACK;
                rotation_right(t, n->pai);
                n = t->raiz;
            }
        }
    }
    n->color = BLACK;
}

int remove_rb(struct tree *t, int chave){
    struct no *n, *x;

    if ((n = busca(t, t->raiz, chave)) == t->nil)
        return -1;

    x = remove_no(t, n);

    if (x)
        remove_fixup_rb(t, x);

    free(n);
    return 0;
}

void printTree(struct no *n, struct no *nil, int h){
    if (n == nil)
        return;

    printTree(n->esq, nil, h + 1);
    printf("%d,%d,%d\n", n->chave, h, n->color);
    printTree(n->dir, nil, h + 1);
}

void destroi_nos(struct tree *t, struct no *n){
    if (n != t->nil){
        destroi_nos(t, n->esq);
        destroi_nos(t, n->dir);
        free(n);
    }
}

void destroi_arvore(struct tree *t){
    if (t->raiz != t->nil)
        destroi_nos(t, t->raiz);
    
    free(t->nil);
    free(t);
}