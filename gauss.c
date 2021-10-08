
#include <stdio.h>
#include <stdlib.h>
#include <polylib/polylib64.h>

int main()
{
	Matrix *m;

	m = Matrix_Read();

	printf( "rank = %d\n", Gauss ( m, m->NbRows, m->NbColumns ) );

	Matrix_Print( stdout, "%3d ", m );

	return 0;
}
