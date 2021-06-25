#ifndef DOMINO_H
#define DOMINO_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<time.h>
#define MAX_LISTA 28


typedef struct{
	char normal[6];
	int esquerda,direita,somatorio;
}tp_item;


//Cria as peças do jogo
void Criador_Pecas(tp_item p[]){
	char aux[2];
	int i,j,k;
	for(i=0;i<7;i++){
		for(j=i;j<7;j++){
			p[k].direita=j;
			p[k].esquerda=i;
			p[k].somatorio=i+j;
			p[k].normal[0]='|';
			itoa(i,aux,10);
			p[k].normal[1]=aux[0];
			p[k].normal[2]='|';
			itoa(j,aux,10);
			p[k].normal[3]=aux[0];
			p[k].normal[4]='|';
			p[k].normal[5]='\0';		
			k++;
		}
	}
}

//Funções de lista normal modificada para o domino

typedef struct{
	tp_item lista[MAX_LISTA];
	int ini,fim;
}tp_lista;

//inicializar a lista
void inicializa_lista(tp_lista *lista){
	lista->fim = lista->ini = 0;
}

//verificar se a lista esta vazia
int lista_vazia(tp_lista* lista){
	if(lista->ini == lista->fim){
		return 1;
	}else{
		return 0;
	}
}

//verificar se a lista esta cheia
int lista_cheia(tp_lista *lista){
	if(lista->fim == MAX_LISTA){
		return 1;
	}else{
		return 0;
	}
}

//insira um item no final da lista
int insere_lista_no_fim(tp_lista *lista,tp_item e){
	if(lista_cheia(lista)){
		return 0;
	}else{
		lista->lista[lista->fim]= e;
		lista->fim++;
		return 1;
	}
}



//imprimir uma lista toda
void imprime_lista(tp_lista *lista){
	int i;
	
	for(i=0;i<lista->fim;i++){
		printf("%d-%s ",i+1,lista->lista[i]);
	}
	printf("\n");
}

//imprimir uma lista toda

//remover um item da lista
int remove_lista(tp_lista *lista,int e ){
	int i=0,j=0;
	if(lista_vazia(lista)){//se a lista estiver vazia
		return 0;
	}else{
		for(j=e;j<lista->fim;j++)lista->lista[j] = lista->lista[j+1];
		lista->fim--;
		i--;
		return 1;
	}
}

//Funções de Lista duplamente encadeada modificadas para o domino


typedef struct tp_dlistAuxNode{
	tp_item info;
	struct tp_dlistAuxNode *ant;
	struct tp_dlistAuxNode *next;
}tp_dlistNode;


typedef struct{
	tp_dlistNode *start;
	tp_dlistNode *end;
}tp_dlist;


tp_dlist *start_dlist(){
	tp_dlist *list = (tp_dlist *) malloc(sizeof(tp_dlist));
	list->start = NULL;
	list->end = NULL;
	return list;
}


tp_dlistNode *allocDlistNode(){
	tp_dlistNode *pt;
	pt = (tp_dlistNode *) malloc(sizeof(tp_dlistNode));
	return pt;
}


int dlist_empty(tp_dlist *list){
	if ((list->start == NULL) && (list->end == NULL)) return 1;
	return 0;
}


int insert_dlist_end (tp_dlist *list, tp_item e){
	tp_dlistNode *_new;
	_new = allocDlistNode();
	if (!_new) return 0;
	_new->info = e;
	if (dlist_empty(list)){
		_new->next = NULL;
		_new->ant = NULL;
		list->start = list->end = _new;	
	}
	else{
		_new->next = NULL;
		_new->ant = list->end;
		list->end->next = _new;
		list->end = _new;	
	}
	return 1;
}


