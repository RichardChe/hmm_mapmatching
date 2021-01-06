#include <vector>
#include <regex>
#include <string>
#include <iostream>
#include <sstream>
#include "inMemMap.hpp"
#include "point.hpp"
#include <cmath>
#include <algorithm>

// #define DEBUG

struct StartNode
{
    StartNode(float dist, MapNode* matchNode_, MapNode* nbrNode_, Point projPt_,
              float ti):fDist(dist), matchNode(matchNode_), nbrNode(nbrNode_),
              projPt(projPt_), fti(ti){};
// results.append((dist, (label, oloc), nbr, nbr_data[0], pi, ti))
    float fDist;
    MapNode* matchNode;
    MapNode* nbrNode;
    Point projPt;
    float fti;
};

void project(Point s1, Point s2, Point p, Point& proj, float& t,
              float delta=0){
    if(s1.fX == s2.fX && s1.fY == s2.fY){
        proj = s1;
        t = 0.0;
        return;
    }
    float l2 = (s1.fX - s2.fX) * (s1.fX - s2.fX) + 
               (s1.fY - s2.fY) * (s1.fY - s2.fY);
    // t = max(delta, min(1-delta, ((p[0]-s1[0])*(s2[0]-s1[0]) + (p[1]-s1[1])*(s2[1]-s1[1])) / l2))
    t = std::max(delta, std::min(1 - delta, ((p.fX-s1.fX)*(s2.fX-s1.fX) +
                        (p.fY-s1.fY)*(s2.fY-s1.fY)) / l2));
    proj = Point(s1.fX + t * (s2.fX-s1.fX), s1.fY + t * (s2.fY-s1.fY));
}

MapNode::MapNode(float x, float y, std::string to)
    : mPoint(x, y){
    std::regex ws_re("\\,"); // split with ,
    vTo = std::vector<std::string>(std::sregex_token_iterator(to.begin(), to.end(), ws_re, -1),
                               std::sregex_token_iterator() );
    
#ifdef DEBUG
    std::cout << "in MapNode:" << std::endl;
    std::cout << "X:" << mPoint.fX << " Y:" << mPoint.fY << std::endl;
    for(auto n:vTo){
        std::cout << n << std::endl;
    }
#endif    
}

InMemMap::~InMemMap(){
    for(auto currNode: mGraph){
        delete currNode.second;
    }
}

InMemMap::InMemMap(std::string name, std::map<std::string, std::string> graphString,
                   bool useLatLon, int linkedEdges, bool useRTree,
                   bool deserialization)
    :sName(name), bUseLatLon(useLatLon), 
     bUseRTree(useRTree), bDeserialization(deserialization){
        iLinkedEdges = linkedEdges; // TODO change a extra classname
        float currx, curry;
        std::string currto;
        for(auto nodeString: graphString){
            std::string currNodeName(nodeString.first);
            std::istringstream strStream(nodeString.second);
            strStream >> currx >> curry >> currto;
            // std::cout << currx << " " << curry << " "<< currto << std::endl;            
            MapNode* currNode = new MapNode(currx, curry, currto);
            mGraph.insert(std::pair<std::string, MapNode*>(currNodeName, currNode) );
        }
    }

// fMaxDistInit
void InMemMap::edgesCloseTo(Point pt, float maxDist, std::vector<std::string>& result){
    std::cout << "Searching closeby nodes with linear search, use an index and set max_dist" << std::endl;
    float lat = pt.fY, lon = pt.fX;
    Point leftTop, rightBottom;
    getBoxAroundPoint(pt, maxDist, leftTop, rightBottom);
    std::map<std::string, MapNode*> nodesInROI;
    getItemsInBBox(leftTop, rightBottom, nodesInROI);
# ifdef DEBUG
    std::cout << "nodesInROI.size(): "<< nodesInROI.size() << std::endl;
# endif    
    for(auto currNode : nodesInROI){
        std::string currKey = currNode.first;
        MapNode* currMapNode = currNode.second;
        std::vector<std::string> currNbrs = currMapNode->vTo;
        for(auto currNbr : currNbrs){
            if(currNbr == currKey)
                continue;
            MapNode* currNbrNode = mGraph[currNbr];
            Point currNbrLoc = currNbrNode->mPoint;
            float dist, ti;
            Point projPt;
            distancePtToSeg(pt, currMapNode->mPoint, currNbrLoc, dist, projPt, ti);
            if(dist < maxDist){
                StartNode currStartNode(dist, currMapNode, currNbrNode, projPt, ti);
            }
        }
    }
}

void InMemMap::getItemsInBBox(const Point& leftTop, const Point& rightBottom,
                              std::map<std::string, MapNode*>& nodesInROI){
    float xMin = leftTop.fX, yMin = leftTop.fY;
    float xMax = rightBottom.fX, yMax = rightBottom.fY;
    for(auto mapNode : mGraph){
        std::string currKey = mapNode.first;
        MapNode* currNode = mapNode.second;
# ifdef DEBUG
        std::cout << "in getItemsInBBox" << std::endl;
        std::cout << "currKey:" <<currKey << std::endl;
        // std::cout << xMin << " "<< yMin << " "<<xMax << " " << yMax << std::endl;
        // std::cout << currNode->mPoint.fX  << " " << currNode->mPoint.fY << std::endl;
        // std::cout << "----------" << std::endl;
# endif
        if(xMin < currNode->mPoint.fX && currNode->mPoint.fX < xMax &&
           yMin < currNode->mPoint.fY && currNode->mPoint.fY < yMax){
            nodesInROI.insert(std::pair<std::string, MapNode*>(currKey, currNode));
        }
    }
}

float InMemMap::distance(const Point& p1, const Point& p2){
    // std::cout << "not implemented..." << std::endl;
    return sqrtf((p1.fX - p2.fX) * (p1.fX - p2.fX) + 
                 (p1.fY - p2.fY) * (p1.fY - p2.fY));
} // TODO: function ptr

void InMemMap::distancePtToSeg(Point p, Point s1, Point s2, float& dist,
                                 Point& proj, float& t){
    project(s1, s2, p, proj, t);
    dist = distance(proj, p);
#ifdef DEBUG
    std::cout << "dist:" << dist << " proj:(" << proj.fX << "," << proj.fY << ")"
              << "t: " << t << std::endl;
#endif    
        // p_int, ti = project(s1, s2, p, delta=delta)
    // return distance(p_int, p), p_int, ti

    // std::cout << "not implemented..." << std::endl;
    // return 0; 
} //TODO: func ptr

// int InMemMap::distance_segment_to_segment(){
//     std::cout << "not implemented..." << std::endl;
//     return 0; 
// } //TODO: func ptr

int InMemMap::lines_parallel(){
    std::cout << "not implemented..." << std::endl;
    return 0; 
} //TODO: func parallel

void InMemMap::getBoxAroundPoint(const Point& pt, float dist, Point& leftTop,
                                    Point& rightBottom){
    // std::cout << "not implemented..." << std::endl;
    leftTop.fX = pt.fX - dist;
    leftTop.fY = pt.fY - dist;
    rightBottom.fX = pt.fX + dist;
    rightBottom.fY = pt.fY + dist;
} //TODO: func parallel