
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NR 10007

//Functie pentru alocarea unei matrici cu m linii si n coloane.
int **allocate_matrix(int m, int n)
{
	//Se aloca memorie pentru m linii;
	int **matrix = (int **)malloc(m * sizeof(int *));
	//Verificam daca alocarea a avut loc cu succes.
	if (!matrix) {//Verificam daca alocarea a avut loc cu succes.
		free(matrix);//Daca alocarea nu a avut loc, eliberam ce am alocat.
		return 0;
	}
	//Alocam memorie pentru fiecare linie.
	for (int i = 0; i < m; i++) {
		matrix[i] = (int *)malloc(n * sizeof(int));
		if (!matrix[i]) {//Verificam daca alocarea s-a efectuat cu succes.
		//Daca una dintre alocari nu are loc, se elibereaza tot ce am alocat.
			for (int j = 0; j < i; j++)
				free(matrix[j]);
			free(matrix);
			return 0;
		}
	}
	return matrix;
}

void free_matrix(int **matrix, int m)//Functie pentru eliberarea unei matrici.
{
	for (int i = 0; i < m; i++)//Se elibereaza memoria pentru fiecare linie.
		free(matrix[i]);
	free(matrix);//Se elibereaza memoria pentru fiecare linie.
}

//Functie care verifica daca indexul dat coincide unei matrici din memorie.
int check(int index, int k)
{
	if (index >= k || index < 0)
		return 0;
	else
		return 1;
}

//Functie care afiseaza dimensiunile unei matrici.
void case_d(int k, int *row, int *coll)
{
	int index;
	scanf("%d", &index);
	if (!check(index, k))
		printf("No matrix with the given index\n");
	else
		//Se afiseaza dimeniunile matricei.
		printf("%d %d\n", row[index], coll[index]);
}

//Functie care afiseaza matricea corespunzatoare indexului citit.
void case_p(int k, int ***mat, int *row, int *coll)
{
	int index;
	scanf("%d", &index);
	if (check(index, k))
		for (int i = 0; i < row[index]; i++) {
			for (int j = 0; j < coll[index]; j++)
				printf("%d ", mat[index][i][j]);
		printf("\n");
		}
	else
		printf("No matrix with the given index\n");
}

//Functie pentru caracterul C, pentru redimensionarea matricei.
void case_c(int k, int ***mat, int *row, int *coll)
{
	int index, m, n, *index_m, *index_n, i, j;
	scanf("%d", &index);
	if (!check(index, k)) {//Se verifica indexul citit.
		printf("No matrix with the given index\n");
	} else {
		//Se citeste numarul de linii dupa care se face redimensionarea.
		scanf("%d", &m);
		//Alocam memorie pentru vectorul care retine indicii.
		index_m = (int *)malloc(m * sizeof(int));
		if (!index_m)
			return;
		for (i = 0; i < m; i++)
			scanf("%d", &index_m[i]);
		//Se citeste numarul de coloane dupa care se face redimensionarea.
		scanf("%d", &n);
		//Alocam memorie pentru vectorul care retine indicii.
		index_n = (int *)malloc(n * sizeof(int));
		if (!index_n)
			return;
		for (i = 0; i < n; i++)
			scanf("%d", &index_n[i]);
		//Alocam memorie unei matrici auxiliare care va avea dimensiunile date.
		int **tmp = allocate_matrix(m, n);
		if (!tmp) {
			free(tmp);
			return;
		}
		int **matrix = mat[index];
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++) {
				int x = index_m[i];
				int y = index_n[j];
				tmp[i][j] = matrix[x][y];//Construim matricea auxiliara.
			}
		//Eliberam matricea veche.
		for (i = 0; i < row[index]; i++)
			free(mat[index][i]);
		free(mat[index]);
		mat[index] = tmp;//Matricei cu indexul dat, ii atribuim noua valoare.
		row[index] = m;
		coll[index] = n;
		free(index_m);
		free(index_n);
		}
}

