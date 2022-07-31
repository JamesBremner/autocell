#include <autocell.h>
#include <iostream>

using namespace std;

void neighbours(
    cell::cAutomaton<cell::cCell> &A,
    int cw, int ch)
{
    int w, h;
    std::cout << "Neighbours of cell at " << cw << ", " << ch
              << " are ";
    for (auto c : A.neighbours(cw, ch))
    {
        A.coords(w, h, c);
        std::cout << "( " << w << ", " << h << " ) ";
    }
    std::cout << "\n";
}

int main()
{
    /* for a simple test with no application specific behaviour by the cells
        the base cCell class can be used to define the automaton
    */
    cell::cAutomaton<cell::cCell> A(3, 3);
    int cw = 0;
    int ch = 0;
    neighbours(A, cw, ch);
    cw = 1;
    ch = 1;
    neighbours(A, cw, ch);
    cw = 2;
    ch = 2;
    neighbours(A, cw, ch);

    std::cout << "No wrapping\n";
    A.wrap(false);
    cw = 0;
    ch = 0;
    neighbours(A, cw, ch);
    cw = 1;
    ch = 1;
    neighbours(A, cw, ch);
    cw = 2;
    ch = 2;
    neighbours(A, cw, ch);

    std::cout << "diagonal wrapping\n";
    A.wrap(true);
    A.ortho(false);
    cw = 0;
    ch = 0;
    neighbours(A, cw, ch);
    cw = 1;
    ch = 1;
    neighbours(A, cw, ch);
    cw = 2;
    ch = 2;
    neighbours(A, cw, ch);
        std::cout << "diagonal no wrap\n";
    A.wrap(false);
    A.ortho(false);
    cw = 0;
    ch = 0;
    neighbours(A, cw, ch);
    cw = 1;
    ch = 1;
    neighbours(A, cw, ch);
    cw = 2;
    ch = 2;
    neighbours(A, cw, ch);

    std::set<int> chosen;
    while( chosen.size() < 5 )
        A.random( chosen );
    for( int i : chosen )
        std::cout << i << " ";
    std::cout << "\n";
}
