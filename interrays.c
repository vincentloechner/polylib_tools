/* Intersection of two polyhedra, input as rays
    input : P1, P2 polyhedron (rays matrices)
    output : polyhedron intersection ( P1 . P2 )
*/

#include <stdio.h>
#include <polylib/polylib64.h>

int main()
{
    Matrix *t1, *t2;
    Polyhedron *D1, *D2, *I;

    t1 = Matrix_Read();
    D1 = Rays2Polyhedron(t1, 200);
    Matrix_Free(t1);
    t2 = Matrix_Read();
    D2 = Rays2Polyhedron(t2, 200);
    Matrix_Free(t2);

    I = DomainIntersection( D1, D2, 200 );
    Domain_Free(D1);
    Domain_Free(D2);

    Polyhedron_Print( stdout, P_VALUE_FMT, I );

    Domain_Free(I);
    return 0;
}


