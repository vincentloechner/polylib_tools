
#include <stdio.h>
#include <polylib/polylib64.h>

int main()
{
	Matrix *M1, *M2;

	M1 = Matrix_Read();
	M2 = Matrix_Alloc( M1->NbRows, M1->NbColumns+1 );

	MatInverse( M1, M2 );

	Matrix_Print( stdout, P_VALUE_FMT, M2 );

	return( 0 );
}

