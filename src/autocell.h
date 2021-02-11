#include <vector>
#include <memory>
namespace cell
{

/// Individual cell
class cCell
{
public:
    cCell();
    int ID()
    {
        return myID;
    }
    static void RestartID()
    {
        myLastID = -1;
    }
private:
    static int myLastID;
    int myID;
};
typedef std::shared_ptr< cCell > cell_t;

/// A 2D cell automaton
class cAutomaton
{
public:
    /** CTOR
        @param[in] w width
        @param[in] h height
    */
    cAutomaton(
        int w, int h );

    /** Configure behaviour at edges of grid
        @param[in] f true for wrapping the edges around, default value
        @param[in] f false for stopping the grid at the edges

        A cell at the edge of the grid has no neighbour outside the grid
        when wrapping is false
        A cell at the edge of the grid has neighbours on the other side of the grid
        when wraqpping is ture.
    */
    void wrap( bool f = true )
    {
        myfwrap = f;
    }

    /** Pointer to cell
        @param[in] w zero-based width index
        @param[in] h zero-based height index
        @return shared pointer to cell

        The pointer can be used to acess methods of specialized cell class.

        Exception thrown if w or h out of bounds
    */
    cell_t cell(
        int w, int h );

    /** neighbours
        @param[in] w zero-based width index of cell
        @param[in] h zero-based height index of cell
        @return vector of shared pointers to cell's neighbours
    */
    std::vector< cell_t > neighbours(
        int w, int h );

    /** w, h co-ordinates of cell
        @param[out] w width
        @param[out] h height
        @param[in] cell
    */
    void coords(
        int& w, int& h,
        cell_t cell );

private:
    std::vector< cell_t > myCell;
    int myWidth;
    int myHeight;
    bool myfwrap;   ///< true if edges wrap around

    std::vector< cell_t > neighboursWrap(
        int w, int h );
    std::vector< cell_t > neighboursNoWrap(
        int w, int h );
};
}
