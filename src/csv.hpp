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
            std::string rbuf, cbuf;
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

        CSV(const std::string& str, char delim = ',', char newline = '\n') {
            std::stringstream ss(str); 
            parseCSV(ss, delim, newline); 
        }

        CSV(std::ifstream& file, char delim = ',', char newline = '\n') {   
            parseCSV(file, delim, newline); 
        }
}; 

} //end of csvcpp namespace