int insert_dlist_start(tp_dlist *list, tp_item e){
	tp_dlistNode *_new;
	_new = allocDlistNode();
	if (!_new) return 0;
	_new->info = e;
	if (dlist_empty(list)){
		_new->next = NULL;
		_new->ant = NULL;
		list->start = list->end = _new;	
	}
	
	else{
		_new->ant = NULL;
		_new->next = list->start;
		
		list->start->ant = _new;
		list->start = _new;	
	}
	return 1;
}


void print_dlist(tp_dlist *list, int order){
	if (dlist_empty(list)){
		printf("Escolha uma peca:\n\nA mesa esta vazia jogue uma peca.\n");	
	}
	else{
		tp_dlistNode *atu;
		switch(order){
			case 1: 
				atu = list->start;
				while(atu != NULL){
					printf(" %s ",atu->info.normal);
					atu = atu->next;
				}
				printf("\n");
			break;
			case 2:
				atu = list->end;
				while(atu != NULL){
					printf("%s ", atu->info.normal);
					atu = atu->ant;
				}
				printf("\n");
			break;
			default: printf("Invalid code\n");	
		}
	}
}


//////////////////

typedef struct tp_slistNode{
	
	tp_item info;
	
	struct tp_slistNode *next;
		
}tp_slist;

tp_slist *start_slist(){
	
	return NULL;
	
}

int slist_empty(tp_slist *l){
	
	if (l == NULL) return 1;
	
	else return 0;
	
}

tp_slist *alloc_slist(){
	
	tp_slist *list;
	
	list = (tp_slist *) malloc(sizeof(tp_slist));
	
	return list;
	
}


	
int insertOrder_slist(tp_slist **l, tp_item e){
	
	tp_slist *new_node, *atu, *ant;
	
	new_node = alloc_slist();
	
	if (new_node == NULL) return 0;
	
	new_node->info = e;
	
	atu = *l;
	ant = NULL;
	
	while((atu != NULL) && (atu->info.somatorio > e.somatorio)){
		
		ant = atu;
		atu = atu->next;
		
	}
	
	if (ant == NULL) *l = new_node;
	
	else ant->next = new_node;
	
	new_node->next = atu;
	
	
	
}

void print_slist (tp_slist *l){
	int i=0;
	tp_slist *atu;
	atu = l;
	
	while (atu != NULL){
		i++;
		printf("%d-%s ",i, atu->info.normal);
		atu = atu->next;
		
		
	}
	
}


//Funções criadas para o domino

//cria as peças do jogo e preenche o cava em uma sequencia aleatoria dessas peças
void recebe_monte(tp_lista *cava){
	
	int i,j,A[MAX_LISTA],status;
	tp_item p[MAX_LISTA];
	Criador_Pecas(p);
	srand(time(NULL));
	for (i = 0; i < MAX_LISTA; ++i) {
        do {
			A[i] = rand() % MAX_LISTA;
		    status = 1;
		    for (j = 0; j < i; ++j)
		   	    if (A[i] == A[j])
		        status = 0;
		}while (status == 0);   
		insere_lista_no_fim(cava,p[A[i]]);    
	}
}

//ordena a mao do jogador
void quanto_maior_melhor(tp_lista *mao){
	tp_slist *auxm;
	auxm = start_slist();
	int i,aux,j;
	j=mao->fim;
		for(i=0;i<j;i++){
			insertOrder_slist(&auxm ,mao->lista[0]);
			remove_lista(mao,0);
		}
		for(i=0;i<j;i++){
			insere_lista_no_fim(mao , auxm->info);
			auxm=auxm->next;
		}			
}

//distribui todas as 7 peças para cada jogador de forma ordenada
void distribuidor_ordenador_poderoso_aquele_que_nao_respeita_a_ordem_de_chegada(tp_lista *cava,tp_lista *mao){
	tp_slist *auxm;
	auxm = start_slist();
	int i,aux;
	for(i=0;i<7;i++){
		insertOrder_slist(&auxm ,cava->lista[0]);
		remove_lista(cava,0);
	}
	for(i=0;i<7;i++){
		insere_lista_no_fim(mao , auxm->info);
		auxm=auxm->next;
	}			
}


