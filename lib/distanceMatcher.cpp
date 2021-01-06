#include "distanceMatcher.hpp"
#include "inMemMap.hpp"
#include <string>
#include <cmath>

DistanceMatcher::DistanceMatcher(InMemMap* map, float maxDist, float maxDistInit):
    mpMap(map), bOnlyEdges(true){
    fMaxDist = maxDist;
    // fMaxDistInit = maxDistInit < 0 ? maxDist : maxDistInit;
    if(maxDistInit < 0) fMaxDistInit = maxDist;
    else fMaxDistInit = maxDistInit;
}

int DistanceMatcher::createStartNodes(){
    bool useEdges = bOnlyEdges;
    Point startNode = mPath[0];
    std::vector<std::string> nodes;
    if(useEdges){
        mpMap->edgesCloseTo(startNode, fMaxDistInit, nodes);
    }

    return 0;
}

void DistanceMatcher::match(const std::vector<Point>& path){
    mPath = path;
    int numStartNodes = createStartNodes();
}
