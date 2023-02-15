# Sabai
A Lightweight MultiDimensional Array Library

Sabai is a thoroughly tested array library. It's focused on speed, as well as flexiblity.

Use sabai as follows:

sabai::StaticVector<int, 3> x;
auto y = 3*x

Sabai contains numerous matrix decompositions to solve linear systems. These include

LU Decomposition
Cholesky Decomposition

Forward substituion and backward substitution routines are also included.

We can use these to solve dense linear algebra problems.

Sabai also supports

dot products
outer products
inner products
matrix-matrix products
elementwise vector-vector products
elementwise scalar-vector products
matric-vector products

Note that these products do not have to be included. One can use these as needed or define one's own versions.

Tensors may be created, but there are no operations currently defined for them.

Sabai is Thai for relaxed, or good. Hopefully this library will enable you to relax as you explore the amazing applications of arrays!
