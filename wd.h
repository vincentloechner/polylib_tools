
/* wd.h : writedomain */

/* not MT safe */
extern char *Polyhedron2Ascii( Polyhedron *D, int nbparam );

extern char *Polyhedron2AsciiNamed( Polyhedron *D, const char **names );
