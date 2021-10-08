#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <polylib/polylib64.h>

// don't generate strings larger than this or you'll corrupt your memory -
// fast and dirty :(
#define MAXLEN 2048

#define EOS(s) ((s)+strlen(s))

static int writeOneSideDomain(Polyhedron *D, int i, char *t, int s, int nbparam)
{
	int premier, j;

	premier = 1;
	for( j=0 ; j<D->Dimension ; ++j )
	{	if( D->Constraint[i][1+j] != 0 && s*D->Constraint[i][1+j] > 0 )
		{
			if( !premier )
				strcat( t, "+" );
			else
				premier = 0;
			if( s*D->Constraint[i][1+j] != 1 )
				sprintf( EOS(t), P_VALUE_FMT, s*D->Constraint[i][1+j] );

			if( j>=D->Dimension-nbparam )
			{	/*param*/
				sprintf( EOS(t), "%c", 'N'+j-D->Dimension+nbparam );
			}
			else
				sprintf( EOS(t), "%c", 'i'+j );
		}
	}
	return( premier );
}
/* affiche un domaine (parametre) */
/* nbparam : nombre de parametres */
char *Polyhedron2Ascii( Polyhedron *D, int nbparam )
{
	static char wDchn[MAXLEN];
	int i, p;

	strcpy( wDchn, "  { " );
	for( i=0 ; i<D->NbConstraints ; ++i )
	{
		int j, s;

		/* s = sens de l'inegalite >= ou <= */
		s = 1;
		for( j=0 ; j<D->Dimension ; ++j )
		{	if( D->Constraint[i][1+j] )
		{	if( D->Constraint[i][1+j]<0 )
			s = -1;
			break;		/* on s'arrete au premier !=0 rencontre */
		}
		}
		if( j==D->Dimension && D->Constraint[i][1+j]==1 && D->Constraint[i][0]==1)
			continue;
		/* c'est la positivity constraint... on ne l'affiche pas */

		if( i>0 )
			strcat( wDchn, ", " );

		/* affichage */
		/* terme gauche */
		if( writeOneSideDomain(D, i, wDchn, s, nbparam) )
			strcat( wDchn, "0" );

		/* operateur */
		if( D->Constraint[i][0] )
		{	/* inegalite dans le sens de s */
			if( s>0 )
				strcat( wDchn, " >= " );
			else
				strcat( wDchn, " <= " );
		}
		else
			/* egalite */
			strcat( wDchn, " = " );


		/* terme droit + constante */
		if( (p=writeOneSideDomain(D, i, wDchn, -s, nbparam)) ||
					D->Constraint[i][1+D->Dimension]!=0 )
		{
			if( s*D->Constraint[i][1+D->Dimension]>0 )
				strcat( wDchn, "-" );
			else if( !p )
				strcat( wDchn, "+" );
			sprintf( EOS(wDchn), "%d", abs(D->Constraint[i][1+D->Dimension]) );
		}
	}
	strcat( wDchn, " }" );
	return( wDchn );
}


static int writeOneSideDomainNM(Polyhedron *D, int i, char *t, int s, char **names)
{
	int premier, j;

	premier = 1;
	for( j=0 ; j<D->Dimension ; ++j )
	{
		if( D->Constraint[i][1+j] != 0 && s*D->Constraint[i][1+j] > 0 )
		{
			if( !premier )
				strcat( t, "+" );
			else
				premier = 0;
			if( s*D->Constraint[i][1+j] != 1 )
				sprintf( EOS(t), P_VALUE_FMT, s*D->Constraint[i][1+j] );
			sprintf( EOS(t), "%s", names[j] );
		}
	}
	return( premier );
}
/* pretty prints a domain (parametric) */
/* names = parameter names */
char *Polyhedron2AsciiNamed( Polyhedron *D, char **names )
{
	static char wDchn[MAXLEN];
	int i, p;

	strcpy( wDchn, "  { " );
	for( i=0 ; i<D->NbConstraints ; ++i )
	{
		int j, s;

		/* s = sens de l'inegalite >= ou <= */
		s = 1;
		for( j=0 ; j<D->Dimension ; ++j )
		{	if( D->Constraint[i][1+j] )
		{	if( D->Constraint[i][1+j]<0 )
			s = -1;
			break;		/* on s'arrete au premier !=0 rencontre */
		}
		}
		if( j==D->Dimension && D->Constraint[i][1+j]==1 && D->Constraint[i][0]==1)
			continue;
		/* c'est la positivity constraint... on ne l'affiche pas */

		if( i>0 )
			strcat( wDchn, ", " );

		/* affichage */
		/* terme gauche */
		if( writeOneSideDomainNM(D, i, wDchn, s, names) )
			strcat( wDchn, "0" );

		/* operateur */
		if( D->Constraint[i][0] )
		{	/* inegalite dans le sens de s */
			if( s>0 )
				strcat( wDchn, " >= " );
			else
				strcat( wDchn, " <= " );
		}
		else
			/* egalite */
			strcat( wDchn, " = " );


		/* terme droit + constante */
		if( (p=writeOneSideDomainNM(D, i, wDchn, -s, names)) ||
					D->Constraint[i][1+D->Dimension]!=0 )
		{
			if( s*D->Constraint[i][1+D->Dimension]>0 )
				strcat( wDchn, "-" );
			else if( !p )
				strcat( wDchn, "+" );
			sprintf( EOS(wDchn), "%d", abs(D->Constraint[i][1+D->Dimension]) );
		}
	}
	strcat( wDchn, " }" );
	return( wDchn );
}
