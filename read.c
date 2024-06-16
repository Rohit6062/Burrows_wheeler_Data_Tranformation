#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char* argv[]){
    if(argc>1){
        char str[30];
        strcpy(str,argv[1]);
        FILE* f = fopen(str,"r");
        int c;
        c=getc(f);
        while(c!=EOF){
            if(c==1)
            printf("Found\n");
            c=getc(f);
        }
    }
    return 0;
}
