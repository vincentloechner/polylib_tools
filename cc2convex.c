/*       Constraints + Constraints 2 Convex Polyhedron
*/

/*
alain's example :
4 4
1 0 1 -1
1 -1 0 10
1 0 -1 10
1 1 0 0
4 4
1 1 0 -1
1 -1 0 10
1 0 -1 0
1 0 1 10
*/

#include <stdio.h>
#include <polylib/polylib64.h>

int main()
{
	Matrix *c, *Rays;
	Polyhedron *P1, *P2, *U, *C;

	c = Matrix_Read();
	if( c->NbColumns < 2 )
	{
		printf( "Wrong input: %d columns\n", c->NbColumns );
		Matrix_Free(c);
		exit( 1 );
	}
	P1 = Constraints2Polyhedron(c, 200);
	c = Matrix_Read();
	if( c->NbColumns < 2 )
	{
		printf( "Wrong input: %d columns\n", c->NbColumns );
		Matrix_Free(c);
		exit( 1 );
	}
	P2 = Constraints2Polyhedron(c, 200);
	Matrix_Free(c);

	Polyhedron_Print( stdout, P_VALUE_FMT, P1 );
	Polyhedron_Print( stdout, P_VALUE_FMT, P2 );

/*	U = DomainUnion(P1, P2, 200);
	printf( "Union = ");
	Polyhedron_Print( stdout, P_VALUE_FMT, U );
	C = DomainConvex( U, 200 );
*/
	Rays = Matrix_Alloc( P1->NbRays + P2->NbRays, P1->Dimension+2 );
	Vector_Copy( P1->Ray[0], Rays->p[0], P1->NbRays*(P1->Dimension+2) );
	Vector_Copy( P2->Ray[0], Rays->p[P1->NbRays], P2->NbRays*(P1->Dimension+2) );

	Matrix_Print( stdout, P_VALUE_FMT, Rays );
	C = Rays2Polyhedron( Rays, 200 );

	Polyhedron_Print( stdout, P_VALUE_FMT, C );

	return 0;
}
