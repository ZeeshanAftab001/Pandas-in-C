/* Implementation of Minimal Pandas Library in c */



#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "pandas.h"


DataFrame read_csv(char * file_name){

    DataFrame df;
    char *header=NULL;
    size_t len=0; 
    FILE *file=fopen(file_name,"r");
    __ssize_t read = getline(&header, &len, file);

    if (read != -1) {

        if (header[read - 1] == '\n') header[read - 1] = '\0';
       // printf("Header: %s\n", header);
    }
    df.cols=1;
    df.rows=0;

    for (int i = 0; i < strlen(header); i++){
        if(header[i]==',') df.cols++;
    }
    df.columns=malloc(df.cols*sizeof(char *));

    /*
        Tokenization of Column Names on the basis of ,
        and storing them into array of strings.
    */

    char * token=strtok(header,",");
    // printf("\n%s\n",token);
    int col=0;
    while (token){
        df.columns[col++]=strdup(token);
        token=strtok(NULL,",");
    }

    fclose(file);

    return df;
}


int main(){

    DataFrame df=read_csv("file.csv");
    for (int i = 0; i < df.cols; i++)
    {
        printf("\n%s\n",df.columns[i]);
    }
    
}
