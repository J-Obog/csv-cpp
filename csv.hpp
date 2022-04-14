#pragma once
#include <vector>
#include <unordered_map>
#include <string>

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
        CSVRow() = default; 
        ~CSVRow() = default; 
        
        CSVRow(std::string& str) {
            _cols = split_str(str, ',');
        }

        str_vec get_cols() const {
            return _cols; 
        }
}; 

class CSV {
    private:
        header_map _hmap; 
        std::vector<CSVRow> _rows; 

        void _set_headers() {
            if(!_rows.empty()) {
                int count = 0; 
                
                for(std::string& col: _rows[0].get_cols()) 
                    _hmap.insert({col, count++}); 
            }
        }

    public:
        CSV() = default; 
        ~CSV() = default; 
        
        void from_string(std::string& str) {
            str_vec rows = split_str(str, '\n'); 
            
            for(std::string& row: rows)
                _rows.push_back(CSVRow(row));                 
            
             _set_headers(); 
        }
}; 