//Functie pentru caracterul M, pentru inmultirea a doua matrici.
int **case_m(int k, int ***mat, int *row, int *coll, int index_1, int index_2)
{
	int **matrix1 = mat[index_1];
	int **matrix2 = mat[index_2];
	int m = row[index_1], n = coll[index_1], p = coll[index_2];
	//Alocam memorie pentru matricea in care retinem rezultatul inmultirii.
	int **matrix = allocate_matrix(m, p);
	if (!matrix) {
		free(matrix);
		return 0;
		}
	int i, j, l, pr, sum;
	for (i = 0; i < m; i++) {
		for (j = 0; j < p; j++) {
			sum = 0;
			for (l = 0; l < n; l++) {
				pr = matrix1[i][l] * matrix2[l][j];
				sum += pr;
				sum = sum % NR;
				if (sum < 0)
					sum = sum + NR;
				matrix[i][j] = sum;
			}
		}
	}
	//Retinem valorile noii matrici in vectorii pentru cele doua dimensiuni.
	row[k] = m;
	coll[k] = p;
	return matrix;
}

//Funtie care calculeaza suma unei matrici.
int sum_matrix(int ***mat, int m, int n, int k)
{
	int sum;
	sum = 0;
	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			sum = sum + mat[k][i][j];
			sum = sum % NR;
		}
	if (sum < 0)
		sum = sum + NR;
	return sum;
}

void swap_nr(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

//Functie care sorteaza matricile crescator in functie de suma lor
void case_o(int k, int ***mat, int *row, int *coll)
{
	//Alocam memorie unui vector in care retinem suma pentru fiecare matrice.
	int *sum = (int *)malloc(k * sizeof(int));
	if (!sum)
		return;
	for (int i = 0; i < k; i++) {
		int x = row[i];
		int y = coll[i];
		sum[i] = sum_matrix(mat, x, y, i);
	}
	for (int i = 0; i < k - 1; i++)
		for (int j = i + 1; j < k; j++)
		//Daca matricea dinainte are suma mai mare, se face interschimbarea.
			if (sum[i] > sum[j]) {
				int tmp = sum[i];
				sum[i] = sum[j];
				sum[j] = tmp;

				int **aux = mat[i];
				mat[i] = mat[j];
				mat[j] = aux;

				swap_nr(&row[i], &row[j]);
				swap_nr(&coll[i], &coll[j]);
			}
	free(sum);//Se elibereaza vectorul in care am retinut sumele.
}

//Functie pentru transpusa unei matrici.
void case_t(int k, int ***mat, int *row, int *coll)
{
	int index, m, n, i, j;

	scanf("%d", &index);

	if (!check(index, k)) {
		printf("No matrix with the given index\n");
	} else {
		m = row[index];
		n = coll[index];
		int **tmp = allocate_matrix(n, m);
		//Alocam memorie pentru o matrice auxiliara in care retinem transpusa.
		if (!tmp) {//Verificam daca alocarea s-a efectuat cu succes.
			free(tmp);
			return;
		}
		int **matrix = mat[index];
		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++)
				tmp[i][j] = matrix[j][i];//Construim matricea transpusa.
		free_matrix(mat[index], row[index]);
		mat[index] = tmp;
		swap_nr(&row[index], &coll[index]);
	}
}

//Functie pentru inmultirea a doua matrici, transmise ca paramatrii.
int **multi(int *row, int index, int **mat_1, int **mat_2, int m)
{
	int i, j, l;
	int pr;
	m = row[index];
	//Alocam memorie pentru o matrice patratica.
	int **matrix = allocate_matrix(m, m);
	int **matrix1 = mat_1;
	int **matrix2 = mat_2;
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			matrix[i][j] = 0;
			for (l = 0; l < m; l++) {
				pr = matrix1[i][l] * matrix2[l][j];
				matrix[i][j] += pr;
				matrix[i][j] = matrix[i][j] % NR;
		}
		matrix[i][j] = matrix[i][j] % NR;
		if (matrix[i][j] < 0)
			matrix[i][j] = matrix[i][j] + NR;
		}
	}
		return matrix;
}

