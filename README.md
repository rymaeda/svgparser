# svgparser
Nano SVG parser. Inkscape 'd' field specific.
This plain C console mode code use the expat library to parse "d" (see below)
field of SVG Inkscape file. This are a LCC-Win32 project files but must compile
flawless on Linux.

In DOS/Windows world to run the example program one must call it with the command:

C:\svgparser.exe dummy.svg

This initial version of 'xmlparser' read path points in svg files in the variable
'd' and store them in the matrix of structs SVG_TCOORD. Another dialets of SVG
paths, like from LibreCAD, are't supported yet.

******Input (snippet from one SVG input file):
d="M294.28572 91.312014L225.729105 103.7032695L174.28572 124.71684L137.469136563
 152.837408125L112.982975 183.85796L107.740884648 199.569097422L108.433898438
 214.941271875L116.012849258 229.619830391L131.42857 243.25012L197.675802344
 272.505148906L289.69637875 294.03952125L392.583050781 304.457065469L491.42857
 300.36161L551.423131875 284.776232188L593.1113225 260.01629L618.243851875
 230.644777813L628.57143 201.22469L624.310292656 174.078476094L605.07734125
 147.09725375L571.162864219 122.664912031L522.85715 103.16534L472.003857188
 92.7970277813L413.7455725 87.87748975L294.28572 91.312014L294.28572 91.312014"

******Output:
Number of points: 25
( 294.3,  91.3 )( 225.7, 103.7 )( 174.3, 124.7 )( 137.5, 152.8 )( 113.0, 183.9 )
( 107.7, 199.6 )( 108.4, 214.9 )( 116.0, 229.6 )( 131.4, 243.3 )( 197.7, 272.5 )
( 289.7, 294.0 )( 392.6, 304.5 )( 491.4, 300.4 )( 551.4, 284.8 )( 593.1, 260.0 )
( 618.2, 230.6 )( 628.6, 201.2 )( 624.3, 174.1 )( 605.1, 147.1 )( 571.2, 122.7 )
( 522.9, 103.2 )( 472.0,  92.8 )( 413.7,  87.9 )( 294.3,  91.3 )


This example program is just the initial step to show how to extract points
informations from Inkscape SVG files as pointed generously by MacBob in CAMBam
forum:

"I find Inkscape rather complicated, but one of the tools
I most like is the Bezier Curve drawing tool.  Inkscape
allows you to import a jpg file and then to use it as a
template to generate a bezier curve boundary.  Soothing!

Inkscape saves its data as an SVG file, which is basically
an XML format.  Bezier curves are saved as 'paths', which
have a 'd' attribute giving the coordinates and control
points.  Inkscape also supports saving the file as a DXF
file, which can be imported directly into CamBam.

However, what I wanted was a set of (x1, y1, x2, y2) lines
(...). Luckily Inkscape has a 'Flatten Beziers' command
(Extensions >> Modify Path >> Flatten Beziers...) which
converts a bezier path to a series of straight lines.
Saving in SVG format then provides a 'd' path attribute
that is just the set of coordinates along the path.
I then wrote a simple Perl script to convert these SVG
paths to my lines format."
(http://www.cambam.co.uk/forum/index.php?topic=3279.0)

I plan to make STL 3D objects as proposed by MacBob in another message in same
thread.

Ricardo Maeda
rymaeda@yahoo.com
23/february/2015
