#pragma once

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
#ifdef GUI
    wex::gui *myGui;
#endif

public:
    /// construct board with w columns and h rows
    cConway(int w, int h);

#ifdef GUI
    void set(wex::gui &gui)
    {
        myGui = &gui;
    }
#endif
    /// initilize with count living cells
    void random(int count);

    void next(bool odd);

    /// simulate for generationCount generationds
    void live(int generationCount);

#ifdef GUI
    void displayGUI(
        PAINTSTRUCT &ps);
#endif

private:
    int countLivingNeighbours(
        cell::cAutomaton<cCellLife> &board,
        int c, int r);
    void next(
        cell::cAutomaton<cCellLife> &old,
        cell::cAutomaton<cCellLife> &next);
    void displayText(
        cell::cAutomaton<cCellLife> &board);
};
