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

int countLivingNeighbours(
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
void display(cell::cAutomaton<cCellLife> &board)
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
void next(
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

int main()
{
    // setup board with random cells alive
    cell::cAutomaton<cCellLife> board(10, 10);
    board.ortho(false);
    board.wrap(false);
    std::set<int> chosen;
    srand(time(0));
    while (chosen.size() < 20)
        board.random(chosen)->alive = true;

    // alternate board
    cell::cAutomaton<cCellLife> board2(10, 10);
    board2.ortho(false);
    board2.wrap(false);

    for (int g = 0; g < 5; g++)
    {
        display(board);
        next(board, board2);
        display(board2);
        next(board2, board);
    }

}