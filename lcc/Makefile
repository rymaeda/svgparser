# Wedit Makefile for project svgparser
SRCDIR=c:\users\ricardo\documents\lcc\svgparser
CFLAGS=-I"c:\lcc\include"  -ansic
CC=$(LCCROOT)\bin\lcc.exe
LINKER=$(LCCROOT)\bin\lcclnk.exe
OBJS=\
	svgparser.obj \
	svg_polyparser.obj \
	geometric.obj

LIBS=libexpat.lib
EXE=svgparser.exe

$(EXE):	$(OBJS) Makefile
	$(LINKER)  -s -subsystem console -o $(SRCDIR)\lcc\svgparser.exe $(OBJS) $(LIBS)

# Build svgparser.c
SVGPARSER_C=\
	$(SRCDIR)\svg_polyparser.h\
	$(SRCDIR)\geometric.h\

svgparser.obj: $(SVGPARSER_C) $(SRCDIR)\svgparser.c
	$(CC) -c $(CFLAGS) $(SRCDIR)\svgparser.c

# Build svg_polyparser.c
SVG_POLYPARSER_C=\
	$(SRCDIR)\svg_polyparser.h\
	$(SRCDIR)\geometric.h\

svg_polyparser.obj: $(SVG_POLYPARSER_C) $(SRCDIR)\svg_polyparser.c
	$(CC) -c $(CFLAGS) $(SRCDIR)\svg_polyparser.c

# Build geometric.c
GEOMETRIC_C=\
	$(SRCDIR)\geometric.h\

geometric.obj: $(GEOMETRIC_C) $(SRCDIR)\geometric.c
	$(CC) -c $(CFLAGS) $(SRCDIR)\geometric.c

link:
	$(LINKER)  -s -subsystem console -o $(SRCDIR)\lcc\svgparser.exe $(OBJS) $(LIBS)

clean:
	del $(OBJS) svgparser.exe
