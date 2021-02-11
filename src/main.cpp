#include <autocell.h>
#include <iostream>

using namespace std;


int main()
{
    cell::cAutomaton A( 3, 3 );
    int cw = 1;
    int ch = 1;
    int w, h;
    std::cout << "Neighbours of cell at " << cw <<", " << ch
        <<" index "<< A.cell(cw,ch)->ID()
        << " are ";
    for( auto c : A.neighbours( cw, ch ) ) {
        A.coords( w, h, c );
        std::cout <<"( " << w << ", " << h << " ) ";
    }
    std::cout << "\n";
}
