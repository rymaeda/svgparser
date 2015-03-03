#ifndef SVG_PARSER
#define SVG_PARSER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define SVG_MAXPOLY 100 /* max number of polygonals */

typedef struct Coord{
	double x;
	double y;
} SVG_TCOORD;

typedef struct svgsegment{
	SVG_TCOORD pt1;
	SVG_TCOORD pt2;
} SVG_SEGMENT;

typedef struct svgpolygon{
	SVG_TCOORD *coords;
	int n_pts;
	double area;
	char flags;
} SVG_POLYGON;

#include "geometric.h"

SVG_TCOORD* svg_polymalloc(char *str, SVG_POLYGON *polygon);

SVG_TCOORD* svg_polymalloc2(int n_pts, SVG_POLYGON *polygon);

void svg_polyfree(SVG_POLYGON *polygon);

int svg_polyparser(char *str, SVG_POLYGON *polygon);

#endif
