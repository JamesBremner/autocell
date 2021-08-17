#include <autocell.h>
#include <iostream>

using namespace std;

void neighbours(
    cell::cAutomaton &A,
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
    cell::cAutomaton A(3, 3);
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
}
