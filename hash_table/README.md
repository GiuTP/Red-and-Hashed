<a id="readme-top"></a>

# #️⃣ Tabela Hash com Hashing Duplo

Implementação em C de uma **Tabela Hash** com duas funções de hash e tratamento de colisão por tabela de overflow — trabalho da disciplina **Algoritmos e Estrutura de Dados III (CI1057)** na UFPR.

---

<!-- SUMÁRIO -->
<details>
  <summary>Sumário</summary>
  <ol>
    <li><a href="#-sobre-o-tad">Sobre o TAD</a></li>
    <li><a href="#-fundamentação">Fundamentação</a></li>
    <li><a href="#-funções-de-hash">Funções de Hash</a></li>
    <li><a href="#-operações-e-casos">Operações e Casos</a></li>
    <li><a href="#-interface-pública-hash_tableh">Interface Pública (hash_table.h)</a></li>
    <li><a href="#-estrutura-do-diretório">Estrutura do Diretório</a></li>
    <li><a href="#-compilação-e-uso">Compilação e Uso</a></li>
  </ol>
</details>

---

## 📖 Sobre o TAD

A **Tabela Hash** é uma estrutura de dados que mapeia chaves a posições em um arranjo de tamanho fixo por meio de uma função de hash, visando acesso em **O(1)** no caso médio. Esta implementação utiliza **duas tabelas** (`T1` e `T2`) com funções de hash distintas para tratar colisões: a tabela `T1` armazena as chaves primárias e `T2` funciona como tabela de overflow para chaves deslocadas por colisão em `T1`.

Cada slot possui um estado: `EMPTY`, `OCCUPIED` ou `EXCLUDED` — o estado `EXCLUDED` (lógica de lazy deletion) permite que buscas não sejam interrompidas por slots liberados.

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## ⏱ Fundamentação

```
+-------------------------------------------------------------+
|           Ciclo de vida de uma operação de inserção         |
|                                                             |
|  1. Calcula pos1 = h1(k) → tenta inserir em T1[pos1]        |
|  2. Se T1[pos1] livre → insere diretamente em T1            |
|  3. Se colisão em T1 → desloca chave antiga para T2         |
|     via h2(chave_antiga) → T1[pos1] recebe a nova chave     |
|  4. Chaves duplicadas são ignoradas                         |
+-------------------------------------------------------------+
```

O tamanho das tabelas é fixado em `m = 11` (primo), o que melhora a distribuição das funções de hash por divisão.

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 🔢 Funções de Hash

| Função | Fórmula | Método |
|--------|---------|--------|
| `h1(k)` | `k mod m` | Divisão |
| `h2(k)` | `⌊m · frac(k · 0.9)⌋` | Multiplicação (constante de Knuth ≈ 0,9) |

A função `h2` aplica o **método da multiplicação**: multiplica a chave por uma constante fracionária e extrai a parte fracionária do resultado, que é então escalonada para o intervalo `[0, m-1]`.

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 🔄 Operações e Casos

### Busca (`search_hash`)

| Caso | Condição | Retorno |
|------|----------|---------|
| **-1** | `T1[h1(k)]` está `EMPTY` | Chave não existe |
| **1** | `T1[h1(k)]` está `OCCUPIED` e `T1[h1(k)].k == k` | Chave em T1 |
| **2** | `T2[h2(k)]` está `OCCUPIED` e `T2[h2(k)].k == k` | Chave em T2 |
| **-1** | Nenhum dos casos acima | Chave não existe |

### Inserção (`insert_hash`)

| Caso | Condição | Ação |
|------|----------|------|
| **Direto em T1** | `T1[h1(k)]` está `EMPTY` ou `EXCLUDED` | Insere `k` em `T1[pos1]` |
| **Colisão em T1** | `T1[h1(k)]` está `OCCUPIED` com chave diferente | Move chave antiga para `T2[h2(chave_antiga)]`; insere `k` em `T1[pos1]` |
| **Duplicata** | `k == T1[h1(k)].k` | Nenhuma ação |

### Remoção (`delete_hash`)

| Caso | Condição | Ação |
|------|----------|------|
| **Chave em T2** | `search_hash` retorna 2 | Marca slot em T2 como `EMPTY` |
| **Chave em T1** | `search_hash` retorna 1 | Marca slot em T1 como `EXCLUDED` (lazy deletion) |

> O uso de `EXCLUDED` em T1 (em vez de `EMPTY`) preserva a capacidade de encontrar chaves deslocadas para T2 durante buscas subsequentes.

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 🧩 Interface Pública (`hash_table.h`)

| Função | Assinatura | Descrição |
|--------|-----------|-----------|
| `initialize_table` | `void initialize_table(struct hashTable *T)` | Inicializa todos os slots como `EMPTY` |
| `search_hash` | `int search_hash(struct hashTable *T, int k, int *pos)` | Busca `k`; retorna 1 (T1), 2 (T2) ou -1 (não encontrado) |
| `insert_hash` | `void insert_hash(struct hashTable *T, int k)` | Insere `k` com tratamento de colisão |
| `delete_hash` | `void delete_hash(struct hashTable *T, int k)` | Remove `k` com lazy deletion |
| `print_hash` | `void print_hash(struct hashTable *T)` | Imprime todos os elementos ordenados por chave |
| `destroyTable` | `void destroyTable(struct hashTable *T)` | Libera a memória da tabela |

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 📁 Estrutura do Diretório

```
hash_table/
├── hash_table.h    interface, definições de tipos e estados (enum stateHash)
├── hash_table.c    implementação das operações e funções auxiliares
├── main.c          leitura de operações via stdin e orquestração
└── makefile        automação de compilação
```

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 🚀 Compilação e Uso

```sh
# Compilar
make

# Uso: entrada via stdin no formato "<op> <chave>"
# op = 'i' (inserir) | 'r' (remover)
echo "i 5
i 16
i 10
r 5" | ./bin/hash_table
```

**Formato de saída** — `print_hash` imprime todos os slots ocupados, ordenados por chave:
```
<chave>,<tabela>,<posição>
# tabela: T1 ou T2
```

| Comando | Descrição |
|---------|-----------|
| `make` | Compila e gera o executável em `bin/` |
| `make clean` | Remove objetos e executável |

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>
