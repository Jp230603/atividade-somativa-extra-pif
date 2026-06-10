#include <stdio.h>
#include "produto.h"

void aplicar_desconto_float(float *preco, float percentual)
{
    *preco -= *preco * (percentual / 100.0f);
}

void aplicar_desconto(Produto *produto, float percentual)
{
    produto->preco -= produto->preco * (percentual / 100.0f);
}

void imprimir_produtos(Produto *ptr, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        printf(" \n\t [ID %d] Preço: R$ %.2f\n", (ptr + i)->id, (ptr + i)->preco);
    }
}