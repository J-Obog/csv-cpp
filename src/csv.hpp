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


/*class CSVRow {
    private:
        hmap* _hmptr;  
        std::vector<std::string> _cols;
        
    public:
        CSVRow(const std::string& str, hmap* hmptr = nullptr) : _cols(split_str(str, ',')), _hmptr(hmptr) {};
        std::vector<std::string> get_cols() const { return _cols; }; 
        std::string& operator[] (std::string cname) { return _cols[_hmptr->at(cname)]; }
};*/ 


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
        
        //const CSVRow& operator[] (int rnum) const { return _rows[rnum]; }
}; 