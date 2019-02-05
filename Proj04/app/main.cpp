// main.cpp
//
// ICS 46 Spring 2017
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.

#include "InputReader.hpp"
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "TripReader.hpp"
#include <iostream>
#include <cmath>

//testing
#include <algorithm>
#include <iterator>

double distanceFunction(const RoadSegment &road)
{ 
    return road.miles;
}

double timeFunction(const RoadSegment &road)
{
    return road.miles/road.milesPerHour;
}

int main()
{
    InputReader input(std::cin);
    RoadMap map = RoadMapReader().readRoadMap(input);
    std::vector<Trip> log = TripReader().readTrips(input);

    if (!map.isStronglyConnected())
    {
        std::cout << "Not connected" << std::endl;
        return 0;
    }

    for (int i = 0; i < log.size(); i++)
    {
        std::map<int,int> dijkstra;

        if (log[i].metric == TripMetric::Distance)
        {
            std::cout << "Shortest distance from " << map.vertexInfo(log[i].startVertex) << " to " 
                      << map.vertexInfo(log[i].endVertex) << std::endl;

            dijkstra = map.findShortestPaths(log[i].startVertex,distanceFunction);

            std::vector<int> path;
            double distance = 0;

            while(true)
            {
                path.push_back(log[i].endVertex);
                if (log[i].endVertex == dijkstra.at(log[i].endVertex))
                    break;
                log[i].endVertex = dijkstra.at(log[i].endVertex);
            }

            std::cout << "    Begin at " << map.vertexInfo(log[i].startVertex) << std::endl;

            for (int i = path.size()-1; i>= 1; --i)
            {
                std::cout << "    Countinue to " << map.vertexInfo(path[i-1])
                     << " (" << map.edgeInfo(path[i],path[i-1]).miles << " miles)" << std::endl;
                distance += map.edgeInfo(path[i],path[i-1]).miles;
            }

            std::cout << "Total Distance: " << distance << " miles" << std::endl;

        }
        else
        {
            std::cout << "Shortest time from " << map.vertexInfo(log[i].startVertex) << " to " 
                      << map.vertexInfo(log[i].endVertex) << std::endl;

            dijkstra = map.findShortestPaths(log[i].startVertex,timeFunction);

            std::vector<int> path;
            double finalTime = 0;

            while(true)
            {
                path.push_back(log[i].endVertex);
                if (log[i].endVertex == dijkstra.at(log[i].endVertex))
                    break;
                log[i].endVertex = dijkstra.at(log[i].endVertex);
            }

            std::cout << "    Begin at " << map.vertexInfo(log[i].startVertex) << std::endl;

            for (int i = path.size()-1; i >= 1; --i)
            {
                double time = map.edgeInfo(path[i],path[i-1]).miles/map.edgeInfo(path[i],path[i-1]).milesPerHour;
                time = time *3600;
                int hours = floor(time/3600);
                int mins = floor(time/60);
                int seconds = floor(time - (hours*3600) - (mins*60));

                std::cout << "    Continue to " << map.vertexInfo(path[i-1])
                          << " (" << map.edgeInfo(path[i],path[i-1]).miles
                          << " miles @ " << map.edgeInfo(path[i],path[i-1]).milesPerHour
                          << " miles per hour = " << hours << " hours " << mins << " min " 
                          << seconds << " seconds" << std::endl;
                finalTime += time;
            }

            int finalHours = floor(finalTime/3600);
            int finalMins = floor(finalTime/60);
            int finalSeconds = floor(finalTime - (finalHours*3600) - (finalMins*60));
            std::cout << "Total Time: " << finalHours << " hours " << finalMins << " min " << finalSeconds 
                      << " seconds" << std::endl;
        }    
    }

    return 0;
}

