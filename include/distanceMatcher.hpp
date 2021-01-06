#include <iostream>
#include <vector>

#include "inMemMap.hpp"
#include "point.hpp"
// #define path std::pair<float, float>

class DistanceMatcher{
public:
    DistanceMatcher(InMemMap* map, float maxDist, float MaxDistInit=-1);
    void match(const std::vector<Point>& path);
    // Base Matching
    InMemMap* mpMap;
    std::vector<Point> mPath;
    float fMaxDistInit; // :param max_dist_init: Maximum distance from start location (if not given, uses max_dist)
    float fMaxDist; // :param max_dist_init: Maximum distance from start location (if not given, uses max_dist)

private:
    bool bOnlyEdges;  // only_edges: Do not include nodes as states, only edges. This is the typical setting for HMM methods.
    int createStartNodes();
};