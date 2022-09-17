#pragma once
#include <vector>
#include <memory>
#include <set>
#include <sstream>

namespace cell
{

    /// Individual cell
    class cCell
    {
    public:
        cCell()
        {
            myID = ++myLastID;
        }
        int ID()
        {
            return myID;
        }
        static void RestartID()
        {
            myLastID = -1;
        }
        virtual char text()
        {
            return 'c';
        }

    private:
        static int myLastID;
        int myID;
    };
    typedef std::shared_ptr<cCell> cell_t;

    /// A 2D cell automaton
    template <class C>
    class cAutomaton
    {
    public:
        /** CTOR
        @param[in] w width in cells
        @param[in] h height in cells
    */
        cAutomaton(
            int w, int h);

        /** Configure behaviour at edges of grid
        @param[in] f true for wrapping the edges around, default value
        @param[in] f false for stopping the grid at the edges

        A cell at the edge of the grid has no neighbour outside the grid
        when wrapping is false
        A cell at the edge of the grid has neighbours on the other side of the grid
        when wrapping is true.
    */
        void wrap(bool f = true)
        {
            myfwrap = f;
        }

        /** Configure behaviour of neighbours
         * @param[in] f false: consider 8 cells as neighbours, ortho and diagonal
         * @param[in] f true: consider 4 cells as neighbours, jut orthogonal
         */
        void ortho(bool f = true)
        {
            myfortho = f;
        }

        /** Pointer to cell
        @param[in] w zero-based width index
        @param[in] h zero-based height index
        @return shared pointer to cell

        The pointer can be used to acess methods of specialized cell class.

        Exception thrown if w or h out of bounds
    */
        C *cell(
            int w, int h);

        /** choose a random cell
     * @param[in] chosen a set of cell indices that should not be chosen
     * @param[out] chosen input plus index of chosen cell
     * @return shared pointer to chosen cell
     *
     * Usage to choose 5 cells at random with no duplicates
     * <pre>
    cell::cAutomaton A(3, 3);       // 3 by 3 cell grid
    std::set<int> chosen;           // set of chosen cell indices
    srand (time(NULL));             // seed random no generator
    while( chosen.size() < 5 )      // choose 5
        A.random( chosen );         // choose
    for( int i : chosen )           // display choices
        std::cout << i << " ";
    std::cout << "\n";
    </pre>
    */
        C *random(
            std::set<int> &chosen);

        /** neighbours
        @param[in] w zero-based width index of cell
        @param[in] h zero-based height index of cell
        @return vector of pointers to cell's neighbours
    */
        std::vector<C *> neighbours(
            int w, int h);

        std::vector<C *> neighbours( C* cell )
        {
            int w,h;
            coords( w, h, cell );
            return neighbours( w, h );
        }

        /** w, h co-ordinates of cell
        @param[out] w width
        @param[out] h height
        @param[in] cell
    */
        void coords(
            int &w, int &h,
            C *cell);

        std::string text();
        std::string text(int row);

        void size(
            int &w, int &h)
        {
            w = myWidth;
            h = myHeight;
        }

        typename std::vector<C *>::iterator begin()
        {
            return myCell.begin();
        }
        typename std::vector<C *>::iterator end()
        {
            return myCell.end();
        }

    private:
        std::vector<C *> myCell;
        int myWidth;
        int myHeight;
        bool myfwrap;  ///< true if edges wrap around
        bool myfortho; ///< true if only orthogonal neighbours

