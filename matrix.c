#include <stdio.h>
#include <stdlib.h> // malloc(),free 함수가 선언된 헤더파일
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); // 행렬을 담을 배열(2차원)을 동적으로 할당
void print_matrix(int** matrix, int row, int col); // 랜덤값을 담은 행렬을 출력
int free_matrix(int** matrix, int row, int col); // 메모리 해제
int fill_data(int** matrix, int row, int col); // 행렬에 랜덤으로 값을 할당 받음
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬 A + 행렬 B
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬 A - 행렬 B
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // A의 전치행렬 T구하기
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // 행렬 A * 행렬 T

int main()
{

    char command; // 메뉴판 이니셜을 받을 변수
    printf("[----- Chahyeona  2020039009 -----]\n");

    int row, col;
    srand(time(NULL)); // 난수

    printf("Input row and col : ");
    scanf("%d %d", &row, &col); // 만들고자 하는 행과 열의 수 입력 받기
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; } // malloc()은 원하는 크기만큼 제대로 할당받지 못하면 NULL을 반환함.

    do {
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

        switch (command) { // 행렬에 랜덤으로 값을 할당 받음
        case 'z': case 'Z': 
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P': // 랜덤값을 담은 행렬을 출력
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': // 행렬 A + 행렬 B
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': // 행렬 A - 행렬 B
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T': // A의 전치행렬 T구하기
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M': // 행렬 A * 행렬 T(행렬의 곱)
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': // 프로그램 종료, 메모리 회수
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre condition */ // 입력받은 row나 col의 값이 음수라면, -1을 리턴 
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    int** ptr;
    ptr = (int**)malloc(sizeof(int*) * row); // 이중포인터 ptr에 (int 포인터 크기)*(row 크기)를할당
                                             // 각 행들의 주소가 들어감. -> 포인터가 들어갈 공간
    for (int i = 0; i < row; i++)            // 행의 개수만큼 반복
    {
        ptr[i] = (int*)malloc(sizeof(int) * col); // int의 크기 * col 만큼 메모리 할당
    }                                             // 데이터 값이 할당되는 공간

    return ptr; // 생성된 2차원 배열을 가리키는 이중포인터를 리턴
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%5d ", matrix[i][j]); // 1행부터 차례대로 랜덤값을 할당받은 행렬 출력 
        }
        printf("\n");
    }
}


///* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    /* check pre condition */ // 입력받은 row나 col의 값이 음수라면, -1을 리턴 
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    /* check post condition */
    if (matrix == 0) // 정상적으로 동적할당을 하지 못하면 널 값을 반환함
    {
        printf("allocation fail!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) // 할당과 반대로, 데이터 값이 들어가는 메모리들을 먼저 해제해야함.
        free(matrix[i]);
    free(matrix); // 각 행들의 주소값을 담는 메모리 해제

     return 1;

}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    /* check pre condition */ // 입력받은 row나 col의 값이 음수라면, -1을 리턴 
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            matrix[i][j] = rand() % 20; // 1행부터 차례대로 0~19 사이의 랜덤 값 할당
    }

    /* check post condition */
    if (matrix == NULL) // 정상적으로 동적할당을 하지 못하면 널 값을 반환함
    {
        printf("allocation fail!\n");
        return -1;
    }

    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col); // 행렬A와 행렬B의 합을 담을 공간 할당하기

    /* check pre condition */ // 입력받은 row나 col의 값이 음수라면, -1을 리턴
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) // 같은 위치에 있는 값들을 더하여, 새로운 행렬의 동일한 위치에 값을 넣어줌.
    {
        for (int j = 0; j < col; j++)
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
    }
    print_matrix(matrix_sum, row, col);

    /* check post condition */ 
    if (matrix_a == 0 || matrix_b == 0) // 정상적으로 동적할당을 하지 못하면 널 값을 반환함
    {                                   // 두 행렬 중 하나라도 정상적으로 할당을 받지 못하면 할당 실패 문구 출력
        printf("allocation fail!\n");
        return -1;
    }

    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col); // 행렬의 차를 담을 공간 할당하기

    /* check pre condition */ // 입력받은 row나 col의 값이 음수라면, -1을 리턴
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) // 같은 위치에 있는 값들을 빼서, 새로운 행렬의 동일한 위치에 값을 넣어줌.
    {
        for (int j = 0; j < col; j++)
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
    }
    print_matrix(matrix_sub, row, col);

    /* check post condition */
    if (matrix_a == 0 || matrix_b == 0) // 정상적으로 동적할당을 하지 못하면 널 값을 반환함
    {
        printf("allocation fail!\n");
        return -1;
    }

    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    /* check pre condition */ // 입력받은 row나 col의 값이 음수라면, -1을 리턴
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    /* check post condition */
    if (matrix == 0 || matrix_t == 0)  // 정상적으로 동적할당을 하지 못하면 널 값을 반환함
    {
        printf("allocation fail!\n");
        return -1;
    }
    for (int j = 0; j < row; j++) // 두 행렬의 행과 열을 서로 교환
    {
        for (int i = 0; i < col; i++)
        {
            matrix_t[j][i] = matrix[i][j];
        }
    }

    return 1;
}

/* matrix_axt  matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    /* check pre condition */ // 입력받은 row나 col의 값이 음수라면, -1을 리턴
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    int** matrix_axt = create_matrix(row, row); // 행렬 A와 행렬 T의 곱한 값을 담을 새로운 메모리공간 할당
    int sum = 0;                                
    int i,j;
    for (i = 0; i < row; i++) // 행렬의 크기는 row * row 이다. 
    {
        for (j = 0; j < row; j++)
        {
            sum = 0; // 다음 연산을 위해 0으로 초기화는 필수
            for (int k = 0; k < col; k++)
            {
                sum += (matrix_a[i][k] * matrix_t[k][j]); // 행렬 A의 행과 행렬 T의 열들을 각각 곱한 값들의 총합을 sum 변수에 넣기 
            }
            matrix_axt[i][j] = sum; // 0행 부터 차례대로 새로운 행렬에 sum 값을 할당
        }
    }
    print_matrix(matrix_axt, row, row); 

    /* check post condition */
    if (matrix_a == 0 || matrix_t == 0) // 정상적으로 동적할당을 하지 못하면 널 값을 반환함
    {
        printf("allocation fail!\n");
        return -1;
    }

    return 1;
}