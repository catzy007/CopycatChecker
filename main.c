#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float test1(char *filename1, char *filename2);
float test2(char *filename1, char *filename2);
float test3(char *filename1, char *filename2);

int main(int argc, int *argv[]){
	float val1=test1("database1.cfg","database2.cfg");
	float val2=test2("database1.cfg","database2.cfg");
	float val3=test3("database1.cfg","database2.cfg");
	
	//change value below for better result.
	float str1=0.1; //default=0.1
	float str2=0.4; //default=0.3
	float str3=0.5; //default=0.6
	//sum of str1 str2 str3 must exactly 1.
	
	float result=(val1*str1)+(val2*str2)+(val3*str3);
	printf("Total : %.2f%% Similar\n",result);
}

///test1 is counting amount of character of file1 and file2 then compare it 
float test1(char *filename1, char *filename2){
	FILE *file1;
	FILE *file2;
	int i,j,maxlen=255,loop=1;
	char dict[62]={"abcdefghijklmnopqrstuvwzyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"};
 
//count amount of character from file1
	file1=fopen(filename1,"r");
	int *charcnt1=malloc(sizeof(int)*62);
	for(i=0;i<62;i++){
		charcnt1[i]=0;
	}
	char *text1=malloc(sizeof(char)*maxlen);
	while(fgets(text1,maxlen,file1)!= NULL){
		//printf("%.2d - %s",loop++,text1); //debug_line_can_be_removed
		i=0;
		while(text1[i]!='\0'){
			for(j=0;j<62;j++){
				if(text1[i]==dict[j]){
					charcnt1[j]+=1;
				}
			}
			i++;
		}
	}
	free(text1);
	fclose(file1);
	
//count amount of character from file2
	file2=fopen(filename2,"r");
	int *charcnt2=malloc(sizeof(int)*62);
	for(i=0;i<62;i++){
		charcnt2[i]=0;
	}
	char *text2=malloc(sizeof(char)*maxlen);
	while(fgets(text2,maxlen,file2)!= NULL){
		//printf("%.2d - %s",loop++,text2); //debug_line_can_be_removed
		i=0;
		while(text2[i]!='\0'){
			for(j=0;j<62;j++){
				if(text2[i]==dict[j]){
					charcnt2[j]+=1;
				}
			}
			i++;
		}
	}
	free(text2);
	fclose(file2);
	
//comparator algorithm begin
	int countC=0,countN=0;
	for(j=0;j<62;j++){
		//printf("%c %d-%d\n",dict[j],charcnt1[j],charcnt2[j]); //debug_line_can_be_removed
		if(charcnt1[j]==charcnt2[j] && charcnt1[j]!=0 && charcnt2[j]!=0){
			//printf("%c %d-%d\n",dict[j],charcnt1[j],charcnt2[j]); //debug_line_can_be_removed
			countC++;
		}else if(charcnt1[j]!=charcnt2[j]){
			//printf("%c %d-%d\n",dict[j],charcnt1[j],charcnt2[j]); //debug_line_can_be_removed
			countN++;
		}
	}
	float result=((float)countC/((float)countC+(float)countN))*100;

	free(charcnt1);
	free(charcnt2);
	printf("T1 %d %d - %.2f%%\n",countC,countN,result);
	return result;
}

