/* Image by an affine function + scanning loop (lexicographic)
    input : t transformation matrix
            P polyhedron
            C Context
	output : loop scanning t P over the context C
*/

#include <stdio.h>
#include <polylib/polylib64.h>
#include "wd.h"

#define WS 1000

int main()
{
	Matrix *t;
	Matrix *b, *con;
	Polyhedron *Dt, *D, *Con, *s;
	const char **param_name;

	t = Matrix_Read();

	b = Matrix_Read();
	D = Constraints2Polyhedron(b, WS);
	Matrix_Free(b);

	con = Matrix_Read();
	Con = Constraints2Polyhedron(con, WS);
	Matrix_Free(con);

	param_name = Read_ParamNames(stdin,D->Dimension);

	Dt = Polyhedron_Image( D, t, WS );

	printf("\nt . P = ");
	Matrix_Print( stdout, "%4ld ", Polyhedron2Constraints(Dt));

	printf( "SCAN :\n" );
	s = Polyhedron_Scan( Dt, Con, WS );

	for( ; s ; s=s->next )
		printf( "%s\n", Polyhedron2AsciiNamed( s, param_name ) );


	Domain_Free(D);
	Domain_Free(Con);

	return 0;
}
