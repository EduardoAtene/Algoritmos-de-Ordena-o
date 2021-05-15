#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_VETOR_MIL 1000
#define TAM_VETOR_10K 10000
#define TAM_VETOR_100K 100000
#define TAM_VETOR_200K 200000
#define TAM_VETOR_300K 300000
#define TAM_VETOR_400K 400000
#define TAM_VETOR_500K 500000

struct temp_segundos{
	double s_cresc[2];	
	double s_decres[2];	
	double s_embar[2];
};

struct tipos{
	int crescente[2];
	int decrescente[2];
	int embaralhado[2];
	struct temp_segundos t_segu;
};

typedef struct tipos tipos_A;

struct tipos_ord{
	tipos_A bubble;
	tipos_A select;
	tipos_A marge;
	tipos_A quick;
	tipos_A insertion;
};

typedef struct tipos_ord tipo;

struct temp{
	tipo temp_mil;
	tipo temp_10k;
	tipo temp_100k;
	tipo temp_200k;	
	tipo temp_300k;
	tipo temp_400k;
	tipo temp_500k;		
};

typedef struct temp tempo;

// REALIZAR TROCA DE VALORES

int troca_valores(int *vetor,int i,int x){
	/*Esta função irá trocar os valores do vetor.
		Onde o vetor[i] será maior que o vetor[i+1]
		Sendo assim, realizará a troca de forma crescente.
	*/
	int aux;
	aux = vetor[i];
	vetor[i] = vetor[x];
	vetor[x] = aux;
}

// ALGORITMO FISHER_YATES | EMBARALHADOR

int fisher_yates(int *vetor, int n){
	int final = n-1,comeco=0,sortear,num_sorteado;

	// Inicializador dos números aleatórios.
	srand(time(NULL));
	//printf("\n FISHER_YATER ATIVADO \n");
	for(final;comeco<final;final--){
		sortear = final;
		num_sorteado = rand() % sortear;
		troca_valores(vetor,final,num_sorteado);
		
	}
	//printf("\n FISHER_YATERS FINALIZADO \n");
}
	

//ORDEÇÃO POR BOLHA
int bubble(int *vetor, int n){
	int i,fim=n,continua;
	do{
		continua = 0;	
		for(i=0;i<=fim-1;i++){
			if (vetor[i]>vetor[i+1]){
				troca_valores(vetor,i,i+1);
				continua = i;
			}
		}
		fim -= 1;
	}while(continua!=0);
	  
}

//ORDENEÇAÕ POR SELEÇÃO


int selection(int *vetor, int n){
		
	int menor_valor,i,j;
	for(i=0;i<(n-1);i++){
		menor_valor = i;
		for(j=(i+1);j<=n;j++){
			if(vetor[menor_valor]>vetor[j])
				menor_valor = j;
		}
		troca_valores(vetor,i,menor_valor);
	}
}

