#if !defined(PANDAS_H)
#define PANDAS_H


typedef struct{

    char **columns; // array of strings for storing column names
    char *** data; // 2d of strings for storsing data in rows and columns.
    int rows;
    int cols;

} DataFrame;

DataFrame read_csv(char * file_name);

void display_df(DataFrame *);

#endif // PANDAS_H
