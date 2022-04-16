#pragma once
#include <vector> 
#include <unordered_map> 
#include <string>
#include <fstream>

typedef std::unordered_map<std::string, int> hmap; 
typedef std::vector<std::string> svec; 

svec split_str(const std::string& str, char delim) {
    svec v; 
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


class CSVRow {
    private:
        hmap* _hmptr;  
        svec _cols;
        
    public:
        CSVRow(const std::string& str, hmap* hmptr = nullptr) : _cols(split_str(str, ',')), _hmptr(hmptr) {};
        svec get_cols() const { return _cols; }; 
        std::string& operator[] (std::string cname) { return _cols[_hmptr->at(cname)]; }
}; 


class CSV {
    private:
        hmap _hm; 
        std::vector<CSVRow> _rows; 

    public:
        void set_header(svec h_cols, bool upsert = false) {
            int count = 0; 
            
            if(!upsert)
                _hm.clear(); 

            for(std::string& col: h_cols)
                _hm[col] = count++; 
        } 

        void init_header() {
            if(!_rows.empty()) 
                set_header(_rows[0].get_cols());
        }

        void from_string(std::string& str) {
            svec rows = split_str(str, '\n'); 
            
            for(std::string& row: rows)
                _rows.push_back(CSVRow(row, &_hm));                

            init_header();  
        }

        void from_file(std::string& fname) {
            std::ifstream file(fname, std::ios::in); 
            std::string line; 

            if(file.is_open())
                while(std::getline(file, line))
                    _rows.push_back(CSVRow(line, &_hm));

            file.close();
            init_header();  
        }
        
        const CSVRow& operator[] (int rnum) const { return _rows[rnum]; }
}; 