//insertion
void insertionSort(int arr[], int n){
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Marge	
void intercala(int v[], int p, int q, int r,int tamanho)
{
	int w[tamanho], i, j, k;
	i = p;
	j = q;
	k = 0;
	while (i < q && j < r) {
		if (v[i] < v[j]) {
			w[k] = v[i];
			i++;
		}
		else {
			w[k] = v[j];
			j++;
		}
		k++;
	}
	while (i < q) {
		w[k] = v[i];
		i++;
		k++;
	}
	while (j < r) {
		w[k] = v[j];
		j++;
		k++;
	}
	for (i = p; i < r; i++)
		v[i] = w[i-p];
}

void mergesort(int v[], int p, int r,int tamanho)
	{
	int q;
	if (p < r - 1) {
		q = (p + r) / 2;
		mergesort(v, p, q,tamanho);
		mergesort(v, q, r,tamanho);
		intercala(v, p, q, r,tamanho);
		}
	}


// QuickSort

void quicksort(int *a, int esquerda, int direita) {
    int i, j, x, y;
     
    i = esquerda;
    j = direita;
    x = a[(esquerda + direita) / 2];
     
    while(i <= j) {
        while(a[i] < x && i < direita) {
            i++;
        }
        while(a[j] > x && j > esquerda) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > esquerda) {
        quicksort(a, esquerda, j);
    }
    if(i < direita) {
        quicksort(a, i, direita);
    }
}


// TRANSFORMAR EM SEGUNDOS EM MINUTOS

int trans_minutos(double t, int *vet_tempo){
	int minutos,segundos;
	vet_tempo[0] = t/60;
	vet_tempo[1] = (int)t %60;

}



// ATIVAR ALGORITMOS DE ORDENAÇÃO

void ativar_bubble(int *vetor,int tamanho,int *min_segu,double *t_segundos){

//	fisher_yates(vetor,tamanho);
	double t0,t1;	
	t0 = (double) clock() / CLOCKS_PER_SEC;
	bubble(vetor,tamanho);
	t1 = (double) clock() / CLOCKS_PER_SEC;
	t_segundos[0] = (t1-t0);
	trans_minutos(t_segundos[0],min_segu);

	/*
	printf("\n  %50d",tamanho);		
	printf("\n      TEMPOOOOO    \n");	
	printf("Tempo: %f",(t1-t0));
	printf("\n Minutos: %d Segundos: %d \n",min_segu[0],min_segu[1]);
	*/
}

void ativar_insert(int *vetor,int tamanho,int *min_segu,double *t_segundos){

//	fisher_yates(vetor,tamanho);
	double t0,t1;
	t0 = (double) clock() / CLOCKS_PER_SEC;
	insertionSort(vetor,tamanho);
	t1 = (double) clock() / CLOCKS_PER_SEC;
	t_segundos[0] = (t1-t0);
	trans_minutos(t_segundos[0],min_segu);

	/*
	printf("\n  %50d",tamanho);		
	printf("\n      TEMPOOOOO    \n");	
	printf("Tempo: %f",(t1-t0));
	printf("\n Minutos: %d Segundos: %d \n",min_segu[0],min_segu[1]);
	*/
}


void ativa_select(int *vetor,int tamanho,int *min_segu,double *t_segundos){
	double t2,t3;	
	t2 = (double) clock() / CLOCKS_PER_SEC;
	selection(vetor,tamanho);
	t3 = (double) clock() / CLOCKS_PER_SEC;
	t_segundos[0] = (t3-t2);	 	

	trans_minutos(t_segundos[0],min_segu);

	/*
	printf("\n   %50d",tamanho);	
	printf("\n      TEMPOOOOO    \n");	
	printf("Tempo: %f",(t1-t0));
	printf("\n");
	printf("\n Minutos: %d Segundos: %d \n",min_segu[0],min_segu[1]);
	*/
}

void ativar_marge(int *vetor,int tamanho,int *min_segu,double *t_segundos){
	//fisher_yates(vetor,tamanho);
	double t0,t1;	
	t0 = (double) clock() / CLOCKS_PER_SEC;
	
	mergesort(vetor,0,tamanho,tamanho);
	
	t1 = (double) clock() / CLOCKS_PER_SEC;
	t_segundos[0] = (t1-t0);	
	trans_minutos(t_segundos[0],min_segu);
	
	/*
	printf("\n   %50d",tamanho);	
	printf("\n      TEMPOOOOO    \n");	
	printf("Tempo: %f",((t1-t0)));
	printf("\n");
	printf("\n Minutos: %d Segundos: %d \n",min_segu[0],min_segu[1]);
	*/
}

void ativar_quick(int *vetor,int tamanho,int *min_segu,double *t_segundos){
	//fisher_yates(vetor,tamanho);
	double t0,t1;	
	t0 = (double) clock() / CLOCKS_PER_SEC;
	quicksort(vetor,0,tamanho);
	t1 = (double) clock() / CLOCKS_PER_SEC;
	t_segundos[0] = (t1-t0);	
	trans_minutos(t_segundos[0],min_segu);
	
	
	/*
	printf("\n    %50d",tamanho);
	printf("\n      TEMPOOOOO    \n");	
	printf("Tempo: %f",(t1-t0));
	printf("\n");
	printf("\n Minutos: %d Segundos: %d \n",min_segu[0],min_segu[1]);
	*/
}



void imprimir(int *vetor, int tamanho){
	int i;
	for(i=0;i<=tamanho;i++){
		printf("%d     ",vetor[i]);
		if(i%5 == 0)
			printf("\n");

	}
}

void gerar_valores_vet_ord_cres(int *vetor,int tamanho){
	int i,aux=0;
	for(i=0;i<=tamanho;i++){
		vetor[i] = i;
	}
}


void gerar_valores_vet_ord_decre(int *vetor,int tamanho){
	int i,aux=0;
	for(i=tamanho;i>=0;i--){
		vetor[i] = aux;
	}
}

void gerar_vetores(int *vet,int tamanho){
	/*vet.crescente = (int*) malloc(tamanho*sizeof(int));
	vet.decrescente = (int*) malloc(tamanho*sizeof(int));
	vet.embaralhado = (int*) malloc(tamanho*sizeof(int));
	*/
	
	gerar_valores_vet_ord_cres(vet,tamanho);
	gerar_valores_vet_ord_decre(vet,tamanho);
	
	//criar vet
	gerar_valores_vet_ord_cres(vet,tamanho);
	//embaralhar vet
	fisher_yates(vet,tamanho);	
}

void desalocar(int *vetor){
	free(vetor);
}

void verefic_aloc(int *vetor){
	if(vetor==NULL){
		printf("Erro: Sem Memoria!\n");
		exit(1); // Termina o programa
		}
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(void) {
	int *vetor_mil_c = (int*) malloc(TAM_VETOR_MIL*sizeof(int));
	int *vetor_mil_d = (int*) malloc(TAM_VETOR_MIL*sizeof(int));
	int *vetor_mil_e = (int*) malloc(TAM_VETOR_MIL*sizeof(int));
	
	int *vetor_10k_c = (int*) malloc(TAM_VETOR_10K*sizeof(int));
	int *vetor_10k_d = (int*) malloc(TAM_VETOR_10K*sizeof(int));
	int *vetor_10k_e = (int*) malloc(TAM_VETOR_10K*sizeof(int));	
	
	int *vetor_100k_c = (int*) malloc(TAM_VETOR_100K*sizeof(int));
	int *vetor_100k_d = (int*) malloc(TAM_VETOR_100K*sizeof(int));
	int *vetor_100k_e = (int*) malloc(TAM_VETOR_100K*sizeof(int));				
	
	int *vetor_200k_c = (int*) malloc(TAM_VETOR_200K*sizeof(int));
	int *vetor_200k_d = (int*) malloc(TAM_VETOR_200K*sizeof(int));
	int *vetor_200k_e = (int*) malloc(TAM_VETOR_200K*sizeof(int));
	
	int *vetor_300k_c = (int*) malloc(TAM_VETOR_300K*sizeof(int));
	int *vetor_300k_d = (int*) malloc(TAM_VETOR_300K*sizeof(int));
	int *vetor_300k_e = (int*) malloc(TAM_VETOR_300K*sizeof(int));	
	
	int *vetor_400k_c = (int*) malloc(TAM_VETOR_400K*sizeof(int));
	int *vetor_400k_d = (int*) malloc(TAM_VETOR_400K*sizeof(int));
	int *vetor_400k_e = (int*) malloc(TAM_VETOR_400K*sizeof(int));	
	
	int *vetor_500k_c = (int*) malloc(TAM_VETOR_500K*sizeof(int));
	int *vetor_500k_d = (int*) malloc(TAM_VETOR_500K*sizeof(int));
	int *vetor_500k_e = (int*) malloc(TAM_VETOR_500K*sizeof(int));	
						
	tempo tempos;
		
	// VERIFICAR ALOCAÇÃO
	
	verefic_aloc(vetor_mil_c);	
	verefic_aloc(vetor_mil_d);	
	verefic_aloc(vetor_mil_e);	
	
	verefic_aloc(vetor_10k_c);	
	verefic_aloc(vetor_10k_d);	
	verefic_aloc(vetor_10k_e);	
	
	verefic_aloc(vetor_100k_c);	
	verefic_aloc(vetor_100k_d);	
	verefic_aloc(vetor_100k_e);	

	verefic_aloc(vetor_200k_c);	
	verefic_aloc(vetor_200k_d);	
	verefic_aloc(vetor_200k_e);	

	verefic_aloc(vetor_300k_c);	
	verefic_aloc(vetor_300k_d);	
	verefic_aloc(vetor_300k_e);	

	verefic_aloc(vetor_400k_c);	
	verefic_aloc(vetor_400k_d);	
	verefic_aloc(vetor_400k_e);	

	verefic_aloc(vetor_500k_c);	
	verefic_aloc(vetor_500k_d);	
	verefic_aloc(vetor_500k_e);	
	
	printf("ORDENANDO...");		
	
	
	gerar_valores_vet_ord_cres(vetor_mil_c,TAM_VETOR_MIL);
	gerar_valores_vet_ord_decre(vetor_mil_d,TAM_VETOR_MIL);
	gerar_valores_vet_ord_cres(vetor_mil_e,TAM_VETOR_MIL);
	fisher_yates(vetor_mil_e,TAM_VETOR_MIL);
	
	gerar_valores_vet_ord_cres(vetor_10k_c,TAM_VETOR_10K);
	gerar_valores_vet_ord_decre(vetor_10k_d,TAM_VETOR_10K);
	gerar_valores_vet_ord_cres(vetor_10k_e,TAM_VETOR_10K);
	fisher_yates(vetor_10k_e,TAM_VETOR_10K);
	
	gerar_valores_vet_ord_cres(vetor_100k_c,TAM_VETOR_100K);
	gerar_valores_vet_ord_decre(vetor_100k_d,TAM_VETOR_100K);
	gerar_valores_vet_ord_cres(vetor_100k_e,TAM_VETOR_100K);
	fisher_yates(vetor_100k_e,TAM_VETOR_100K);

	gerar_valores_vet_ord_cres(vetor_200k_c,TAM_VETOR_200K);
	gerar_valores_vet_ord_decre(vetor_200k_d,TAM_VETOR_200K);
	gerar_valores_vet_ord_cres(vetor_200k_e,TAM_VETOR_200K);
	fisher_yates(vetor_200k_e,TAM_VETOR_200K);
	
	gerar_valores_vet_ord_cres(vetor_300k_c,TAM_VETOR_300K);
	gerar_valores_vet_ord_decre(vetor_300k_d,TAM_VETOR_300K);
	gerar_valores_vet_ord_cres(vetor_300k_e,TAM_VETOR_300K);
	fisher_yates(vetor_300k_e,TAM_VETOR_300K);
	
	gerar_valores_vet_ord_cres(vetor_400k_c,TAM_VETOR_400K);
	gerar_valores_vet_ord_decre(vetor_400k_d,TAM_VETOR_400K);
	gerar_valores_vet_ord_cres(vetor_400k_e,TAM_VETOR_400K);
	fisher_yates(vetor_400k_e,TAM_VETOR_400K);

	gerar_valores_vet_ord_cres(vetor_500k_c,TAM_VETOR_500K);
	gerar_valores_vet_ord_decre(vetor_500k_d,TAM_VETOR_500K);
	gerar_valores_vet_ord_cres(vetor_500k_e,TAM_VETOR_500K);
	fisher_yates(vetor_500k_e,TAM_VETOR_500K);	


	
	ativar_bubble(vetor_mil_c, TAM_VETOR_MIL, tempos.temp_mil.bubble.crescente,tempos.temp_mil.bubble.t_segu.s_cresc);
	ativar_bubble(vetor_10k_c,TAM_VETOR_10K,tempos.temp_10k.bubble.crescente,tempos.temp_10k.bubble.t_segu.s_cresc);
	ativar_bubble(vetor_100k_c,TAM_VETOR_100K,tempos.temp_100k.bubble.crescente,tempos.temp_100k.bubble.t_segu.s_cresc);
	ativar_bubble(vetor_200k_c,TAM_VETOR_200K,tempos.temp_200k.bubble.crescente,tempos.temp_200k.bubble.t_segu.s_cresc);
	ativar_bubble(vetor_300k_c,TAM_VETOR_300K,tempos.temp_300k.bubble.crescente,tempos.temp_300k.bubble.t_segu.s_cresc);
	ativar_bubble(vetor_400k_c,TAM_VETOR_400K,tempos.temp_400k.bubble.crescente,tempos.temp_400k.bubble.t_segu.s_cresc);
	ativar_bubble(vetor_500k_c,TAM_VETOR_500K,tempos.temp_500k.bubble.crescente,tempos.temp_500k.bubble.t_segu.s_cresc);

	ativar_bubble(vetor_mil_d,TAM_VETOR_MIL,tempos.temp_mil.bubble.decrescente,tempos.temp_mil.bubble.t_segu.s_decres);
	ativar_bubble(vetor_10k_d,TAM_VETOR_10K,tempos.temp_10k.bubble.decrescente,tempos.temp_10k.bubble.t_segu.s_decres);
	ativar_bubble(vetor_100k_d,TAM_VETOR_100K,tempos.temp_100k.bubble.decrescente,tempos.temp_100k.bubble.t_segu.s_decres);
	ativar_bubble(vetor_200k_d,TAM_VETOR_200K,tempos.temp_200k.bubble.decrescente,tempos.temp_200k.bubble.t_segu.s_decres);
	ativar_bubble(vetor_300k_d,TAM_VETOR_300K,tempos.temp_300k.bubble.decrescente,tempos.temp_300k.bubble.t_segu.s_decres);
	ativar_bubble(vetor_400k_d,TAM_VETOR_400K,tempos.temp_400k.bubble.decrescente,tempos.temp_400k.bubble.t_segu.s_decres);
	ativar_bubble(vetor_500k_d,TAM_VETOR_500K,tempos.temp_500k.bubble.decrescente,tempos.temp_500k.bubble.t_segu.s_decres);

	
	ativar_bubble(vetor_mil_e,TAM_VETOR_MIL,tempos.temp_mil.bubble.embaralhado,tempos.temp_mil.bubble.t_segu.s_embar);
	ativar_bubble(vetor_10k_e,TAM_VETOR_10K,tempos.temp_10k.bubble.embaralhado,tempos.temp_10k.bubble.t_segu.s_embar);
	ativar_bubble(vetor_100k_e,TAM_VETOR_100K,tempos.temp_100k.bubble.embaralhado,tempos.temp_100k.bubble.t_segu.s_embar);
	ativar_bubble(vetor_200k_e,TAM_VETOR_200K,tempos.temp_200k.bubble.embaralhado,tempos.temp_200k.bubble.t_segu.s_embar);
	ativar_bubble(vetor_300k_e,TAM_VETOR_300K,tempos.temp_300k.bubble.embaralhado,tempos.temp_300k.bubble.t_segu.s_embar);
	ativar_bubble(vetor_400k_e,TAM_VETOR_400K,tempos.temp_400k.bubble.embaralhado,tempos.temp_400k.bubble.t_segu.s_embar);
	ativar_bubble(vetor_500k_e,TAM_VETOR_500K,tempos.temp_500k.bubble.embaralhado,tempos.temp_500k.bubble.t_segu.s_embar);
	
////////////////////////////////////////////////////////////////////////////////////////////


	gerar_valores_vet_ord_cres(vetor_mil_c,TAM_VETOR_MIL);
	gerar_valores_vet_ord_decre(vetor_mil_d,TAM_VETOR_MIL);
	gerar_valores_vet_ord_cres(vetor_mil_e,TAM_VETOR_MIL);
	fisher_yates(vetor_mil_e,TAM_VETOR_MIL);
	
	gerar_valores_vet_ord_cres(vetor_10k_c,TAM_VETOR_10K);
	gerar_valores_vet_ord_decre(vetor_10k_d,TAM_VETOR_10K);
	gerar_valores_vet_ord_cres(vetor_10k_e,TAM_VETOR_10K);
	fisher_yates(vetor_10k_e,TAM_VETOR_10K);
	
	gerar_valores_vet_ord_cres(vetor_100k_c,TAM_VETOR_100K);
	gerar_valores_vet_ord_decre(vetor_100k_d,TAM_VETOR_100K);
	gerar_valores_vet_ord_cres(vetor_100k_e,TAM_VETOR_100K);
	fisher_yates(vetor_100k_e,TAM_VETOR_100K);

	gerar_valores_vet_ord_cres(vetor_200k_c,TAM_VETOR_200K);
	gerar_valores_vet_ord_decre(vetor_200k_d,TAM_VETOR_200K);
	gerar_valores_vet_ord_cres(vetor_200k_e,TAM_VETOR_200K);
	fisher_yates(vetor_200k_e,TAM_VETOR_200K);
	
	gerar_valores_vet_ord_cres(vetor_300k_c,TAM_VETOR_300K);
	gerar_valores_vet_ord_decre(vetor_300k_d,TAM_VETOR_300K);
	gerar_valores_vet_ord_cres(vetor_300k_e,TAM_VETOR_300K);
	fisher_yates(vetor_300k_e,TAM_VETOR_300K);
	
	gerar_valores_vet_ord_cres(vetor_400k_c,TAM_VETOR_400K);
	gerar_valores_vet_ord_decre(vetor_400k_d,TAM_VETOR_400K);
	gerar_valores_vet_ord_cres(vetor_400k_e,TAM_VETOR_400K);
	fisher_yates(vetor_400k_e,TAM_VETOR_400K);

	gerar_valores_vet_ord_cres(vetor_500k_c,TAM_VETOR_500K);
	gerar_valores_vet_ord_decre(vetor_500k_d,TAM_VETOR_500K);
	gerar_valores_vet_ord_cres(vetor_500k_e,TAM_VETOR_500K);
	fisher_yates(vetor_500k_e,TAM_VETOR_500K);	

	
	ativar_insert(vetor_mil_c, TAM_VETOR_MIL, tempos.temp_mil.insertion.crescente,tempos.temp_mil.insertion.t_segu.s_cresc);
	ativar_insert(vetor_10k_c,TAM_VETOR_10K,tempos.temp_10k.insertion.crescente,tempos.temp_10k.insertion.t_segu.s_cresc);
	ativar_insert(vetor_100k_c,TAM_VETOR_100K,tempos.temp_100k.insertion.crescente,tempos.temp_100k.insertion.t_segu.s_cresc);
	ativar_insert(vetor_200k_c,TAM_VETOR_200K,tempos.temp_200k.insertion.crescente,tempos.temp_200k.insertion.t_segu.s_cresc);
	ativar_insert(vetor_300k_c,TAM_VETOR_300K,tempos.temp_300k.insertion.crescente,tempos.temp_300k.insertion.t_segu.s_cresc);
	ativar_insert(vetor_400k_c,TAM_VETOR_400K,tempos.temp_400k.insertion.crescente,tempos.temp_400k.insertion.t_segu.s_cresc);
	ativar_insert(vetor_500k_c,TAM_VETOR_500K,tempos.temp_500k.insertion.crescente,tempos.temp_500k.insertion.t_segu.s_cresc);

	ativar_insert(vetor_mil_d,TAM_VETOR_MIL,tempos.temp_mil.insertion.decrescente,tempos.temp_mil.insertion.t_segu.s_decres);
	ativar_insert(vetor_10k_d,TAM_VETOR_10K,tempos.temp_10k.insertion.decrescente,tempos.temp_10k.insertion.t_segu.s_decres);
	ativar_insert(vetor_100k_d,TAM_VETOR_100K,tempos.temp_100k.insertion.decrescente,tempos.temp_100k.insertion.t_segu.s_decres);
	ativar_insert(vetor_200k_d,TAM_VETOR_200K,tempos.temp_200k.insertion.decrescente,tempos.temp_200k.insertion.t_segu.s_decres);
	ativar_insert(vetor_300k_d,TAM_VETOR_300K,tempos.temp_300k.insertion.decrescente,tempos.temp_300k.insertion.t_segu.s_decres);
	ativar_insert(vetor_400k_d,TAM_VETOR_400K,tempos.temp_400k.insertion.decrescente,tempos.temp_400k.insertion.t_segu.s_decres);
	ativar_insert(vetor_500k_d,TAM_VETOR_500K,tempos.temp_500k.insertion.decrescente,tempos.temp_500k.insertion.t_segu.s_decres);

	
	ativar_insert(vetor_mil_e,TAM_VETOR_MIL,tempos.temp_mil.insertion.embaralhado,tempos.temp_mil.insertion.t_segu.s_embar);
	ativar_insert(vetor_10k_e,TAM_VETOR_10K,tempos.temp_10k.insertion.embaralhado,tempos.temp_10k.insertion.t_segu.s_embar);
	ativar_insert(vetor_100k_e,TAM_VETOR_100K,tempos.temp_100k.insertion.embaralhado,tempos.temp_100k.insertion.t_segu.s_embar);
	ativar_insert(vetor_200k_e,TAM_VETOR_200K,tempos.temp_200k.insertion.embaralhado,tempos.temp_200k.insertion.t_segu.s_embar);
	ativar_insert(vetor_300k_e,TAM_VETOR_300K,tempos.temp_300k.insertion.embaralhado,tempos.temp_300k.insertion.t_segu.s_embar);
	ativar_insert(vetor_400k_e,TAM_VETOR_400K,tempos.temp_400k.insertion.embaralhado,tempos.temp_400k.insertion.t_segu.s_embar);
	ativar_insert(vetor_500k_e,TAM_VETOR_500K,tempos.temp_500k.insertion.embaralhado,tempos.temp_500k.insertion.t_segu.s_embar);
	
	
////////////////////////////////////////////////////////////////////////////////////////////

	gerar_valores_vet_ord_cres(vetor_mil_c,TAM_VETOR_MIL);
	gerar_valores_vet_ord_decre(vetor_mil_d,TAM_VETOR_MIL);
	gerar_valores_vet_ord_cres(vetor_mil_e,TAM_VETOR_MIL);
	fisher_yates(vetor_mil_e,TAM_VETOR_MIL);
	
	gerar_valores_vet_ord_cres(vetor_10k_c,TAM_VETOR_10K);
	gerar_valores_vet_ord_decre(vetor_10k_d,TAM_VETOR_10K);
	gerar_valores_vet_ord_cres(vetor_10k_e,TAM_VETOR_10K);
	fisher_yates(vetor_10k_e,TAM_VETOR_10K);
	
	gerar_valores_vet_ord_cres(vetor_100k_c,TAM_VETOR_100K);
	gerar_valores_vet_ord_decre(vetor_100k_d,TAM_VETOR_100K);
	gerar_valores_vet_ord_cres(vetor_100k_e,TAM_VETOR_100K);
	fisher_yates(vetor_100k_e,TAM_VETOR_100K);

	gerar_valores_vet_ord_cres(vetor_200k_c,TAM_VETOR_200K);
	gerar_valores_vet_ord_decre(vetor_200k_d,TAM_VETOR_200K);
	gerar_valores_vet_ord_cres(vetor_200k_e,TAM_VETOR_200K);
	fisher_yates(vetor_200k_e,TAM_VETOR_200K);

	gerar_valores_vet_ord_cres(vetor_300k_c,TAM_VETOR_300K);
	gerar_valores_vet_ord_decre(vetor_300k_d,TAM_VETOR_300K);
	gerar_valores_vet_ord_cres(vetor_300k_e,TAM_VETOR_300K);
	fisher_yates(vetor_300k_e,TAM_VETOR_300K);
	
	gerar_valores_vet_ord_cres(vetor_400k_c,TAM_VETOR_400K);
	gerar_valores_vet_ord_decre(vetor_400k_d,TAM_VETOR_400K);
	gerar_valores_vet_ord_cres(vetor_400k_e,TAM_VETOR_400K);
	fisher_yates(vetor_400k_e,TAM_VETOR_400K);

	gerar_valores_vet_ord_cres(vetor_500k_c,TAM_VETOR_500K);
	gerar_valores_vet_ord_decre(vetor_500k_d,TAM_VETOR_500K);
	gerar_valores_vet_ord_cres(vetor_500k_e,TAM_VETOR_500K);
	fisher_yates(vetor_500k_e,TAM_VETOR_500K);
	
	ativa_select(vetor_mil_c,TAM_VETOR_MIL,tempos.temp_mil.select.crescente,tempos.temp_mil.select.t_segu.s_cresc);
	ativa_select(vetor_10k_c,TAM_VETOR_10K,tempos.temp_10k.select.crescente,tempos.temp_10k.select.t_segu.s_cresc);
	ativa_select(vetor_100k_c,TAM_VETOR_100K,tempos.temp_100k.select.crescente,tempos.temp_100k.select.t_segu.s_cresc);
	ativa_select(vetor_200k_c,TAM_VETOR_200K,tempos.temp_200k.select.crescente,tempos.temp_200k.select.t_segu.s_cresc);
	ativa_select(vetor_300k_c,TAM_VETOR_300K,tempos.temp_300k.select.crescente,tempos.temp_300k.select.t_segu.s_cresc);
	ativa_select(vetor_400k_c,TAM_VETOR_400K,tempos.temp_400k.select.crescente,tempos.temp_400k.select.t_segu.s_cresc);
	ativa_select(vetor_500k_c,TAM_VETOR_500K,tempos.temp_500k.select.crescente,tempos.temp_500k.select.t_segu.s_cresc);

	ativa_select(vetor_mil_d,TAM_VETOR_MIL,tempos.temp_mil.select.decrescente,tempos.temp_mil.select.t_segu.s_decres);
	ativa_select(vetor_10k_d,TAM_VETOR_10K,tempos.temp_10k.select.decrescente,tempos.temp_10k.select.t_segu.s_decres);
	ativa_select(vetor_100k_d,TAM_VETOR_100K,tempos.temp_100k.select.decrescente,tempos.temp_100k.select.t_segu.s_decres);
	ativa_select(vetor_200k_d,TAM_VETOR_200K,tempos.temp_200k.select.decrescente,tempos.temp_200k.select.t_segu.s_decres);
	ativa_select(vetor_300k_d,TAM_VETOR_300K,tempos.temp_300k.select.decrescente,tempos.temp_300k.select.t_segu.s_decres);
	ativa_select(vetor_400k_d,TAM_VETOR_400K,tempos.temp_400k.select.decrescente,tempos.temp_400k.select.t_segu.s_decres);
	ativa_select(vetor_500k_d,TAM_VETOR_500K,tempos.temp_500k.select.decrescente,tempos.temp_500k.select.t_segu.s_decres);

	
	ativa_select(vetor_mil_e,TAM_VETOR_MIL,tempos.temp_mil.select.embaralhado,tempos.temp_mil.select.t_segu.s_embar);
	ativa_select(vetor_10k_e,TAM_VETOR_10K,tempos.temp_10k.select.embaralhado,tempos.temp_10k.select.t_segu.s_embar);
	ativa_select(vetor_100k_e,TAM_VETOR_100K,tempos.temp_100k.select.embaralhado,tempos.temp_100k.select.t_segu.s_embar);
	ativa_select(vetor_200k_e,TAM_VETOR_200K,tempos.temp_200k.select.embaralhado,tempos.temp_200k.select.t_segu.s_embar);
	ativa_select(vetor_300k_e,TAM_VETOR_300K,tempos.temp_300k.select.embaralhado,tempos.temp_300k.select.t_segu.s_embar);
	ativa_select(vetor_400k_e,TAM_VETOR_400K,tempos.temp_400k.select.embaralhado,tempos.temp_400k.select.t_segu.s_embar);
	ativa_select(vetor_500k_e,TAM_VETOR_500K,tempos.temp_500k.select.embaralhado,tempos.temp_500k.select.t_segu.s_embar);
	

////////////////////////////////////////////////////////////////////////////////////////////

	gerar_valores_vet_ord_cres(vetor_mil_c,TAM_VETOR_MIL);
	gerar_valores_vet_ord_decre(vetor_mil_d,TAM_VETOR_MIL);
	gerar_valores_vet_ord_cres(vetor_mil_e,TAM_VETOR_MIL);
	fisher_yates(vetor_mil_e,TAM_VETOR_MIL);
	
	gerar_valores_vet_ord_cres(vetor_10k_c,TAM_VETOR_10K);
	gerar_valores_vet_ord_decre(vetor_10k_d,TAM_VETOR_10K);
	gerar_valores_vet_ord_cres(vetor_10k_e,TAM_VETOR_10K);
	fisher_yates(vetor_10k_e,TAM_VETOR_10K);

	gerar_valores_vet_ord_cres(vetor_100k_c,TAM_VETOR_100K);
	gerar_valores_vet_ord_decre(vetor_100k_d,TAM_VETOR_100K);
	gerar_valores_vet_ord_cres(vetor_100k_e,TAM_VETOR_100K);
	fisher_yates(vetor_100k_e,TAM_VETOR_100K);

	gerar_valores_vet_ord_cres(vetor_200k_c,TAM_VETOR_200K);
	gerar_valores_vet_ord_decre(vetor_200k_d,TAM_VETOR_200K);
	gerar_valores_vet_ord_cres(vetor_200k_e,TAM_VETOR_200K);
	fisher_yates(vetor_200k_e,TAM_VETOR_200K);

	gerar_valores_vet_ord_cres(vetor_300k_c,TAM_VETOR_300K);
	gerar_valores_vet_ord_decre(vetor_300k_d,TAM_VETOR_300K);
	gerar_valores_vet_ord_cres(vetor_300k_e,TAM_VETOR_300K);
	fisher_yates(vetor_300k_e,TAM_VETOR_300K);

	gerar_valores_vet_ord_cres(vetor_400k_c,TAM_VETOR_400K);
	gerar_valores_vet_ord_decre(vetor_400k_d,TAM_VETOR_400K);
	gerar_valores_vet_ord_cres(vetor_400k_e,TAM_VETOR_400K);
	fisher_yates(vetor_400k_e,TAM_VETOR_400K);

	gerar_valores_vet_ord_cres(vetor_500k_c,TAM_VETOR_500K);
	gerar_valores_vet_ord_decre(vetor_500k_d,TAM_VETOR_500K);
	gerar_valores_vet_ord_cres(vetor_500k_e,TAM_VETOR_500K);
	fisher_yates(vetor_500k_e,TAM_VETOR_500K);


	ativar_marge(vetor_mil_c,TAM_VETOR_MIL,tempos.temp_mil.marge.crescente,tempos.temp_mil.marge.t_segu.s_cresc);
	ativar_marge(vetor_10k_c,TAM_VETOR_10K,tempos.temp_10k.marge.crescente,tempos.temp_10k.marge.t_segu.s_cresc);
	ativar_marge(vetor_100k_c,TAM_VETOR_100K,tempos.temp_100k.marge.crescente,tempos.temp_100k.marge.t_segu.s_cresc);
	ativar_marge(vetor_200k_c,TAM_VETOR_200K,tempos.temp_200k.marge.crescente,tempos.temp_200k.marge.t_segu.s_cresc);
	ativar_marge(vetor_300k_c,TAM_VETOR_300K,tempos.temp_300k.marge.crescente,tempos.temp_300k.marge.t_segu.s_cresc);
	ativar_marge(vetor_400k_c,TAM_VETOR_400K,tempos.temp_400k.marge.crescente,tempos.temp_400k.marge.t_segu.s_cresc);
	ativar_marge(vetor_500k_c,TAM_VETOR_500K,tempos.temp_500k.marge.crescente,tempos.temp_500k.marge.t_segu.s_cresc);

	ativar_marge(vetor_mil_d,TAM_VETOR_MIL,tempos.temp_mil.marge.decrescente,tempos.temp_mil.marge.t_segu.s_decres);
	ativar_marge(vetor_10k_d,TAM_VETOR_10K,tempos.temp_10k.marge.decrescente,tempos.temp_10k.marge.t_segu.s_decres);
	ativar_marge(vetor_100k_d,TAM_VETOR_100K,tempos.temp_100k.marge.decrescente,tempos.temp_100k.marge.t_segu.s_decres);
	ativar_marge(vetor_200k_d,TAM_VETOR_200K,tempos.temp_200k.marge.decrescente,tempos.temp_200k.marge.t_segu.s_decres);
	ativar_marge(vetor_300k_d,TAM_VETOR_300K,tempos.temp_300k.marge.decrescente,tempos.temp_300k.marge.t_segu.s_decres);
	ativar_marge(vetor_400k_d,TAM_VETOR_400K,tempos.temp_400k.marge.decrescente,tempos.temp_400k.marge.t_segu.s_decres);
	ativar_marge(vetor_500k_d,TAM_VETOR_500K,tempos.temp_500k.marge.decrescente,tempos.temp_500k.marge.t_segu.s_decres);

	
	ativar_marge(vetor_mil_e,TAM_VETOR_MIL,tempos.temp_mil.marge.embaralhado,tempos.temp_mil.marge.t_segu.s_embar);
	ativar_marge(vetor_10k_e,TAM_VETOR_10K,tempos.temp_10k.marge.embaralhado,tempos.temp_10k.marge.t_segu.s_embar);
	ativar_marge(vetor_100k_e,TAM_VETOR_100K,tempos.temp_100k.marge.embaralhado,tempos.temp_100k.marge.t_segu.s_embar);
	ativar_marge(vetor_200k_e,TAM_VETOR_200K,tempos.temp_200k.marge.embaralhado,tempos.temp_200k.marge.t_segu.s_embar);
	ativar_marge(vetor_300k_e,TAM_VETOR_300K,tempos.temp_300k.marge.embaralhado,tempos.temp_300k.marge.t_segu.s_embar);
	ativar_marge(vetor_400k_e,TAM_VETOR_400K,tempos.temp_400k.marge.embaralhado,tempos.temp_400k.marge.t_segu.s_embar);
	ativar_marge(vetor_500k_e,TAM_VETOR_500K,tempos.temp_500k.marge.embaralhado,tempos.temp_500k.marge.t_segu.s_embar);
	
////////////////////////////////////////////////////////////////////////////////////////////

	gerar_valores_vet_ord_cres(vetor_mil_c,TAM_VETOR_MIL);
	gerar_valores_vet_ord_decre(vetor_mil_d,TAM_VETOR_MIL);
	gerar_valores_vet_ord_cres(vetor_mil_e,TAM_VETOR_MIL);
	fisher_yates(vetor_mil_e,TAM_VETOR_MIL);
	
	gerar_valores_vet_ord_cres(vetor_10k_c,TAM_VETOR_10K);
	gerar_valores_vet_ord_decre(vetor_10k_d,TAM_VETOR_10K);
	gerar_valores_vet_ord_cres(vetor_10k_e,TAM_VETOR_10K);
	fisher_yates(vetor_10k_e,TAM_VETOR_10K);
	
	gerar_valores_vet_ord_cres(vetor_100k_c,TAM_VETOR_100K);
	gerar_valores_vet_ord_decre(vetor_100k_d,TAM_VETOR_100K);
	gerar_valores_vet_ord_cres(vetor_100k_e,TAM_VETOR_100K);
	fisher_yates(vetor_100k_e,TAM_VETOR_100K);

	gerar_valores_vet_ord_cres(vetor_200k_c,TAM_VETOR_200K);
	gerar_valores_vet_ord_decre(vetor_200k_d,TAM_VETOR_200K);
	gerar_valores_vet_ord_cres(vetor_200k_e,TAM_VETOR_200K);
	fisher_yates(vetor_200k_e,TAM_VETOR_200K);
	
	gerar_valores_vet_ord_cres(vetor_300k_c,TAM_VETOR_300K);
	gerar_valores_vet_ord_decre(vetor_300k_d,TAM_VETOR_300K);
	gerar_valores_vet_ord_cres(vetor_300k_e,TAM_VETOR_300K);
	fisher_yates(vetor_300k_e,TAM_VETOR_300K);
	
	gerar_valores_vet_ord_cres(vetor_400k_c,TAM_VETOR_400K);
	gerar_valores_vet_ord_decre(vetor_400k_d,TAM_VETOR_400K);
	gerar_valores_vet_ord_cres(vetor_400k_e,TAM_VETOR_400K);
	fisher_yates(vetor_400k_e,TAM_VETOR_400K);

	gerar_valores_vet_ord_cres(vetor_500k_c,TAM_VETOR_500K);
	gerar_valores_vet_ord_decre(vetor_500k_d,TAM_VETOR_500K);
	gerar_valores_vet_ord_cres(vetor_500k_e,TAM_VETOR_500K);
	fisher_yates(vetor_500k_e,TAM_VETOR_500K);
	

	ativar_quick(vetor_mil_c,TAM_VETOR_MIL,tempos.temp_mil.quick.crescente,tempos.temp_mil.quick.t_segu.s_cresc);
	ativar_quick(vetor_10k_c,TAM_VETOR_10K,tempos.temp_10k.quick.crescente,tempos.temp_10k.quick.t_segu.s_cresc);
	ativar_quick(vetor_100k_c,TAM_VETOR_100K,tempos.temp_100k.quick.crescente,tempos.temp_100k.quick.t_segu.s_cresc);
	ativar_quick(vetor_200k_c,TAM_VETOR_200K,tempos.temp_200k.quick.crescente,tempos.temp_200k.quick.t_segu.s_cresc);
	ativar_quick(vetor_300k_c,TAM_VETOR_300K,tempos.temp_300k.quick.crescente,tempos.temp_300k.quick.t_segu.s_cresc);
	ativar_quick(vetor_400k_c,TAM_VETOR_400K,tempos.temp_400k.quick.crescente,tempos.temp_400k.quick.t_segu.s_cresc);
	ativar_quick(vetor_500k_c,TAM_VETOR_500K,tempos.temp_500k.quick.crescente,tempos.temp_500k.quick.t_segu.s_cresc);

	ativar_quick(vetor_mil_d,TAM_VETOR_MIL,tempos.temp_mil.quick.decrescente,tempos.temp_mil.quick.t_segu.s_decres);
	ativar_quick(vetor_10k_d,TAM_VETOR_10K,tempos.temp_10k.quick.decrescente,tempos.temp_10k.quick.t_segu.s_decres);
	ativar_quick(vetor_100k_d,TAM_VETOR_100K,tempos.temp_100k.quick.decrescente,tempos.temp_100k.quick.t_segu.s_decres);
	ativar_quick(vetor_200k_d,TAM_VETOR_200K,tempos.temp_200k.quick.decrescente,tempos.temp_200k.quick.t_segu.s_decres);
	ativar_quick(vetor_300k_d,TAM_VETOR_300K,tempos.temp_300k.quick.decrescente,tempos.temp_300k.quick.t_segu.s_decres);
	ativar_quick(vetor_400k_d,TAM_VETOR_400K,tempos.temp_400k.quick.decrescente,tempos.temp_400k.quick.t_segu.s_decres);
	ativar_quick(vetor_500k_d,TAM_VETOR_500K,tempos.temp_500k.quick.decrescente,tempos.temp_500k.quick.t_segu.s_decres);

	
	ativar_quick(vetor_mil_e,TAM_VETOR_MIL,tempos.temp_mil.quick.embaralhado,tempos.temp_mil.quick.t_segu.s_embar);
	ativar_quick(vetor_10k_e,TAM_VETOR_10K,tempos.temp_10k.quick.embaralhado,tempos.temp_10k.quick.t_segu.s_embar);
	ativar_quick(vetor_100k_e,TAM_VETOR_100K,tempos.temp_100k.quick.embaralhado,tempos.temp_100k.quick.t_segu.s_embar);
	ativar_quick(vetor_200k_e,TAM_VETOR_200K,tempos.temp_200k.quick.embaralhado,tempos.temp_200k.quick.t_segu.s_embar);
	ativar_quick(vetor_300k_e,TAM_VETOR_300K,tempos.temp_300k.quick.embaralhado,tempos.temp_300k.quick.t_segu.s_embar);
	ativar_quick(vetor_400k_e,TAM_VETOR_400K,tempos.temp_400k.quick.embaralhado,tempos.temp_400k.quick.t_segu.s_embar);
	ativar_quick(vetor_500k_e,TAM_VETOR_500K,tempos.temp_500k.quick.embaralhado,tempos.temp_500k.quick.t_segu.s_embar);

	
	////////////////////////////////////////////////////////////////////////////////////////////////

// TABELA EM SEGUNDOSSS

	printf("\n                         TABELAS EM SEGUNDOS                              \n");
	printf("============================================================================\n");
	printf("================================CRESCENTE===================================\n");
	printf("============================================================================\n");
	printf("===========TABELA  DE COMPARACAO DO TEMEPO DE EXECUCAO=======================\n");
	printf("============================================================================\n \n");

	int *a = (int*) malloc(7*sizeof(int));
	verefic_aloc(a);	
	a[0] = 1000;
	a[1] = 10000;
	a[2] = 100000;
	a[3] = 200000;
	a[4] = 300000;
	a[5] = 400000;
	a[6] = 500000;
	printf("            ||%7d %12d %12d %12d %12d %12d %12d",a[0],a[1],a[2],a[3],a[4],a[5],a[6]);
	printf("\n======================================================================================================\n");
	printf("Bublle      ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f  \n",
	tempos.temp_mil.bubble.t_segu.s_cresc[0],tempos.temp_10k.bubble.t_segu.s_cresc[0],
	tempos.temp_100k.bubble.t_segu.s_cresc[0],tempos.temp_200k.bubble.t_segu.s_cresc[0],
	tempos.temp_300k.bubble.t_segu.s_cresc[0],tempos.temp_400k.bubble.t_segu.s_cresc[0],
	tempos.temp_500k.bubble.t_segu.s_cresc[0]);
	
	printf("Select      ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.select.t_segu.s_cresc[0],tempos.temp_10k.select.t_segu.s_cresc[0],
	tempos.temp_100k.select.t_segu.s_cresc[0],tempos.temp_200k.select.t_segu.s_cresc[0],
	tempos.temp_300k.select.t_segu.s_cresc[0],tempos.temp_400k.select.t_segu.s_cresc[0],
	tempos.temp_500k.select.t_segu.s_cresc[0]);
	
	printf("Insertion   ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.insertion.t_segu.s_cresc[0],tempos.temp_10k.insertion.t_segu.s_cresc[0],
	tempos.temp_100k.insertion.t_segu.s_cresc[0],tempos.temp_200k.insertion.t_segu.s_cresc[0],
	tempos.temp_300k.insertion.t_segu.s_cresc[0],tempos.temp_400k.insertion.t_segu.s_cresc[0],
	tempos.temp_500k.insertion.t_segu.s_cresc[0]);
		
	
	printf("MargeSort   ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.marge.t_segu.s_cresc[0],tempos.temp_10k.marge.t_segu.s_cresc[0],
	tempos.temp_100k.marge.t_segu.s_cresc[0],tempos.temp_200k.marge.t_segu.s_cresc[0],
	tempos.temp_300k.marge.t_segu.s_cresc[0],tempos.temp_400k.marge.t_segu.s_cresc[0],
	tempos.temp_500k.marge.t_segu.s_cresc[0]);
	
	printf("QuickSort   ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.quick.t_segu.s_cresc[0],tempos.temp_10k.quick.t_segu.s_cresc[0],
	tempos.temp_100k.quick.t_segu.s_cresc[0],tempos.temp_200k.quick.t_segu.s_cresc[0],
	tempos.temp_300k.quick.t_segu.s_cresc[0],tempos.temp_400k.quick.t_segu.s_cresc[0],
	tempos.temp_500k.quick.t_segu.s_cresc[0]);	
	printf("\n");	
	
	printf("\n                           TABELAS EM SEGUNDOS                             \n");
	printf("============================================================================\n");
	printf("===============================DECRESCENTE==================================\n");
	printf("============================================================================\n");
	printf("===========TABELA  DE COMPARACAO DO TEMEPO DE EXECUCAO=======================\n");
	printf("============================================================================\n \n");


	printf("            ||%7d %12d %12d %12d %12d %12d %12d",a[0],a[1],a[2],a[3],a[4],a[5],a[6]);
	printf("\n======================================================================================================\n");
	printf("Bublle      ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.bubble.t_segu.s_decres[0],tempos.temp_10k.bubble.t_segu.s_decres[0],
	tempos.temp_100k.bubble.t_segu.s_decres[0],tempos.temp_200k.bubble.t_segu.s_decres[0],
	tempos.temp_300k.bubble.t_segu.s_decres[0],tempos.temp_400k.bubble.t_segu.s_decres[0],
	tempos.temp_500k.bubble.t_segu.s_decres[0]);
	
	printf("Select      ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.select.t_segu.s_decres[0],tempos.temp_10k.select.t_segu.s_decres[0],
	tempos.temp_100k.select.t_segu.s_decres[0],tempos.temp_200k.select.t_segu.s_decres[0],
	tempos.temp_300k.select.t_segu.s_decres[0],tempos.temp_400k.select.t_segu.s_decres[0],
	tempos.temp_500k.select.t_segu.s_decres[0]);

	printf("Insertion   ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.insertion.t_segu.s_decres[0],tempos.temp_10k.insertion.t_segu.s_decres[0],
	tempos.temp_100k.insertion.t_segu.s_decres[0],tempos.temp_200k.insertion.t_segu.s_decres[0],
	tempos.temp_300k.insertion.t_segu.s_decres[0],tempos.temp_400k.insertion.t_segu.s_decres[0],
	tempos.temp_500k.insertion.t_segu.s_decres[0]);
		
	printf("MargeSort   ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n", 
	tempos.temp_mil.marge.t_segu.s_decres[0],tempos.temp_10k.marge.t_segu.s_decres[0],
	tempos.temp_100k.marge.t_segu.s_decres[0],tempos.temp_200k.marge.t_segu.s_decres[0],
	tempos.temp_300k.marge.t_segu.s_decres[0],tempos.temp_400k.marge.t_segu.s_decres[0],
	tempos.temp_500k.marge.t_segu.s_decres[0]);
	
	printf("QuickSort   ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.quick.t_segu.s_decres[0],tempos.temp_10k.quick.t_segu.s_decres[0],
	tempos.temp_100k.quick.t_segu.s_decres[0],tempos.temp_200k.quick.t_segu.s_decres[0],
	tempos.temp_300k.quick.t_segu.s_decres[0],tempos.temp_400k.quick.t_segu.s_decres[0],
	tempos.temp_500k.quick.t_segu.s_decres[0]);
	printf("\n");	
	
	
	printf("\n                         TABELAS EM SEGUNDOS                              \n");
	printf("============================================================================\n");
	printf("===============================EMBARALHADO==================================\n");
	printf("============================================================================\n");
	printf("===========TABELA  DE COMPARACAO DO TEMEPO DE EXECUCAO=======================\n");
	printf("============================================================================\n \n");


	printf("            ||%7d %12d %12d %12d %12d %12d %12d",a[0],a[1],a[2],a[3],a[4],a[5],a[6]);
	printf("\n======================================================================================================\n");
	printf("Bublle      ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.bubble.t_segu.s_embar[0],tempos.temp_10k.bubble.t_segu.s_embar[0],
	tempos.temp_100k.bubble.t_segu.s_embar[0],tempos.temp_200k.bubble.t_segu.s_embar[0],
	tempos.temp_300k.bubble.t_segu.s_embar[0],tempos.temp_400k.bubble.t_segu.s_embar[0],
	tempos.temp_500k.bubble.t_segu.s_embar[0]);
	
	printf("Select      ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.select.t_segu.s_embar[0],tempos.temp_10k.select.t_segu.s_embar[0],
	tempos.temp_100k.select.t_segu.s_embar[0],tempos.temp_200k.select.t_segu.s_embar[0],
	tempos.temp_300k.select.t_segu.s_embar[0],tempos.temp_400k.select.t_segu.s_embar[0],
	tempos.temp_500k.select.t_segu.s_embar[0]);

	printf("Insertion   ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.insertion.t_segu.s_embar[0],tempos.temp_10k.insertion.t_segu.s_embar[0],
	tempos.temp_100k.insertion.t_segu.s_embar[0],tempos.temp_200k.insertion.t_segu.s_embar[0],
	tempos.temp_300k.insertion.t_segu.s_embar[0],tempos.temp_400k.insertion.t_segu.s_embar[0],
	tempos.temp_500k.insertion.t_segu.s_embar[0]);
			
	printf("MargeSort   ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.marge.t_segu.s_embar[0],tempos.temp_10k.marge.t_segu.s_embar[0],
	tempos.temp_100k.marge.t_segu.s_embar[0],tempos.temp_200k.marge.t_segu.s_embar[0],
	tempos.temp_300k.marge.t_segu.s_embar[0],tempos.temp_400k.marge.t_segu.s_embar[0],
	tempos.temp_500k.marge.t_segu.s_embar[0]);
	
	printf("QuickSort   ||  %0.4f %12.4f %12.4f %12.4f %12.4 %12.4f %12.4f %12.4f \n",
	tempos.temp_mil.quick.t_segu.s_embar[0],tempos.temp_10k.quick.t_segu.s_embar[0],
	tempos.temp_100k.quick.t_segu.s_embar[0],tempos.temp_200k.quick.t_segu.s_embar[0],
	tempos.temp_300k.quick.t_segu.s_embar[0],tempos.temp_400k.quick.t_segu.s_embar[0],
	tempos.temp_500k.quick.t_segu.s_embar[0]);	
	printf("\n");	
	printf("\n");
	
	
	//IMPRIMIR EM MINUTOS
	
	int aux_m;		
	printf("Obs: 1 para SIM | 0 para NAO \n");
	printf("Gostaria de exiber a tabela em minutos? ");
	scanf("%d",&aux_m);
	if(aux_m==1){
		printf("\n                          TABELAS EM MINUTOS                               \n");
		printf("============================================================================\n");
		printf("================================CRESCENTE===================================\n");
		printf("============================================================================\n");
		printf("===========TABELA  DE COMPARACAO DO TEMEPO DE EXECUCAO=======================\n");
		printf("============================================================================\n \n");
		
		printf("            ||%6d %8d %8d %8d %8d %8d %8d",a[0],a[1],a[2],a[3],a[4],a[5],a[6]);
		printf("\n============================================================================\n");
		printf("Bublle      ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n",
		tempos.temp_mil.bubble.crescente[0] ,tempos.temp_mil.bubble.crescente[1],
		tempos.temp_10k.bubble.crescente[0] ,tempos.temp_10k.bubble.crescente[1],
		tempos.temp_100k.bubble.crescente[0] ,tempos.temp_100k.bubble.crescente[1],
		tempos.temp_200k.bubble.crescente[0] ,tempos.temp_200k.bubble.crescente[1],
		tempos.temp_300k.bubble.crescente[0] ,tempos.temp_300k.bubble.crescente[1],
		tempos.temp_400k.bubble.crescente[0] ,tempos.temp_400k.bubble.crescente[1],
		tempos.temp_500k.bubble.crescente[0] ,tempos.temp_500k.bubble.crescente[1]	
		);
			
		printf("Select      ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.select.crescente[0] ,tempos.temp_mil.select.crescente[1],
		tempos.temp_10k.select.crescente[0] ,tempos.temp_10k.select.crescente[1],
		tempos.temp_100k.select.crescente[0] ,tempos.temp_100k.select.crescente[1],
		tempos.temp_200k.select.crescente[0] ,tempos.temp_200k.select.crescente[1],
		tempos.temp_300k.select.crescente[0] ,tempos.temp_300k.select.crescente[1],
		tempos.temp_400k.select.crescente[0] ,tempos.temp_400k.select.crescente[1],
		tempos.temp_500k.select.crescente[0] ,tempos.temp_500k.select.crescente[1]	
		);
			
		printf("Insertion   ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.insertion.crescente[0] ,tempos.temp_mil.insertion.crescente[1],
		tempos.temp_10k.insertion.crescente[0] ,tempos.temp_10k.insertion.crescente[1],
		tempos.temp_100k.insertion.crescente[0] ,tempos.temp_100k.insertion.crescente[1],
		tempos.temp_200k.insertion.crescente[0] ,tempos.temp_200k.insertion.crescente[1],
		tempos.temp_300k.insertion.crescente[0] ,tempos.temp_300k.insertion.crescente[1],
		tempos.temp_400k.insertion.crescente[0] ,tempos.temp_400k.insertion.crescente[1],
		tempos.temp_500k.insertion.crescente[0] ,tempos.temp_500k.insertion.crescente[1]	
		);
						
		printf("MargeSort   ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.marge.crescente[0] ,tempos.temp_mil.marge.crescente[1],
		tempos.temp_10k.marge.crescente[0] ,tempos.temp_10k.marge.crescente[1],
		tempos.temp_100k.marge.crescente[0] ,tempos.temp_100k.marge.crescente[1],
		tempos.temp_200k.marge.crescente[0] ,tempos.temp_200k.marge.crescente[1],
		tempos.temp_300k.marge.crescente[0] ,tempos.temp_300k.marge.crescente[1],
		tempos.temp_400k.marge.crescente[0] ,tempos.temp_400k.marge.crescente[1],
		tempos.temp_500k.marge.crescente[0] ,tempos.temp_500k.marge.crescente[1]	
		);
			
		printf("QuickSrort  ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.quick.crescente[0] ,tempos.temp_mil.quick.crescente[1],
		tempos.temp_10k.quick.crescente[0] ,tempos.temp_10k.quick.crescente[1],
		tempos.temp_100k.quick.crescente[0] ,tempos.temp_100k.quick.crescente[1],
		tempos.temp_200k.quick.crescente[0] ,tempos.temp_200k.quick.crescente[1],
		tempos.temp_300k.quick.crescente[0] ,tempos.temp_300k.quick.crescente[1],
		tempos.temp_400k.quick.crescente[0] ,tempos.temp_400k.quick.crescente[1],
		tempos.temp_500k.quick.crescente[0] ,tempos.temp_500k.quick.crescente[1]	
		);		
		printf("\n");	
		
		printf("\n                          TABELAS EM MINUTOS                               \n");
		printf("============================================================================\n");
		printf("===============================DECRESCENTE==================================\n");
		printf("============================================================================\n");
		printf("===========TABELA  DE COMPARACAO DO TEMEPO DE EXECUCAO=======================\n");
		printf("============================================================================\n \n");
				
		printf("            ||%6d %8d %8d %8d %8d %8d %8d",a[0],a[1],a[2],a[3],a[4],a[5],a[6]);
		printf("\n============================================================================\n");
		printf("Bublle      ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n",
		tempos.temp_mil.bubble.decrescente[0] ,tempos.temp_mil.bubble.decrescente[1],
		tempos.temp_10k.bubble.decrescente[0] ,tempos.temp_10k.bubble.decrescente[1],
		tempos.temp_100k.bubble.decrescente[0] ,tempos.temp_100k.bubble.decrescente[1],
		tempos.temp_200k.bubble.decrescente[0] ,tempos.temp_200k.bubble.decrescente[1],
		tempos.temp_300k.bubble.decrescente[0] ,tempos.temp_300k.bubble.decrescente[1],
		tempos.temp_400k.bubble.decrescente[0] ,tempos.temp_400k.bubble.decrescente[1],
		tempos.temp_500k.bubble.decrescente[0] ,tempos.temp_500k.bubble.decrescente[1]	
		);
			
		printf("Select      ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.select.decrescente[0] ,tempos.temp_mil.select.decrescente[1],
		tempos.temp_10k.select.decrescente[0] ,tempos.temp_10k.select.decrescente[1],
		tempos.temp_100k.select.decrescente[0] ,tempos.temp_100k.select.decrescente[1],
		tempos.temp_200k.select.decrescente[0] ,tempos.temp_200k.select.decrescente[1],
		tempos.temp_300k.select.decrescente[0] ,tempos.temp_300k.select.decrescente[1],
		tempos.temp_400k.select.decrescente[0] ,tempos.temp_400k.select.decrescente[1],
		tempos.temp_500k.select.decrescente[0] ,tempos.temp_500k.select.decrescente[1]	
		);

		printf("Insertion   ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.insertion.decrescente[0] ,tempos.temp_mil.insertion.decrescente[1],
		tempos.temp_10k.insertion.decrescente[0] ,tempos.temp_10k.insertion.decrescente[1],
		tempos.temp_100k.insertion.decrescente[0] ,tempos.temp_100k.insertion.decrescente[1],
		tempos.temp_200k.insertion.decrescente[0] ,tempos.temp_200k.insertion.decrescente[1],
		tempos.temp_300k.insertion.decrescente[0] ,tempos.temp_300k.insertion.decrescente[1],
		tempos.temp_400k.insertion.decrescente[0] ,tempos.temp_400k.insertion.decrescente[1],
		tempos.temp_500k.insertion.decrescente[0] ,tempos.temp_500k.insertion.decrescente[1]	
		);
				
		printf("MargeSort   ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.marge.decrescente[0] ,tempos.temp_mil.marge.decrescente[1],
		tempos.temp_10k.marge.decrescente[0] ,tempos.temp_10k.marge.decrescente[1],
		tempos.temp_100k.marge.decrescente[0] ,tempos.temp_100k.marge.decrescente[1],
		tempos.temp_200k.marge.decrescente[0] ,tempos.temp_200k.marge.decrescente[1],
		tempos.temp_300k.marge.decrescente[0] ,tempos.temp_300k.marge.decrescente[1],
		tempos.temp_400k.marge.decrescente[0] ,tempos.temp_400k.marge.decrescente[1],
		tempos.temp_500k.marge.decrescente[0] ,tempos.temp_500k.marge.decrescente[1]	
		);
			
		printf("QuickSrort  ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.quick.decrescente[0] ,tempos.temp_mil.quick.decrescente[1],
		tempos.temp_10k.quick.decrescente[0] ,tempos.temp_10k.quick.decrescente[1],
		tempos.temp_100k.quick.decrescente[0] ,tempos.temp_100k.quick.decrescente[1],
		tempos.temp_200k.quick.decrescente[0] ,tempos.temp_200k.quick.decrescente[1],
		tempos.temp_300k.quick.decrescente[0] ,tempos.temp_300k.quick.decrescente[1],
		tempos.temp_400k.quick.decrescente[0] ,tempos.temp_400k.quick.decrescente[1],
		tempos.temp_500k.quick.decrescente[0] ,tempos.temp_500k.quick.decrescente[1]	
		);		
		printf("\n");	
		
		printf("\n                          TABELAS EM MINUTOS                               \n");
		printf("============================================================================\n");
		printf("===============================EMBARALHADO==================================\n");
		printf("============================================================================\n");
		printf("===========TABELA  DE COMPARACAO DO TEMEPO DE EXECUCAO=======================\n");
		printf("============================================================================\n \n");
				
		printf("            ||%6d %8d %8d %8d %8d %8d %8d",a[0],a[1],a[2],a[3],a[4],a[5],a[6]);
		printf("\n============================================================================\n");
		printf("Bublle      ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n",
		tempos.temp_mil.bubble.embaralhado[0] ,tempos.temp_mil.bubble.embaralhado[1],
		tempos.temp_10k.bubble.embaralhado[0] ,tempos.temp_10k.bubble.embaralhado[1],
		tempos.temp_100k.bubble.embaralhado[0] ,tempos.temp_100k.bubble.embaralhado[1],
		tempos.temp_200k.bubble.embaralhado[0] ,tempos.temp_200k.bubble.embaralhado[1],
		tempos.temp_300k.bubble.embaralhado[0] ,tempos.temp_300k.bubble.embaralhado[1],
		tempos.temp_400k.bubble.embaralhado[0] ,tempos.temp_400k.bubble.embaralhado[1],
		tempos.temp_500k.bubble.embaralhado[0] ,tempos.temp_500k.bubble.embaralhado[1]	
		);
		
		printf("Select      ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.select.embaralhado[0] ,tempos.temp_mil.select.embaralhado[1],
		tempos.temp_10k.select.embaralhado[0] ,tempos.temp_10k.select.embaralhado[1],
		tempos.temp_100k.select.embaralhado[0] ,tempos.temp_100k.select.embaralhado[1],
		tempos.temp_200k.select.embaralhado[0] ,tempos.temp_200k.select.embaralhado[1],
		tempos.temp_300k.select.embaralhado[0] ,tempos.temp_300k.select.embaralhado[1],
		tempos.temp_400k.select.embaralhado[0] ,tempos.temp_400k.select.embaralhado[1],
		tempos.temp_500k.select.embaralhado[0] ,tempos.temp_500k.select.embaralhado[1]	
		);
		
		printf("Insertion   ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.insertion.embaralhado[0] ,tempos.temp_mil.insertion.embaralhado[1],
		tempos.temp_10k.insertion.embaralhado[0] ,tempos.temp_10k.insertion.embaralhado[1],
		tempos.temp_100k.insertion.embaralhado[0] ,tempos.temp_100k.insertion.embaralhado[1],
		tempos.temp_200k.insertion.embaralhado[0] ,tempos.temp_200k.insertion.embaralhado[1],
		tempos.temp_300k.insertion.embaralhado[0] ,tempos.temp_300k.insertion.embaralhado[1],
		tempos.temp_400k.insertion.embaralhado[0] ,tempos.temp_400k.insertion.embaralhado[1],
		tempos.temp_500k.insertion.embaralhado[0] ,tempos.temp_500k.insertion.embaralhado[1]	
		);		
		
		printf("MargeSort   ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.marge.embaralhado[0] ,tempos.temp_mil.marge.embaralhado[1],
		tempos.temp_10k.marge.embaralhado[0] ,tempos.temp_10k.marge.embaralhado[1],
		tempos.temp_100k.marge.embaralhado[0] ,tempos.temp_100k.marge.embaralhado[1],
		tempos.temp_200k.marge.embaralhado[0] ,tempos.temp_200k.marge.embaralhado[1],
		tempos.temp_300k.marge.embaralhado[0] ,tempos.temp_300k.marge.embaralhado[1],
		tempos.temp_400k.marge.embaralhado[0] ,tempos.temp_400k.marge.embaralhado[1],
		tempos.temp_500k.marge.embaralhado[0] ,tempos.temp_500k.marge.embaralhado[1]	
		);
			
		printf("QuickSrort  ||%3d : %d    %d : %d     %d : %d     %d : %d     %d : %d     %d : %d     %d : %d\n", 
		tempos.temp_mil.quick.embaralhado[0] ,tempos.temp_mil.quick.embaralhado[1],
		tempos.temp_10k.quick.embaralhado[0] ,tempos.temp_10k.quick.embaralhado[1],
		tempos.temp_100k.quick.embaralhado[0] ,tempos.temp_100k.quick.embaralhado[1],
		tempos.temp_200k.quick.embaralhado[0] ,tempos.temp_200k.quick.embaralhado[1],
		tempos.temp_300k.quick.embaralhado[0] ,tempos.temp_300k.quick.embaralhado[1],
		tempos.temp_400k.quick.embaralhado[0] ,tempos.temp_400k.quick.embaralhado[1],
		tempos.temp_500k.quick.embaralhado[0] ,tempos.temp_500k.quick.embaralhado[1]	
		);		
		printf("\n");
	}



	//DESALOCAR VETORES DA MEMÓRIA
		
	
	free(vetor_mil_c);
	free(vetor_mil_d);
	free(vetor_mil_e);
	
	free(vetor_10k_c);
	free(vetor_10k_d);
	free(vetor_10k_e);

	free(vetor_100k_c);
	free(vetor_100k_d);
	free(vetor_100k_e);

	free(vetor_200k_c);
	free(vetor_200k_d);
	free(vetor_200k_e);
	
	free(vetor_300k_c);
	free(vetor_300k_d);
	free(vetor_300k_e);	
	
	free(vetor_400k_c);
	free(vetor_400k_d);
	free(vetor_400k_e);	
	
	free(vetor_500k_c);
	free(vetor_500k_d);
	free(vetor_500k_e);
	
	free(a);
	
	system("pause");
	return 0;
}
