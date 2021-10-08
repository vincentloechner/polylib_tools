
#include <polylib/polylib64.h>

/* #define DEBUG_LH	*/	/* prints some debug information in LinearHull */
/* #define TEST_LH	*/	/* generates a main to test the function */

/***********************************************************/
/* Compute the linear hull of a parameterized polyhedron P */
/* with NbParam parameters                                 */
/* returns a polyhedron of dimension:                      */
/*   (dim(P)-NbParam) x dim(lin.hull)                      */
/***********************************************************/
/* Vin100, Feb. 2001                                       */
/***********************************************************/
Polyhedron *LinearHull( Polyhedron *P, int NbParam, int MaxRays )
{
	int r, i, j, d, r1;
	Matrix *M;
	Polyhedron *P1;

#ifdef DEBUG_LH
	fprintf( stderr, "\nEntering LinearHull: NbParam=%d\nP = ", NbParam);
	Polyhedron_Print( stderr, P_VALUE_FMT, P );
#endif
	/*** step 1 : compute the linear hull of P ***/
	/* add bid. lines for each uni. or vertex ray */
	d = P->Dimension;
	M = Matrix_Alloc( P->NbRays, d+2 );
	M->NbRows = 0;
	r1 = -1;
	for( r=0 ; r<P->NbRays ; r++ )
	{
		if( value_notzero_p(P->Ray[r][0]) )
		{	/* it's a unidirectional ray or a vertex */
			if( value_notzero_p(P->Ray[r][d+1]) )
			{	/* it's a vertex */
				if( r1 == -1 )
					/* it's the first vertex */
					r1 = r;
				else
				{	/* add the bid.: difference between the two vertices */
					value_assign( M->p[M->NbRows][0], VALUE_ZERO );
					for( i=1 ; i<=d ; i++ )
						value_assign( M->p[M->NbRows][i],
						    value_minus( value_mult(P->Ray[r1][i],P->Ray[r][d+1] ),
						             value_mult(P->Ray[r][i],P->Ray[r1][d+1] ) ) );
					value_assign( M->p[M->NbRows][d+1], VALUE_ZERO );
					M->NbRows++;
				}
			}
			else
			{
				value_assign( M->p[M->NbRows][0], VALUE_ZERO );
				for( i=1 ; i<=d ; i++ )
					value_assign( M->p[M->NbRows][i], P->Ray[r][i] );
				value_assign( M->p[M->NbRows][d+1], VALUE_ZERO );
				M->NbRows++;
			}
		}
	}
	if( M->NbRows )
	{
		P1 = DomainAddRays( P, M, MaxRays );
		Polyhedron_Free( P );
		P = P1;
	}
#ifdef DEBUG_LH
	fprintf( stderr, "\nVertices and unidirectional rays suppressed: P = ");
	Polyhedron_Print( stderr, P_VALUE_FMT, P );
#endif
	/*** step 2 : intersect the linear hull of P with the index space ***/
	/* all parameters = 0 */
	Matrix_Free( M );
	M = Matrix_Alloc (NbParam, d + 2);
	for( i=0 ; i<NbParam ; i++ )
	{
		for( j=0 ; j<d+2 ; j++ )
			value_assign( M->p[i][j], VALUE_ZERO );
		value_assign( M->p[i][d-NbParam+1+i], VALUE_ONE );
	}
	P1 = DomainAddConstraints( P, M, MaxRays );
	Polyhedron_Free( P );
	P = P1;
	Matrix_Free( M );
	/* P has one vertex and some bid. rays */
#ifdef DEBUG_LH
	fprintf( stderr, "\nResulting bid.: P = ");
	Polyhedron_Print( stderr, P_VALUE_FMT, P );
#endif

	return( P );
}

#ifdef TEST_LH
#define MAXRAYS 100
int main()
{
	Matrix *C;
	Polyhedron *P, *LH;
	int nbp;

	C = Matrix_Read();
	P = Constraints2Polyhedron( C, MAXRAYS );
	Matrix_Free( C );

	scanf( "%d", &nbp );

	LH = LinearHull( P, nbp, MAXRAYS );
	Polyhedron_Print( stdout, P_VALUE_FMT, LH );

	return( 0 );
}
#endif