        std::vector<C *> neighboursWrap(
            int w, int h);
        std::vector<C *> neighboursNoWrap(
            int w, int h);
        void wrap(int &w, int &h);
        bool inside(int w, int h);
    };
    template <class C>
    cAutomaton<C>::cAutomaton(
        int w, int h)
        : myWidth(w), myHeight(h), myfwrap(true), myfortho(true)
    {
        cCell::RestartID();
        for (int k = 0; k < myWidth * myHeight; k++)
        {
            myCell.push_back(new C);
        }
    }
    template <class C>
    C *cAutomaton<C>::cell(
        int w, int h)
    {
        if (0 > w || w >= myWidth || 0 > h || h >= myHeight)
            throw std::runtime_error(
                "cAutomaton cell out of bounds" + std::to_string(w) + " " + std::to_string(h));
        return myCell[myWidth * h + w];
    }
    template <class C>
    C *cAutomaton<C>::random(std::set<int> &forbidden)
    {
        int index;
        do
        {
            index = rand() % (myWidth * myHeight);
        } while (!forbidden.insert(index).second);

        return myCell[index];
    }
    template <class C>
    std::vector<C *> cAutomaton<C>::neighbours(
        int w, int h)
    {
        if (myfwrap)
            return neighboursWrap(w, h);
        else
            return neighboursNoWrap(w, h);
    }
    template <class C>
    void cAutomaton<C>::wrap(int &w, int &h)
    {
        // std::cout << "wrap " << w <<" "<< h;
        if (w < 0)
            w = myWidth - 1;
        if (h < 0)
            h = myHeight - 1;
        if (w > myWidth - 1)
            w = 0;
        if (h > myHeight - 1)
            h = 0;
        // std::cout << " -> " << w <<" "<< h << "\n";
    }
    template <class C>
    bool cAutomaton<C>::inside(int w, int h)
    {
        bool ret = true;
        if (w < 0)
            ret = false;
        if (h < 0)
            ret = false;
        if (w > myWidth - 1)
            ret = false;
        if (h > myHeight - 1)
            ret = false;
        return ret;
    }
    template <class C>
    std::vector<C *> cAutomaton<C>::neighboursWrap(
        int w, int h)
    {
        std::vector<C *> ret;
        int nw, nh;
        nw = w - 1;
        if (nw < 0)
            nw = myWidth - 1;
        nh = h;
        ret.push_back(cell(nw, nh));
        nw = w + 1;
        if (nw >= myWidth)
            nw = 0;
        nh = h;
        ret.push_back(cell(nw, nh));
        nw = w;
        nh = h + 1;
        if (nh >= myHeight)
            nh = 0;
        ret.push_back(cell(nw, nh));
        nw = w;
        nh = h - 1;
        if (nh < 0)
            nh = myHeight - 1;
        ret.push_back(cell(nw, nh));
        if (!myfortho)
        {
            nw = w - 1;
            nh = h - 1;
            wrap(nw, nh);
            ret.push_back(cell(nw, nh));
            nw = w + 1;
            nh = h - 1;
            wrap(nw, nh);
            ret.push_back(cell(nw, nh));
            nw = w - 1;
            nh = h + 1;
            wrap(nw, nh);
            ret.push_back(cell(nw, nh));
            nw = w + 1;
            nh = h + 1;
            wrap(nw, nh);
            ret.push_back(cell(nw, nh));
        }
        return ret;
    }
    template <class C>
    std::vector<C *> cAutomaton<C>::neighboursNoWrap(
        int w, int h)
    {
        std::vector<C *> ret;
        int nw, nh;
        if (w != 0)
        {
            nw = w - 1;
            if (nw < 0)
                nw = myWidth - 1;
            nh = h;
            ret.push_back(cell(nw, nh));
        }
        if (w != myWidth - 1)
        {
            nw = w + 1;
            if (nw >= myWidth)
                nw = 0;
            nh = h;
            ret.push_back(cell(nw, nh));
        }
        if (h != myHeight - 1)
        {
            nw = w;
            nh = h + 1;
            if (nh >= myHeight)
                nh = 0;
            ret.push_back(cell(nw, nh));
        }
        if (h != 0)
        {
            nw = w;
            nh = h - 1;
            if (nh < 0)
                nh = myHeight - 1;
            ret.push_back(cell(nw, nh));
        }
        if (!myfortho)
        {
            nw = w - 1;
            nh = h - 1;
            if (inside(nw, nh))
                ret.push_back(cell(nw, nh));
            nw = w + 1;
            nh = h - 1;
            if (inside(nw, nh))
                ret.push_back(cell(nw, nh));
            nw = w - 1;
            nh = h + 1;
            if (inside(nw, nh))
                ret.push_back(cell(nw, nh));
            nw = w + 1;
            nh = h + 1;
            if (inside(nw, nh))
                ret.push_back(cell(nw, nh));
        }
        return ret;
    }
    template <class C>
    void cAutomaton<C>::coords(
        int &w, int &h,
        C *c)
    {
        int id = c->ID();
        h = id / myWidth;
        w = id - h * myWidth;
    }
    template <class C>
    std::string cAutomaton<C>::text()
    {
        std::stringstream s;
        int index = 0;
        for (int r = 0; r < myHeight; r++)
        {
            s << text( r ) << "\n";
        }
        return s.str();
    }
    template <class C>
    std::string cAutomaton<C>::text(int row)
    {
        std::stringstream s;
        int index = row * myWidth;
        for (int c = 0; c < myWidth; c++)
        {
            s << myCell[index++]->text();
        }
        return s.str();
    }
}