//Functie pentru ridicarea la putere a unei matrici.
void case_r(int ***mat, int *row, int *coll, int k)
{
	int index, m, power;
	scanf("%d", &index);
	if (!check(index, k)) {
		printf("No matrix with the given index\n");
		return;
	}
	scanf("%d", &power);

	if (power < 0) {
		printf("Power should be positive\n");
		return;
		}
	if (row[index] != coll[index]) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		m = row[index];
		int i, j;
		//Retinem intr-o matrice auxiliara matricea identica.
		int **tmp = allocate_matrix(m, m);
		if (!tmp) {
			free(tmp);
			return;
		}
		//Retinem intr-o matrice auxiliara matricea identica.
		for (i = 0; i < m; i++)
			for (j = 0; j < m; j++)
				if (i == j)
					tmp[i][j] = 1;
				else
					tmp[i][j] = 0;
		int **matrix1 = mat[index];
		int **aux;
		int **auxi;
		while (power > 0) {
			if (power % 2 == 1) {
		//Daca puterea este impara, se inmulteste matricea cu matricea identica.
				aux = multi(row, index, matrix1, tmp, m);
				free_matrix(tmp, m);
				tmp = aux;
			}
			//Daca puterea este para, inmultim matricea data cu ea insasi.
			auxi = multi(row, index, matrix1, matrix1, m);
			free_matrix(matrix1, m);
			matrix1 = auxi;
			power = power / 2;
		}
		free_matrix(matrix1, row[index]);//Eliberam matricea veche.
		mat[index] = tmp;//Matricei cu indexul dat ii atribuim noua.
	}
}

//Functie pentru eliminarea unei matrici din multime.
void case_f(int ***mat, int *row, int *coll, int k, int index)
{
	int m = row[index], i;
	int aux_row, aux_coll, **aux_mat;
	free_matrix(mat[index], m);//Eliberam matricea cu indexul corespunzator.
	for (i = index; i < k - 1; i++) {
		aux_row = row[i];
		row[i] = row[i + 1];
		row[i + 1] = aux_row;

		aux_coll = coll[i];
		coll[i] = coll[i + 1];
		coll[i + 1] = aux_coll;

		aux_mat = mat[i];
		mat[i] = mat[i + 1];
		mat[i + 1] = aux_mat;
	}
}

//Functia pentru eliberarea tuturor resurselor.
void case_q(int k, int ***mat, int *row, int *coll)
{
	int i;
	for (i = 0; i < k; i++)
		free_matrix(mat[i], row[i]);
	free(row);
	free(coll);
	free(mat);
}

//Functie pentru obtinerea celor 4 blocuri dintr-o matrice data.
void get_the_matrices1(int **matrix1, int **A11, int **A12, int **A21,
					   int **A22, int m)
{
	int i, j;
	for (i = 0; i < m / 2; i++)
		for (j = 0; j < m / 2; j++) {
			A11[i][j] = matrix1[i][j];
			A12[i][j] = matrix1[i][j + m / 2];
			A21[i][j] = matrix1[i + m / 2][j];
			A22[i][j] = matrix1[i + m / 2][j + m / 2];
		}
}

//Functie pentru adunarea matricelor. Rezultatul este salvat in matrix.
void add_matrix(int **matrix1, int **matrix2, int **matrix, int m)
{
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			int sum;
			sum = matrix1[i][j] + matrix2[i][j];
			if (sum >= 0)
				sum = sum % NR;
			else
				sum = sum % NR + NR;
			matrix[i][j] = sum;
		}
	}
}

//Functie pentru scaderea matricelor. Rezultatul este salvat in matrix.
void dif_matrix(int **matrix1, int **matrix2, int **matrix, int m)
{
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			int dif;
			dif = matrix1[i][j] - matrix2[i][j];
			if (dif >= 0)
				dif = dif % NR;
			else
				dif = dif % NR + NR;
			matrix[i][j] = dif;
		}
	}
}

//Functie pentru obtinerea primului bloc din matricea finala.
void getc11(int **C, int **C11, int m)
{
	int i, j;
	for (i = 0; i < m / 2; i++)
		for (j = 0; j < m / 2; j++) {
			C[i][j] = C11[i][j];
			if (C[i][j] >= 0)
				C[i][j] = C[i][j] % NR;
			else
				C[i][j] = C[i][j] % NR + NR;
		}
}

//Functie pentru obtinerea celui de-al doilea bloc din matricea finala.
void getc12(int **C, int **C12, int m)
{
	int i, j;
	for (i = 0; i < m / 2; i++)
		for (j = 0; j < m / 2; j++) {
			if (C12[i][j] >= 0)
				C12[i][j] = C12[i][j] % NR;
			else
				C12[i][j] = C12[i][j] % NR + NR;
			C[i][j + m / 2] = C12[i][j];
		}
}

