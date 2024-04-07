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
    return 0;
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
	
	// Desenvolva o código da função
	
    return 0.;
}

/*
 * B.2.b)
 * Determina área média por concelho
 */
float media_area(concelho *lista, int nc) {
	
	// Desenvolva o código da função
		
    return 0.;
}

/*
 * B.4.a)
 * Determina população total do conjunto de concelhos
 */
int total_pop(concelho *tab, int nc) {
	
	// Desenvolva o código da função
		
    return 0;
}

/*
 * B.2.c1)
 * Determina índice do concelho com maior área.
 */
int max_area(concelho *tab, int nc) {
	
	// Desenvolva o código da função
		
    return -1;
}

/*
 * Determina índice do concelho com maior população.
 */
int max_pop(concelho *tab, int nc) {
	
	// Desenvolva o código da função
		
    return 0;
}

/*
 * Determina índice do concelho com maior densidade.
 */
int max_densidade(concelho *tab, int nc) {
	
	// Desenvolva o código da função
		
    return -1;
}

/*
 * Determina índice do concelho com maior relação h/100m.
 */
int max_h100m(concelho *tab, int nc) {
	
	// Desenvolva o código da função
		
    return -1;
}

/*
 * B.3.a)
 * Copia tabela para tabela nova.
 */
concelho *copia_tabela(concelho *tab_in, int nc) {
	
	// Desenvolva o código da função
		
    return NULL;
}

void ordem_area(concelho *tab_ord, int nc) {
	
	// Desenvolva o código da função

}

void ordem_pop(concelho *tab_ord, int nc) {
	
	// Desenvolva o código da função

}

void ordem_h100m(concelho *tab_ord, int nc) {
	
	// Desenvolva o código da função

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


}