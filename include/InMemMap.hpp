#include <string>
#include <iostream>
#include <map>
#include <vector>

class MapNode{
public:
    MapNode(float x, float y, std::string to);
private:
    float _fX;
    float _fY; 
    std::vector<std::string> _vTo;
};

class InMemMap{
public:
    InMemMap(std::string name, std::map<std::string, std::string> graphString,
             bool useLatLon=true, int linkedEdges=false,
             bool useRTree=false, bool deserialization=false);
    // def __init__(self, name, use_latlon=True, use_rtree=False, index_edges=False,
                //  crs_lonlat=None, crs_xy=None, graph=None, linked_edges=None, dir=None, deserializing=False):
    std::string sName;
    bool bUseLatLon;
    int distance(); // TODO: function ptr
    int distance_pt_to_seg(); //TODO: func ptr
    int distance_segment_to_segment(); //TODO: func ptr
    int lines_parallel(); //TODO: func parallel
    int box_around_point(); //TODO: func parallel

    bool bDeserialization;
    int iLinkedEdges; //TODO
    // int rtree; //TODO
    bool bUseRTree; //TODO
    std::map<std::string, MapNode> mGraph;
};