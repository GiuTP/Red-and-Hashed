<a id="readme-top"></a>

# 🔴⚫ Árvore Rubro-Negra

Implementação em C de uma **Árvore Rubro-Negra** (*Red-Black Tree*) — trabalho da disciplina **Algoritmos e Estrutura de Dados III (CI1057)** na UFPR.

---

<!-- SUMÁRIO -->
<details>
  <summary>Sumário</summary>
  <ol>
    <li><a href="#-sobre-o-tad">Sobre o TAD</a></li>
    <li><a href="#-fundamentação">Fundamentação</a></li>
    <li><a href="#-propriedades-da-árvore-rubro-negra">Propriedades da Árvore Rubro-Negra</a></li>
    <li><a href="#-operações-e-casos">Operações e Casos</a></li>
    <li><a href="#-interface-pública-rbrh">Interface Pública (rb.h)</a></li>
    <li><a href="#-estrutura-do-diretório">Estrutura do Diretório</a></li>
    <li><a href="#-compilação-e-uso">Compilação e Uso</a></li>
  </ol>
</details>

---

## 📖 Sobre o TAD

A **Árvore Rubro-Negra** é uma Árvore Binária de Busca (BST) auto-balanceada onde cada nó carrega um atributo de cor — vermelho ou preto. As regras cromáticas garantem que a árvore permaneça aproximadamente balanceada após inserções e remoções, assegurando complexidade **O(log n)** para todas as operações.

Esta implementação é baseada no **Capítulo 13** de *Introduction to Algorithms* (Cormen et al., CLRS, 3ª ed.).

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## ⏱ Fundamentação

A árvore utiliza um nó **sentinela** (`t->nil`) em lugar de ponteiros `NULL`. Esse sentinela é sempre preto e simplifica o tratamento das bordas nas rotações e nos procedimentos de correção (*fixup*).

```
+-------------------------------------------------------------+
|           Ciclo de vida de uma operação de inserção         |
|                                                             |
|  1. Cria nó vermelho                                        |
|  2. Insere como em uma BST convencional                     |
|  3. Verifica violações das propriedades cromáticas          |
|  4. Aplica rotações e recolorações (insere_fixup_rb)        |
|  5. Garante que a raiz seja sempre preta                    |
+-------------------------------------------------------------+
```

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 📐 Propriedades da Árvore Rubro-Negra

Uma Árvore Rubro-Negra válida satisfaz as seguintes propriedades (CLRS, cap. 13):

1. Todo nó é **vermelho** ou **preto**.
2. A **raiz** é sempre **preta**.
3. Todo nó **folha** (sentinela `nil`) é **preto**.
4. Se um nó é **vermelho**, ambos os seus filhos são **pretos** *(sem dois vermelhos consecutivos)*.
5. Para qualquer nó, todos os caminhos até as folhas descendentes contêm o mesmo número de nós **pretos** (*black-height*).

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 🔄 Operações e Casos

### Inserção (`insere_rb`)

O nó é sempre inserido como **vermelho**. Se o pai também for vermelho, a propriedade 4 é violada e o fixup é acionado:

| Caso | Condição | Ação |
|------|----------|------|
| **Caso 1** | Tio do nó é **vermelho** | Recolore pai, tio e avô; sobe o ponteiro para o avô |
| **Caso 2** | Tio é **preto** e nó é filho à **direita** | Rotação à esquerda no pai; transforma no Caso 3 |
| **Caso 3** | Tio é **preto** e nó é filho à **esquerda** | Recolore pai e avô; rotação à direita no avô |

> Os casos simétricos (pai é filho à direita do avô) são tratados analogamente com rotações espelhadas.

### Remoção (`remove_rb`)

A remoção é feita como em uma BST, usando o **antecessor** (nó mais à direita da subárvore esquerda) quando o nó possui dois filhos. Se o nó removido (ou seu substituto) for **preto**, a *black-height* é violada e o fixup é necessário:

| Caso | Condição | Ação |
|------|----------|------|
| **Caso 1** | Irmão do nó é **vermelho** | Recolore irmão e pai; rotação à esquerda no pai |
| **Caso 2** | Irmão é **preto** com dois filhos **pretos** | Recolore irmão; sobe o ponteiro |
| **Caso 3** | Irmão **preto**, filho direito preto, filho esquerdo vermelho | Recolore e rotação à direita no irmão; transforma no Caso 4 |
| **Caso 4** | Irmão **preto**, filho direito **vermelho** | Ajusta cores; rotação à esquerda no pai; termina o loop |

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 🧩 Interface Pública (`rb.h`)

| Função | Assinatura | Descrição |
|--------|-----------|-----------|
| `cria_arvore` | `struct tree *cria_arvore()` | Inicializa a árvore com sentinela |
| `insere_rb` | `int insere_rb(struct tree *t, int chave)` | Insere uma chave mantendo as propriedades RB |
| `remove_rb` | `int remove_rb(struct tree *t, int chave)` | Remove uma chave mantendo as propriedades RB |
| `busca` | `struct no *busca(struct tree *t, struct no *n, int chave)` | Busca recursiva por chave |
| `printTree` | `void printTree(struct no *n, struct no *nil, int h)` | Impressão in-order com nível e cor |
| `destroi_arvore` | `void destroi_arvore(struct tree *t)` | Libera toda a memória alocada |

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 📁 Estrutura do Diretório

```
red_black_tree/
├── rb.h        interface e definições (struct no, struct tree, protótipos)
├── rb.c        implementação de todas as operações
├── main.c      leitura de operações via stdin e orquestração
└── makefile    automação de compilação
```

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 🚀 Compilação e Uso

```sh
# Compilar
make

# Uso: entrada via stdin no formato "<op> <chave>"
# op = 'i' (inserir) | 'r' (remover)
echo "i 10
i 20
i 5
r 10" | ./bin/rb
```

**Formato de saída** — `printTree` imprime em ordem simétrica (in-order):
```
<chave>,<nível>,<cor>
# cor: 0 = preto, 1 = vermelho
```

| Comando | Descrição |
|---------|-----------|
| `make` | Compila e gera `bin/rb` |
| `make clean` | Remove objetos e executável |

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>
