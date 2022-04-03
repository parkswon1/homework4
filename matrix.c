#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* create a 2d array whose size is row x col using malloc()
and return the 2d array */
int** create_matrix(int row, int col);
/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col);
/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col);
/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col);
/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main(){
    char command; // char형 comand 변수 선언
    printf("[----- [Park Seok Won]  [2017018003] -----]\n");
    int row, col; // 행,열 받아올 int형 row col변수 선언
    srand(time(NULL)); //실행할 때마다 새로운 값이나오는 변수 선언
    printf("Input your row and col : ");
    scanf("%d %d", &row, &col); //int형으로 행,렬 받아오기
    int** matrix_a = create_matrix(row,col); //int형 matrix_a 함수호출해서 생성
    int** matrix_b = create_matrix(row,col); //int형 matrix_b 함수호출해서 생성
    int** matrix_a_t = create_matrix(row,col); //int형 matrix_a_t 함수호출해서 생성 a의 전치행렬이 들어갈것이다

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //matrix들이 NULL일경우 비정상종료 return -1

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
        scanf(" %c", &command); //command 값 받아오기

        switch(command) { //command값에의해 동작 수행방향 결정
        case 'z': case 'Z': //command가 z거나 Z일때
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);//fill_data함수 호출 mattrix_a, row, col을 인수로 넣어준다.
            fill_data(matrix_b, row, col);//fill_data함수 호출 mattrix_b, row, col을 인수로 넣어준다.
            break;//실행 끝나면 정지
        case 'p': case'P': //command가 p거나 p일때
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); //print_matrix 함수 호출 mattrix_a, row, col을 인수로 넣어준다.
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); //print_matrix 함수 호출 mattrix_b, row, col을 인수로 넣어준다.
			break;//실행 끝나면 정지
        case 'a': case 'A': //command가 a거나 A일때
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); //addition_matrix함수 호출 mattrix_a, mattrix_b, row, col을 인수로 넣어준다.
			break;//실행 끝나면 정지
         case 's': case 'S': //command가 s거나 S일때
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //subtraction_matrix함수 호출 mattrix_a, mattrix_b, row, col을 인수로 넣어준다.
			break;
        case 't': case 'T': //command가 t거나 T일때
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //subtraction_matrix함수 호출 mattrix_a, matrix_a_t, row, col을 인수로 넣어준다.
            print_matrix(matrix_a_t, col, row); //print_matrix 함수 호출 mattrix_a_t, row, col을 인수로 넣어준다.
			break;//실행 끝나면 정지
        case 'm': case 'M': //command가 m거나 M일때
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); //transpose_matrix함수 호출 mattrix_a, matrix_a_t, row, col을 인수로 넣어준다.
            multiply_matrix(matrix_a, matrix_a_t, row, col); //multiply_matrix함수 호출 mattrix_a, matrix_a_t, row, col을 인수로 넣어준다.
			break;//실행 끝나면 정지
        case 'q': case 'Q': //command가 q거나 Q일때
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //free_matrix 함수 호출 matrix_a_t, row, col을 인수로 넣어준다.
            free_matrix(matrix_a, row, col); //free_matrix 함수 호출 mattrix_a, row, col을 인수로 넣어준다.
            free_matrix(matrix_b, row, col); //free_matrix 함수 호출 matrix_b, row, col을 인수로 넣어준다.
			break;//실행 끝나면 정지
        default: //모든 실행에서 입력값이 잘못되는걸 확인
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); 
			break;//실행 끝나면 정지
        }
    }while(command != 'q'&& command != 'Q'); //command입력값이 q거나 Q이면 멈춘다
    return 1; //정상적인 종료를 알림
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) //matrix를 만드는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row coll이 0이하의 수일경우 정상적인 크기가 아니라는 경고출력
		printf("Check the size of row and col!\n");
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); //row 값만큼 동적할당 받아서 행의 주소를 잡아준다
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col); //만들어진 행에다가 col의 값만큼 동적할당 받아서 열을 만들어준다.
	}

	/* Check post conditions */
	if (matrix == NULL) { //위에서 만들어진 matrix가 NULL이면 오류 출력
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

	return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) //matrix의 안의 숫자들을 출력하는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row coll이 0이하의 수일경우 정상적인 크기가 아니라는 경고출력
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) { //matrix_row를 0부터 row보다 작을 때까지 증가시키면서 loop
		for (int matrix_col = 0; matrix_col < col; matrix_col++) //matrix_col를 0부터 col보다 작을 때까지 증가시키면서 loop
			printf("%3d ", matrix[matrix_row][matrix_col]); //matrix안에 있는 matrix_row,matrix_col를 출력
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) { //위에서 만들어진 matrix가 NULL이면 오류 출력
		printf("Memory Allocation Failed.\n");
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) //matrix안의 동적할당들을 free 시켜주는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row coll이 0이하의 수일경우 정상적인 크기가 아니라는 경고출력
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		free(matrix[matrix_row]); //matrix안의 row안의 동적할당을 free시켜준다
	}

	free(matrix); //matrix안의 동적할당을 free시켜준다
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //matrix안의 숫자들을 랜덤함수로 받아와 채워주는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row coll이 0이하의 수일경우 정상적인 크기가 아니라는 경고출력
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20; //0~19사이의 값을 랜던하게 matrix[matrix_row][matrix_col]안아다가 채운다
	/* Check post conditions */
    if (matrix == NULL) { //위에서 만들어진 matrix가 NULL이면 오류 출력
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) //matrix 2개를 받아와 서로의 인자들을 더해주는 함수
{
    int** matrix_sum = create_matrix(row, col); //더한 값을 받아올 매트릭스를 생성
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row coll이 0이하의 수일경우 정상적인 크기가 아니라는 경고출력
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
            //matrix_a[matrix_row][matrix_col]의 값과 matrix_b[matrix_row][matrix_col]의 값을 더해서 matrix_sum에다가 넣어준다
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) { //위에서 만들어진 matrix가 NULL이면 오류 출력
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col); //값을 출력시킬 matrix_sum함수 호출
	free_matrix(matrix_sum, row, col); //사용다한 matrix_sum의 동적할당들을 초기화
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) //matrix 2개를 받아와 서로의 인자들을 빼주는 함수
{
    int** matrix_sub = create_matrix(row, col); //뺀 값을 저장할 매트릭스를 생성
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row coll이 0이하의 수일경우 정상적인 크기가 아니라는 경고출력
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { 
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
            //matrix_a[matrix_row][matrix_col]의 값에 matrix_b[matrix_row][matrix_col]의 값을 빼해서 matrix_sub에다가 넣어준다
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) { //위에서 만들어진 matrix가 NULL이면 오류 출력
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col); //matrix_sub의 값들을 출력
	free_matrix(matrix_sub, row, col); //사용하단 matrix_sub의 동적할당들을 초기화

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) //matrix의 전치행렬을 만들어주는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row coll이 0이하의 수일경우 정상적인 크기가 아니라는 경고출력
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { 
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row]; 
            //matrix[matrix_col][matrix_row]의 값을matrix_t[matrix_row][matrix_col]에다가 저장한다
            //두 matrix의 행과 열순서를 반대로해 전치행렬을 만드는 모습
	}
	/* Check post conditions */ 
    if (matrix == NULL || matrix_t ==NULL) { //위에서 만들어진 matrix가 NULL이면 오류 출력
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) //matrix들을 외적하는 함수
{
    int** matrix_axt = create_matrix(row, row); //외적한 값을 받아올 matrix 외적하면 row,col이 row,row가되기 때문 인수들을 row로 넣어준다
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row coll이 0이하의 수일경우 정상적인 크기가 아니라는 경고출력
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0; //값을 받아올 int형 변수
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];
                //matrix_a의 행과 matrix_t의 열의 인자들을 순서대로 곱한뒤 더해서 temp에 저장한다.
			matrix_axt[matrix_a_row][matrix_t_row] = temp; //temp를 matrix_axt의 인자도 만들어서 저장한다
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) { //위에서 만들어진 matrix가 NULL이면 오류 출력
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row); //matrix_axt를 출력한다.
	free_matrix(matrix_axt, row, col); //matrix_axt의 동적할당들을 초기화시킨다.
	return 1;
}