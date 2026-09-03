#ifndef REDBLACK
#define REDBLACK

/* Struct dos nós da árvore */
struct no{
    int chave;
    struct no *esq;
    struct no *dir;
    struct no *pai;
    void *valor;
    int color; 
};

/* Struct da árvore */
struct tree{
    struct no *raiz;
    struct no *nil;
};

/* Cria uma árvore, alocando memória para a raiz, o sentinela e atribuindo os ponteiros iniciais. */
/* Retorna: um ponteiro para a árvore criada.                           */
struct tree *cria_arvore();

/* Cria um nó "solto" com a chave passada de parâmetro.                 */
/* Retorna: um ponteiro para o nó criado.                               */
struct no *cria_no(int chave, struct no *nil);

/* Rotaciona a subárvore para a esquerda com base no nó de parâmetro.   */
void rotation_left(struct tree *t, struct no *n);

/* Rotaciona a subárvore para a direita com base no nó de parâmetro.    */
void rotation_right(struct tree *t, struct no *n);

/* Insere um nó na árvore como se fosse uma BST.                        */
/* Atuliza o ponteiro do pai do nó inserido para o pai correto.         */ 
/* Retorna:
    * -1 em caso de erro de inserção;
    *  0 em caso de sucesso.                                            */
int insere_bst(struct tree *t, struct no *n);

/* Corrige a árvore caso alguma propriedade da Red-Black tenha sido violada após inserção. */
void insere_fixup_rb(struct tree *t, struct no *n);

/* Função wrapper para inserir na árvore Red-Black. Ela faz os seguintes passos:
    * Cria o nó com a chave passada;
    * Insere na árvore como se fosse uma BST;
    * Corrige a árvore se necessário.                                   */
/* Retorna:
    * -2 caso não foi criar o nó;
    * -1 caso não foi possível inserir o nó;
    *  0 caso foi um sucesso.                                           */
int insere_rb(struct tree *t, int chave);

/* Tranposta o nó u para o lugar do nó v */
void transplant_rb(struct tree *t, struct no *u, struct no *v);

/* Procura o antecessor do nó passado. O Sucesso é o nó mais a direita da subárvore da esquerda. */
/* Retorna: um ponteiro para o antecessor.                                                       */
struct no *find_max(struct tree *t, struct no *n);

/* Busca a chave passada dentro da árvore.            */
/* Retorna: 
    * Caso encontre, o ponteiro do nó da chave;
    * Caso não encontre, o ponteiro para o sentinela. */
struct no *busca(struct tree *t, struct no *n, int chave);

/* Remove o nó passado quase igual a uma BST.  */
/* Separando em caso:
    * Caso o nó possui nenhum ou 1 filho e for preto é retornado o ponteiro do filho da esquerda/direita para correção;
    * Caso o nó possui dois filhos e seu antecessor for preto é retornado o ponteiro do seu filho da esquerda para correção;
    * Caso o nó removido for vermelho ou seu antecessor for vermelho, é retornado NULL                                          */
struct no *remove_no(struct tree *t, struct no *n);

/* Corrige a árvore caso alguma propriedade da Red-Black tenha sido violada após remoção. */
void remove_fixup_rb(struct tree *t, struct no *n);

/* Função wrapper para remover na árvore Red-Black. Ela faz os seguintes passos:
    * Busca o nó da chave passada;
    * Remove da árvore quase igual a BST;
    * Corrige a árvore se necessário.                                   */
/* Retorna:
    * -1 caso o nó não existir;
    *  0 caso foi um sucesso.                                           */
int remove_rb(struct tree *t, int chave);

/* Imprime os valores presente na árvore em ordem (inorder). */
void printTree(struct no *n, struct no *nil, int h);

/* Libera a memória alocada para todos os nós presentes na árvore. */
void destroi_nos(struct tree *t, struct no *n);

/* Libera a memória alocada para todos os nós (destroi_nos). Por fim, libera a memória alocada para a raiz e o sentinela */
void destroi_arvore(struct tree *t);

#endif