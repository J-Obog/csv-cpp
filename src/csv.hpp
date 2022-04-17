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
        std::vector<std::string>& _dref;
        const std::unordered_map<std::string, int>* _hmptr; 

    public:
        Row(std::vector<std::string>& dref) : _dref(dref) {}
        Row(std::vector<std::string>& dref, const std::unordered_map<std::string, int>* hmptr) : _dref(dref), _hmptr(hmptr) {}

        std::string& operator[] (const std::string& hcol) {
            return _dref[_hmptr->at(hcol)]; 
        }
};


class CSV {
    private:
        std::vector<std::vector<std::string>> _data;
        std::unordered_map<std::string, int> _hmap; 

    public:
        const static int HEADER = 0; 

        CSV(const std::string& str) {
            for(std::string& s: split_str(str, '\n'))
                _data.push_back(split_str(s, ',')); 
        }

        CSV(std::ifstream& file) {
            std::string line; 
            
            while(std::getline(file, line))
                _data.push_back(split_str(line, ','));
        }
        
        Row operator[] (int idx) { return Row(_data[idx], &_hmap); }
}; 