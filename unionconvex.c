#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <polylib/polylib.h>


void Union_Read( Polyhedron **P, Polyhedron **C, char ***param_name )
{
	Matrix *pm;
	Polyhedron *ptmp;
	unsigned NbRows, NbColumns;
	char s[1025], param[1025];
	int i, j, c, f;

	*P = NULL;
	pm = Matrix_Read();
	f=1;
	while( f )
	{
		do
		{
			if( fgets(s, 1024, stdin) == 0  )
				f=0;
		}
		while ( (*s=='#' || *s=='\n') && f );

		if( f && sscanf(s, "%d %d", &NbRows, &NbColumns)==2 )
		{
			/* gets old pm and add it to the union */
			if( *P )
				if( pm->NbColumns != ((*P)->Dimension)+2 )
				{
					fprintf( stderr,
						"Polyhedra must be in the same dimension space !\n");
					exit(0);
				}
			ptmp = Constraints2Polyhedron(pm, 200);
			ptmp->next = *P;
			*P = ptmp;
			Matrix_Free(pm);

			/* reads the new pm */
			pm = Matrix_Alloc(NbRows, NbColumns);
			Matrix_Read_Input( pm );
		}
		else
			break;
	}

	/* Context : last read pm */
	*C = Constraints2Polyhedron(pm, 200);
	Matrix_Free(pm);


	if( f )
	{
		/* read the parameter names */
		*param_name = (char **)malloc( (*C)->Dimension*sizeof(char *) );
		c = 0;
		for( i=0 ; i<(*C)->Dimension ; ++i )
		{
			j=0;
			for( ; ; ++c )
			{
				if( s[c]==' ' || s[c]=='\n' || s[c]==0 ) {
					if( j==0 )
						continue;
					else
						break;
				}
				param[j++] = s[c];
			}

			/* else, no parameters (use default) */
			if( j==0 )
				break;
			param[j] = 0;
			(*param_name)[i] = (char *)malloc( j );
			strcpy( (*param_name)[i], param );
		}
		if( i != (*C)->Dimension )
		{
			free( *param_name );
			*param_name = Read_ParamNames(NULL,(*C)->Dimension);
		}
	}
	else
		*param_name = Read_ParamNames(NULL,(*C)->Dimension);

}



int main( int argc, char **argv)
{
	Polyhedron *P, *C;
	char **param_name;
	Polyhedron *D, *dif;
	Polyhedron *d;

	if( argc != 1 )
	{
		fprintf( stderr, " Usage : %s [< file]\n", argv[0] );
		return( -1 );
	}

	Union_Read( &P, &C, &param_name );

	D = DomainConvex( P, 1000 );
	printf( "convex :\n");
	Matrix_Print( stdout, "%6ld", Polyhedron2Constraints(D) );

	dif = DomainDifference( D, P, 1000 );
	printf( "Diff :\n");
	PolyPrint( dif);
	printf( "\nConstraints :\n");
	for( d=dif ; d ; d=d->next )
		Matrix_Print( stdout, "%5ld ", Polyhedron2Constraints(d) );


	return( 0 );
}