//primeira jogada do jogo onde não ha restrições
void primeira_jogada(tp_dlist *mesa,tp_lista *mao){
	int m;
	printf("O jogo vai comecar!!!\n\nEsperando a confirmacao do primeiro jogador:\n\n");
			system("pause");
			system("cls");
			print_dlist(mesa,1);
			printf("\nMao do jogador 1:\n");
			imprime_lista(mao);
			printf("Numero da peca para jogar:\n");
			scanf("%d",&m);
			system("cls");
			insert_dlist_end(mesa,mao->lista[m-1]);
			remove_lista(mao,m-1);
			printf("Pecas da mesa:\n");
			print_dlist(mesa,1);
			printf("Mao do jogador 1:\n");
			imprime_lista(mao);
			system("pause");
			system("cls");
}

//calcula a quantidade de pontos do jogador no moomento
int pontos(tp_lista *mao){
	int  i , somatorio = 0;
	for (i = 0; i < mao->fim; ++i){
		somatorio += mao->lista[i].somatorio;
	}
	return somatorio;
}

//função que inverte uma peça para colocar ela na mesa
void inverte_peca(tp_lista *mao,int aux){
	tp_item inversor;
	inversor.direita = mao->lista[aux].esquerda;
	inversor.esquerda = mao->lista[aux].direita;
	inversor.somatorio = mao->lista[aux].somatorio;
	strcpy(inversor.normal,strrev(mao->lista[aux].normal));
	mao->lista[aux] = inversor;
}

//teste para ver se o jogador tem o direito de cavar uma peça
int test_cava(tp_dlist *mesa,tp_lista *mao){
	tp_lista aux;
	inicializa_lista(&aux);
	int i;
	for(i=0;i<mao->fim;i++){
		insere_lista_no_fim(&aux,mao->lista[i]);
		
	}
    while(lista_vazia(&aux) != 1){
        if(aux.lista[0].direita == mesa->start->info.esquerda){
            return 1;
        }
        else if(aux.lista[0].esquerda == mesa->start->info.esquerda){
            return 1;
        }
        else if(aux.lista[0].direita == mesa->end->info.direita){
            return 1;
        }
        else if(aux.lista[0].esquerda == mesa->end->info.direita){
            return 1;
        }
        remove_lista(&aux,0);
    }
    return 0;
}

//jogador escolhe jogar no lado direito da mesa
void jogar_direita(tp_lista *mao,int m,tp_dlist *mesa,int *auxlegal){
		if(mao->lista[m-1].esquerda == mesa->end->info.direita){
			insert_dlist_end(mesa,mao->lista[m-1]);
			remove_lista(mao,m-1);	
			*auxlegal = 0;	
		}else if(mao->lista[m-1].direita == mesa->end->info.direita){
			inverte_peca(mao,m-1);
			insert_dlist_end(mesa,mao->lista[m-1]);
			remove_lista(mao,m-1);
			*auxlegal = 0;
		}else{
			printf("peca invalida\ntente novamente\n");
			system("pause");
			*auxlegal = 1;
		}
}

//jogador escolhe jogar no lado esquerdo da mesa
void jogar_esquerda(tp_lista *mao,int m,tp_dlist *mesa,int *auxlegal){
		if(mao->lista[m-1].direita == mesa->start->info.esquerda){
			insert_dlist_start(mesa,mao->lista[m-1]);
			remove_lista(mao,m-1);	
			*auxlegal = 0;
		}else if(mao->lista[m-1].esquerda == mesa->start->info.esquerda){
			inverte_peca(mao,m-1);
			insert_dlist_start(mesa,mao->lista[m-1]);
			remove_lista(mao,m-1);
			*auxlegal = 0;
		}else{
			printf("peca invalida\ntente novamente\n");
			system("pause");
			*auxlegal = 1;
		}
}

