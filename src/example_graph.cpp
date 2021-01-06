#include <iostream>
#include <string>
#include <regex>
#include "inMemMap.hpp"
#include <map>

using namespace std;

int main(){
    string map_name  = "mymap";
    map<string, string> graph;
    graph.insert(pair<string, string>("A", "1.0 1.0 B,C,X") );
    graph.insert(pair<string, string>("B", "1.0 3.0 A,C,D,K") );
    graph.insert(pair<string, string>("C", "2.0 2.0 A,B,D,E,X,Y") );
    graph.insert(pair<string, string>("D", "2.0 4.0 B,C,F,E,K,L") );
    graph.insert(pair<string, string>("E", "3.0 3.0 C,D,F,Y") );
    graph.insert(pair<string, string>("F", "3.0 5.0 D,E,L") );
    graph.insert(pair<string, string>("X", "2.0 0.0 A,C,Y") );
    graph.insert(pair<string, string>("Y", "3.0 1.0 X,C,E") );
    graph.insert(pair<string, string>("K", "1.0 5.0 B,D,L") );
    graph.insert(pair<string, string>("L", "2.0 6.0 K,D,F") );

    InMemMap myMap (map_name, graph, false);
    for(auto currNode : myMap.mGraph){
        cout << "Node name:" << currNode.first
             << " Loc:" << currNode.second->mPoint.fX << "," << currNode.second->mPoint.fY
             << " Connected to: (";
            for(int i = 0 ; i < currNode.second->vTo.size() ; i++){
                cout << currNode.second->vTo[i] << " ";
            }
            cout << ")" << endl;

    }
    return 0;
}