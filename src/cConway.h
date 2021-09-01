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
    /// initialize with count living cells
    void random(int count);

    /// initialize with glider
    void glider();

    /// initialize with glider gun
    void glidergun();

    /** Grow the next generation
     * @param[in] odd current board: true for board1, false for board2
     * 
     * Takes the current board and creates living calls in the other board
     * using the rules
     */
    void next(bool odd);

    /// simulate for generationCount generations
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
