/* Image by an affine function + scanning loop (lexicographic)
    input : t transformation matrix
            P polyhedron
            C Context
	output : loop scanning t P over the context C
*/

#include <stdio.h>
#include <polylib/polylib64.h>

int main()
{
	Matrix *t;
	Matrix *b, *con;
	Polyhedron *Dt, *D, *Con;

	t = Matrix_Read();

	b = Matrix_Read();
	D = Constraints2Polyhedron(b, 200);
	Matrix_Free(b);

	con = Matrix_Read();
	Con = Constraints2Polyhedron(con, 200);
	Matrix_Free(con);

	Dt = Polyhedron_Preimage( D, t, 200 );

	printf("\nt . P = ");
	Matrix_Print( stdout, "%4d ", Polyhedron2Constraints(Dt));

	printf( "SCAN : " );
	Polyhedron_Print( stdout, "%4d ", Polyhedron_Scan( Dt, Con, 200 ) );

	Domain_Free(D);
	Domain_Free(Con);

	return 0;
}


