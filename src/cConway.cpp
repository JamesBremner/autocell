#include <autocell.h>
#include <iostream>
#include <time.h>
#ifdef GUI
#include "wex.h"
#endif
#include "cConway.h"


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

void cConway::displayText(
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
#ifdef GUI
void cConway::displayGUI(
    PAINTSTRUCT &ps)
{
    // keep track of which board current
    static bool odd = true;
    cell::cAutomaton<cCellLife> *B;
    if (odd)
        B = &board1;
    else
        B = &board2;

    // display living cells in current board
    int w, h;
    B->size(w, h);
    wex::shapes S(ps);
    S.color(0);
    S.fill();
    for (int r = 0; r < h; r++)
    {
        for (int c = 0; c < w; c++)
        {
            if (B->cell(c, r)->alive)
                S.rectangle({c * 5, r * 5, 5, 5});
        }
    }

    // create next generation
    next(odd);

    // swap current board
    odd = !odd;
}
#endif
//     Any live cell with two or three live neighbours survives.
// Any dead cell with three live neighbours becomes a live cell.
// All other live cells die in the next generation. Similarly, all other dead cells stay dead.
void cConway::next(
    cell::cAutomaton<cCellLife> &old,
    cell::cAutomaton<cCellLife> &next)
{
    int w, h;
    old.size(w, h);

    for (int r = 0; r < h; r++)
    {
        for (int c = 0; c < w; c++)
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
void cConway::next(bool odd)
{
    if (odd)
        next(board1, board2);
    else
        next(board2, board1);
}
void cConway::live(int generationCount)
{
    for (int g = 0; g < generationCount; g++)
    {
        displayText(board1);
        next(board1, board2);
        displayText(board2);
        next(board2, board1);
    }
}