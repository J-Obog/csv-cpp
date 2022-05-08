#pragma once
#include <vector> 
#include <unordered_map> 
#include <string>
#include <fstream>
#include <sstream>

namespace csvcpp { 

//parsing parameters
struct ParseParams {
    char delim = ',';
    char newline = '\n';
    bool setHeaders = true;  
}; 

//csv reader& writer
class CSV {
    private:
        std::vector<std::vector<std::string>> _data;
        std::unordered_map<std::string, size_t> _hmap;
        ParseParams _params;  
        
        void parseCSV(std::istream& istr) {
            std::string rbuf, cbuf;
            std::stringstream lnss; 
            
            //csv parsing
            while(std::getline(istr, rbuf, _params.newline)) {
                _data.push_back({});
                lnss << rbuf;
        
                while(std::getline(lnss, cbuf, _params.delim))                     
                    _data[_data.size() - 1].push_back(cbuf);       

                lnss.clear(); 
            }

            //setting headers
            if(_params.setHeaders && (_data.size() > 0)) {
                for(size_t i = 0; i < _data[0].size(); i++) 
                    _hmap[_data[0][i]] = i; 
            }
        } 

    public:
        CSV(const std::string& str, const ParseParams& params) : _params(params) {
            std::stringstream ss(str); 
            parseCSV(ss); 
        }

        CSV(std::istream& file, const ParseParams& params) : _params(params) {   
            parseCSV(file); 
        }

        const std::vector<std::string>& getRow(size_t row) const {
            return _data[row]; 
        }   

        void setRow(size_t row, std::vector<std::string>& vals) {
            _data[row] = vals; 
        }

        const std::string& getCol(size_t row, size_t col) const {
            return _data[row][col]; 
        }

        const std::string& getCol(size_t row, const std::string& header) const {
            _data[row][_hmap.at(header)]; 
        }

        void setCol(size_t row, size_t col, const std::string& val) {
            _data[row][col] = val; 
        }

        void setCol(size_t row, const std::string& header, const std::string& val) {
            _data[row][_hmap.at(header)] = val;
        }

        void insertRow(size_t row, std::vector<std::string>& vals) {
            _data.insert(_data.begin() + row, vals); 
        }

        void deleteRow(size_t row) {
            _data.erase(_data.begin() + row); 
        }
}; 

} //end of csvcpp namespace