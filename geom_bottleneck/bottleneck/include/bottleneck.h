/*
    Copyrigth 2015, D. Morozov, M. Kerber, A. Nigmetov

    This file is part of GeomBottleneck.

    GeomBottleneck is free software: you can redistribute it and/or modify
    it under the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GeomBottleneck is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with GeomBottleneck.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef BOTTLENECK_H
#define BOTTLENECK_H


//#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>

#include "basic_defs_bt.h"
#include "bound_match.h"
//#include "test_neighb_oracle.h"
//#include "test_dist_calc.h"

namespace geom_bt {
typedef std::pair<double, std::pair<size_t, size_t>> DistVerticesPair;

// functions taking DiagramPointSet as input.
// ATTENTION: parameters A and B (diagrams) will be changed after the call
// (projections added).

// return the interval (distMin, distMax) such that: 
// a) actual bottleneck distance between A and B is contained in the interval
// b) if the interval is not (0,0), then  (distMax - distMin) / distMin < epsilon 
std::pair<double, double> bottleneckDistApproxInterval(DiagramPointSet& A, DiagramPointSet& B, const double epsilon);


// heuristic (sample diagram to estimate the distance)
std::pair<double, double> bottleneckDistApproxIntervalHeur(DiagramPointSet& A, DiagramPointSet& B, const double epsilon);

// get approximate distance,
// see bottleneckDistApproxInterval
double bottleneckDistApprox(DiagramPointSet& A, DiagramPointSet& B, const double epsilon);

// get exact bottleneck distance,
double bottleneckDistExact(DiagramPointSet& A, DiagramPointSet& B, const int decPrecision);

// get exact bottleneck distance,
double bottleneckDistExact(DiagramPointSet& A, DiagramPointSet& B);


// functions taking containers as input
// template parameter PairContainer must be a container of pairs of real
// numbers (pair.first = x-coordinate, pair.second = y-coordinate)
// PairContainer class must support iteration of the form
// for(it = pairContainer.begin(); it != pairContainer.end(); ++it)

// return the interval (distMin, distMax) such that: 
// a) actual bottleneck distance between A and B is contained in the interval
// b) if the interval is not (0,0), then  (distMax - distMin) / distMin < epsilon 
template<class PairContainer>
std::pair<double, double> bottleneckDistApproxInterval(PairContainer& A, PairContainer& B, const double epsilon)
{
    DiagramPointSet a(A.begin(), A.end());
    DiagramPointSet b(B.begin(), B.end());
    return bottleneckDistApproxInterval(a, b, epsilon);
}


template<class PairContainer>
double bottleneckDistApproxHeur(PairContainer& A, PairContainer& B, const double epsilon)
{
    DiagramPointSet a(A.begin(), A.end());
    DiagramPointSet b(B.begin(), B.end());
    std::pair<double,  double> resPair = bottleneckDistApproxIntervalHeur(a, b, epsilon);
    return resPair.second;
}


// get approximate distance,
// see bottleneckDistApproxInterval
template<class PairContainer>
double bottleneckDistApprox(PairContainer& A, PairContainer& B, const double epsilon)
{
    DiagramPointSet a(A.begin(), A.end());
    DiagramPointSet b(B.begin(), B.end());
    return bottleneckDistApprox(a, b, epsilon);
}

// get exact bottleneck distance,
template<class PairContainer>
double bottleneckDistExact(PairContainer& A, PairContainer& B)
{
    DiagramPointSet a(A.begin(), A.end());
    DiagramPointSet b(B.begin(), B.end());
    return bottleneckDistExact(a, b, 14);
}


// get exact bottleneck distance,
template<class PairContainer>
double bottleneckDistExact(PairContainer& A, PairContainer& B, const int decPrecision)
{
    DiagramPointSet a(A.begin(), A.end());
    DiagramPointSet b(B.begin(), B.end());
    return bottleneckDistExact(a, b, decPrecision);
}

// fill in result with points from file fname
// return false if file can't be opened
// or error occurred while reading
// decPrecision is the maximal decimal precision in the input,
// it is zero if all coordinates in the input are integers
bool readDiagramPointSet(const char* fname, std::vector<std::pair<double, double>>& result, int& decPrecision);
// wrapper for standard string
bool readDiagramPointSet(const std::string& fname, std::vector<std::pair<double, double>>& result, int& decPrecision);


// these two functions are now just wrappers for the previous ones,
// in case someone needs them; decPrecision is ignored
bool readDiagramPointSet(const char* fname, std::vector<std::pair<double, double>>& result);
// wrapper for standard string
bool readDiagramPointSet(const std::string& fname, std::vector<std::pair<double, double>>& result);

}
#endif
