*************
*   Qn. 8   *
*************

From each point on the strokes made by your mouse draw a line segment to the
world coordinate (0,0). The color of the line segment is determined by the
following rules. 1st quadrant - RED 2nd quadrant - GREEN 3rd quadrant - BLUE 4th
quadrant - YELLOW x-axis - BLACK y-axis - BLACK The brightness of the colour for
line segment in each quadrant depends on the angular distance of the line
segment from the starting angle of the quadrant. The ratio of angular coverage
to the quadrant’s total angular distance is the color brightness. Ex:- If the
line segment is in 3rd quadrant at an angle from the positive x-axis, then the
angle covered is and 3 4Π 3 4Π − Π the brightness is determined by the ratio (4*
Π /3 - Π )/( Π /2). Hence the color is -> RGB (0,0,(4* Π /3 - Π )/( Π /2)).
Note:- Make the background white.

-----------------
Run the program:
-----------------
    - g++ main.cpp -lglut -lGL -lGLEW -lGLU -o main
    - ./main 1 (for the first color)
    - ./main 2 (for the second color)