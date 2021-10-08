/*       Rays 2 Polyhedron
*/

#include <stdio.h>
#include <polylib/polylib64.h>

int main()
{
	Matrix *R;
	Polyhedron *P1, *P2, *U, *C;

	R = Matrix_Read();
	if( R->NbColumns < 2 )
	{
		printf( "Wrong input: %d columns\n", R->NbColumns );
		Matrix_Free(R);
		exit( 1 );
	}
	P1 = Rays2Polyhedron(R, 200);
	R = Matrix_Read();
	if( R->NbColumns < 2 )
	{
		printf( "Wrong input: %d columns\n", R->NbColumns );
		Matrix_Free(R);
		exit( 1 );
	}
	P2 = Rays2Polyhedron(R, 200);
	Matrix_Free(R);

/*	Polyhedron_Print( stdout, P_VALUE_FMT, P1 );
	Polyhedron_Print( stdout, P_VALUE_FMT, P2 );
*/
	U = DomainUnion(P1, P2, 200);
	printf( "Union = ");
	Polyhedron_Print( stdout, P_VALUE_FMT, U );
	C = DomainConvex( U, 200 );
	Polyhedron_Print( stdout, P_VALUE_FMT, C );

	return 0;
}