//onde o jogador vai escolher o  seu proximo passo no jogo por exemplo jogar uma peça na mesa cavar e passar 
void sistema_de_jogada(int i,tp_dlist *mesa,tp_lista *mao,tp_lista *cava){
	int auxlegal=1,m,lado;
	printf("Esperando a confirmacao do proximo jogador:\n\n");
			system("pause");
			system("cls");
			while(auxlegal == 1 ){
				printf("Pecas da mesa:\n");
				print_dlist(mesa,1);
				printf("Mao do jogador %d:\n",i);
				imprime_lista(mao);
				printf("Opcoes de jogo:\n1- jogar esquerda\n2- jogar direita\n3- cavar\n4- passar\ndigite a opcao desejada:\n");
				scanf("%d",&lado);	
				if(lado==1){
				printf("Digite o numero da peca:\n");
				scanf("%d",&m);
				jogar_esquerda(mao,m,mesa,&auxlegal);				
				}else if(lado==2){
					printf("Digite o numero da peca:\n");
					scanf("%d",&m);
					jogar_direita(mao,m,mesa,&auxlegal);	
				}else if(( lado == 3) && (test_cava(mesa,mao) == 0)){
					if(lista_vazia(cava) == 1){
						printf("Nao existem mais pecas no cava.\n");
					}else{
					printf("Voce ira cavar a peca %s !!\n",cava->lista[0].normal);
					insere_lista_no_fim(mao , cava->lista[0]);
					quanto_maior_melhor(mao);
					remove_lista(cava,0);	
					}
					system("pause");
					auxlegal =1;
				}else if((lado == 4) && (lista_vazia(cava)== 1) && (test_cava(mesa,mao) == 0)){
					printf("Voce passou!\n");
					system("pause");
					auxlegal = 0;
				}else{
					printf("Opcao invalida.\nTente novamente\n\n");
					system("pause");
					auxlegal=1;
				}
					system("cls");	
				}
				system("cls");
				printf("Pecas da mesa:\n");
				print_dlist(mesa,1);
				printf("Mao do jogador %d:\n",i);
				imprime_lista(mao);
				system("pause");
				system("cls");
	
}

//teste para ver se possivel colocar mais peças na mesa
int teste_jogo_fechado(tp_dlist *mesa){
	int i = 0;
	tp_dlistNode *aux;
	aux = mesa->start;
	int esqrmesa = mesa->start->info.esquerda;
	int dirmesa = mesa->end->info.direita;
	while(aux != NULL){
		if((aux->info.direita == esqrmesa) || (aux->info.esquerda == dirmesa)){
			i++;	
		} 
		if((aux->info.direita == dirmesa) || (aux->info.esquerda == esqrmesa)){
			i++;	
		}
		aux = aux->next;
	}
	if(i == 14){
		system("cls");
		return 1;	
	}else{
		return 0;	
	}
	
}

//teste para ver quem e o vencedor no final do jogo
int teste_da_vitoria(tp_lista mao1,tp_lista mao2,tp_dlist *mesa){
	if(lista_vazia(&mao1) == 1){
		printf("vitoria do primeiro jogador!!\n");
		system("pause");
//		return 0;
	}else if(lista_vazia(&mao2) == 1){
		printf("vitoria do segundo jogador!!\n");
		system("pause");
//		return 0;
	}else if(teste_jogo_fechado(mesa) == 1){
		if(pontos(&mao1) < pontos(&mao2)){
			printf("O jogo fechou!!\n\nvitoria do primeiro jogador!!\n\n");
		}
		if(pontos(&mao1) > pontos(&mao2)){
			printf("O jogo fechou!!\n\nvitoria do segundo jogador!!\n\n");	
		}
		if(pontos(&mao1) == pontos(&mao2)){
			printf("O jogo fechou!!\n\nO resultado e um empate!!\n\n");
		}
		system("pause");
//		return 0;
	}
	system("cls");
}



#endif
