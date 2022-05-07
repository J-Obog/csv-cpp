#pragma once
#include <vector> 
#include <unordered_map> 
#include <string>
#include <fstream>
#include <sstream>

namespace csvcpp { 

class CSV {
    private:
        std::vector<std::vector<std::string>> _data;
        std::unordered_map<std::string, size_t> _hmap; 
        
        void parseCSV(std::istream& istr, char delim, char newline) {
            std::string rbuf; 
            std::string cbuf;
            std::stringstream lnss; 
            
            while(getline(istr, rbuf, newline)) {
                _data.push_back({});
                lnss << rbuf;
        
                while(getline(lnss, cbuf, delim)) {
                    _data[_data.size() - 1].push_back(cbuf);       
                }
        
                lnss.clear(); 
            }
        }


    public:

        /*CSV(const std::string& str) {
            for(std::string& s: split_str(str, '\n'))
                _data.push_back(split_str(s, ',')); 
        }

        CSV(std::ifstream& file) {
            std::string line; 
            
            while(std::getline(file, line))
                _data.push_back(split_str(line, ','));
        }*/
}; 

} //end of csvcpp namespace