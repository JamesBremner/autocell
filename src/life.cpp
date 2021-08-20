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
            return '.';
    }
};
class cConway
{
    cell::cAutomaton<cCellLife> board1;
    cell::cAutomaton<cCellLife> board2;

public:
    /// construct board with w columns and h rows
    cConway(int w, int h);

    /// initilize with count living cells
    void random(int count);

    /// simulate for generationCount generationds
    void live(int generationCount);

private:
    int countLivingNeighbours(
        cell::cAutomaton<cCellLife> &board,
        int c, int r);
    void next(
        cell::cAutomaton<cCellLife> &old,
        cell::cAutomaton<cCellLife> &next);
    void display(
        cell::cAutomaton<cCellLife> &board);
};

cConway::cConway(int w, int h)
    : board1(w, h), board2(w, h)
{
    board1.ortho(false);
    board1.wrap(false);
    board2.ortho(false);
    board2.wrap(false);
}
void cConway::random(int count)
{
    std::set<int> chosen;
    srand(time(0));
    while (chosen.size() < count)
        board1.random(chosen)->alive = true;
}

int cConway::countLivingNeighbours(
    cell::cAutomaton<cCellLife> &board,
    int c, int r)
{
    int count = 0;
    for (auto pcell : board.neighbours(c, r))
        if (pcell->alive)
            count++;
    return count;
}

/// display * for living cells
void cConway::display(
    cell::cAutomaton<cCellLife> &board)
{
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            std::cout << board.cell(c, r)->text();
        }
        std::cout << "\n";
    }
    std::cout << "\n=======================\n";
}
//     Any live cell with two or three live neighbours survives.
// Any dead cell with three live neighbours becomes a live cell.
// All other live cells die in the next generation. Similarly, all other dead cells stay dead.
void cConway::next(
    cell::cAutomaton<cCellLife> &old,
    cell::cAutomaton<cCellLife> &next)
{
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            auto c1 = old.cell(c, r);
            auto c2 = next.cell(c, r);
            c2->alive = false;

            int count = countLivingNeighbours(old, c, r);

            if (c1->alive)
                if (count == 2 || count == 3)
                    c2->alive = true;
                else if (count == 3)
                    c2->alive = true;
        }
    }
}
void cConway::live(int generationCount)
{
    for (int g = 0; g < generationCount; g++)
    {
        display(board1);
        next(board1, board2);
        display(board2);
        next(board2, board1);
    }
}

int main()
{
    // contruct 10 by 10 conway game of life
    cConway conway( 10, 10 );

    // initialize with 20 living cells
    conway.random( 20 );

    // simulate 5 generations
    conway.live( 5 );

 
}