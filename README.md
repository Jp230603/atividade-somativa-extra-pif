<h1 align="center">Atividade Somativa Extra — Ponteiros em C 🧭</h1>

Resolução das 5 atividades sobre ponteiros, passagem por referência, structs, aritmética de ponteiros e alocação dinâmica de memória em C.

## Estrutura da atividade:

```
.
├── include/
│   └── produto.h  # Declarações da struct Produto e protótipos das funções
├── src/
│   └── produto.c  # Implementação das funções de manipulação de produtos
├── main/
│   └── main.c # Ponto de entrada: demonstra sequencialmente as 5 atividades
├── Makefile
└── README.md
```

A separação segue a convenção de projetos C:

- **`include/`** expõe a interface pública via headers (`.h`) — o que o usuário do módulo precisa conhecer
- **`src/`** contém a implementação reutilizável (`.c`) — o que fica escondido do chamador
- **`main/`** isola o ponto de entrada, facilitando futura substituição ou extensão sem tocar na lógica de negócio

---

## Compilação

### Usando o Makefile (recomendado)

```bash
make
```

Para remover o binário gerado:

```bash
make clean
```

### Compilação manual

```bash
gcc -Wall -Wextra -pedantic -std=c11 -Iinclude src/produto.c main/main.c -o programa
```

### Flags detalhadas 🚩

| Flag | Descrição |
|------|-----------|
| `-Wall` | Ativa todos os avisos padrão do compilador |
| `-Wextra` | Ativa avisos adicionais além dos habilitados por `-Wall` (argumentos não utilizados, comparações suspeitas etc.) |
| `-pedantic` | Exige conformidade estrita com o padrão C; rejeita extensões do compilador (ex.: VLAs do GCC) |
| `-std=c11` | Compila segundo o padrão ISO/IEC 9899:2011 (C11), que permite declaração de variáveis no meio do bloco e `_Bool` nativo |
| `-Iinclude` | Adiciona `include/` ao caminho de busca de headers, permitindo `#include "produto.h"` em qualquer `.c` |

---

## Execução ⚙️

```bash
./programa
```

As Atividades 1 a 4 executam automaticamente. Na Atividade 5, o programa solicita a quantidade de produtos e os dados de cada um.

## Atividades ✏️

### Atividade 1 — Fundamentos de Ponteiros e Modificação Direta

**Conceito:** um ponteiro armazena um endereço de memória. Ao desreferenciar com `*`, lemos ou escrevemos diretamente naquele endereço.

```c
float preco = 100.0f;
float *ptr = &preco;   // ptr aponta para o endereço de preco
*ptr *= 1.10f;    // escreve em &preco — altera a variável original
printf("%.2f\n", preco);   // imprime 110.00
```

A instrução `*ptr *= 1.10f` não cria cópia alguma: o valor em memória é modificado in-place.

### Atividade 2 — Passagem por Referência

**Conceito:** C só tem passagem por valor. Para modificar uma variável do chamador dentro de uma função, passa-se o seu endereço.

```c
void aplicar_desconto_float(float *preco, float percentual) 
{
    *preco -= *preco * (percentual / 100.0f);
}

// chamada:
aplicar_desconto_float(&preco2, 15.0f);
```

`&preco2` passa o endereço; dentro da função, `*preco` acessa a variável original. O retorno é `void` — a "devolução" acontece via efeito colateral no ponteiro.

### Atividade 3 — Ponteiros para Structs

**Conceito:** o operador `->` é açúcar sintático para `(*ptr).campo`. Permite acessar membros de uma struct diretamente pelo ponteiro, sem copiar a struct inteira.

```c
typedef struct 
{
    int   id;
    float preco;
} Produto;

void aplicar_desconto(Produto *produto, float percentual) 
{
    produto->preco -= produto->preco * (percentual / 100.0f);
}
```

Passar `Produto *` é eficiente: independentemente do tamanho da struct, apenas um ponteiro (8 bytes em 64-bit) é copiado na chamada.

### Atividade 4 — Aritmética de Ponteiros em Arrays

**Conceito:** o nome de um array decai para um ponteiro para seu primeiro elemento. Somar `i` a esse ponteiro avança `i * sizeof(Produto)` bytes.

```c
void imprimir_produtos(Produto *ptr, int quantidade) 
{
    for (int i = 0; i < quantidade; i++) 
    {
        printf("[ID %d] R$ %.2f\n", (ptr + i)->id, (ptr + i)->preco);
    }
}
```

`ptr[i]` e `*(ptr + i)` são **idênticos** para o compilador; a exigência de usar `(ptr + i)->` torna explícita a aritmética de endereços por trás da notação de colchetes.

### Atividade 5 — Alocação Dinâmica de Memória

**Conceito:** `malloc` reserva um bloco contíguo no **heap** em tempo de execução; `free` o devolve ao sistema. O tamanho não precisa ser conhecido em tempo de compilação.

```c
int item;
scanf("%d", &n);

Produto *produtos = malloc((size_t)item * sizeof(Produto));

if (!produtos) 
{ 
    /* trata falha */ 
}

for (int i = 0; i < item; i++) 
{
    scanf("%d", &(produtos + i)->id);
    scanf("%f", &(produtos + i)->preco);
}

imprimir_produtos(produtos, item);
free(produtos); // obrigatório — evita memory leak
```

**Por que `(size_t)n`?** `malloc` recebe `size_t` (sem sinal). O cast evita o warning de conversão sinalizado por `-Wextra` e previne overflow em valores negativos de `n`.

**Verificação de `malloc`:** em sistemas com pouca memória, `malloc` pode retornar `NULL`. Ignorar essa verificação causa undefined behavior ao desreferenciar `NULL`.

## Arquitetura e Fluxo de Compilação 🏗️🧪

```
include/produto.h
    └── declara: struct Produto, aplicar_desconto_float, aplicar_desconto, imprimir_produtos
         ↑
src/produto.c          ─── compila para produto.o
    └── implementa as 3 funções acima
         ↑
main/main.c            ─── compila para main.o
    └── #include "produto.h"  (resolvido via -Iinclude)
    └── chama as funções em ordem das atividades 1→5

gcc linker: produto.o + main.o → ./programa
```

---

## Conceitos Abordados

| Conceito | Atividade | Arquivo |
|----------|-----------|---------|
| Ponteiro e desreferenciamento (`*`, `&`) | 1 | `main.c` |
| Passagem por referência com `float *` | 2 | `produto.c` |
| `struct` e operador seta (`->`) | 3 | `produto.c` |
| Aritmética de ponteiros `(ptr + i)->campo` | 4 | `produto.c` |
| `malloc`, `free`, verificação de `NULL` | 5 | `main.c` |
| Guards de inclusão (`#ifndef`/`#define`/`#endif`) | — | `produto.h` |
| Cast `(size_t)` para `malloc` | 5 | `main.c` |