//Functie pentru obtinerea celui de-al treilea bloc din matricea finala.
void getc21(int **C, int **C21, int m)
{
	int i, j;
	for (i = 0; i < m / 2; i++)
		for (j = 0; j < m / 2; j++) {
			if (C21[i][j] >= 0)
				C21[i][j] = C21[i][j] % NR;
			else
				C21[i][j] = C21[i][j] % NR + NR;
			C[i + m / 2][j] = C21[i][j];
		}
}

//Functie pentru obtinerea celui de-al patrulea bloc din matricea finala.
void getc22(int **C, int **C22, int m)
{
	int i, j;
	for (i = 0; i < m / 2; i++)
		for (j = 0; j < m / 2; j++) {
			if (C22[i][j] >= 0)
				C22[i][j] = C22[i][j] % NR;
			else
				C22[i][j] = C22[i][j] % NR + NR;
			C[i + m / 2][j + m / 2] = C22[i][j];
		}
}

/*Functie care aloca memorie pentru cele 8 blocuri de matrici extrase din
matricile initiale. De asemenea, alocam memorie si pentru matricile
auxliare necesare algortmului Strassen.
*/
void allocate_matrices(int ***A11, int ***A12, int ***A21, int ***A22,
					   int ***B11, int ***B12, int ***B21, int ***B22,
					   int ***P1, int ***P2, int ***P3, int ***P4, int ***P5,
					   int ***P6, int ***P7, int m)
{
	*A11 = allocate_matrix(m / 2, m / 2);
	*A12 = allocate_matrix(m / 2, m / 2);
	*A21 = allocate_matrix(m / 2, m / 2);
	*A22 = allocate_matrix(m / 2, m / 2);
	*B11 = allocate_matrix(m / 2, m / 2);
	*B12 = allocate_matrix(m / 2, m / 2);
	*B21 = allocate_matrix(m / 2, m / 2);
	*B22 = allocate_matrix(m / 2, m / 2);
	*P1 = allocate_matrix(m / 2, m / 2);
	*P2 = allocate_matrix(m / 2, m / 2);
	*P3 = allocate_matrix(m / 2, m / 2);
	*P4 = allocate_matrix(m / 2, m / 2);
	*P5 = allocate_matrix(m / 2, m / 2);
	*P6 = allocate_matrix(m / 2, m / 2);
	*P7 = allocate_matrix(m / 2, m / 2);
}

/*Functie care aloca memorie pentru sumele si diferenele dintre matrici cu
ajutorul carora vom calcula matricile P1, P2, P3, P4, P5, P6, P7.
*/
void allocate_matrices_sum(int ***sum1, int ***sum2, int ***sum3, int ***sum4,
						   int ***sum5, int ***sum6, int ***dif1, int ***dif2,
						   int ***dif3, int ***dif4, int m)
{
	*sum1 = allocate_matrix(m / 2, m / 2);
	*sum2 = allocate_matrix(m / 2, m / 2);
	*sum3 = allocate_matrix(m / 2, m / 2);
	*sum4 = allocate_matrix(m / 2, m / 2);
	*sum5 = allocate_matrix(m / 2, m / 2);
	*sum6 = allocate_matrix(m / 2, m / 2);
	*dif1 = allocate_matrix(m / 2, m / 2);
	*dif2 = allocate_matrix(m / 2, m / 2);
	*dif3 = allocate_matrix(m / 2, m / 2);
	*dif4 = allocate_matrix(m / 2, m / 2);
}

//Functie pentru eliberarea memoriei matricelor alocate.
void free_matrices_sum(int ***sum1, int ***sum2, int ***sum3, int ***sum4,
					   int ***sum5, int ***sum6, int ***dif1, int ***dif2,
					   int ***dif3, int ***dif4, int m)
{
	free_matrix(*sum1, m / 2);
	free_matrix(*sum2, m / 2);
	free_matrix(*sum3, m / 2);
	free_matrix(*sum4, m / 2);
	free_matrix(*sum5, m / 2);
	free_matrix(*sum6, m / 2);
	free_matrix(*dif1, m / 2);
	free_matrix(*dif2, m / 2);
	free_matrix(*dif3, m / 2);
	free_matrix(*dif4, m / 2);
}

