#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [하준형]  [2016039030] -----]\n");

    int row, col;
    srand(time(NULL));  /* for using rand() */

    printf("Input row and col : ");
    scanf("%d %d", &row, &col); /* input row & col */
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z': /* Initialize Matrix */
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P': /* Print Matrix */
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': /* Add Matrix */
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': /* Subtract Matrix */
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T': /* Transpose Matrix */
            printf("Transpose matrix_a \n");
            printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M': /* Multiply Matrix */
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': /* Quit */
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    int **matrix, i;

    /*check pre conditions*/
    if(row <= 0 || col <= 0){
        printf("Check the size of row and col!\n");
        
        return NULL;
    }


    matrix = (int**)malloc(sizeof(int *) * row);

    for(i = 0; i < row; i++)
        matrix[i] = (int*) malloc (sizeof(int) * col);
        

    /*check post conditions*/
    if(matrix == NULL) {return NULL;}

    return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    int i, j;

    if(matrix != NULL){
        for(i = 0; i < row; i++){
            for(j = 0; j < col; j++)
                printf("%3d ", matrix[i][j]);

            printf("\n");
        }
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    int i;
       /*check pre conditions*/
    if(matrix == NULL) {return -1;}
   
    for(i = 0; i < row; i++) /* free data */
        free(matrix[i]);
    free(matrix);

    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    int i, j;

    if(matrix == NULL) {return -1;}

    for(i = 0; i < row; i++) /* fill date with rand() */
        for(j = 0; j < col; j++)
            matrix[i][j] = rand() % 20;
    
    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int **matrix_sum, i, j;
    
    if(matrix_a == NULL || matrix_b == NULL) {return -1;} /*check pre conditions*/

    matrix_sum = create_matrix(row, col);

    for(i = 0; i < row; i++) /* calculate the addition */
        for(j = 0; j < col; j++)
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];

    print_matrix(matrix_sum, row, col);
    free_matrix(matrix_sum, row, col);

    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
   int **matrix_sub, i, j;

    if(matrix_a == NULL || matrix_b == NULL) {return -1;} /*check pre conditions*/

   matrix_sub = create_matrix(row, col);

    for(i = 0; i < row; i++) /* calculate the subtraction */
        for(j = 0; j < col; j++)
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
    
    print_matrix(matrix_sub, row, col);
    free_matrix(matrix_sub, row, col);

    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    int i,j;
    
    if(matrix == NULL || matrix_t == NULL) {return -1;}   /*check pre conditions*/
    
    for(i = 0; i < row; i++) /* making matrix_t */
        for(j = 0; j < col; j++)
            matrix_t[i][j] = matrix[j][i];

    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int **matrix_axt, i, j, n;
    int sum = 0;

    if(matrix_a == NULL || matrix_t == NULL) {return -1;} /*check pre conditions*/

   /*the product of multiplying matrix_a with matrix_t is row x row */
    matrix_axt = create_matrix(row, row);

    for(i = 0; i < row; i++){  /* i is matrix_a's row & matrix_axt's row */
        for(n = 0; n < row; n++){ /* n is matrix_t's col & matrix_axt's col*/
            for(j = 0; j < col; j++) /* j is matrix_a's col & matrix_t's row */
                sum += matrix_a[i][j] * matrix_t[j][n];
            
            matrix_axt[i][n] = sum; 
            sum = 0;
        }
    }
    
    print_matrix(matrix_axt, row, row);
    free_matrix(matrix_axt, row, row);

    return 1;
}

