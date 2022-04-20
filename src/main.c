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

//void manipulate();
void readFile();

char printInside(FILE * ref){
	char ch = getc(ref);
	putchar(ch);	
	//printf("\\x%02x", ch);
}

void findSequence(Paragrafo * par,FILE * ref){
	char line[50];
	char ch;
	char array[1000][50];
	int i = 0;
	while(1){
		fgets(line,sizeof(line),ref);
		strcpy(array[i],line);	
		i++;
	}
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
			char  fh[50];
			Paragrafo text;
			/*while(1){
				
				//findSequence(fp);
				fgets(fh,sizeof(fh),fp);
				printf("%s\n", fh);	
				if(feof(fp)) break;				
			}*/
		}		
	}
	fclose(fp);
}

int main(int argc,char * argv[]){
	if(argv[1] == NULL){
		printf("Arquivo nao especificado");
	}else{
		printf("\nAbrindo arquivo : %s\n",argv[1]);
		readFile(argv[1]);
	}
	printf("\nGoodbye \U0001f984 \n");
	return 0;
}
