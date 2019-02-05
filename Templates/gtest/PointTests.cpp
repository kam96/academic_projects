// PointTest.cpp
//
// ICS 45C Fall 2016
// Code Example
//
// This source file contains unit tests for our Point<CoordinateType>
// template class.

#include <gtest/gtest.h>
#include <cmath>
#include <string>
#include "Point.hpp"



TEST(PointTest, pointsWithIntCoordinatesHaveTheirGivenCoordinates)
{
    Point<int> p{3, -2, 5};
    EXPECT_EQ(3, p.x());
    EXPECT_EQ(-2, p.y());
    EXPECT_EQ(5, p.z());
}


TEST(PointTest, pointsWithDoubleCoordinatesHaveTheirGivenCoordinates)
{
    Point<double> p{3.5, 6.75, -2.125};
    EXPECT_EQ(3.5, p.x());
    EXPECT_EQ(6.75, p.y());
    EXPECT_EQ(-2.125, p.z());
}


TEST(PointTest, pointsWithStringCoordinatesAreStrangelyLegal)
{
    // It's legal to instantiate Point objects with string coordinates,
    // though you won't be able to do certain things to them -- in
    // particular, you won't be able to calculate a distance between
    // them.

    Point<std::string> p{"Boo", "is", "perfect"};
    EXPECT_EQ(std::string{"Boo"}, p.x());
    EXPECT_EQ(std::string{"is"}, p.y());
    EXPECT_EQ(std::string{"perfect"}, p.z());
}


TEST(PointTest, coordinatesCanBeUpdated)
{
    Point<int> p{1, 2, 3};

    p.x() = -4;
    p.y() = 9;
    p.z() = -5;

    EXPECT_EQ(p.x(), -4);
    EXPECT_EQ(p.y(), 9);
    EXPECT_EQ(p.z(), -5);
}


TEST(PointTest, distancesAreCalculatedCorrectly)
{
    // (2, 3, 6, 7) is a Pythagorean quadruple

    Point<double> p1{10, -6, 1};
    Point<double> p2{12, -9, 7};

    EXPECT_NEAR(7.0, p1.distanceFrom(p2), 0.0001);
}