//Functie pentru eliberarea memoriei matricelor alocate.
void free_matrices(int ***A11, int ***A12, int ***A21, int ***A22, int ***B11,
				   int ***B12, int ***B21, int ***B22, int ***P1, int ***P2,
				   int ***P3, int ***P4, int ***P5, int ***P6, int ***P7,
				   int ***C11, int ***C12, int ***C21, int ***C22, int m)
{
	free_matrix(*P1, m / 2);
	free_matrix(*P2, m / 2);
	free_matrix(*P3, m / 2);
	free_matrix(*P4, m / 2);
	free_matrix(*P5, m / 2);
	free_matrix(*P6, m / 2);
	free_matrix(*P7, m / 2);
	free_matrix(*A11, m / 2);
	free_matrix(*A12, m / 2);
	free_matrix(*A21, m / 2);
	free_matrix(*A22, m / 2);
	free_matrix(*B11, m / 2);
	free_matrix(*B12, m / 2);
	free_matrix(*B21, m / 2);
	free_matrix(*B22, m / 2);
	free_matrix(*C11, m / 2);
	free_matrix(*C12, m / 2);
	free_matrix(*C21, m / 2);
	free_matrix(*C22, m / 2);
}

/*Se vor calcula cu ajutorul celor 8 blocuri matricile necesare determinarii
rezulatului inmultirii celor doua matrici.
Am determinat fiecare careu din matricea finala, urmand sa determinam in final
forma finala a matricei rezultat.
Am folosit formulele prezentate in documentul atasat temei.
*/
void strassen(int **matrix1, int **matrix2, int **C, int m)
{
	//Cazul cand matricile au un singur element.
	if (m == 1) {
		int nr;
		nr = matrix1[0][0] * matrix2[0][0];
		nr = nr % NR;
		C[0][0] = nr;
		return;
	}
	int **A11,  **A12, **A21, **A22, **B11, **B12, **B21, **B22, **P1, **P2,
	**P3, **P4, **P5, **P6, **P7;

	/*Alocam memorie pentru cele 8 blocuri si pentru matricile necesare
	determinarii matricei finale
	*/
	allocate_matrices(&A11, &A12, &A21, &A22, &B11, &B12, &B21,
					  &B22, &P1, &P2, &P3, &P4, &P5, &P6, &P7, m);

	//Obtinem cele 8 blocuri
	get_the_matrices1(matrix1, A11, A12, A21, A22, m);
	get_the_matrices1(matrix2, B11, B12, B21, B22, m);

	int **sum1, **sum2, **sum3, **sum4, **sum5, **sum6;
	int **dif1, **dif2, **dif3, **dif4;
	allocate_matrices_sum(&sum1, &sum2, &sum3, &sum4, &sum5, &sum6, &dif1,
						  &dif2, &dif3, &dif4, m);

	add_matrix(A11, A22, sum1, m / 2);
	add_matrix(B11, B22, sum2, m / 2);
	strassen(sum1, sum2, P1, m / 2);//P1 = (A11 + A22) * (B11 + B22)

	add_matrix(A21, A22, sum3, m / 2);
	strassen(sum3, B11, P2, m / 2);//P2 = (A21 + A22) * B11

	dif_matrix(B12, B22, dif1, m / 2);
	strassen(A11, dif1, P3, m / 2);	//P3 = A11 * (B12 - B22)

	dif_matrix(B21, B11, dif2, m / 2);
	strassen(A22, dif2, P4, m / 2);	//P4 = A22 * (B21 - B11)

	add_matrix(A11, A12, sum4, m / 2);
	strassen(sum4, B22, P5, m / 2);	//P5 = (A11 + A12) * B22

	dif_matrix(A21, A11, dif3, m / 2);
	add_matrix(B11, B12, sum5, m / 2);
	strassen(dif3, sum5, P6, m / 2);//P6 = (A21 - A11) * (B11 + B12)

	dif_matrix(A12, A22, dif4, m / 2);
	add_matrix(B21, B22, sum6, m / 2);
	strassen(dif4, sum6, P7, m / 2);//P7 = (A12 - A22) * (B21 + B22)

	int **C11 = allocate_matrix(m / 2, m / 2);
	//C11 = P1 + P4 - P5 + P6
	add_matrix(P1, P4, C11, m / 2);
	dif_matrix(C11, P5, C11, m / 2);
	add_matrix(C11, P7, C11, m / 2);
	getc11(C, C11, m);

	int **C12 = allocate_matrix(m / 2, m / 2);
	//C12 = P3 + P5
	add_matrix(P3, P5, C12, m / 2);
	getc12(C, C12, m);

	int **C21 = allocate_matrix(m / 2, m / 2);
	//C21 = P2 + P4
	add_matrix(P2, P4, C21, m / 2);
	getc21(C, C21, m);

	int **C22 = allocate_matrix(m / 2, m / 2);
	//C22 = P1 - P2 + P3 + P6
	dif_matrix(P1, P2, C22, m / 2);
	add_matrix(C22, P3, C22, m / 2);
	add_matrix(C22, P6, C22, m / 2);
	getc22(C, C22, m);

	free_matrices_sum(&sum1, &sum2, &sum3, &sum4, &sum5, &sum6, &dif1, &dif2,
					  &dif3, &dif4, m);

	free_matrices(&A11, &A12, &A21, &A22, &B11, &B12, &B21, &B22, &P1, &P2,
				  &P3, &P4, &P5, &P6, &P7, &C11, &C12, &C21, &C22, m);
}

