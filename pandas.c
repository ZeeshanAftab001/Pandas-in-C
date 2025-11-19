/* Implementation of Minimal Pandas Library in c */



#include "stdio.h"
#include "string.h"
#include "stdlib.h"


char ** read_csv(char * file_name,int *num_cols){

    char *header=NULL;
    size_t len=0; 
    FILE *file=fopen(file_name,"r");
    __ssize_t read = getline(&header, &len, file);

    if (read != -1) {

        if (header[read - 1] == '\n') header[read - 1] = '\0';
       // printf("Header: %s\n", header);
    }

    int cols = 1;
    for (int i = 0; i < strlen(header); i++){
        if(header[i]==',') cols++;
    }
   // printf("\nNo of Colums are : %d",cols);

    char ** colums=malloc(cols * sizeof(char *));

    /*
        Tokenization of Column Names on the basis of ,
        and storing them into array of strings.
    */

    char * token=strtok(header,",");
    // printf("\n%s\n",token);
    int col=0;
    while (token){
        colums[col++]=strdup(token);
        token=strtok(NULL,",");
    }

    *num_cols = cols;
  
    return colums;
}


int main(){

    char **columns;
    int num_cols;
    columns=read_csv("file.csv",&num_cols);
    for(int i=0;i<num_cols;i++){
        printf("\n%s\n",columns[i]);
    }
    for(int i=0;i<num_cols;i++){
        free(columns[i]);
    }
  
}