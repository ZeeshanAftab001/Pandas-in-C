#if !defined(PANDAS_H)
#define PANDAS_H


typedef struct{

    char **columns; // array of strings for storing column names
    char *** data; // 2d of strings for storsing data in rows and columns.
    int rows;
    int cols;
    int capacity;

} DataFrame;

DataFrame read_csv(char *);

void display_df(DataFrame *);
void df_head(DataFrame *,int);
void df_info(DataFrame *);
void df_describe(DataFrame *);
DataFrame df_select_columns(DataFrame *,char *);

#endif // PANDAS_H
