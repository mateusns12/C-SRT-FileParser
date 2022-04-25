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
	char buff[500];

	FILE * fp;
	int numero = 0;
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
			ungetc(ch,fp);
			while(1){
				
				fgets(buff,sizeof(buff),fp);
				
				//tempo = "";
				//memset(buff,0,sizeof(buff));
				
				if(feof(fp)) break;	
			}		
		}
	}
	fclose(fp);
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
				if(feof(fp)) break;
				fh = getc(fp);				
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
