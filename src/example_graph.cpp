#include <iostream>
#include <string>
#include <regex>
#include "InMemMap.hpp"
#include <map>

using namespace std;

int main(){
    string map_name  = "mymap";
    map<string, string> graph;
    graph.insert(pair<string, string>("A", "1 1 B,C,X") );
    graph.insert(pair<string, string>("B", "1 3 A,C,D,K") );
    graph.insert(pair<string, string>("C", "2 2 A,B,D,E,X,Y") );
    graph.insert(pair<string, string>("D", "2 4 B,C,F,E,K,L") );
    graph.insert(pair<string, string>("E", "3 3 C,D,F,Y") );
    graph.insert(pair<string, string>("F", "3 5 D,E,L") );
    graph.insert(pair<string, string>("X", "2 0 A,C,Y") );
    graph.insert(pair<string, string>("Y", "3 1 X,C,E") );
    graph.insert(pair<string, string>("K", "1 5 B,D,L") );
    graph.insert(pair<string, string>("L", "2 6 K,D,F") );

    InMemMap myMap (map_name, graph, false);
    // InMemMap("mymap", graph={
    //     "A": ((1, 1), ["B", "C", "X"]),
    //     "B": ((1, 3), ["A", "C", "D", "K"]),
    //     "C": ((2, 2), ["A", "B", "D", "E", "X", "Y"]),
    //     "D": ((2, 4), ["B", "C", "F", "E", "K", "L"]),
    //     "E": ((3, 3), ["C", "D", "F", "Y"]),
    //     "F": ((3, 5), ["D", "E", "L"]),
    //     "X": ((2, 0), ["A", "C", "Y"]),
    //     "Y": ((3, 1), ["X", "C", "E"]),
    //     "K": ((1, 5), ["B", "D", "L"]),
    //     "L": ((2, 6), ["K", "D", "F"])
    // }
    return 0;
}