#include "InMemMap.hpp"
#include <vector>
#include <regex>
#include <string>
#include <iostream>
#include<sstream>

// #define DEBUG

MapNode::MapNode(float x, float y, std::string to)
    : _fX(x), _fY(y){
    std::regex ws_re("\\,"); // split with ,
    _vTo = std::vector<std::string>(std::sregex_token_iterator(to.begin(), to.end(), ws_re, -1),
                               std::sregex_token_iterator() );

#ifdef DEBUG
    std::cout << "in MapNode:" << std::endl;
    for(auto n:_vTo){
        std::cout << n << std::endl;
    }
#endif
    
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
            std::cout << currx << " " << curry << " "<< currto << std::endl;            
            MapNode currNode(currx, curry, currto);
            mGraph.insert(std::pair<std::string, MapNode>(currNodeName, currNode) );
        }
    }

int InMemMap::distance(){
    std::cout << "not implemented..." << std::endl;
    return 0; 
} // TODO: function ptr

int InMemMap::distance_pt_to_seg(){
    std::cout << "not implemented..." << std::endl;
    return 0; 
} //TODO: func ptr

int InMemMap::distance_segment_to_segment(){
    std::cout << "not implemented..." << std::endl;
    return 0; 
} //TODO: func ptr

int InMemMap::lines_parallel(){
    std::cout << "not implemented..." << std::endl;
    return 0; 
} //TODO: func parallel

int InMemMap::box_around_point(){
    std::cout << "not implemented..." << std::endl;
    return 0; 
} //TODO: func parallel