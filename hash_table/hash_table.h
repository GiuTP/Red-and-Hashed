#ifndef HT
#define HT

#define m 11
enum stateHash { EMPTY, EXCLUDED, OCCUPIED }; 

struct slotHash{
    int k;
    enum stateHash state;
};

struct hashTable{
    struct slotHash T1[m];
    struct slotHash T2[m];
};

int h1(int k);

int h2(int k);

void initialize_table(struct hashTable *T);

/* Retorna um int com 1, 2 ou -1
   -1: chave nao estah em T
    1: chave estah em T1
    2: chave estah em T2 */
int search_hash(struct hashTable *T, int k, int *pos);

void insert_hash(struct hashTable *T, int k);

void delete_hash(struct hashTable *T, int k);

void print_hash(struct hashTable *T);

void destroyTable(struct hashTable *T);

#endif 