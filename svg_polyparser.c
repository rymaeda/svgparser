/*------------------------------------------------------------------------
 Module:        c:\users\ricardo\documents\lcc\xmlparser\svg_polyparser.c
 Author:        ricardo
 Project:       xml-svg-parser
 State:         Version 0.03
 Creation Date: 30-jan-2015
 Revisions:		12-feb-2015 allocate memory, changed interface
 				17-feb-2015 incorporated pointer to structs to polygons
				18-feb-2015 bug fixes, improved "d" field parsing.
				23-feb-2015 sintax improvements.
 Description:   Parse "path" string of SVG Inkscape format and read and
 				store coordenates in one matrix of structs.
 Todo:			prevent double spaces/letter problems and miriad of
 				others errors checking.
------------------------------------------------------------------------*/

#include "svg_polyparser.h"

static int g_index; /* index of scanned string */
static int g_len; /* lengh of string */

/*------------------------------------------------------------------------
 Procedure:     svg_polytest ID:1
 Purpose:       Count how many coords points there are
 				in string.
 Input:         Pointer to string
 Output:        How many points has the string
 Errors:
------------------------------------------------------------------------*/
int svg_polyinit(char *str){
	int i, c;
	int ff; /* flip-flop */
	ff= 1;
	c= 0;
	g_len= strlen(str);
	for(i=0; i<g_len; ){
		while((isdigit(str[i])||str[i]=='.'||str[i]=='-')&&(i<g_len)){
			if (ff){
				c++;
				ff= 0;
			}
			i++;
		}
		while(!(isdigit(str[i])||str[i]=='.'||str[i]=='-')&&(i<g_len)){
			if (!ff)
				ff= 1;
			i++;
		}
	}
	return (c-2)/2; /* discount of last point (sentilnel) */
}

/*------------------------------------------------------------------------
 Procedure:     svg_polymalloc ID:1
 Purpose:       Allocate memory to points of current
                polygonal.
 Input:         SVG "d" path string and SVG_POLYGON
                struct.
 Output:        SVG_POLYGON with number of poins filled
                and memory allocated.
 Errors:        none yet.
------------------------------------------------------------------------*/
SVG_TCOORD* svg_polymalloc(char *str, SVG_POLYGON *polygon){
	polygon->n_pts= svg_polyinit(str);
	return (SVG_TCOORD*)malloc( sizeof(SVG_TCOORD) * polygon->n_pts );
}

SVG_TCOORD* svg_polymalloc2(int n_pts, SVG_POLYGON *polygon){
	return (SVG_TCOORD*)malloc( sizeof(SVG_TCOORD) * n_pts );
}


/*------------------------------------------------------------------------
 Procedure:     svg_polymalloc ID:1
 Purpose:       Deallocate memory to points of one polygonal.
 Input:         Pointer to SVG_POLYGON struct.
 Output:        Free memory.
 Errors:        none yet.
------------------------------------------------------------------------*/
void svg_polyfree(SVG_POLYGON *polygon){
	free( polygon->coords );
}

/*------------------------------------------------------------------------
 Procedure:     svg_getf ID:1
 Purpose:       Search for floating point number in string.
 Input:         Pointer to string.
 Output:        Conversion of pointed number in string to double,
 				modification in strig with apended zero (i.e. end
				of string) for each floting point number founded.
 Errors:
------------------------------------------------------------------------*/
double svg_getf(char * str){
	int s, e, i;
	char tmp[32];

	s= g_index;
	while(!(isdigit(str[s])||str[s]=='.'||str[s]=='-')&&(s<g_len))
		s++;
	e= s;
	i=0;
	while(isdigit(str[e])||str[e]=='.'||str[e]=='-')
		tmp[i++]= str[e++];
	tmp[i]= 0;
	g_index= e+1;
	return atof(tmp);
}


/*------------------------------------------------------------------------
 Procedure:     svg_polyparser ID:1
 Purpose:       Extract coordinates point from svg path,
                stored in string to matrix.
 Input:         Pointer to string and pointer to structure
 				with number of points and pointer to matrix.
 Output:        Matrix populated with coordinates
 Errors:
------------------------------------------------------------------------*/
int svg_polyparser(char *str, SVG_POLYGON *polygon){
	int i;

	g_index= 0; /* g_index are incremented after each call to svg_getf() */
	g_len= strlen(str);
	for (i= 0; i<polygon->n_pts; i++){
		polygon->coords[i].x= svg_getf( str );
		polygon->coords[i].y= svg_getf( str );
	}
	polygon->area= geo_area(polygon);
	return 0;
}
