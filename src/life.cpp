#include <autocell.h>
#include <iostream>
#include <time.h>
#ifdef GUI
#include "wex.h"
#endif
#include "cConway.h"


int main()
{
    // contruct conway game of life
    cConway conway(40, 40);

    // initialize with living cells
    conway.random(320);
    //conway.glider();

#ifndef GUI

    // simulate 5 generations
    conway.live(1);


#else

    // construct top level application window
    wex::gui &form = wex::maker::make();
    form.move({50, 50, 400, 400});
    form.text("Conway's Game of Life");

    // update display and move forward one generation
    wex::timer *myTimer = new wex::timer(form, 1000);
    form.events().timer([&](int id)
                        { form.update(); });
    form.events().draw([&](PAINTSTRUCT &ps)
                       {
                           conway.displayGUI( ps );
                       });

    // show the application
    form.show();

    //Pass the control of the application to the windows message queue.
    form.run();

#endif
}