#include <stdio.h>
#include <stdlib.h>
#include "produto.h"

int main(void)
{
    /* ============================================================
     * ATIVIDADE 1 — Fundamentos de Ponteiros e Modificação Direta
     * ============================================================ */
    puts("=== Atividade 1: Ponteiro para float ===");

    float preco = 100.0f;
    float *ptr_preco = &preco;

    printf("Preço original: R$ %.2f\n", preco);
    *ptr_preco *= 1.10f;
    printf("Preço após aumento de 10%% (via ponteiro): R$ %.2f\n\n", preco);

    /* ============================================================
     * ATIVIDADE 2 — Passagem por Referência
     * aplicar_desconto_float() recebe float* e altera o valor original.
     * ============================================================ */
    puts("=== Atividade 2: Passagem por Referência ===");

    float preco2 = 200.0f;
    printf("Preço original: R$ %.2f\n", preco2);
    aplicar_desconto_float(&preco2, 15.0f);
    printf("Preço após desconto de 15%% (via ponteiro float): R$ %.2f\n\n", preco2);

    /* ============================================================
     * ATIVIDADE 3 — Ponteiros para Structs
     * aplicar_desconto() recebe Produto* e usa '->' para modificar preço.
     * ============================================================ */
    puts("=== Atividade 3: Ponteiros para Structs ===");

    Produto produto3 = {1, 300.0f};

    printf("Produto ID: %d | Preço original: R$ %.2f\n", produto3.id, produto3.preco);
    aplicar_desconto(&produto3, 20.0f);
    printf("Produto ID: %d | Preço após desconto de 20%%: R$ %.2f\n\n", produto3.id, produto3.preco);

    /* ============================================================
     * ATIVIDADE 4 — Aritmética de Ponteiros em Arrays
     * imprimir_produtos() usa (ptr + i)->campo, sem ptr[i].
     * ============================================================ */
    puts("=== Atividade 4: Aritmética de Ponteiros em Arrays ===");

    Produto estoque[3] = 
    {
        {1, 49.90f},
        {2, 89.99f},
        {3, 129.50f}
    };

    imprimir_produtos(estoque, 3);
    puts("");

    /* ============================================================
     * ATIVIDADE 5 — Alocação Dinâmica de Memória (malloc/free)
     * ============================================================ */
    puts("=== Atividade 5: Alocação Dinâmica (malloc/free) ===");

    int itens;

    printf("Quantos produtos deseja cadastrar? ");
    
    if (scanf("%d", &itens) != 1 || itens <= 0) 
    {
        fprintf(stderr, "Quantidade inválida.\n");
        return 1;
    }

    Produto *produtos = malloc((size_t)itens * sizeof(Produto));

    if (!produtos) 
    {
        fprintf(stderr, "Falha na alocação de memória.\n");
        return 1;
    }

    for (int i = 0; i < itens; i++) 
    {
        printf("\nProduto %d:\n", i + 1);
        printf("  ID: ");
        scanf("%d", &(produtos + i)->id);
        printf("  Preço: R$ ");
        scanf("%f", &(produtos + i)->preco);
    }

    puts("\nProdutos cadastrados:");
    imprimir_produtos(produtos, itens);

    free(produtos);
    puts("\nMemória liberada com sucesso.");

    return 0;
}
