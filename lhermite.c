/* LEFT HERMITE */
/* input : a matrix M */
/* output : H, U and Q such that : M = H Q and H = M U */

#include <stdio.h>
#include <polylib/polylib64.h>


int main()
{
	Matrix *A, *H, *U, *Q;

	A = Matrix_Read();

	left_hermite(A, &H, &U, &Q);

	printf( "H = ");
	Matrix_Print( stdout, "%3d ", H );
	printf( "U = ");
	Matrix_Print( stdout, "%3d ", U );
	printf( "Q = ");
	Matrix_Print( stdout, "%3d ", Q );

	return 0;
}
