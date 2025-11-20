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
    df.capacity=4;

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
    df.data = malloc(df.capacity * sizeof(char **));
    char * line=NULL;
    len=0;

    while(getline(&line,&len,file) != -1){
         
        /*
        closing the string formally with \0
        */
        if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
       
        /*
        create an array of string pointers to store the values in string
        */
        if(df.rows == df.capacity){ // check the row and availible capacity
            df.capacity *= 2; // double the capacity.2*4=8
            /*
            After doubling the capacity,its time to reallocate 
            memory using realloc function.
            */
           df.data=realloc(df.data,(df.capacity*sizeof(char**)));
        }

        df.data[df.rows] = malloc(df.cols * sizeof(char*)); // allocate memory for array of strings.
        /*
        else do the same,e.g adding data to the 2d array
        in row and columns.
        */
       token=strtok(line,","); // tokenize each line
       col=0;
       while(token){
        df.data[df.rows][col++]=strdup(token);
        token=strtok(NULL,",");
       }

       /*
       increase the value of df.rows in each iteration.
       */
        df.rows++;

    }

    fclose(file);

    return df;
}

void display_df(DataFrame *df){

    printf("\n------DataFrame-----\n");
    printf("\n--------------------\n");
    printf("|");
    for (int i = 0; i < df->cols; i++){
        printf(" %s |",df->columns[i]);
    }
    printf("\n--------------------\n");
    printf("\n--------------------\n");
    printf("|");
    for (int i = 0; i < df->rows; i++) {

        for (int j = 0; j < df->cols; j++) {
        printf(" %s |", df->data[i][j]);  
        }
        printf("\n--------------------\n");
    }

}


int main(){

    DataFrame df=read_csv("file.csv");
    
    

    printf("\n");
    display_df(&df);
    /*
    free the memory
    */
   for (int i = 0; i < df.rows; i++) {
        for (int j = 0; j < df.cols; j++) {
        free(df.data[i][j]);
    }
    free(df.data[i]);
    }
    free(df.data);

    for (int i = 0; i < df.cols; i++) {
        free(df.columns[i]);
    }
    free(df.columns);




    
}
