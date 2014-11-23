#include "colors.inc"

camera {
        location <2.3, 2.5, -6>
        look_at <0.95, 0.6, 1.1>
        right 4/3 * x * 0.31
        up y * 0.31
}

light_source { <5, 8, -15> color White }
sky_sphere {
        pigment { color White }
}

#declare linethickness = 3;
#macro axis(from, dir)
        cylinder { from, from + dir, 0.004 * linethickness
                pigment { color Gray }
        }
        cone { from + dir, 0.01 * linethickness, from + dir + vnormalize(dir) * 0.03 * linethickness, 0
                pigment { color Gray }
        }
#end
axis(<0,0,0>, <2.2,   0,   0>)
axis(<0,0,0>, <  0, 1.7,   0>)
axis(<0,0,0>, <  0,   0, 1.7>)

#declare vectorthickness = 5;
#macro vector(from, vv) 
	sphere { from, 0.006 * vectorthickness }
        cylinder { from, from + vv, 0.004 * vectorthickness
                pigment { color rgb <1.0,0.5,0.5> }
        }
        cone { from + vv, 0.01 * vectorthickness, from + vv + vnormalize(vv) * 0.03 * linethickness, 0
                pigment { color rgb <1.0,0.5,0.5> }
        }
#end

#macro vektor(from, vv) 
	sphere { from, 0.006 * vectorthickness }
        cylinder { from, from + vv, 0.004 * vectorthickness
                pigment { color rgb <0.5,1.0,0.5> }
        }
        cone { from + vv, 0.01 * vectorthickness, from + vv + vnormalize(vv) * 0.03 * linethickness, 0
                pigment { color rgb <0.5,1.0,0.5> }
        }
#end

#macro line(from, to)
        cylinder { from, to, 0.003 * linethickness
                pigment { color rgb <0.5,1.0,0.5> }
        }
#end


vector(<0,0,0>, <2, 0  , 0  >)
vector(<0,0,0>, <0, 1.3, 0  >)
vector(<0,0,0>, <0, 0  , 1.5>)

line(<2, 0, 0  >, <2, 0  , 1.5>)
line(<0, 0, 1.5>, <2, 0  , 1.5>)
line(<2, 0, 1.5>, <2, 1.3, 1.5>)
/* line(<0, 1.3, 0>, <2, 1.3, 1.5>) */

vektor(<0,0,0>, <2, 1.3, 1.5>)

sphere { <0, 0, 0>, 0.007 * 5
	pigment { color rgb <1.0,0.5,0.5> }
}

text {
	ttf "timrom.ttf" "x" 0.2, 0
	pigment { Red }
	scale 0.2 translate <2.25,0.05,0>
}
text {
	ttf "timrom.ttf" "z" 0.2, 0
	pigment { Red }
	scale 0.2 translate <0.05,1.7,0>
}
text {
	ttf "timrom.ttf" "y" 0.2, 0
	pigment { Red }
	scale 0.2 translate <-0.15,0.0,1.7>
}




