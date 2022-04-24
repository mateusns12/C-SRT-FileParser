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

void findSequence(char * file){
	//char line = (char*)malloc(sizeof(char));
	char buff[30];
	char line[100] = "";
	FILE * fp;
	Paragrafo parag;
        if((fp = fopen(file,"r")) == NULL){                                printf("\nArquivo nao pode ser aberto\n");
        }else{
                int ch = getc(fp);
                if(ch == EOF){                                                     printf("\nArquivo vazio");                                 ungetc(ch,fp);                                     }else{
			int i = 0;
			while(1){
				ungetc(ch,fp);
				fgets(buff,sizeof(buff),fp);
				//printf("Gathered: %s",buff);
				if(buff[0]!='\n'){

				if(atoi(buff)){
					parag.numero = atoi(buff);
					fgets(buff,sizeof(buff),fp);
					parag.tempo =malloc(sizeof(char));
					//strcpy(parag.tempo,buff);
					parag.tempo = buff;
				char buffer[50];
				while(1){
					//fgets(buffer,sizeof(buffer),fp);
					ch = getc(fp);
					//printf("Gathered: %s",buffer);
					//strcat(line,buffer);
					//if(buffer[0]=='\n')
					//	break;
					line[i] = ch;
					i++;
					if(ch == '\n'){
						char fh = getc(fp);
						if(fh=='\n') break;
					ungetc(fh,fp);
					}
				}
				parag.legenda = malloc(sizeof(char));
				strcpy(parag.legenda,line);
				}
				//break;	
				}
				if(feof(fp)) break;
			}
	printf("\n%d\n%s\n%s",parag.numero,parag.tempo,parag.legenda);
	//if ch = \n{
	//	if ch = \n{
	//		if ch isdigit(){
	//			new sequence
	//		}
	//	}
	//}
		}
	}fclose(fp);
}

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
				//findSequence(fp);
				//fgets(fh,sizeof(fh),fp);
				//printf("%s\n", fh);
				fh = getc(fp);
				putchar(fh);
				if(feof(fp)) break;
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