///test2 is comparing file1 and file2 line by line======================
float test2(char *filename1, char *filename2){
//count maximum line of each file
	FILE *file1;
	FILE *file2;
	int j=0,i=0,maxlen=255;
	int linecnt1=0,linecnt2=0,linecnt;
	
	char tst1[255];
	file1=fopen(filename1,"r");
	while(fgets(tst1,255,file1)!=NULL){
		linecnt1++;
	}
	fclose(file1);
	
	char tst2[255];
	file2=fopen(filename2,"r");
	while(fgets(tst2,255,file2)!=NULL){
		linecnt2++;
	}
	fclose(file2);
	
	if(linecnt1>linecnt2){
		linecnt=linecnt2;
	}else if(linecnt2>linecnt1){
		linecnt=linecnt1;
	}else{
		linecnt=linecnt1;
	}
	//printf("%d - %d %d\n",linecnt,linecnt1,linecnt2); //debug_line_can_be_removed
	
//copying all line to heap memmory	
	//copying text1
	i=0;
	file1=fopen(filename1,"r");
	char *text1=malloc(sizeof(char)*maxlen);
	char **ptrtxt1=malloc(sizeof(char*)*linecnt1);
	while(i<linecnt1){
		fgets(text1,maxlen,file1);
		ptrtxt1[i]=malloc(sizeof(char)*maxlen);
		memcpy(ptrtxt1[i],text1,maxlen);
		//printf("%d %s",i,ptrtxt1[i]); //debug_line_can_be_removed
		i++;
	}
	fclose(file1);
	free(text1);

	//copying text2
	i=0;
	file2=fopen(filename2,"r");
	char *text2=malloc(sizeof(char)*maxlen);
	char **ptrtxt2=malloc(sizeof(char*)*linecnt2);
	while(i<linecnt2){
		fgets(text2,maxlen,file2);
		ptrtxt2[i]=malloc(sizeof(char)*maxlen);
		memcpy(ptrtxt2[i],text2,maxlen);
		//printf("%d %s",i,ptrtxt2[i]); //debug_line_can_be_removed
		i++;
	}
	fclose(file2);
	free(text2);

//comparator algorithm begin
	i=0;j=0;
	int countC=0,countN=0;	
	while(i<linecnt){
		j=0;
		while(ptrtxt1[i][j]!='\0' || ptrtxt2[i][j]!='\0'){
			if(ptrtxt1[i][j]==ptrtxt2[i][j]){
				//printf("%c",ptrtxt1[i][j]); //debug_line_can_be_removed
				countC++;
			}else{
				countN++;
			}
			j++;
		}
		i++;
	}
	float result=((float)countC/((float)countC+(float)countN))*100;
	
//free some memory
	for(i=0;i<linecnt1;i++){	
		free(ptrtxt1[i]);
	}
	for(i=0;i<linecnt2;i++){	
		free(ptrtxt2[i]);
	}
	free(ptrtxt1);
	free(ptrtxt2);
	
	
	printf("T2 %d %d - %.2f%%\n",countC,countN,result);
	return result;
}

