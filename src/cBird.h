class cCellBirds;

/// basic little brown bird
class cBird
{
public:
    int myCount;

    cBird()
        : myCount(1)
    {
    }
    virtual char text() const
    {
        return 'b';
    }
    virtual void move(
        cCellBirds *from,
        const std::vector<cCellBirds*>& neighbours);

    virtual int countBirds() const
    {
        return 1;
    }

protected:

    /** Move to empty cell
     * @param[in] from pointer to cell departing
     * @param[in] to pointer to cell reaching
     * @return true id f move succesful
     */
    bool MoveToEmpty(
        cCellBirds *from,
        cCellBirds *to);
};

/// An Eagle eats other birds
class cEagle : public cBird
{
public:
    virtual char text() const
    {
        return 'E';
    }
    virtual void move(
        cCellBirds *from,
        const std::vector<cCellBirds*>& neighbours);

    /// eagles do not count as birds
    virtual int countBirds() const
    {
        return 0;
    }
};

/// a flock of birds
class cFlock : public cBird
{
public:
    virtual char text()
    {
        return 'f';
    }
    virtual void move(
        cCellBirds *from,
        const std::vector<cCellBirds*>& neighbours);
    virtual int countBirds() const
    {
        return myCount;
    }
};
