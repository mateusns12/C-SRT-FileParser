#include <stdio.h>
#include <stdlib.h>

//void manipulate();
void readFile();

void readFile(char * file){
	FILE * fp;
	if((fp = fopen(file,"r")) == NULL){
		printf("\nArquivo nao pode ser aberto\n");
	}else{
		printf("\nArquivo aberto\n");
		//manipulate();
		char ch;
		int seq;
		char * text;
		/*ch = getc(fp);
		ungetc(ch,fp);
		putchar(c);
		*/
		while(1){
			putchar(ch);
			ch = getc(fp);
			if(feof(fp)) break;
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
	printf(" Goodbye \U0001f984 \n");
	return 0;
}
