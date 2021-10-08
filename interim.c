/* Intersection 'n Image
    input : t1, t2 trans (homogeneous)
            P1, P2 polyhedron
    output : polyhedron intersection ( t1 P1 , t2 P2 )
*/

#include <stdio.h>
/*
#include "types.h"
#include "vector.h"
#include "polyhedron.h"
#include "polyparam.h"
*/
#include <polylib/polylib64.h>

int main()
{
    Matrix *b, *t1, *t2;
    Polyhedron *D1, *D2;

    t1 = Matrix_Read();
    t2 = Matrix_Read();

    b = Matrix_Read();
    D1 = Constraints2Polyhedron(b, 200);
    Matrix_Free(b);
    b = Matrix_Read();
    D2 = Constraints2Polyhedron(b, 200);
    Matrix_Free(b);

	Polyhedron_Print( stdout, " %3d",
DomainIntersection( Polyhedron_Image(D1,t1,200),Polyhedron_Image(D2,t2,200), 200
	                     ) );

    Domain_Free(D1);
    Domain_Free(D2);

    return 0;
}


