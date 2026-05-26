#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct No {
    char nome[50];
    struct No* esquerda;
    struct No* direita;
    char pista[100];
    bool pistaColetada;
} Comodo;

typedef struct PistasSalvas {
    char pista[100];
    struct PistasSalvas* proximo;
} PistasSalvas;

Comodo* criarComodo(char nome[], char pista[]) {
    Comodo* novo = (Comodo*)malloc(sizeof(Comodo));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o cômodo.\n");
        exit(1);
    }
    strcpy(novo->nome, nome); // copia a string para o campo nome
    strcpy(novo->pista, pista); // copia a string para o campo pista
    novo->pistaColetada = false; // inicializa o campo pistaColetada como false
    novo->esquerda = NULL; // cria um filho a esquerda do nó atual vazio
    novo->direita = NULL; // cria um filho a direita do nó atual vazio
    return novo;
}

void inserirComodo(Comodo** comodoNovo, char nome[], char pista[]) {
    if (*comodoNovo == NULL) { //
        *comodoNovo = criarComodo(nome, pista); // se não existir um nó, cria um novo nó
        return;
    }
    if (strcmp(nome, (*comodoNovo)->nome) < 0) { // compara o "valor" da string nome com o "valor" da string do nó atual, se for menor, vai para a esquerda
        inserirComodo(&(*comodoNovo)->esquerda, nome, pista);
    } else {
        inserirComodo(&(*comodoNovo)->direita, nome, pista);
    }
}

void irParaEsquerda(Comodo** comodoAtual) {
    if (*comodoAtual == NULL || (*comodoAtual)->esquerda == NULL) {
        printf("Não é possível ir para a esquerda.\n");
        return;
    }
    *comodoAtual = (*comodoAtual)->esquerda;
}

void irParaDireita(Comodo** comodoAtual) {
    if (*comodoAtual == NULL || (*comodoAtual)->direita == NULL) {
        printf("Não é possível ir para a direita.\n");
        return;
    }
    *comodoAtual = (*comodoAtual)->direita;
}

/* void voltar(Comodo** comodoAtual, Comodo* raiz) {
    if (*comodoAtual == raiz) {
        printf("Você já está no cômodo inicial.\n");
        return;
    }
    *comodoAtual = raiz;
} */

void exibirComodo(Comodo* comodoAtual) {
    if (comodoAtual == NULL) {
        printf("Cômodo não encontrado.\n");
        return;
    }
    printf("Você está no cômodo: %s\n", comodoAtual->nome);
}

void exibirPista(Comodo* comodoAtual) {
    if (comodoAtual == NULL) {
        printf("Cômodo não encontrado.\n");
        return;
    }
    printf("Pista: %s coletada\n", comodoAtual->pista);
}

void coletarPista(PistasSalvas** listaPistas, Comodo* comodoAtual) {
    if (comodoAtual->pistaColetada == true) {
        printf("Pista já coletada: %s\n", comodoAtual->pista);
        return;
    }
    PistasSalvas* novaPista = (PistasSalvas*)malloc(sizeof(PistasSalvas));
    if (novaPista == NULL) {
        printf("Erro ao alocar memória para a pista salva.\n");
        exit(1);
    }

    strcpy(novaPista->pista, comodoAtual->pista); // copia a pista do cômodo atual para a nova pista salva
    comodoAtual->pistaColetada = true; // marca a pista como coletada
    novaPista->proximo = *listaPistas;
    *listaPistas = novaPista;
    printf("Pista coletada: %s\n", novaPista->pista);
}

void exibirPistasSalvas(PistasSalvas* listaPistas) {
    printf("Pistas salvas:\n");
    PistasSalvas* pistaAtual = listaPistas;
    while (pistaAtual != NULL && pistaAtual->pista[0] != '\0') {
        printf("- %s\n", pistaAtual->pista);
        pistaAtual = pistaAtual->proximo;
    }
}


void preOrdem(Comodo* comodoAtual) {
    if (comodoAtual != NULL) {
        printf("%s ", comodoAtual->nome);
        preOrdem(comodoAtual->esquerda);
        preOrdem(comodoAtual->direita);
    }
}

void emOrdem(Comodo* comodoAtual) {
    if (comodoAtual != NULL) {
        emOrdem(comodoAtual->esquerda);
        printf("%s ", comodoAtual->nome);
        emOrdem(comodoAtual->direita);
    }
}

void posOrdem(Comodo* comodoAtual) {
    if (comodoAtual != NULL) {
        posOrdem(comodoAtual->esquerda);
        posOrdem(comodoAtual->direita);
        printf("%s ", comodoAtual->nome);
    }
}

void liberarPistasSalvas(PistasSalvas* listaPistas) {
    PistasSalvas* atual = listaPistas;
    while (atual != NULL) {
        PistasSalvas* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}
void liberarArvore(Comodo* comodoAtual) {
    if (comodoAtual != NULL) {
        liberarArvore(comodoAtual->esquerda);
        liberarArvore(comodoAtual->direita);
        free(comodoAtual);
    }
}

int main () {
    Comodo* raiz = NULL;
    int opcao;
    PistasSalvas* listaPistas = NULL;
    
    raiz = criarComodo("Hall de entrada", "Pista: O hall de entrada está limpo, sem sinais de luta.");
    inserirComodo(&raiz, "Cozinha", "Pista: A cozinha está limpa, mas há sinais de uma luta.");
    inserirComodo(&raiz, "Quarto", "Pista: O quarto está revirado, com uma janela quebrada.");
    inserirComodo(&raiz, "Sala de estar", "Pista: A sala de estar está desordenada, com objetos espalhados.");
    inserirComodo(&raiz, "Banheiro", "Pista: O banheiro está sujo, com água parada no chão.");
    inserirComodo(&raiz, "Jardim", "Pista: O jardim está em desordem, com folhas espalhadas por todo o lugar.");

    Comodo* atual = raiz;
    coletarPista(&listaPistas, atual);

    printf(" ### BEM VINDO AO JOGO DE DETETIVE ### \n");
    printf("\n ---------- INICIANDO JOGO ---------- \n");
    exibirComodo(atual);

    printf("Para onde você deseja ir? (1 - Esquerda, 2 - Direita, 3 - Exibir pista do cômodo, 0 - Sair): ");
    scanf("%d", &opcao);
    while (opcao != 0) {
        switch (opcao) {
            case 1:
                irParaEsquerda(&atual);
                coletarPista(&listaPistas, atual);
                break;
            case 2:
                irParaDireita(&atual);
                coletarPista(&listaPistas, atual);
                break;
            case 3:
                exibirPista(atual);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        exibirComodo(atual);
        printf("Para onde você deseja ir? (1 - Esquerda, 2 - Direita, 3 - Exibir pista do cômodo, 0 - Sair): ");
        scanf("%d", &opcao);
    }

    if (opcao == 0) {
        exibirPistasSalvas(listaPistas);
        printf("Saindo do jogo. Obrigado por jogar!\n");
    }


    printf("Percurso em pré-ordem: ");
    preOrdem(raiz);
    printf("\n");


    /*printf("Percurso em ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Percurso em pós-ordem: ");
    posOrdem(raiz);
    printf("\n");*/

    liberarArvore(raiz);
    liberarPistasSalvas(listaPistas);
    return 0;
}