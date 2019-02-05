#include "Maze.hpp"
#include "MazeSolver.hpp"
#include "Direction.hpp"
#include "MazeSolution.hpp"
using namespace std;

class MyMazeSolver : public MazeSolver
{
public:
    MyMazeSolver();

    vector <Direction> available_directions
    (const Maze &maze, pair<int,int> cell, vector<vector<bool>> visited);

    void solver(const Maze &maze, MazeSolution &mazesolution, vector<vector<bool>> visited);

    virtual void solveMaze(const Maze &maze, MazeSolution &mazeSolution);
};
