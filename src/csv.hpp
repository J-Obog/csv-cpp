#pragma once
#include <vector> 
#include <unordered_map> 
#include <string>
#include <fstream>


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


class Row {
    private:
        std::vector<std::string>& _vref;

    public:
        Row(std::vector<std::string>& vref) : _vref(vref) {};
};


class CSV {
    private:
        std::vector<std::vector<std::string>> _data;

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
        
        Row operator[] (int idx) { return Row(_data[idx]); }
}; 