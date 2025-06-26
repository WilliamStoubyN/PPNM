This is my solution for project 1.

The file "spline.cc" contains my attempt to build a cubic sub-spline with the given conditions for the coefficients.

The file "spline.cc" contains a class for the cubic sub-spline, 
a class for the quartic sub-spline from the 2nd extra task and
a binary search algorithm identical to the one used in the Splines homework.

The spline classes each take three vectors x, y, yPrime representing the tabulated dataset. In the cubic sub-spline class, buildSpline() determines the three coefficients b[i], c[i] and d[i] based on the conditions given in the project. Note that neither spline class has a vector b variable, as the second condition determines b[i] = yPrime[i].

The quartic sub-spline classes has an additional vector e variable compared to the cubic, which is used for the e[i] coefficient. To determine e[i], I used the continuity condition given by Equation 1.3 in the book, specifically setting

$ S''_{i}(x_{i+1}) = y''_{i + 1} $

