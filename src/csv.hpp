#pragma once
#include <vector> 
#include <unordered_map> 
#include <string>
#include <fstream>

namespace csvcpp { 

std::vector<std::string> split_str(const std::string& str, char delim) {
    std::vector<std::string> v; 
    std::string buf; 

    for(const char& chr: str) {
        if(chr == delim) {
            if(!buf.empty())
                v.push_back(buf);
            buf.clear(); 
        } else {
            buf += chr; 
        }
    }
    return v; 
}

class CSV {
    private:
        std::vector<std::vector<std::string>> _data;
        std::unordered_map<std::string, size_t> _hmap; 

    public:

        CSV(const std::string& str) {
            for(std::string& s: split_str(str, '\n'))
                _data.push_back(split_str(s, ',')); 
        }

        CSV(std::ifstream& file) {
            std::string line; 
            
            while(std::getline(file, line))
                _data.push_back(split_str(line, ','));
        }
}; 

} //end of csvcpp namespace