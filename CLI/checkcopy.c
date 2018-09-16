#include "checkcopy.h"

///test1 is counting amount of character of file1 and file2 then compare it 
float test1(char *filename1, char *filename2, char *resultS1){
	FILE *file1;
	FILE *file2;
	int i,j,maxlen=255;
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
	sprintf(resultS1,"%.2f%%",result);

	free(charcnt1);
	free(charcnt2);
	//printf("T1 %.5d %.5d - %s\n",countC,countN,hasilS1);
	return result;
}

///test2 is comparing file1 and file2 line by line======================
float test2(char *filename1, char *filename2, char *resultS2){
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
	sprintf(resultS2,"%.2f%%",result);
	
//free some memory
	for(i=0;i<linecnt1;i++){	
		free(ptrtxt1[i]);
	}
	for(i=0;i<linecnt2;i++){	
		free(ptrtxt2[i]);
	}
	free(ptrtxt1);
	free(ptrtxt2);
	
	//printf("T2 %.5d %.5d - %.2f%%\n",countC,countN,result);
	return result;
}

///=====================================================================
///test3 is comparing file1 and file2 word by word======================
float test3(char *filename1, char *filename2, char *resultS3){
	FILE *file1;
	FILE *file2;
	int i=0,j=0,k=0,maxlen=255;
	int linecnt1=0,linecnt2=0,linecnt;
	
//count maximum line of each file ======================================
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
	
//copying all line to heap memmory =====================================
	//copying text1 ====================================================
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

	//copying text2 ====================================================
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


//some filter algorithm begin ==========================================
	char dictOCT[]={"\011\040\041\042\043\044\045\046\047\050\051\052\053\054\055\056\057\072\073\074\075\076\077\100\133\134\135\136\137\140\173\174\175\176"};
	//for(k=0;k<sizeof(dictOCT)-1;k++){printf("%.2d 0%o %c\n",k,dictOCT[k],dictOCT[k]);} //debug_line_can_be_removed
	
	i=0;j=0;k=0;
	while(i<linecnt1){
		j=0;
		while(ptrtxt1[i][j]!='\0'){
			for(k=0;k<sizeof(dictOCT)-1;k++){
				if(ptrtxt1[i][j]==dictOCT[k]){
					ptrtxt1[i][j]='\040';
					//printf("%c",ptrtxt1[i][j]); //debug_line_can_be_removed
				}
			}
			j++;
		}
		//printf("%.3d %s",i,ptrtxt1[i]); //debug_line_can_be_removed
		i++;
	}
	
	i=0;j=0;k=0;
	while(i<linecnt2){
		j=0;
		while(ptrtxt2[i][j]!='\0'){
			for(k=0;k<sizeof(dictOCT)-1;k++){
				if(ptrtxt2[i][j]==dictOCT[k]){
					ptrtxt2[i][j]='\040';
					//printf("%c",ptrtxt2[i][j]); //debug_line_can_be_removed
				}
			}
			j++;
		}
		//printf("%.3d %s",i,ptrtxt2[i]); //debug_line_can_be_removed
		i++;
	}

//copying all word to heap memmory =====================================
	//copy word from each file1 ========================================
	int cntWord1=0,lenWord1=0;
	char *wordS1;
	char **wordCpy1=malloc(sizeof(char*)*1);
	for(i=0,j=0;i<linecnt;i++){
		while(wordS1=strtok_r(ptrtxt1[i],"\040",&ptrtxt1[i])){
			//some fiter algorithm
			if(ptrtxt1[i][0]!='\0'){
				cntWord1++;
				wordCpy1=realloc(wordCpy1,sizeof(char*)*(cntWord1));
				if(!wordCpy1){ //allocate check
					printf("Can't allocate more memory - %d\n",sizeof(char*)*(cntWord1));
					return -1;
				}
				lenWord1=1;while(wordS1[lenWord1]!='\0'){lenWord1++;}
				wordCpy1[j]=malloc(sizeof(char)*(lenWord1+1));
				strcpy(wordCpy1[j],wordS1);
				//printf("%d\n",cntWord1); //debug_line_can_be_removed
				//printf("%d %d %d %d %d %p %s %s\n",i,j,linecnt,cntWord1,lenWord1,&wordCpy1[i],wordS1,wordCpy1[i]); //debug_line_can_be_removed
				j++;
			}
		}
	}
	free(ptrtxt1);
	
	//copy word from each file2 ========================================
	int cntWord2=0,lenWord2=0;
	char *wordS2;
	char **wordCpy2=malloc(sizeof(char*)*1);
	for(i=0,j=0;i<linecnt;i++){
		while(wordS2=strtok_r(ptrtxt2[i],"\040",&ptrtxt2[i])){
			//some fiter algorithm
			if(ptrtxt2[i][0]!='\0'){
				cntWord2++;
				wordCpy2=realloc(wordCpy2,sizeof(char*)*(cntWord2));
				if(!wordCpy2){ //allocate check
					printf("Can't allocate more memory - %d\n",sizeof(char*)*(cntWord2));
					return -1;
				}
				lenWord2=1;while(wordS2[lenWord2]!='\0'){lenWord2++;}
				wordCpy2[j]=malloc(sizeof(char)*(lenWord2+1));
				strcpy(wordCpy2[j],wordS2);
				//printf("%d\n",cntWord2); //debug_line_can_be_removed
				//printf("%d %d %d %d %d %p %s %s\n",i,j,linecnt,cntWord2,lenWord2,&wordCpy2[i],word2,wordCpy2[i]); //debug_line_can_be_removed
				j++;
			}
		}
	}
	free(ptrtxt2);
	
//last filter begin ====================================================
	for(i=0;i<cntWord1;i++){
		strtok(wordCpy1[i],"\n");
		//printf("%d %d %s\n",i,strlen(wordCpy1[i]),wordCpy1[i]); //debug_line_can_be_removed
	}
	for(i=0;i<cntWord2;i++){
		strtok(wordCpy2[i],"\n");
		//printf("%d %s\n",i,wordCpy2[i]); //debug_line_can_be_removed
	}

//comparator algorithm begin ===========================================
	int countC12=0;
	int countC21=0;
	float result,result1,result2;
	
	for(i=0;i<cntWord1;i++){
		for(j=0;j<cntWord2;j++){
			//printf("%.3d %.3d %.3d <%s-%s>\n",i,j,countC12,wordCpy1[i],wordCpy2[j]); //debug_line_can_be_removed
			if(strcmp(wordCpy1[i],wordCpy2[j])==0){
				countC12++;
				//printf("%.3d %.3d %.3d <%s-%s>\n",i,j,countC12,wordCpy1[i],wordCpy2[j]); //debug_line_can_be_removed
				break;
			}
		}
	}
	for(i=0;i<cntWord2;i++){
		for(j=0;j<cntWord1;j++){
			//printf("%.3d %.3d %.3d <%s-%s>\n",i,j,countC21,wordCpy1[i],wordCpy2[j]); //debug_line_can_be_removed
			if(strcmp(wordCpy2[i],wordCpy1[j])==0){
				countC21++;
				//printf("%.3d %.3d %.3d <%s-%s>\n",i,j,countC21,wordCpy2[i],wordCpy1[j]); //debug_line_can_be_removed
				break;
			}
		}
	}

	result1=((float)countC12/(float)cntWord1)*100;
	result2=((float)countC21/(float)cntWord2)*100;
	result=(result1+result2)/2;
	
	//printf("%d-%d %d-%d\n",cntWord1,countC12,cntWord2,countC21); //debug_line_can_be_removed
	//printf("%.2f %.2f\n",result1,result2); //debug_line_can_be_removed
	
	sprintf(resultS3,"%.2f%%",result);
	
//free some memmory ====================================================
	for(i=0;i<cntWord1;i++){	
		//printf("%d %p\n",i,&wordCpy1[i]); //debug_line_can_be_removed
		free(wordCpy1[i]);
	}
	free(wordCpy1);
	for(i=0;i<cntWord2;i++){	
		//printf("%d %p\n",i,&wordCpy2[i]); //debug_line_can_be_removed
		free(wordCpy2[i]);
	}
	free(wordCpy2);

	return result;
}
