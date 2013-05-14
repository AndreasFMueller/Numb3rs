(*
  ec.m -- Mathematic source to compute product on an elliptic curve
          in homogenous coordinates

  (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil 
 *)

(* parametrized line through two points *)
x = (1-t) x0 + t x1
y = (1-t) y0 + t y1
z = (1-t) z0 + t z1

(* elliptic curve *)
p[x_, y_, z_] := z y^2 - x^3 - a x z^2 - b z^3

(* inserting the line into the elliptic curve should give a third
   solution besides 0 and 1, so the quotient by t (t-1) should
   be linear, giving a formula for t *)
PolynomialRemainder[p[x, y, z], t (t-1), t]
q = PolynomialQuotient[p[x, y, z], t (t-1), t]
p0 = Expand[p[x0, y0, z0]]
p1 = Expand[p[x1, y1, z1]]
q1 = q /. p0 -> 0
q1 = q1 /. p1 -> 0
q1 = q1 /. p0 -> 0
q1 = q1 /. p1 -> 0
(t /. Solve[ { q1 == 0 }, t ])[[1]] //CForm
