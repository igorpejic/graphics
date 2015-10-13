#ifndef _readpoints_h
#define _readpoints_h
#include "shapes_loc.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Point
{
    Point(double _x, double _y) : x(_x), y(_y){}
    double x,y;
};

std::vector<Point> readPoints()
{
    std::vector<Point> points;
    std::ifstream infile(shapes_loc().c_str());
    std::string line,w1,w2;
    int linecount = 0 ;
    double x,y;
    if ( infile )
    {
        while ( getline( infile , line ) )
        {
            //std::cout << linecount << ": " << line << '\n' ;//supposing '\n' to be line end
            std::istringstream iss(line, std::istringstream::in);
            if (!line.length())
            {   /*std::cout<<"empty line\n";*/ continue;}

            if (line[0] == '#') // Ignore the line starts with #
            { /*std::cout<<"comment line\n";*/ continue;}

            std::istringstream(line) >> w1 >> w2;
            x = std::stod(w1);
            y = std::stod(w2);
            //std::cout<<x<<"\t"<<y<<std::endl;
            points.push_back(Point(x,y));
            linecount++ ;
        }
    }
    return points;
}
#endif
