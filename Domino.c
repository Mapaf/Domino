#include"domino.h"

main(){
	while(1){
		system("color 70");
		system("title DOM-INATOR");
		char url[]="title.txt";
		char ch;
		FILE *arq;
		arq = fopen(url, "r");
		if(arq == NULL){
			printf("Erro, nao foi possivel abrir o arquivo\n");
		}else{
			while( (ch=fgetc(arq))!= EOF )
			putchar(ch);
		}
		fclose(arq);
		printf("\n\n");
		system("pause");
		system("cls");
		printf("---MENU---\n\n1- jogar.\n\n2- regras do jogo.\n\n3- creditos.\n\n");
		int z;
		printf("-digite a opcao desejada:\n");
		scanf("%d",&z);
		system("pause");
		system("cls");
		if(z==1){
		//	criando variaveis
			tp_lista cava;
			tp_lista mao,mao2;
			int controladorDvez;
			tp_dlist *mesa;
		//monte aleatorio
			inicializa_lista(&cava);
			recebe_monte(&cava);
		//distribuir de mãos
			inicializa_lista(&mao);
			inicializa_lista(&mao2);
			distribuidor_ordenador_poderoso_aquele_que_nao_respeita_a_ordem_de_chegada(&cava,&mao);
			distribuidor_ordenador_poderoso_aquele_que_nao_respeita_a_ordem_de_chegada(&cava,&mao2);
		//inicio do jogo a primeira jogada
			mesa=start_dlist();
			primeira_jogada(mesa,&mao);
		////	que comece o jogo
			while((lista_vazia(&mao) != 1) && (lista_vazia(&mao2) != 1) && (teste_jogo_fechado(mesa) != 1) ){
				if(controladorDvez%2 == 1){
		//			VEZ DO JOGADOR 1
					sistema_de_jogada(1,mesa,&mao,&cava);
					pontos(&mao);
					teste_jogo_fechado(mesa);
					controladorDvez++;
				}else if(controladorDvez%2 == 0){
		//			VEZ DO JOGADOR 2
					sistema_de_jogada(2,mesa,&mao2,&cava);
					pontos(&mao2);
					teste_jogo_fechado(mesa);
					controladorDvez++;
				}
			}
		//	TESTE PARA A VITORIA
			teste_da_vitoria(mao,mao2,mesa);	
		}else if(z==2){
			char url[]="rules.txt";
			char ch;
			FILE *arq;
			arq = fopen(url, "r");
			if(arq == NULL){
				printf("Erro, nao foi possivel abrir o arquivo\n");
			}else{
				while( (ch=fgetc(arq))!= EOF )
				putchar(ch);
			}		
			fclose(arq);
			printf("\n");
			system("pause");
			system("cls");	
		}else if(z==3){
			printf("Criadores do algoritimo:\n\n");
			printf("1- Marcos Aurelio Paixao de Araujo Filho\n\n");
			printf("1- Joao Victor Sledz de Bulhoes\n\n");
			printf("1- Ewerton de Oliveira Alves\n\n");
			printf("1- Alvaro Madureira Dantas\n\n");
			printf("Historia e regras do domino:\n\nludijogos.com\n\n");
			system("pause");
			system("cls");
		}else{
			printf("Opcao invalida.\n");
			system("pause");
			system("cls");
		}	
	}
}


