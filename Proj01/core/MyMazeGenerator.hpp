#include "MazeGenerator.hpp"
#include "Direction.hpp"
#include "Maze.hpp"
#include <random>
using namespace std;

class MyMazeGenerator : public MazeGenerator
{
public:
    //Default constructor for MyMazeGenerator
    MyMazeGenerator();

    //Inherited from MazeGenerator
    virtual void generateMaze(Maze& maze);
private:
    //Declaration of random device and engine used in randomDirection()
    random_device device;
    default_random_engine engine{device()};

    //Returns a random direction using a uniform integer distribution
    //and integer switch to generate any direction at random 
    //UP=0,RIGHT=1,DOWN=2,LEFT=3
    Direction randomDirection();

    //Determines if maze cells around the parameter 'cell' exist and 
    //have been visited. If the cell exists and has not been visited
    //the direction is then added to the vector to be returned
    vector<Direction> available_directions(vector<vector<bool>> visited, pair<int,int> cell);

    //Adds/subtracts from the coordinates of the parameter 'cell' and 
    //returns the new values. 'dir' is passed in order to determine
    //which coordinate in the pair is to be changed
    pair<int,int> move_cell(pair<int,int> cell, Direction dir);

    //Recursive depth-first search function. Is passed the current maze,
    //a vector of vector of cells visited, and a selected cell. The 
    //function will mark the cell as visited in the vector of vectors
    //and then select a neighbor at random based on possible directions.
    //It continues to call itself until no more unvisited neighbors exist.
    void createMaze(Maze &maze, vector<vector<bool>> &visited, pair<int,int> cell);
};
