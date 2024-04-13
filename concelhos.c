/*
 *   concelhos.c
 *
 *   ISEP, 2019
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define MAX_LINHA (100)	  	// Comprimento maximo de uma linha
#define MAX_CONCELHOS (400)	// Numero maximo de concelhos

typedef struct {
    char  nome[80];
    int   homens;
    int   mulheres;
    float area;
} concelho;

/*
 * B.1
 * Leitura de ficheiro com nome em nomefich para vetor de concelhos em lista.
 * Retorna número de concelhos lidos.
 */
int ler_tabela(char *nomefich, concelho *tab) {
    FILE *ficheiro = fopen(nomefich, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro %s.\n", nomefich);
        return 0;
    }

    int num_concelhos = 0;
    char linha[MAX_LINHA];

    // Ler cada linha do arquivo
    while (fgets(linha, MAX_LINHA, ficheiro) != NULL) {
    
        char *token = strtok(linha, ",");
  
        
        strcpy(tab[num_concelhos].nome, token);
        token = strtok(NULL, ",");
        tab[num_concelhos].homens = atoi(token);

        token = strtok(NULL, ",");
        tab[num_concelhos].mulheres = atoi(token);

        token = strtok(NULL, ",");
        tab[num_concelhos].area = atof(token);

        // Incrementar o contador de concelhos
        num_concelhos++;
    }

    fclose(ficheiro);
    return num_concelhos;
}

/*
 * Apresenta informação sobre um concelho
 */
void lista_concelho(concelho *tab, int ic) {
    if ( ic<0 ) return;
    mbstate_t t;
    concelho c = tab[ic];
    const char *scopy = c.nome;
    memset(&t, '\0', sizeof (t));
    int n = mbsrtowcs(NULL, &scopy, strlen (scopy), &t);  // Comprimento do nome
    printf("%3d ", ic+1);
    printf("%s%*s ", c.nome, 28-n, "");
    printf("%9d ", c.homens);
    printf("%9d ", c.mulheres);
    printf("%9.2f ", c.area);
    printf("\n");
}

/*
 * Cabeçalho a usar nas listas e nos resumos.
 */
void cabecalho() {
    printf("Num      Concelho                   Homens  Mulheres   Área(km²) \n");
}

/*
 * Apresenta tabela completa.
 */
void lista_tabela(concelho *lista, int nc) {
    cabecalho();
    if ( ! lista ) return;
    for( int i=0 ; i<nc ; i++ ) 
	    lista_concelho(lista,i);
}

/*
 * Apresenta resumo de tabela.
 */
void resumo_tabela(concelho *tab, int nc) {
    const int linhas_resumo = 5;
    if ( ! tab ) return;
    if ( nc<2*linhas_resumo )	// Se tabela é pequena, 
	    lista_tabela(tab,nc);   // é listada na totalidade
    else {
        int i;
	    cabecalho();
        for( i=0 ; i<linhas_resumo ; i++ )       // Início da tabela
	        lista_concelho(tab,i);
        printf("    . . .\n");
        for( i=nc-linhas_resumo ; i<nc ; i++ )   // Fim da tabela
	        lista_concelho(tab,i);
    }
}

/*
 * B.2.a)
 * Determina área total do conjunto de concelhos
 */
float total_area(concelho *lista, int nc) {
    float area_total = 0.0;
    for (int i = 0; i < nc; i++) {
        area_total += lista[i].area;
    }
    return area_total;
}


/*
 * B.2.b)
 * Determina área média por concelho
 */
float media_area(concelho *lista, int nc) {
    if (nc == 0) return 0.0;
    float area_total = total_area(lista, nc);
    return area_total / nc;
}


/*
 * B.4.a)
 * Determina população total do conjunto de concelhos
 */
int total_pop(concelho *tab, int nc) {
    int pop_total = 0;
    for (int i = 0; i < nc; i++) {
        pop_total += tab[i].homens + tab[i].mulheres;
    }
    return pop_total;
}

/*
 * B.2.c1)
 * Determina índice do concelho com maior área.
 */
int max_area(concelho *tab, int nc) {
    if (nc == 0) return -1;
    int indice_max_area = 0;
    float max_area = tab[0].area;
    for (int i = 1; i < nc; i++) {
        if (tab[i].area > max_area) {
            max_area = tab[i].area;
            indice_max_area = i;
        }
    }
    return indice_max_area;
}


/*
 * Determina índice do concelho com maior população.
 */
int max_pop(concelho *tab, int nc) {
    if (nc == 0) return -1;
    int indice_max_pop = 0;
    int max_pop = tab[0].homens + tab[0].mulheres;
    for (int i = 1; i < nc; i++) {
        int pop = tab[i].homens + tab[i].mulheres;
        if (pop > max_pop) {
            max_pop = pop;
            indice_max_pop = i;
        }
    }
    return indice_max_pop;
}

/*
 * Determina índice do concelho com maior densidade.
 */
