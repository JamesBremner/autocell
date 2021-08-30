The template class  `cAutomaton` provides essential code for 2D cellular automatons and, more generally, convenient functions for working with 2D grids that handle wrapping at the grid edges and either 4 orthogonal or 8 diagonal neighbours.

The class cCell is a base class for application code using cAutomaton.  This should be specialized for a particular application, and cAutomaton constructed with the specialiation.

The life application is an implementation of Conway's Game of Life, providing a demonstration of how to use cAutomaton.  The guilife version uses windex to provide a dynamic gui display of evolution.
