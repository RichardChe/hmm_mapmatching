#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "point.hpp"

class MapNode{
public:
    MapNode(float x, float y, std::string to);
    Point mPoint;
    std::vector<std::string> vTo;
};

class InMemMap{
public:
    InMemMap(std::string name, std::map<std::string, std::string> graphString,
             bool useLatLon=true, int linkedEdges=false,
             bool useRTree=false, bool deserialization=false);
    ~InMemMap();
    // def __init__(self, name, use_latlon=True, use_rtree=False, index_edges=False,
                //  crs_lonlat=None, crs_xy=None, graph=None, linked_edges=None, dir=None, deserializing=False):
    std::string sName;
    bool bUseLatLon;
    float distance(const Point& p1, const Point& p2); // TODO: function ptr
    void distancePtToSeg(Point p, Point s1, Point s2, float& dist,
                           Point& proj, float& t);
    int lines_parallel(); //TODO: func parallel

    bool bDeserialization;
    int iLinkedEdges; //TODO
    // int rtree; //TODO
    bool bUseRTree; //TODO
    std::map<std::string, MapNode*> mGraph;
    void edgesCloseTo(Point pt, float maxDist, std::vector<std::string>& result);
private:
    void getBoxAroundPoint(const Point& pt, float dist, Point& leftTop,
                           Point& rightBottom);
    void getItemsInBBox(const Point& leftTop, const Point& rightBottom,
                        std::map<std::string, MapNode*>& nodesInROI);
    // void getItemsInBBox()
};