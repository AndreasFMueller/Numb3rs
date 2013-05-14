(*
  ec2.m -- Mathematic source to compute squaring on an elliptic curve
           in homogenous coordinates

  (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil 
 *)
(* elliptic curve *)
p[x_, y_, z_] := z y^2 - x^3 - a x z^2 - b z^3

(* gradient, normal to the tangent *)
g = { D[p[x0,y0,z0], x0], D[p[x0,y0,z0], y0], D[p[x0,y0,z0], z0] }
g//CForm

(* cross product, gives diretion vector of tangent *)
v = { x0, y0, z0 } + t Cross[g, {x0, y0, z0}]
v//CForm

(* insert into the elliptic curve, the third intersection point
   will be found as the solution of the linear function that
   we obtain as the polynomial quotient when deviding by t^2 *)
x = v[[1]]
y = v[[2]]
z = v[[3]]
pp = Expand[p[x,y,z]]
q = PolynomialQuotient[pp, t^2, t]
q1 = q /. pp -> 0
t = PolynomialRemainder[q, t, t] / PolynomialQuotient[q, t, t]
Simplify[t] // CForm

