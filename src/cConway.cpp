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

void cConway::glider()
{
    board1.cell(10, 10)->alive = true;
    board1.cell(11, 11)->alive = true;
    board1.cell(9, 12)->alive = true;
    board1.cell(10, 12)->alive = true;
    board1.cell(11, 12)->alive = true;
}

void cConway::glidergun()
{
    board1.cell(1, 5)->alive = true;
    board1.cell(2, 5)->alive = true;
    board1.cell(1, 6)->alive = true;
    board1.cell(2, 6)->alive = true;
    board1.cell(11, 5)->alive = true;
    board1.cell(11, 6)->alive = true;
    board1.cell(11, 7)->alive = true;
    board1.cell(12, 4)->alive = true;
    board1.cell(12, 8)->alive = true;
    board1.cell(13, 3)->alive = true;
    board1.cell(13, 9)->alive = true;
    board1.cell(14, 3)->alive = true;
    board1.cell(14, 9)->alive = true;
    board1.cell(15, 6)->alive = true;
    board1.cell(16, 4)->alive = true;
    board1.cell(16, 8)->alive = true;
    board1.cell(17, 5)->alive = true;
    board1.cell(17, 6)->alive = true;
    board1.cell(17, 7)->alive = true;
    board1.cell(18, 6)->alive = true;
    board1.cell(21, 3)->alive = true;
    board1.cell(21, 4)->alive = true;
    board1.cell(21, 5)->alive = true;
    board1.cell(22, 3)->alive = true;
    board1.cell(22, 4)->alive = true;
    board1.cell(22, 5)->alive = true;
    board1.cell(23, 2)->alive = true;
    board1.cell(23, 6)->alive = true;
    board1.cell(25, 1)->alive = true;
    board1.cell(25, 2)->alive = true;
    board1.cell(25, 6)->alive = true;
    board1.cell(25, 7)->alive = true;
    board1.cell(35, 3)->alive = true;
    board1.cell(35, 4)->alive = true;
    board1.cell(36, 3)->alive = true;
    board1.cell(36, 4)->alive = true;
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
    int w, h;
    board.size(w, h);
    for (int r = 0; r < h; r++)
    {
        for (int c = 0; c < w; c++)
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
            {
                if (count == 2 || count == 3)
                    c2->alive = true;
            }
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