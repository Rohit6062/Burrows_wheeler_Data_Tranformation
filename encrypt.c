#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bwd.c"
#include<unistd.h>


byte* joinstring(byte* cmd, byte* name){
    int x= strlen(name)+ strlen(cmd);
    byte* output = malloc(sizeof(byte)*x);
    int i=0;
    strcpy(output,cmd);
    for(i= strlen(cmd);i<x;i++){
        output[i]=name[i-strlen(cmd)];
    }
    output[i]=0;
    return output;
}

byte searchAndSwap(byte curr,byte* list){
    byte output=0;
    if(list[0]==curr)return output;
    int i=0;
    while(list[i]!=curr)i++;
    output=i;
    byte tmp = list[output];
    list[output] = list[0];
    list[0] = tmp;
    return output;
}
byte m2DecryptHeaper(byte curr,byte* list){
    byte output=list[curr];
    byte tmp = list[curr];
    list[curr] = list[0];
    list[0] = tmp;
    return output;
}

void m2Encrypt(byte* strO){
    if(!fileToEncrypt || !outputFile)return;
    int x;
    int i=1;
    int n=1;
    byte* str = malloc(sizeof(byte)*n);
    while(1){
        x=fgetc(fileToEncrypt);
        if(x==EOF)break;
        str[n-1]=x;
        str = realloc(str, sizeof(byte)*++n);
    }
    str[n-1]=1;
    if(n<2)return;
    byte* encrypted = bwd(str,n);
    byte* list  = malloc(sizeof(byte)*256);
    for(i=0;i<256;i++) list[i]=i;
    for(i=0;i<n;i++) encrypted[i] = searchAndSwap(encrypted[i],list);
    FILE* f = fopen("tmp.dat","w");
    fwrite(encrypted,n,1,f);
    fclose(f);
    system("./compress tmp.dat compressed.dat");
    system(joinstring("mv compressed.dat ",strO));
    system("rm tmp.dat");
    printf("Done\n");
}

void m2Decrypt(byte* strI){
    if(!outputFile || !fileToEncrypt)return;
    byte* list = malloc(sizeof(byte)*256); 
    for(int i=0;i<256;i++) list[i]=i;
    system(joinstring(joinstring("./decompress ",strI)," tmp.txt"));
    fileToEncrypt = fopen("tmp.txt","r");
    int x;
    int n=1;
    byte* str = malloc(sizeof(byte)*n);
    while(1){
        x=fgetc(fileToEncrypt);
        if(x==EOF)break;
        str[n-1]=x;
        str = realloc(str, sizeof(byte)*++n);
    }
    n--;
    for(int i=0;i<n;i++) str[i] = m2DecryptHeaper(str[i],list);
    byte *out = cmpOrg(str,n);  
    fwrite(out,n-1,1,outputFile);
    system("rm tmp.txt");
    printf("Done\n");
}

int main(int argc , byte* argv[]){
    byte* strI=malloc(sizeof(byte)*30);
    byte* strO=malloc(sizeof(byte)*30);    
    strcpy(strO,"encrypted.txt");
    if(argc>2){
        strcpy(strO,argv[2]);
        strcpy(strI,argv[1]);
    }
    else if(argc>1){
        strcpy(strI,argv[1]);
    }
    else{
        printf("Enter Full File Name: \n");
        scanf("%s",strI);
    }
    fileToEncrypt = fopen(strI,"r");
    outputFile = fopen(strO,"w");
    if(fileToEncrypt == NULL){
        printf("Failed To Open File\n");
        exit(0);
    }
    if(outputFile == NULL){
        printf("Failed To Open File\n");
        exit(0);
    }
    if(*argv[3] == '0')
        m2Encrypt(strO);
    else
        m2Decrypt(strI);
    return 0;
}

    /*
    fileToEncrypt = fopen("bigfile.txt","r");
    outputFile = fopen("encrypted.txt","w");
    m1Encrypt();
    //*/
    /*
    fileToEncrypt = fopen("encrypted.txt","r");
    outputFile = fopen("decrypted.txt","w");
    m1Decrypt();
    return 0;
}
    */
