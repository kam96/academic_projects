#include "MyMazeGenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MyMazeGenerator, "My Maze Generator (Required)");

MyMazeGenerator::MyMazeGenerator(){}

//random_device device;
//default_random_engine engine{device()};

Direction MyMazeGenerator::randomDirection() 
{ 
    uniform_int_distribution<int> distribution{0,3};
    switch(distribution(engine))
    {
        case 1: return Direction::right;
        case 2: return Direction::down;
        case 3: return Direction::left;
    }
    return Direction::up;
}

vector<Direction> MyMazeGenerator::available_directions(vector<vector<bool>> visited, pair<int,int> cell)
{
    vector<Direction> availableDir;

    if (cell.first > 0 && visited[cell.first-1][cell.second] == false)
        availableDir.push_back(Direction::left); 
    if (cell.first < visited.size()-1 && visited[cell.first+1][cell.second] == false) 
        availableDir.push_back(Direction::right);
    if (cell.second > 0 && visited[cell.first][cell.second-1] == false) 
        availableDir.push_back(Direction::up);
    if (cell.second < visited[cell.first].size()-1 && visited[cell.first][cell.second+1]==false)  
        availableDir.push_back(Direction::down);

    return availableDir;
}

pair<int,int> MyMazeGenerator::move_cell(pair<int,int> cell, Direction dir)
{
    switch(dir)
    {
        case Direction::down: cell.second += 1;
            break;
        case Direction::right: cell.first += 1;
            break;
        case Direction::up: cell.second -= 1;
            break;
        case Direction::left: cell.first -= 1;
            break;
    }

    return cell;
}

void MyMazeGenerator::createMaze(Maze &maze, vector<vector<bool>> &visited, pair<int,int> cell)
{
    visited[cell.first][cell.second] = true;
    vector<Direction> possibleDir = available_directions(visited, cell);

    while(!possibleDir.empty()) 
    {
        Direction randomDir = randomDirection();
        bool exit = false;
        while(!exit)
        {
            for (int i = 0; i < possibleDir.size(); i++)
            {
                if (randomDir == possibleDir[i]) 
                {
                   exit = true;
                   break;
                }
                else
                   randomDir = randomDirection();
            }
        }

        maze.removeWall(cell.first, cell.second, randomDir);
        cell = move_cell(cell,randomDir);
        createMaze(maze,visited,cell);
        possibleDir = available_directions(visited,cell);
    }
}

void MyMazeGenerator::generateMaze(Maze &maze)
{
    vector<vector<bool>> visitedTile(maze.getWidth(), vector<bool> (maze.getHeight()));
    pair <int,int> currentCell = make_pair(0,0);
    for (int i = 0; i < maze.getWidth(); i++)
    {
        for (int j = 0; j < maze.getHeight(); j++)
            visitedTile[i][j] = false;
    } 

    maze.addAllWalls(); 
    createMaze(maze, visitedTile, currentCell);
}
