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
void findSequence(char * file, int shift);
void Menu(char * file);
char * changeTimestamp(char * buffer, Time stamp,int shift);
int getTimestamp(char * buffer, Time * stamp);

int main(int argc,char * argv[]){
	if(argv[1] == NULL){
		printf("\nFile not especified");
	}else{
		printf("\nOpenning File : %s\n",argv[1]);
		Menu(argv[1]);
	}
	printf("\nGoodbye \U0001f984 \n");
	return 0;
}

void findSequence(char * file, int shift){
	char buffer[200];
	FILE * IN_file;
	FILE * OUT_file;
	const int STR_LEN = 29;	
	if((IN_file = fopen(file,"r")) == NULL){
		printf("\nFile can't be openned\n");
	}else{
		int ch = getc(IN_file);
		if(ch == EOF){
			printf("\nEmpty File");
			ungetc(ch,IN_file);
		}else{
			OUT_file = fopen("Outfile.srt","w");
			printf("\n\tCreating Outfile.srt...\n");
			ungetc(ch,IN_file);
			Time stamp;
			while(!feof(IN_file)){	
				buffer[0] = 0;		
				fgets(buffer,sizeof(buffer),IN_file);
				if(getTimestamp(buffer,&stamp) == 8){
					changeTimestamp(buffer,stamp,shift);
				}
				fprintf(OUT_file,buffer);
			}		
		}fclose(OUT_file);
		printf("\n\tOutfile.srt created.\n");
	}
	fclose(IN_file);
	
}

int getTimestamp(char * buffer, Time * stamp){
	int res = sscanf(buffer,"%d:%d:%d,%d --> %d:%d:%d,%d",
	&stamp->hours_1,&stamp->minutes_1,&stamp->seconds_1,&stamp->milisseconds_1,
	&stamp->hours_2,&stamp->minutes_2,&stamp->seconds_2,&stamp->milisseconds_2);
	return res;
}

char * changeTimestamp(char * buffer, Time stamp,int shift){

	if(shift>0){
		int seconds = stamp.seconds_1 + shift;
		int mins = stamp.minutes_1 + seconds/60;
		stamp.hours_1 = stamp.hours_1 + mins/60;
		
		if(seconds >= 60){
			stamp.seconds_1 = (seconds%60);
		}else stamp.seconds_1 = seconds;
		if(mins >= 60){
			stamp.minutes_1 = (mins%60);
		}else stamp.minutes_1 = mins;

		seconds = stamp.seconds_2 + shift;
		mins = stamp.minutes_2 + seconds/60;
		stamp.hours_2 = stamp.hours_2 + mins/60;
		
		if(seconds >= 60){
			stamp.seconds_2 = (seconds%60);
		}else stamp.seconds_2 = seconds;
		if(mins >= 60){
			stamp.minutes_2 = (mins%60);
		}else stamp.minutes_2 = mins;
	}	
				
	sprintf(buffer,"%.2d:%.2d:%.2d,%.3d --> %.2d:%.2d:%.2d,%.3d\n",
	stamp.hours_1,stamp.minutes_1,stamp.seconds_1,stamp.milisseconds_1,
	stamp.hours_2,stamp.minutes_2,stamp.seconds_2,stamp.milisseconds_2);				
}

void readFile(char * file){
	FILE * fp;
	if((fp = fopen(file,"r")) == NULL){
		printf("\nFile can't be openned\n");
	}else{
		printf("\nFile openned\n");
		int ch = getc(fp);	
		if(ch == EOF){
			printf("\nEmpty File");
			ungetc(ch,fp);
		}else{
			ungetc(ch,fp);
			char fh;
			while(!feof(fp)){
				fh = getc(fp);				
				putchar(fh);				
			}
		}		
	}
	fclose(fp);
}

void Menu(char * file){
	int option = 0;
	char * menu = "\nChoose an Option:\n\t1 - Parse\n\t2 - Print File\n\t6 - Exit\n";
	do{
		printf("%s",menu);
                scanf("%d",&option);
		switch(option){
			case 1:
				int secs = 0;
				printf("\nHow many seconds to shift ? : ");
				scanf("%d",&secs);
				findSequence(file,secs);
				break;
			case 2:
				readFile(file);
				break;
			case 3:
				break;
			case 6:
				break;
			default:
				printf("\n\tInvalid\n");
		}
	}while(option != 6);
}
