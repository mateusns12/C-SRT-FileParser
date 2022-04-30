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
void findSequence(char * file, int shift, int opt);
void Menu(char * file);
void changeTimestamp(char * buffer, Time stamp,int shift, int opt);
int getTimestamp(char * buffer, Time * stamp);

int main(int argc,char * argv[]){

	char * usage = "\nInsert path to SRT file in the command line : ./clegend <Path to file>\n\nExample:\n\n[user@DESKTOP C-SRT-FileParser]$ ./clegend src/file.srt\n";

	if(argv[1] == NULL){
		printf("\nFile not especified.\n");
		printf("%s",usage);		
	}else{
		FILE * fp;
		if((fp = fopen(argv[1],"r")) == NULL){
			printf("\nFile can't be openned or is invalid\n %s",usage);
		}else{
		fclose(fp);
		printf("\nOpenning File : %s\n",argv[1]);
		Menu(argv[1]);
		}
	}
	printf("\nGoodbye \U0001f984 \n");
	return 0;
}

void findSequence(char * file, int shift, int opt){
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
					changeTimestamp(buffer,stamp,shift,opt);
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

void changeTimestamp(char * buffer, Time stamp,int shift, int opt){

	if(opt == 2){
		int shift_ms = shift;
		shift = shift/1000;
		stamp.milisseconds_1 += shift_ms;
        stamp.seconds_1 += shift/1000 + stamp.milisseconds_1/60000;
        stamp.milisseconds_1 = stamp.milisseconds_1%1000;

		stamp.milisseconds_2 += shift_ms;
        stamp.seconds_2 += shift/1000 + stamp.milisseconds_2/60000;
        stamp.milisseconds_2 = stamp.milisseconds_2%1000;
		//shift = shift/1000;
    }

	stamp.seconds_1 += shift%60;
    stamp.minutes_1 += shift/60 + stamp.seconds_1/60;
    //stamp.hours_1 += shift/3600;
	//stamp.hours_1 += stamp.seconds_1/60;
	stamp.hours_1 += stamp.minutes_1/60;
    stamp.seconds_1 = stamp.seconds_1%60;
    stamp.minutes_1 = stamp.minutes_1%60;

	if(stamp.milisseconds_1 < 0){
        stamp.milisseconds_1 += 1000;
        stamp.seconds_1 -= 1;
    }
    if(stamp.seconds_1 < 0){
        stamp.seconds_1 += 60;
        stamp.minutes_1 -= 1;
    }
    if(stamp.minutes_1 < 0){
        stamp.minutes_1 += 60;
        stamp.hours_1 -= 1;
    }
    if(stamp.hours_1 < 0){
        stamp.hours_1 += 24;  //this is messed up, but it is unlikely to have a +2 hour shifted subtitle
    }

	stamp.seconds_2 += shift%60;
    stamp.minutes_2 += shift/60 + stamp.seconds_2/60;
    //stamp.hours_2 += shift/3600;
	//stamp.hours_2 += stamp.seconds_2/60;
	stamp.hours_2 += stamp.minutes_2/60;
    stamp.seconds_2 = stamp.seconds_2%60;
    stamp.minutes_2 = stamp.minutes_2%60;

	if(stamp.milisseconds_2 < 0){
        stamp.milisseconds_2 += 1000;
        stamp.seconds_2 -= 1;
    }
    if(stamp.seconds_2 < 0){
        stamp.seconds_2 += 60;
        stamp.minutes_2 -= 1;
    }
    if(stamp.minutes_2 < 0){
        stamp.minutes_2 += 60;
        stamp.hours_2 -= 1;
    }
    if(stamp.hours_2 < 0){
        stamp.hours_2 += 24;  //this is messed up, but it is unlikely to have a +2 hour shifted subtitle
    }
				
	sprintf(buffer,"%.2d:%.2d:%.2d,%.3d --> %.2d:%.2d:%.2d,%.3d\n",
	stamp.hours_1,stamp.minutes_1,stamp.seconds_1,stamp.milisseconds_1,
	stamp.hours_2,stamp.minutes_2,stamp.seconds_2,stamp.milisseconds_2);				
}

void readFile(char * file){
	FILE * fp;
	if((fp = fopen(file,"r")) == NULL){
		printf("\nFile can't be openned or is invalid\n");
	}else{
		printf("\nFile openned\n");
		int ch = getc(fp);	
		if(ch == EOF){
			printf("\nEmpty File\n");
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
	int secs;
	char * menu = "\nChoose an Option :\n\t1 - Parse in seconds\n\t2 - Parse in milliseconds\n\t3 - Print File\n\t6 - Exit\n";
	do{
		printf("%s",menu);
                scanf("%d",&option);
		switch(option){
			case 1:
				secs = 0;
				printf("\nHow many seconds to shift ? : ");
				scanf("%d",&secs);
				findSequence(file,secs,option);
				break;
			case 2:
				secs = 0;
				printf("\nHow many milliseconds to shift ? : ");
				scanf("%d",&secs);
				findSequence(file,secs,option);
				break;
			case 3:
				readFile(file);
				break;
			case 6:
				break;
			default:
				printf("\n\tInvalid\n");
		}
	}while(option != 6);
}
