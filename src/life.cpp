#include <autocell.h>
#include <iostream>
#include <time.h>

class cCellLife : public cell::cCell
{
public:
    cCellLife() : alive(false) {}
    bool alive;
    virtual char text()
    {
        if (alive)
            return '*';
        else
            return ' ';
    }
};

int main()
{
    // setup board with random cells alive
    cell::cAutomaton<cCellLife> board(10, 10);
    std::set<int> chosen;
    srand(time(0));
    while (chosen.size() < 10)
        board.random(chosen)->alive = true;

    // display * for living cells
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            std::cout << board.cell(c, r)->text();
        }
        std::cout << "\n";
    }
}