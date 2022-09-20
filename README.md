The template class  `cAutomaton` provides essential code for 2D cellular automatons and, more generally, convenient functions for working with 2D grids that handle wrapping at the grid edges and either 4 orthogonal or 8 diagonal neighbours.

The class cCell is a base class for application code using cAutomaton.  This should be specialized for a particular application, and cAutomaton constructed with the specialiation.

The test application demonstrates the various wrapping and neighbor options.  It uses the cCell base class with no specializations.

The life application is an implementation of Conway's Game of Life, providing a demonstration of how to use cAutomaton.

![image](https://user-images.githubusercontent.com/2046227/131689933-40a79a0c-7e33-4e1c-8eba-9e49025e0ad7.png)

The birds application simulates the predator-prey of Eagles and small brown birds.

A chess application ( https://github.com/JamesBremner/chess ) is built on this code.
