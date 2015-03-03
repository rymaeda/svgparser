#ifndef GEOMETRIC
#define GEOMETRIC
#include "svg_polyparser.h"
#include <math.h>

/* geo_area */
double geo_area(SVG_POLYGON *polygon);
int geo_parallel(SVG_SEGMENT *s1, SVG_SEGMENT *s2, double distance);
double geo_parallelpoly(SVG_POLYGON* polygon, SVG_POLYGON* parapoly, double distance);
int geo_intersec(SVG_SEGMENT *s1, SVG_SEGMENT *s2, SVG_TCOORD *pti);

#endif