int max_densidade(concelho *tab, int nc) {
    if (nc == 0) return -1;
    int indice_max_densidade = 0;
    float max_densidade = (tab[0].homens + tab[0].mulheres) / tab[0].area;
    for (int i = 1; i < nc; i++) {
        float densidade = (tab[i].homens + tab[i].mulheres) / tab[i].area;
        if (densidade > max_densidade) {
            max_densidade = densidade;
            indice_max_densidade = i;
        }
    }
    return indice_max_densidade;
}


/*
 * Determina índice do concelho com maior relação h/100m.
 */
int max_h100m(concelho *tab, int nc) {
    if (nc == 0) return -1;
    int indice_max_h100m = 0;
    float max_h100m = (float)tab[0].homens / tab[0].mulheres * 100;
    for (int i = 1; i < nc; i++) {
        float h100m = (float)tab[i].homens / tab[i].mulheres * 100;
        if (h100m > max_h100m) {
            max_h100m = h100m;
            indice_max_h100m = i;
        }
    }
    return indice_max_h100m;
}


/*
 * B.3.a)
 * Copia tabela para tabela nova.
 */
concelho *copia_tabela(concelho *tab_in, int nc) {
    concelho *tab_out = malloc(nc * sizeof(concelho));
    if (tab_out == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    for (int i = 0; i < nc; i++) {
        strcpy(tab_out[i].nome, tab_in[i].nome);
        tab_out[i].homens = tab_in[i].homens;
        tab_out[i].mulheres = tab_in[i].mulheres;
        tab_out[i].area = tab_in[i].area;
    }
    return tab_out;
}


void ordem_area(concelho *tab_ord, int nc) {

    qsort(tab_ord, nc, sizeof(concelho), compara_area);
}

int compara_area(const void *a, const void *b) {
    const concelho *concelho_a = (const concelho *)a;
    const concelho *concelho_b = (const concelho *)b;

    if (concelho_a->area < concelho_b->area) return -1;
    if (concelho_a->area > concelho_b->area) return 1;
    return 0;
}


void ordem_pop(concelho *tab_ord, int nc) {

    qsort(tab_ord, nc, sizeof(concelho), compara_pop);
}

int compara_pop(const void *a, const void *b) {
    const concelho *concelho_a = (const concelho *)a;
    const concelho *concelho_b = (const concelho *)b;

    int pop_a = concelho_a->homens + concelho_a->mulheres;
    int pop_b = concelho_b->homens + concelho_b->mulheres;
    if (pop_a < pop_b) return -1;
    if (pop_a > pop_b) return 1;
    return 0;
}


void ordem_h100m(concelho *tab_ord, int nc) {

    qsort(tab_ord, nc, sizeof(concelho), compara_h100m);
}

int compara_h100m(const void *a, const void *b) {
    const concelho *concelho_a = (const concelho *)a;
    const concelho *concelho_b = (const concelho *)b;

    float h100m_a = (float)concelho_a->homens / concelho_a->mulheres * 100;
    float h100m_b = (float)concelho_b->homens / concelho_b->mulheres * 100;
    if (h100m_a < h100m_b) return -1;
    if (h100m_a > h100m_b) return 1;
    return 0;
}


int main() {
    setlocale(LC_CTYPE, "");

    concelho tabela1[MAX_CONCELHOS];

    int NConcelhos = ler_tabela("concelhos_utf8.csv",tabela1);

    lista_tabela(tabela1, NConcelhos);
    printf("\nResumo\n");
    resumo_tabela(tabela1, NConcelhos);

    printf("\nÁrea total: %f km²\n", total_area(tabela1,NConcelhos));

    printf("\nConcelho com maior densidade populacional\n");
    int cmaxd = max_densidade(tabela1,NConcelhos);   
    lista_concelho(tabela1,cmaxd);

    printf("\nConcelho com maior área\n");
    int cmaxa = max_area(tabela1,NConcelhos);
    lista_concelho(tabela1,cmaxa);

    printf("\nLista ordenada por área\n");
    concelho *tab_area = copia_tabela(tabela1,NConcelhos);
    ordem_area(tab_area,NConcelhos);
    resumo_tabela(tab_area, NConcelhos);
    free(tab_area);

    printf("\nLista ordenada por população\n");
    concelho *tab_pop = copia_tabela(tabela1,NConcelhos);
    ordem_pop(tab_pop,NConcelhos);
    resumo_tabela(tab_pop, NConcelhos);
    free(tab_pop);

    printf("\nLista ordenada por relação de género\n");
    concelho *tab_h100m = copia_tabela(tabela1,NConcelhos);
    ordem_h100m(tab_h100m,NConcelhos);
    resumo_tabela(tab_h100m, NConcelhos);
    free(tab_h100m);

setlocale(LC_CTYPE, "");

    concelho tabela1[MAX_CONCELHOS];

    int NConcelhos = ler_tabela("concelhos_utf8.csv", tabela1);


}