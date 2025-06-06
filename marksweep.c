// Trabalho da Disciplina de Paradigmas de Programação
// Algoritmo Coletor de Lixo MarkSweep
// Alunas: Ana Clara, Beatriz e Maria Fernanda

#include <stdio.h>
#include <stdlib.h>

#define MAX_OBJETOS 100

// Definição de um objeto (estrutura)
typedef struct Objeto {
    int dado;               // Pode ser qualquer dado
    struct Objeto* ref1;    // Ponteiro para outro objeto (referência)
    struct Objeto* ref2;    // Outro ponteiro para outro objeto
    int marcado;            // Flag para saber se foi marcado
} Objeto;

// Banco de objetos, que simula a memória
Objeto* heap[MAX_OBJETOS];

// Função para criar um novo objeto
Objeto* criar_objeto(int dado, Objeto* ref1, Objeto* ref2) {
    Objeto* obj = (Objeto*) malloc(sizeof(Objeto));
    obj->dado = dado;
    obj->ref1 = ref1;
    obj->ref2 = ref2;
    obj->marcado = 0;
    return obj;
}

// Função para marcar objetos acessíveis a partir de um objeto raiz
void mark(Objeto* obj) {
    if (obj == NULL || obj->marcado) return;

    printf("Marcando objeto com dado: %d\n", obj->dado);
    obj->marcado = 1;  // Marca o objeto como acessível

    // Marca os objetos referenciados por este objeto
    mark(obj->ref1);
    mark(obj->ref2);
}

// Função para realizar a varredura e liberar objetos não marcados
void sweep() {
    for (int i = 0; i < MAX_OBJETOS; i++) {
        if (heap[i] != NULL) {
            if (heap[i]->marcado == 0) {
                printf("Liberando objeto com dado: %d\n", heap[i]->dado);
                free(heap[i]);
                heap[i] = NULL;
            } else {
                printf("Objeto com dado %d ainda está acessível.\n", heap[i]->dado);
                heap[i]->marcado = 0;
            }
        }
    }
}

// Função para realizar a coleta de lixo (Mark and Sweep)
void coleta_de_lixo(Objeto* raízes[], int quantidade_de_raizes) {
    printf("\nIniciando a coleta de lixo...\n");

    // Etapa de marcação
    printf("\n** Etapa de Marcação **\n");
    for (int i = 0; i < quantidade_de_raizes; i++) {
        mark(raízes[i]);
    }

    // Etapa de varredura
    printf("\n** Etapa de Varredura **\n");
    sweep();
}

int main() {
    // Criando alguns objetos
    Objeto* obj1 = criar_objeto(4, NULL, NULL);
    Objeto* obj2 = criar_objeto(3, obj1, NULL);
    Objeto* obj3 = criar_objeto(2, obj1, NULL);
    Objeto* obj4 = criar_objeto(1, obj3, NULL);

    // Colocando objetos no heap
    heap[0] = obj1;
    heap[1] = obj2;
    heap[2] = obj3;
    heap[3] = obj4;

    // Mostrar o estado da memória antes da coleta de lixo
    printf("\n** Estado inicial da memória **\n");
    for (int i = 0; i < MAX_OBJETOS; i++) {
        if (heap[i] != NULL) {
            printf("Objeto com dado %d na posição %d\n", heap[i]->dado, i);
        }
    }

    // Definir os objetos raiz (objetos que são acessíveis diretamente)
    Objeto* raízes[] = {obj1, obj4};

    // Chama a coleta de lixo
    coleta_de_lixo(raízes, 2);

    // Mostrar o estado da memória após a coleta de lixo
    printf("\n** Estado da memória após a coleta de lixo **\n");
    for (int i = 0; i < MAX_OBJETOS; i++) {
        if (heap[i] != NULL) {
            printf("Objeto com dado %d na posição %d\n", heap[i]->dado, i);
        }
    }

    return 0;
}