#include "pustaka.h"

int at_least(char huruf, int jml, char teks[]){
    int n=0,cntr=0;
    while(teks[n]!='\0'){
        if(tolower(teks[n])==tolower(huruf)){
            cntr++;
        }
        n++;
    }
    if(cntr!=jml){
        return 0;
    }
    return 1;
}
