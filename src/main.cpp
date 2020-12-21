#include <iostream>
#include <string>
#include <regex>
#include "InMemMap.hpp"

using namespace std;

int main(){
    std::string text = "A,B,C,D";
    std::regex ws_re("\\,"); // whitespace
    std::vector<std::string> v(std::sregex_token_iterator(text.begin(), text.end(), ws_re, -1), std::sregex_token_iterator() );

    for(auto s: v){
        std::cout << s << std::endl;
    }
    return 0;
}