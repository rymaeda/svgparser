
#include "geometric.h"

/*------------------------------------------------------------------------
 Procedure:     geo_area ID:1
 Purpose:       Calculate the area in polygonal.
 Input:         Polygonal points.
 Output:        The enclosed area. can be negative
 				if polygonal are in anticlockwise
				manner.
 Errors:
------------------------------------------------------------------------*/
double geo_area(SVG_POLYGON* polygon){
	int i;
	double area= 0;


	for (i=0; i<(polygon->n_pts-1); i++)
		/* Calculating the area under each segment (trapezoidal area formulae) */
		area+= (polygon->coords[i+1].x-polygon->coords[i].x)*(polygon->coords[i+1].y+polygon->coords[i].y)/2;

	/* Closing the poly (calculating the area under the segment between the last and the first points) */
	area+= (polygon->coords[0].x-polygon->coords[polygon->n_pts-1].x)*(polygon->coords[0].y+polygon->coords[polygon->n_pts-1].y)/2;

	/* Area can be negative when the polyline area is calculated in anticlockwise order */
	/*area= (area>0?area:-area);*/

	/* It's all folks! */
	return area;
}

/*------------------------------------------------------------------------
 Procedure:     geo_parallel ID:1
 Purpose:       Calculate one parallel segment apart of
                'distance' from input segment.
 Input:         Input segment and distance. Distance can
                be negative.
 Output:        The two coordinate points of the segment.
 Errors:
------------------------------------------------------------------------*/
int geo_parallel(SVG_SEGMENT *s1, SVG_SEGMENT *s2, double distance)
{
	double cI, cJ, cI2, cJ2, hipo; /* coeficients for vectorial */
	cI= s1->pt2.y - s1->pt1.y;
	cJ= s1->pt1.x - s1->pt2.x;
	hipo= sqrt(cI * cI + cJ * cJ);
	cI2= cI / hipo;
	cJ2= cJ / hipo;
	s2->pt1.x= s1->pt1.x - cI2 * distance;
	s2->pt1.y= s1->pt1.y - cJ2 * distance;
	s2->pt2.x= s2->pt1.x - cJ;
	s2->pt2.y= s2->pt1.y + cI;
	return 0;
}

/*
**	NO FUNCTIONAL
**	WORK IN PROGRESS HERE!!!!
*/

double geo_parallelpoly(SVG_POLYGON* polygon, SVG_POLYGON* parapoly, double distance){
	int i, j;
	SVG_TCOORD pti;
	SVG_SEGMENT s1, s2, saux;
	//SVG_TCOORD* svg_polymalloc2(int n_pts, SVG_POLYGON *polygon){
	for (i=0; i<(polygon->n_pts-2); i+=2){
		j= 0;
		saux.pt1.x= polygon->coords[i+j].x;
		saux.pt1.y= polygon->coords[i+j].y;
		saux.pt2.x= polygon->coords[i+j+1].x;
		saux.pt2.y= polygon->coords[i+j+1].y;
		geo_parallel(&saux, &s1, distance);/* calculate parallel segment s1' */
		saux.pt1.x= polygon->coords[i+j+1].x;
		saux.pt1.y= polygon->coords[i+j+1].y;
		saux.pt2.x= polygon->coords[i+j+2].x;
		saux.pt2.y= polygon->coords[i+j+2].y;
		geo_parallel(&saux, &s2, distance);/* calculate parallel segment s2' */
		geo_intersec( &s1, &s2, &pti);/* calculate interseccion s1' and s2' */
		parapoly->coords[i].x= pti.x;/* store insterseccion in parallel polygone vector */
		parapoly->coords[i].y= pti.y;
	}
	parapoly->n_pts= i+1;
	return 0.0;
}


/*------------------------------------------------------------------------
 Procedure:     geo_intersec ID:1
 Purpose:       Test if segments s1 and s2
                has intersection point between segments
                extreme points.
 Input:         s1 and s2
 Output:        -1: s1 and s2 are parallel or quasi-
                parallels
                1: s1 and s2 have one interseccion between
                extreme points
                0: s1 and s2 dont intersect between
                extreme points.
                In last two returns the pti will store
                the coordenate of intesection point.
 Errors:        todo
------------------------------------------------------------------------*/
int geo_intersec(SVG_SEGMENT *s1, SVG_SEGMENT *s2, SVG_TCOORD *pti)
{
	double A1, A2, A3, A4;
	double B1, B2;
	double ParamSeg1, ParamSeg2;
	double epsilon;

	A1= s1->pt2.x - s1->pt1.x; /* intermediate coeficients */
	A2= s2->pt2.x - s2->pt1.x; /* just to clean the mess */
	A4= s2->pt2.y - s2->pt1.y;
	A3= s1->pt2.y - s1->pt1.y;
	epsilon= A1 * A4 - A2 * A3;
	/*	'epsilon' will be zero always than the two tested segments was parallel
		The next 'if' will return -1 always than the two tested segments was quasi
		-parallel or parallel. Epsilon will can be zero if the two segments was
		overlapped, particular case of parallelism, where there are infinites
		commom points. So be carefull to deal with this return values.*/
	if (fabs(epsilon)<=0.02)
		return -1;
	B1= s2->pt1.x - s1->pt1.x;
	B2= s2->pt1.y - s1->pt1.y;
	ParamSeg1= (A4 * B1 - A2 * B2) / epsilon;
	ParamSeg2= (B1 * A3 - A1 * B2) / epsilon;
	pti->x= s1->pt1.x + ParamSeg1 * A1; /* interseccion x coord */
	pti->y= s1->pt1.y + ParamSeg1 * A3; /* interseccion y coord */
	if ((0.0<=ParamSeg1)&&(ParamSeg1<=1.0)&&(0.0<=ParamSeg2)&&(ParamSeg2<=1.0))
		return 1; /* intersection OK beetwen extreme points */
	else
		return 0; /* intersection OK but not beetwen extreme points */
}
