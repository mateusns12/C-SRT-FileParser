#include <stdio.h>
#include <stdlib.h>
#include <wchar.h> 
#include <string.h>
#include <ctype.h>

typedef struct time{
	int hours_1;
	int minutes_1;
	int seconds_1;
	int milisseconds_1;
	int hours_2;
	int minutes_2;
	int seconds_2;
	int milisseconds_2;
}Time;

typedef struct Sequence{
	int numero;
	char * tempo;
	char * legenda;
}Paragrafo;

typedef struct node{
	Paragrafo seq;
	struct node * next;
}Node;

Node * first = NULL;
Node * last = NULL;

void readFile(char * file);
void findSequence(char * file);
void Menu(char * file);
void InsertSequenceDirectly(Paragrafo par);
void InsertSequence(int sequence, char * tempo, char * text);

int main(int argc,char * argv[]){
	if(argv[1] == NULL){
		printf("Arquivo nao especificado");
	}else{
		printf("\nAbrindo arquivo : %s\n",argv[1]);
		Menu(argv[1]);
	}
	printf("\nGoodbye \U0001f984 \n");
	return 0;
}

Paragrafo setParagrafo(int numero, char tempo[], char legenda[]){
	Paragrafo par;
	par.numero = numero;
	par.tempo = malloc(sizeof(char));
	strcpy(par.tempo,tempo);
	par.legenda = malloc(sizeof(char));
	strcpy(par.legenda,legenda);
	return par;
}

void findSequence(char * file){
	char buff[30];
	char buffer[50];
	char line[500] = "";
	FILE * fp;
	int numero = 0;
	//char * tempo = malloc(sizeof(char));
	//char * legenda = malloc(sizeof(char));
	char * tempo;
	char * legenda;	
	if((fp = fopen(file,"r")) == NULL){
		printf("\nArquivo nao pode ser aberto\n");
	}else{
		int ch = getc(fp);
		if(ch == EOF){
			printf("\nArquivo vazio");
			ungetc(ch,fp);
		}else{
			//int i = 0;
			ungetc(ch,fp);
			while(1){			
				int i = 0;	
				if(feof(fp)) break;
				fgets(buff,sizeof(buff),fp);
				if(buff[0]!='\n'){
					if(atoi(buff)){
						numero = atoi(buff);
						fgets(buff,sizeof(buff),fp);
						tempo = buff;						
						while(1){	
							char zh = getc(fp);						
							if(zh == (char)EOF){
								break;							
							}else{
								line[i] = zh;
								i++;
								if(zh == '\n'){
									char fh = getc(fp);
									if(fh =='\n') break;
									ungetc(fh,fp);
								}
							}							
						}legenda = line;
					}
					//printf("\n%d\n%s\n%s",numero,tempo,legenda);
					legenda = "";
					tempo = "";
					memset(line,0,sizeof(line));
					memset(buff,0,sizeof(buff));
					memset(buffer,0,sizeof(buffer));				
				}//if(feof(fp)) break;
			}		
		}
	}//free(tempo);
	//free(legenda);
	fclose(fp);
}

	//if ch = \n{
	//	if ch = \n{
	//		if ch isdigit(){
	//			new sequence
	//		}
	//	}
	//}

void InsertSequence(int sequence, char * tempo, char * text){
	Node * aux = (Node*)malloc(sizeof(Node));
	aux->seq.numero = sequence;
	aux->seq.tempo = tempo;
	aux->seq.legenda = text;
	if(first==NULL){
		first = aux;
		last = first;
	}else{
		last->next = aux;
		last = last->next;
	}last->next = NULL;
}

void InsertSequenceDirectly(Paragrafo par){
	Node * aux = (Node*)malloc(sizeof(Node));
	aux->seq = par;
	if(first==NULL){
		first = aux;
		last = first;
	}else{
		last->next = aux;
		last = last->next;
	}last->next = NULL;
}

void readFile(char * file){
	FILE * fp;
	if((fp = fopen(file,"r")) == NULL){
		printf("\nArquivo nao pode ser aberto\n");
	}else{
		printf("\nArquivo aberto\n");
		int ch = getc(fp);	
		if(ch == EOF){
			printf("\nArquivo vazio");
			ungetc(ch,fp);
		}else{
			ungetc(ch,fp);
			char fh;
			while(1){
				//if(feof(fp)) break;
				
				fh = getc(fp);
				if(fh == (char)EOF){
					break;
				}
				putchar(fh);				
			}
		}		
	}
	fclose(fp);
}

void Menu(char * file){
	int option = 0;
	char * menu = "\n\t1 - Parse\n\t2 - Imprimir arquivo\n\t6 - Sair\n";
	do{
		printf("%s",menu);
                scanf("%d",&option);
		switch(option){
			case 1:
				findSequence(file);
				break;
			case 2:
				readFile(file);
				break;
			case 3:
				break;
			case 6:
				break;
			default:
				printf("\n\tInvalido\n");
		}
	}while(option != 6);
}