///test3 is comparing file1 and file2 word by word======================
float test3(char *filename1, char *filename2){
//count maximum line of each file
	FILE *file1;
	FILE *file2;
	int j=0,i=0,maxlen=255;
	int linecnt1=0,linecnt2=0,linecnt;
	
	char tst1[255];
	file1=fopen(filename1,"r");
	while(fgets(tst1,255,file1)!=NULL){
		linecnt1++;
	}
	fclose(file1);
	
	char tst2[255];
	file2=fopen(filename2,"r");
	while(fgets(tst2,255,file2)!=NULL){
		linecnt2++;
	}
	fclose(file2);
	
	if(linecnt1>linecnt2){
		linecnt=linecnt2;
	}else if(linecnt2>linecnt1){
		linecnt=linecnt1;
	}else{
		linecnt=linecnt1;
	}
	//printf("%d - %d %d\n",linecnt,linecnt1,linecnt2); //debug_line_can_be_removed
	
//copying all line to heap memmory	
	//copying text1
	i=0;
	file1=fopen(filename1,"r");
	char *text1=malloc(sizeof(char)*maxlen);
	char **ptrtxt1=malloc(sizeof(char*)*linecnt1);
	while(i<linecnt1){
		fgets(text1,maxlen,file1);
		ptrtxt1[i]=malloc(sizeof(char)*maxlen);
		memcpy(ptrtxt1[i],text1,maxlen);
		//printf("%d %s",i,ptrtxt1[i]); //debug_line_can_be_removed
		i++;
	}
	fclose(file1);
	free(text1);

	//copying text2
	i=0;
	file2=fopen(filename2,"r");
	char *text2=malloc(sizeof(char)*maxlen);
	char **ptrtxt2=malloc(sizeof(char*)*linecnt2);
	while(i<linecnt2){
		fgets(text2,maxlen,file2);
		ptrtxt2[i]=malloc(sizeof(char)*maxlen);
		memcpy(ptrtxt2[i],text2,maxlen);
		//printf("%d %s",i,ptrtxt2[i]); //debug_line_can_be_removed
		i++;
	}
	fclose(file2);
	free(text2);

//copying all word to heap memmory
	i=0;j=0;
	char dictOCT[]={"\011\040\041\042\043\044\045\046\047\049\050\051\052\053\054\055\056\057\072\073\074\075\076\077\100\133\134\135\136\137\140\173\174\175\176"};
	
	//copy word from each file1
	int cntWord1=0,lenWord1=0;
	char *word1;
	char **wordCpy1=malloc(sizeof(char*)*1);
	for(i=0,j=0;i<linecnt;i++){
		while(word1=strtok_r(ptrtxt1[i],dictOCT,&ptrtxt1[i])){
			cntWord1++;
			wordCpy1=realloc(wordCpy1,sizeof(char*)*(cntWord1));
			if(!wordCpy1){ //allocate check
				printf("Can't allocate more memory - %d\n",sizeof(char*)*(cntWord1));
				return -1;
			}
			lenWord1=1;while(word1[lenWord1]!='\0'){lenWord1++;}
			wordCpy1[j]=malloc(sizeof(char)*(lenWord1+1));
			strcpy(wordCpy1[j],word1);
			//printf("%d\n",cntWord1);
			//printf("%d %d %d %d %d %p %s %s\n",i,j,linecnt,cntWord1,lenWord1,&wordCpy1[i],word1,wordCpy1[i]); //debug_line_can_be_removed
			j++;
		}
	}
	for(i=0;i<linecnt1;i++){
		ptrtxt1[i]=NULL;
	}
	free(ptrtxt1);
	
	//copy word from each file2
	int cntWord2=0,lenWord2=0;
	char *word2;
	char **wordCpy2=malloc(sizeof(char*)*1);
	for(i=0,j=0;i<linecnt;i++){
		while(word2=strtok_r(ptrtxt2[i],dictOCT,&ptrtxt2[i])){
			cntWord2++;
			wordCpy2=realloc(wordCpy2,sizeof(char*)*(cntWord2));
			if(!wordCpy2){ //allocate check
				printf("Can't allocate more memory - %d\n",sizeof(char*)*(cntWord2));
				return -1;
			}
			lenWord2=1;while(word2[lenWord2]!='\0'){lenWord2++;}
			wordCpy2[j]=malloc(sizeof(char)*(lenWord2+1));
			strcpy(wordCpy2[j],word2);
			//printf("%d\n",cntWord2);
			//printf("%d %d %d %d %d %p %s %s\n",i,j,linecnt,cntWord2,lenWord2,&wordCpy2[i],word2,wordCpy2[i]); //debug_line_can_be_removed
			j++;
		}
	}
	for(i=0;i<linecnt2;i++){
		ptrtxt2[i]=NULL;
	}
	free(ptrtxt2);
	
	//some filter
	for(i=0;i<cntWord1;i++){
		//printf("%d %s",i,wordCpy1[i]);
		strtok(wordCpy1[i],"\n");
	}
	for(i=0;i<cntWord2;i++){
		strtok(wordCpy2[i],"\n");
	}

//comparator algorithm begin
	int countC=0,countN=0,countT=0;
	float result;
	countT=(cntWord1+cntWord2)/2;
	for(i=0;i<cntWord1;i++){
		for(j=0;j<cntWord2;j++){
			//printf("%d %d <%s><%s>\n",i,j,wordCpy1[i],wordCpy2[j]); //debug_line_can_be_removed
			if(strcmp(wordCpy1[i],wordCpy2[j])==0){
				countC++;
				//printf("%d %d <%s><%s>%d\n",i,j,wordCpy1[i],wordCpy2[j],countC);
				break;
			}
		}
	}
	countN=countT-countC;
	result=((float)countC/(float)countT)*100;
	
	
//free some memmory
	for(i=0;i<cntWord1;i++){	
		//printf("%d %p\n",i,&wordCpy1[i]);
		free(wordCpy1[i]);
	}
	free(wordCpy1);
	for(i=0;i<cntWord2;i++){	
		//printf("%d %p\n",i,&wordCpy2[i]);
		free(wordCpy2[i]);
	}
	free(wordCpy2);

	printf("T3 %d %d - %.2f%%\n",countC,countN,result);
	return result;
}
