#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char byte;
FILE* fileToEncrypt = NULL;
FILE* outputFile = NULL;

typedef struct rotation{
    int index;
    byte* suffix;
}rotation;

int mod(int x, int y){
    if(x < y)return x;
    return mod(x-y,y);
}

int cmpfunc(const void* x, const void* y)
{
    rotation * rx = (rotation* )x;
    rotation * ry = (rotation* )y;
    return strcmp(rx->suffix,ry->suffix);
}

void merge(rotation* a, int l, int m, int r){
    int i, j , k;
    int n1 = m - l + 1;
    int n2 = r - m;
    rotation *L = malloc(sizeof(rotation)*n1), *R = malloc(sizeof(rotation)*n2);

    for(i=0;i<n1;i++){
        L[i].index = a[l+i].index;
        L[i].suffix = a[l+i].suffix;
    }
    for(i=0;i<n2;i++){
        R[i].index = a[m+1+i].index;
        R[i].suffix = a[m+1+i].suffix;
    }
    i=0;
    j=0;
    k=l;
    while(i < n1 && j < n2){
        if(*(L[i].suffix)  <= *(R[j].suffix) ){
            a[k].index = L[i].index;
            a[k].suffix = L[i].suffix;
            i++;
        }
        else{
            a[k].index = R[j].index;
            a[k].suffix = R[j].suffix;
            j++;
        }
        k++;
    }
    while(i < n1){
        a[k].index = L[i].index;
        a[k].suffix = L[i].suffix;
        i++;
        k++;
    }
    while(j<n2){
        a[k].index = R[j].index;
        a[k].suffix = R[j].suffix;
        j++;
        k++;
    }
}

void mergeSort(rotation* a, int l,int r){
    if(l<r){
        int m = l+ (r-l)/2;
        mergeSort(a,l,m);
        mergeSort(a,m+1,r);
        merge(a,l,m,r);
    }
}


byte* bwd(byte* input_txt, int n){
    rotation* suff=malloc(sizeof(rotation)*n);
    for(int i=0;i<n;i++){
        suff[i].index = i;
        suff[i].suffix = (input_txt+i);
    }
    qsort(suff,n,sizeof(rotation),cmpfunc);
    int* suffix_arr = malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
        suffix_arr[i]=suff[i].index;
    byte* bwt_arr = (byte*) malloc(sizeof(byte)*n);
    int i;
    for(i=0;i<n;i++){
        bwt_arr[i] = input_txt[mod(suffix_arr[i]+n-1,n)];
    }
    bwt_arr[i]='\0';
    free(suff);
    free(suffix_arr);
    return bwt_arr;
}

byte* cmpOrg(byte* bwt_arr, int n){
    rotation* sorted = malloc(sizeof(rotation)*n);
    int* last= malloc(sizeof(int)*n);
    byte* output = malloc(n*sizeof(byte));
    for(int i=0;i<n;i++){
        sorted[i].index = i;
        sorted[i].suffix = bwt_arr+i;
    }
    mergeSort(sorted,0,n-1);
    for(int i=0;i<n;i++){
        last[sorted[i].index] = i;
    }
    int put = sorted[0].index;
    for(int i=n-1;i>=0;i--){ 
        output[i] = bwt_arr[put];
        put = last[put];
    }
    free(sorted);
    free(last);
    return output;
}

void m1Encrypt(){
    if(!fileToEncrypt || !outputFile)return ;
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
    byte currbyte = encrypted[0];
    fwrite(&currbyte,sizeof(currbyte),1,outputFile);
    int count = 1;
    byte cnt;
    while(i<n){
        if(count > 255){
            cnt = 255; 
            fwrite(&cnt,sizeof(cnt),1,outputFile);
            fwrite(&currbyte,sizeof(currbyte),1,outputFile);
            count = 1;
        }
        if(encrypted[i]==currbyte){
            count++;
        }
        else{
            cnt = count;
            fwrite(&cnt,sizeof(cnt),1,outputFile);
            currbyte = encrypted[i];
            fwrite(&currbyte,sizeof(currbyte),1,outputFile);
            count = 1;
        }
        i++;
    }
    if(count > 255){
        cnt = 255; 
        fwrite(&cnt,sizeof(cnt),1,outputFile);
        fwrite(&currbyte,sizeof(currbyte),1,outputFile);
        cnt = 1;
    }
    cnt = count;
    fwrite(&cnt,sizeof(cnt),1,outputFile);
    printf("Done\n");
    fclose(outputFile);
}

void m1Decrypt(){
    if(fileToEncrypt==NULL || outputFile == NULL)return ;
    int x;
    byte count;
    int i=0;
    int n=1;
    byte* str = malloc(sizeof(byte)*n);
    while(1){
        x=fgetc(fileToEncrypt);
        if(x==EOF)break;
        count = fgetc(fileToEncrypt);
        str[n-1]=x;
        str = realloc(str, sizeof(byte)* (++n + count-1));
        for(int j=0;j<count-1;j++){
            str[n-1] = x; 
            n++;
        }
    }
    n--;
    byte * out  = cmpOrg(str,n);
    fwrite(out,n-1,1,outputFile);
    /*
    byte toWrite;
    for(int i=0;i<n-1;i++){
        toWrite = out[i];
        fwrite(&toWrite,sizeof(toWrite),1,outputFile);
    }*/
    printf("Done\n");
}

/*
int main(){
    byte input_txt[] = "this is some example text\nso i can work now$";
    int i=0;
    int k=0;
    int txt_len = strlen(input_txt);
    input_txt[txt_len-1]=1;
    byte* bwt_arr = bwd(input_txt,txt_len);
    printf("input_txt = %s\n", input_txt);
    printf("Burrows - Wheeler Transformation : %s\n", bwt_arr);
    printf("\n output:- %s\n",cmpOrg(bwt_arr,txt_len));
    return 0;
}*/
