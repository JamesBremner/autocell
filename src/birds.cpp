#include <iostream>
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
    // std::cout << id << " at " << w <<","<< h << "\n";
    auto n = Terrain.neighbours(w, h);
    myBird->move(
        this,
        n[rand() % n.size()]);
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
    cCellBirds *to)
{
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
    cCellBirds *to)
{
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
    cCellBirds *to)
{
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

int main()
{

    generateRandom();

    Display();

    for (auto c : Terrain)
    {
        c->move();
    }
    std::cout << "move\n";
    Display();
}
