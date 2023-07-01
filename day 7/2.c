//TODO tem algum bug nisso o numero é alto de mais quando deveria ser 4473403
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAXIMO_NOME 64
#define QUANTIDADE_MAXIMA 16

typedef struct diretorio
{
    char nome[TAMANHO_MAXIMO_NOME];
    size_t tamanhoTotal;
    size_t tamanho_subdiretorios;
    int subdiretorios;
    struct diretorio *subdiretorio[QUANTIDADE_MAXIMA];
    struct diretorio *anterior;
} diretorio;

diretorio *criaDiretorio(diretorio *anterior, const char *nome);
diretorio *remoantaSistemaDeArquivos();
void printDiretorio(diretorio *dir, int nivel);
void printArvore(diretorio *root, int nivel);
void encontraTotalAte(diretorio *root, size_t ate, size_t *soma);
void encontraMenorAte(diretorio *root, size_t minimo, size_t *resultado);

int main(void)
{
    diretorio *root = remoantaSistemaDeArquivos();
    printArvore(root, 0);
    size_t resposta = 0;
    size_t minimo = 30000000 - (70000000 - root->tamanhoTotal);
    encontraTotalAte(root, minimo, &resposta);
    printf("Resposta: %zu\n", resposta);
}

diretorio *criaDiretorio(diretorio *anterior, const char *nome)
{
    diretorio *dir = malloc(sizeof(*dir));
        if (dir == NULL) return NULL;

    strncpy(dir->nome, nome, TAMANHO_MAXIMO_NOME);
    dir->tamanhoTotal = 0;
    dir->tamanho_subdiretorios = 0;
    dir->subdiretorios = 0;
    dir->anterior = anterior;
    return dir;
}

diretorio *remoantaSistemaDeArquivos()
{
    diretorio *root = NULL;
    diretorio *dirAtual = NULL;

    FILE *arquivo = fopen("input", "r");
    if (arquivo == NULL)
        exit(1);

    char buffer[64];
    while (fgets(buffer, sizeof(buffer), arquivo))
    {
        size_t comprimento = strlen(buffer);
        if (comprimento && buffer[comprimento - 1] == '\n')
            buffer[comprimento - 1] = 0;

        if (buffer[0] == '$')
        {
            char *p = strchr(buffer + 2, ' ');
            if (p == NULL)
                continue;

            *p = 0;
            char *cmd = buffer + 2;
            char *arg = p + 1;

            if (!strcmp(cmd, "ls"))
                continue;

            if (!strcmp(cmd, "cd"))
            {
                if (!strcmp(arg, ".."))
                {
                    if (!dirAtual)
                        continue;

                    if (dirAtual->anterior == NULL)
                    {
                        dirAtual->anterior = criaDiretorio(NULL, "?");
                        root = dirAtual->anterior;
                    }

                    if (dirAtual == root) root = dirAtual->anterior;

                    dirAtual->anterior->tamanhoTotal += dirAtual->tamanhoTotal;
                    dirAtual = dirAtual->anterior;
                } else 
                {
                    diretorio *novoDiretorio = criaDiretorio(dirAtual, arg);
                    if (!root)
                        root = novoDiretorio;
                    if (dirAtual)
                        dirAtual->subdiretorio[dirAtual->subdiretorios++] = novoDiretorio;
                    dirAtual = novoDiretorio;
                }
            }
        } else 
        {
            char *p = strchr(buffer, ' ');
            if (p == NULL) 
                continue;
            *p = 0;

            char *attr = buffer;

            if (!strcmp(attr, "dir")) 
                continue;

            if (!dirAtual) continue;

            size_t tamanhoArquivo = atoi(attr);
            dirAtual->tamanho_subdiretorios += tamanhoArquivo;
            dirAtual->tamanhoTotal += tamanhoArquivo;
        }
    } 

    while (dirAtual != root)
    {
        dirAtual->anterior->tamanhoTotal += dirAtual->tamanhoTotal;
        dirAtual = dirAtual->anterior;
    }
    fclose(arquivo);
    return root;
}

void printDiretorio(diretorio *dir, int nivel)
{
    for (int k = 0; k < nivel*2; k++) printf(" ");
    printf("- %s (tamanho %zu | total %zu)\n", dir->nome, dir->tamanho_subdiretorios, dir->tamanhoTotal);
}

void printArvore(diretorio *root, int nivel)
{
    if (nivel == 0) printDiretorio(root,nivel);
    for (int j = 0; j < root->subdiretorios; j++) {
        printDiretorio(root->subdiretorio[j], nivel+1);
        printArvore(root->subdiretorio[j], nivel+1);
    }
}

void encontraTotalAte(diretorio *root, size_t ate, size_t *soma)
{
    for (int j = 0; j < root->subdiretorios; j++) {
        size_t size = root->subdiretorio[j]->tamanhoTotal;
        if (size <= ate) *soma += size;
        encontraTotalAte(root->subdiretorio[j], ate, soma);
    }
}

void encontraMenorAte(diretorio *root, size_t minimo, size_t *resultado)
{
    for (int j = 0; j < root->subdiretorios; j++) {
        size_t size = root->subdiretorio[j]->tamanhoTotal;
        if (size >= minimo && (*resultado == 0 || *resultado > size))
            *resultado = size;
        encontraMenorAte(root->subdiretorio[j], minimo, resultado);
    }
}