int main(void)
{
	int k = 0, m, n, index_1, index_2, index, *row, *coll, ***mat;
	row = NULL, coll = NULL, mat = NULL;
	while (1) {
		char c;
		scanf(" %c", &c);//Se verifica daca caracterul dat are o comanda.
		if (strchr("LDPCMOTRFQS", c)) {
			if (c == 'L') {//Realocam memorie pentru matrici si pentru vectori.
				mat = (int ***)realloc(mat, (k + 1) * sizeof(int **));
				row = (int *)realloc(row, (k + 1) * sizeof(int));
				coll = (int *)realloc(coll, (k + 1) * sizeof(int));
				scanf("%d%d", &m, &n);
				mat[k] = allocate_matrix(m, n);
				for (int i = 0; i < m; i++)
					for (int j = 0; j < n; j++)
						scanf("%d", &mat[k][i][j]);
				row[k] = m, coll[k] = n;
				k++;
			} else if (c == 'D') {
				case_d(k, row, coll);
			} else if (c == 'P') {
				case_p(k, mat, row, coll);
			} else if (c == 'C') {
				case_c(k, mat, row, coll);
			} else if (c == 'M') {
				scanf("%d %d", &index_1, &index_2);
				if (!check(index_1, k) || !check(index_2, k)) {
					printf("No matrix with the given index\n");
				} else {
					if (coll[index_1] != row[index_2]) {
						printf("Cannot perform matrix multiplication\n");
				} else {//Adaugam rezultatul inmultirii la finalul colectiei.
					mat = (int ***)realloc(mat, (k + 1) * sizeof(int **));
					row = (int *)realloc(row, (k + 1) * sizeof(int));
					coll = (int *)realloc(coll, (k + 1) * sizeof(int));
					mat[k] = case_m(k, mat, row, coll, index_1, index_2);
					k = k + 1; }
				}
			} else if (c == 'T') {
				case_t(k, mat, row, coll);
			} else if (c == 'O') {
				case_o(k, mat, row, coll);
			} else if (c == 'Q') {
				case_q(k, mat, row, coll);
				break;
			} else if (c == 'F') {
				scanf("%d", &index);
				if (!check(index, k)) {
					printf("No matrix with the given index\n");
				} else { //Eliminam matricea din multime.
					case_f(mat, row, coll, k, index);
					k = k - 1; }
				} else if (c == 'R') {
					case_r(mat, row, coll, k);
				} else if (c == 'S') {
					scanf("%d %d", &index_1, &index_2);
				if (!check(index_1, k) || !check(index_2, k)) {
					printf("No matrix with the given index\n");
				} else {
					if (coll[index_1] != row[index_2]) {
						printf("Cannot perform matrix multiplication\n");
				} else {//Adaugam rezultatul inmultirii la finalul colectiei.
					mat = (int ***)realloc(mat, (k + 1) * sizeof(int **));
					row = (int *)realloc(row, (k + 1) * sizeof(int));
					coll = (int *)realloc(coll, (k + 1) * sizeof(int));
					int m, **mat1, **mat2;
					m = row[index_1], mat1 = mat[index_1], mat2 = mat[index_2];
					int **matrix = allocate_matrix(m, m);
					row[k] = m, coll[k] = m;
					strassen(mat1, mat2, matrix, m);
					mat[k] = matrix, k = k + 1; }
				}
				}
		} else {
			if (c >= 'A' && c <= 'Z')
				printf("Unrecognized command\n");
		}
	}

	return 0;
}

