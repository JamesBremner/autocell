#include <iostream>
#include <wex.h>
#include <autocell.h>
#include <cBird.h>

/// Specialized autocell that can  contain a bird
class cCellBirds : public cell::cCell
{
public:
    cCellBirds()
        : cell::cCell(), myBird(0)
    {
    }

    /// move bird in this cell to random neighbour cell
    void move();

    /// set the bird located in this cell
    void set(cBird *b)
    {
        myBird = b;
    }

    /// get pointer to bird in this cell
    cBird *get()
    {
        return myBird;
    }

    /// text representing bird in this cell
    char text()
    {
        if (!myBird)
            return ' ';
        return myBird->text();
    }

private:
    cBird *myBird;
};

cell::cAutomaton<cCellBirds> Terrain(10, 10);

void cCellBirds::move()
{
    if (!myBird)
        return;

    int w, h;
    Terrain.coords(w, h, this);
    myBird->move(
        this,
        Terrain.neighbours(w, h));
}

bool cBird::MoveToEmpty(
    cCellBirds *from,
    cCellBirds *to)
{
    cBird *occupant = to->get();
    if (occupant)
        if (occupant->text() != ' ')
            return false;
    to->set(this);
    from->set(0);
    return true;
}

void cBird::move(
    cCellBirds *from,
    const std::vector<cCellBirds*>& neighbours )
{
    cCellBirds *to = neighbours[rand() % neighbours.size()];

    if (MoveToEmpty(from, to))
        return;

    cBird *occupant = to->get();
    switch (occupant->text())
    {
    case 'b':
        // birds are territorial
        // the occupant will not allow another bird to move in
        break;

    case 'f':
        // join the flock
        occupant->myCount++;
        from->set(0);
        break;

    case 'E':
        // bad luck, Eagle eats bird
        from->set(0);
        break;
    }
}
void cEagle::move(
    cCellBirds *from,
    const std::vector<cCellBirds*>& neighbours)
{
    // hunt for prey
    cCellBirds *to = 0;
    for( auto prey : neighbours )
    {
        if( prey->get() )
            if( prey->get()->text() == 'b' ||
            prey->get()->text() == 'f' )
            {
                to = prey;
                break;
            }
    }
    if( ! to ) {
        // no prey in sight, move randomly
        to = neighbours[rand() % neighbours.size()];
    }

    if (MoveToEmpty(from, to))
        return;
    cBird *occupant = to->get();
    switch (occupant->text())
    {
    case 'b':
        // Eagle eats bird
        to->set(this);
        from->set(0);
        break;

    case 'f':
        // Eagle eats one bird
        to->get()->myCount--;
        return;

    case 'E':
        // birds are territorial
        // the occupant will not allow another bird to move in
        break;
    }
}

void cFlock::move(
    cCellBirds *from,
    const std::vector<cCellBirds*>& neighbours)
{
    cCellBirds *to = neighbours[rand() % neighbours.size()];
    if (MoveToEmpty(from, to))
        return;

    cBird *occupant = to->get();
    switch (occupant->text())
    {
    case 'b':
        myCount++;
        to->set(this);
        from->set(0);
        break;

    case 'E':
        myCount--;
        return;

    case 'f':
        occupant->myCount += myCount;
        from->set(0);
        return;
    }
}

void generateRandom()
{
    std::set<int> chosen;
    srand(time(NULL));        // seed random no generator
    while (chosen.size() < 5) // choose 5
        Terrain.random(chosen)->set(new cBird());
    Terrain.random(chosen)->set(new cEagle());
}

int countBirds()
{
    int count = 0;
    for (auto c : Terrain)
    {
        if (c->get())
            count += c->get()->countBirds();
    }
    return count;
}

void Display()
{
    std::cout << Terrain.text();
    std::cout << countBirds() << "\n";
}

void displayGUI(
    PAINTSTRUCT &ps)
{
    wex::shapes S(ps);
    for (int row = 0; row < 10; row++)
        S.text(
            Terrain.text(row),
            {5, 20 * row});
}

int main()
{

    generateRandom();

    // construct top level application window
    wex::gui &form = wex::maker::make();
    form.move({50, 50, 400, 400});
    form.text("Birds");

    // update display and move forward one generation
    wex::timer *myTimer = new wex::timer(form, 500);
    form.events().timer(
        [&](int id)
        {
            form.update();
        });
    form.events().draw(
        [&](PAINTSTRUCT &ps)
        {
            for (auto c : Terrain)
            {
                c->move();
            }
            displayGUI(ps);
            form.text("Birds " + std::to_string(countBirds()));
        });

    // show the application
    form.show();

    // Pass the control of the application to the windows message queue.
    form.run();
}
