#include "MyMazeSolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MyMazeSolver, "MyMazeSolver (Required)");

MyMazeSolver::MyMazeSolver(){};

vector<Direction> MyMazeSolver::available_directions
(const Maze &maze, pair<int,int> cell,vector<vector<bool>> visited)
{
    vector <Direction> availableDir;
    
    if (!maze.wallExists(cell.first,cell.second,Direction::up) && !visited[cell.first][cell.second-1])
        availableDir.push_back(Direction::up);
    if (!maze.wallExists(cell.first,cell.second,Direction::right) && !visited[cell.first+1][cell.second])
        availableDir.push_back(Direction::right);
    if (!maze.wallExists(cell.first,cell.second,Direction::down) && !visited[cell.first][cell.second+1])
        availableDir.push_back(Direction::down);
    if (!maze.wallExists(cell.first,cell.second,Direction::left) && !visited[cell.first-1][cell.second])
        availableDir.push_back(Direction::left);

    return availableDir;
}

void MyMazeSolver::solver(const Maze &maze,MazeSolution &mazeSolution, vector<vector<bool>> visited)
{
    pair<int,int> current = mazeSolution.getCurrentCell();

    if (mazeSolution.isComplete())
        return;

    visited[current.first][current.second] = true;

    vector<Direction> possibleDir = available_directions(maze,current,visited);

    while(!possibleDir.empty())
    {
        mazeSolution.extend(possibleDir[0]);
        solver(maze,mazeSolution,visited);

        if (mazeSolution.isComplete())
            return;
    }

    mazeSolution.backUp();

    if(current != mazeSolution.getEndingCell())
        solver(maze,mazeSolution,visited);
}

void MyMazeSolver::solveMaze(const Maze &maze, MazeSolution &mazeSolution)
{
    mazeSolution.restart();
    vector <vector<bool>> visited(maze.getWidth(), vector<bool> (maze.getHeight()));

    for (int i = 0; i < maze.getWidth(); i++)
    {
        for (int j = 0; j < maze.getHeight(); j++)
        {
            visited[i][j] = false;
        }
    }

    solver(maze,mazeSolution,visited);
}
