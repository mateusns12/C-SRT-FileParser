#include <stdio.h>
#include <stdlib.h>
#include <wchar.h> 
#include <string.h>
#include <ctype.h>

typedef struct Sequence{
	int numero;
	char * tempo;
	char * legenda;
}Paragrafo;

typedef struct Node{
	Paragrafo par;
	struct Node * next;
}node;

//void manipulate();
void readFile();

void printInside(FILE * ref){
	char ch = getc(ref);
	putchar(ch);	
	//printf("\\x%02x", ch);
}

void findSequence(Paragrafo * par,FILE * ref){
	char line[50];
	char ch;
	char **array; 
	//(char**)malloc(sizeof(char*));
	int i = 0;
	while(1){
		//fgets(line,sizeof(line),ref);
		//strcpy(array[i],line);	
		//i++;
		break;
	}

	//if ch = \n{
	//	if ch = \n{
	//		if ch isdigit(){
	//			new sequence
	//		}
	//	}
	//}
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
			Paragrafo text;
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
				break;
			case 2:
				readFile(file);
				break;
			case 3:
				break;
			default:
				printf("\n\tInvalido\n");
		}
	}while(option != 6);
}

int main(int argc,char * argv[]){
	if(argv[1] == NULL){
		printf("Arquivo nao especificado");
	}else{
		printf("\nAbrindo arquivo : %s\n",argv[1]);
		//readFile(argv[1]);
		Menu(argv[1]);
	}
	printf("\nGoodbye \U0001f984 \n");
	return 0;
}
