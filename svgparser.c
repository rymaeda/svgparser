/*
It must be used with Expat compiled for UTF-8 output.
Based on element.c example file of Expat.
*/

#include <stdio.h>
#include <string.h>
#include <expat/expat.h>
#include "svg_polyparser.h"

#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif

SVG_POLYGON polygons[SVG_MAXPOLY];
int npolygons; /* number of polygons */

static void XMLCALL
startElement(void *userData, const char *name, const char **atts){
	int i;
	for (i = 0; atts[i]; i += 2) /* search for "d" field */
		if (!strcmp("d", atts[i])){ /* if atts[i]=="d" then parse atts[i+1] */
			polygons[npolygons].coords= svg_polymalloc(atts[i+1], polygons + npolygons );
			svg_polyparser(atts[i+1], polygons + npolygons );
			npolygons++;
		}
}

int
main(int argc, char *argv[]){
	int done;
	int depth = 0;
	FILE *fp;
	char buf[BUFSIZ];
	int i, j;

	fp= fopen(argv[1],"rd");
	if(fp==NULL){
		fprintf(stderr, "Can't read input file\n");
		exit(-1);
	}
	XML_Parser parser = XML_ParserCreate(NULL);
//	XML_SetUserData(parser, &depth);
	XML_SetElementHandler(parser, startElement, NULL);
	do {
		int len = (int)fread(buf, 1, sizeof(buf), fp);
		done = len < sizeof(buf);
		if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) {
			fprintf(stderr,
				"%s at line %" XML_FMT_INT_MOD "u\n",
				XML_ErrorString(XML_GetErrorCode(parser)),
				XML_GetCurrentLineNumber(parser));
			return 1;
		}
	}
	while (!done);
	printf("************ PATHS AND POINTS ************\nNumber of polygons: %d\n\n", npolygons);
	for(j=0; j<npolygons; j++){/* print polygons data */
		printf("Polygon: %d  Number of points: %d  Area: %8.1lf\n", j, polygons[j].n_pts, polygons[j].area);
		for (i= 0; i<polygons[j].n_pts; i++){	/* print node coords */
			printf("(%4.2lf,%4.2lf)", polygons[j].coords[i].x, polygons[j].coords[i].y);
			if (!((i+1)%5)) /* formating prints */
				printf("\n");
			else
				printf ("\t");
		}
		printf("\n\n");
	}
	for(j=0; j<npolygons; j++) /* freeing memory */
		svg_polyfree(polygons+j);
	XML_ParserFree(parser);
	fclose(fp);
	return 0;
}
