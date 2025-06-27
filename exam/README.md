This is my solution for project 17.

The file "spline.cc" contains a class for the cubic sub-spline, 
a class for the quartic sub-spline from the 2nd extra task and
a binary search algorithm identical to the one used in the Splines homework.

The spline classes each take three vectors x, y, yPrime representing the tabulated dataset.
In the cubic sub-spline class, buildSpline() determines the three coefficients b[i], c[i] and d[i]
based on the conditions given in the project. Note that neither spline class has a vector b variable,
as the second condition determines b[i] = yPrime[i]. The cubic sub-spline also has the derivative() and integral() methods/functionality requested by the 1st extra task, which were tested by sampling sin(x), x^3 and exp(x) from o to 2pi.

The quartic sub-spline class has an additional vector e variable compared to the cubic,
which is used for the e[i] coefficient. To determine e[i], I used the continuity condition given
by Equation 1.3 in the book, specifically adding:

$$S_{i}''(x_{i+1}) = y_{i+1}''$$

to the three conditions given in the task. As a quick sanity check, I once again sampled points using sin(x) and plotted both sub-splines. The results are expanded somewhat upon in Out.txt and the plots can be seen in 'plots/plot.cubicSubSpline.svg' and 'plots/plot.quarticSubSpline.svg'.
