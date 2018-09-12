#include "pustaka.h"

int at_least(char huruf, int jml_data, char teks[]){
    int a,hitung=0;
    a=0;
    while(teks[a]!='\0')
    {
        if(tolower(huruf)==tolower(teks[a])){
            hitung++;
        }
        a++;
    }
    if(hitung!=jml_data){
        return 0;
    }
    return 1;
}
