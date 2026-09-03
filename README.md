<a id="readme-top"></a>

[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<br />
<div align="center">
  <h3 align="center">🌳 Algoritmos e Estrutura de Dados III</h3>

  <p align="center">
    Implementações de Estrutura de Dados clássicas em C — trabalhos da disciplina <strong>Algoritmos e Estrutura de Dados III (CI1057)</strong> na UFPR.
    <br />
    <a href="https://github.com/GiuTP/Algoritmos-Estrutura-De-Dados-III/issues/new?labels=bug">Reportar Bug</a>
    &middot;
    <a href="https://github.com/GiuTP/Algoritmos-Estrutura-De-Dados-III/issues/new?labels=enhancement">Sugerir Melhoria</a>
  </p>
</div>

---

<!-- SUMÁRIO -->
<details>
  <summary>Sumário</summary>
  <ol>
    <li><a href="#-sobre-o-projeto">Sobre o Projeto</a>
      <ul>
        <li><a href="#-construído-com">Construído com</a></li>
      </ul>
    </li>
    <li><a href="#-fundamentação--arquitetura">Fundamentação / Arquitetura</a></li>
    <li><a href="#-estruturas-de-dados-tads">Estruturas de Dados (TADs)</a></li>
    <li><a href="#-estrutura-do-projeto">Estrutura do Projeto</a></li>
    <li>
      <a href="#-instalação">Instalação</a>
      <ul>
        <li><a href="#-pré-requisitos">Pré-requisitos</a></li>
        <li><a href="#-compilação">Compilação</a></li>
        <li><a href="#-comandos-úteis">Comandos Úteis</a></li>
      </ul>
    </li>
    <li><a href="#-licença">Licença</a></li>
    <li><a href="#-contato">Contato</a></li>
    <li><a href="#-agradecimentos">Agradecimentos</a></li>
  </ol>
</details>

---

## 📖 Sobre o Projeto

Este repositório reúne as implementações de Estrutura de Dados desenvolvidas em linguagem C para a disciplina **Algoritmos e Estrutura de Dados III (CI1057)** da **Universidade Federal do Paraná (UFPR)**.

As estruturas foram implementadas tomando como referência o livro **Introduction to Algorithms (Cormen et al., CLRS)**, especialmente no caso da Árvore Rubro-Negra, cuja implementação segue de perto o pseudocódigo apresentado na obra. Cada Estrutura de Dados é um trabalho independente, organizado em seu próprio diretório com seus arquivos-fonte, cabeçalho e Makefile.

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

### 🛠 Construído com

* [![C][C-badge]][C-url]
* [![Linux][Linux-badge]][Linux-url]

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## ⏱ Fundamentação / Arquitetura

Cada trabalho consiste na implementação de uma estrutura de dados clássica, com uma interface de linha de comando simples: o programa lê operações da entrada padrão (`stdin`) no formato `<operação> <chave>` e produz a saída esperada ao final.

```
+-------------------------------------------------------------+
|               Fluxo Geral de Cada TAD                       |
|                                                             |
|  1. Inicialização da estrutura de dados                     |
|  2. Leitura de operações via stdin (inserção / remoção)     |
|  3. Execução das operações sobre a estrutura                |
|  4. Impressão do estado final                               |
|  5. Liberação completa de memória                           |
+-------------------------------------------------------------+
```

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 🧩 Estruturas de Dados (TADs)

| TAD | Diretório | Descrição |
|-----|-----------|-----------|
| **Árvore Rubro-Negra** | [`red_black_tree/`](red_black_tree/) | Árvore BST auto-balanceada com propriedades cromáticas. Suporta inserção, remoção e busca em O(log n). Implementada conforme o CLRS (cap. 13). |
| **Tabela Hash com Hashing Duplo** | [`hash_table/`](hash_table/) | Tabela hash com duas funções independentes (h1: divisão, h2: multiplicação) e tratamento de colisão por overflow. Suporta inserção, remoção e busca. |

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 📁 Estrutura do Projeto

```
Algoritmos-Estrutura-De-Dados-III/
├── red_black_tree/          Árvore Red-Black
│   ├── rb.h                 interface e definições
│   ├── rb.c                 implementação das operações
│   ├── main.c               ponto de entrada e leitura de operações
│   ├── makefile             automação de compilação
│   └── README.md            documentação específica
├── hash_table/              Tabela Hash com Hashing Duplo
│   ├── hash_table.h         interface e definições
│   ├── hash_table.c         implementação das operações
│   ├── main.c               ponto de entrada e leitura de operações
│   ├── makefile             automação de compilação
│   └── README.md            documentação específica
├── LICENSE
└── README.md
```

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 🚀 Instalação

### 📦 Pré-requisitos

É necessário dispor de um compilador C com suporte a C99 e do GNU Make. No Ubuntu/Debian:

```sh
sudo apt update
sudo apt install build-essential valgrind -y
```

### 🔧 Compilação

1. Clone o repositório:
   ```sh
   git clone https://github.com/GiuTP/Algoritmos-Estrutura-De-Dados-III.git
   cd Algoritmos-Estrutura-De-Dados-III
   ```

2. Acesse o diretório do TAD desejado e compile:
   ```sh
   cd red_black_tree
   make
   ```

3. Execute com entrada padrão:
   ```sh
   echo "i 10
    i 20
    r 10" | ./bin/rb
   ```

### ⚙ Comandos Úteis

| Comando | Descrição |
|---------|-----------|
| `make` | Compila os arquivos-fonte e gera o executável em `bin/` |
| `make run` | Compila (se necessário) e executa o programa |
| `make valgrind` | Executa o programa sob o Valgrind para checagem de vazamentos de memória |
| `make clean` | Remove os arquivos-objeto gerados e o executável |

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 📄 Licença

O código-fonte deste projeto está distribuído sob a licença **MIT**. Consulte o arquivo [`LICENSE`](LICENSE) para mais informações.

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 📬 Contato

Giuliano Tavares — [github.com/GiuTP](https://github.com/GiuTP)

E-Mail: giulianotpt@gmail.com

Link do projeto: [https://github.com/GiuTP/Algoritmos-Estrutura-De-Dados-III](https://github.com/GiuTP/Algoritmos-Estrutura-De-Dados-III)

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

## 🙏 Agradecimentos

* [Best-README-Template](https://github.com/othneildrew/Best-README-Template) — template base deste README
* Thomas H. Cormen et al. — *Introduction to Algorithms* (CLRS), referência principal das implementações

<p align="right">(<a href="#readme-top">voltar ao topo</a>)</p>

---

<!-- MARKDOWN LINKS & IMAGES -->
[stars-shield]: https://img.shields.io/github/stars/GiuTP/Algoritmos-Estrutura-De-Dados-III.svg?style=for-the-badge
[stars-url]: https://github.com/GiuTP/Algoritmos-Estrutura-De-Dados-III/stargazers
[issues-shield]: https://img.shields.io/github/issues/GiuTP/Algoritmos-Estrutura-De-Dados-III.svg?style=for-the-badge
[issues-url]: https://github.com/GiuTP/Algoritmos-Estrutura-De-Dados-III/issues
[license-shield]: https://img.shields.io/github/license/GiuTP/Algoritmos-Estrutura-De-Dados-III.svg?style=for-the-badge
[license-url]: https://github.com/GiuTP/Algoritmos-Estrutura-De-Dados-III/blob/main/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/giuliano-tavares/
[C-badge]: https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white
[C-url]: https://en.wikipedia.org/wiki/C_(programming_language)
[Linux-badge]: https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black
[Linux-url]: https://www.kernel.org/
