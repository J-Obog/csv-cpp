#pragma once
#include <vector> 
#include <unordered_map> 
#include <string>
#include <fstream>
#include <sstream>

namespace csvcpp { 

struct ParseParams {
    char delim = ',';
    char newline = '\n';
    bool setHeaders = true;  
}; 

class CSV {
    private:
        std::vector<std::vector<std::string>> _data;
        std::unordered_map<std::string, size_t> _hmap;
        ParseParams _params;  
        
        void parseCSV(std::istream& istr) {
            std::string rbuf, cbuf;
            std::stringstream lnss; 
            
            while(std::getline(istr, rbuf, _params.newline)) {
                _data.push_back({});
                lnss << rbuf;
        
                while(std::getline(lnss, cbuf, _params.delim)) {
                    _data[_data.size() - 1].push_back(cbuf);       
                }
        
                lnss.clear(); 
            }
        } 

    public:
        CSV(const std::string& str, const ParseParams& params) : _params(params) {
            std::stringstream ss(str); 
            parseCSV(ss); 
        }

        CSV(std::ifstream& file, const ParseParams& params) : _params(params) {   
            parseCSV(file); 
        }
}; 

} //end of csvcpp namespace