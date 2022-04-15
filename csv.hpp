#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

typedef std::unordered_map<std::string, int> header_map; 
typedef std::vector<std::string> str_vec; 

str_vec split_str(std::string& str, char delim) {
    str_vec v; 
    std::string buf; 

    for(char& chr: str) {
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
        header_map* _hmap_ptr;  
        str_vec _cols;
        
    public:
        CSVRow(std::string& str) : _cols(split_str(str, ',')) {};
        str_vec get_cols() const { return _cols; }; 
        std::string operator[] (std::string cname) const { return _cols[_hmap_ptr->at(cname)]; }
}; 


class CSV {
    private:
        header_map _hmap; 
        std::vector<CSVRow> _rows; 

    public:
        void set_header(str_vec h_cols, bool upsert = false) {
            int count = 0; 
            
            if(!upsert)
                _hmap.clear(); 

            for(std::string& col: h_cols)
                _hmap[col] = count++; 
        } 

        void init_header() {
            if(!_rows.empty())
                set_header(_rows[0].get_cols(), true);
        }

        void from_string(std::string& str) {
            str_vec rows = split_str(str, '\n'); 
            
            for(std::string& row: rows)
                _rows.push_back(CSVRow(row));                

            init_header();  
        }

        void from_file(std::string& fname) {
            std::ifstream file(fname, std::ios::in); 
            std::string line; 

            if(file.is_open())
                while(std::getline(file, line))
                    _rows.push_back(CSVRow(line));

            file.close();
            init_header();  
        }

        const CSVRow& operator[] (int rnum) const { return _rows[rnum]; }
}; 
