#include <iostream>
#include <autocell.h>

namespace cell
{
int cCell::myLastID = -1;

cCell::cCell()
{
    myID = ++myLastID;
}

cAutomaton::cAutomaton(
    int w, int h)
    : myWidth( w )
    , myHeight( h )
    , myfwrap( true )
{
    cCell::RestartID();
    for( int k = 0; k < myWidth*myHeight; k++ )
    {
        myCell.push_back( cell_t(new cCell()) );
    }
}
cell_t cAutomaton::cell(
    int w, int h )
{
    if( 0 > w || w >= myWidth || 0 > h || h >= myHeight )
        throw std::runtime_error(
            "cAutomaton cell out of bounds"
            + std::to_string( w ) + " " + std::to_string( h ) );
    return myCell[ myWidth * h + w ];
}
std::vector< cell_t > cAutomaton::neighbours(
    int w, int h )
{
    if( myfwrap )
        return neighboursWrap( w, h );
    else
        return neighboursNoWrap( w, h );
}
std::vector< cell_t > cAutomaton::neighboursWrap(
    int w, int h )
{
    std::vector< cell_t > ret;
    int nw, nh;
    nw = w-1;
    if( nw < 0 )
        nw = myWidth-1;
    nh = h;
    ret.push_back( cell( nw, nh ) );
    nw = w+1;
    if( nw >= myWidth )
        nw = 0;
    nh = h;
    ret.push_back( cell( nw, nh ) );
    nw = w;
    nh = h+1;
    if(nh >= myHeight)
        nh = 0;
    ret.push_back( cell( nw, nh ) );
    nw = w;
    nh = h-1;
    if( nh < 0 )
        nh = myHeight-1;
    ret.push_back( cell( nw, nh ) );
    return ret;
}

std::vector< cell_t > cAutomaton::neighboursNoWrap(
    int w, int h )
{
    std::vector< cell_t > ret;
    int nw, nh;
    if( w != 0 )
    {
        nw = w-1;
        if( nw < 0 )
            nw = myWidth-1;
        nh = h;
        ret.push_back( cell( nw, nh ) );
    }
    if( w != myWidth-1 )
    {
        nw = w+1;
        if( nw >= myWidth )
            nw = 0;
        nh = h;
        ret.push_back( cell( nw, nh ) );
    }
    if( h != myHeight-1 )
    {
        nw = w;
        nh = h+1;
        if(nh >= myHeight)
            nh = 0;
        ret.push_back( cell( nw, nh ) );
    }
    if( h != 0 )
    {
        nw = w;
        nh = h-1;
        if( nh < 0 )
            nh = myHeight-1;
        ret.push_back( cell( nw, nh ) );
    }
    return ret;
}
void cAutomaton::coords(
    int& w, int& h,
    cell_t c )
{
    int id = c->ID();
    h = id / myWidth;
    w = id - h * myWidth;

}
}
