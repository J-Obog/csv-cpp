#pragma once
#include <vector>
#include <unordered_map>
#include <string>

typedef std::unordered_map<std::string, int> header_map; 
typedef std::vector<std::string> str_vec; 

str_vec split_str(std::string& s, char delim) {
    str_vec v; 
    std::string buf; 

    for(char& c: s) {
        if(c == delim) {
            if(!buf.empty())
                v.push_back(buf);
            buf.clear(); 
        } else {
            buf += c; 
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
        
        CSVRow(std::string& s) {
            _cols = split_str(s, ',');
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

                for(std::string& s: _rows[0].get_cols()) 
                    _hmap.insert({s, count++}); 
            }
        }

    public:
        CSV() = default; 
        ~CSV() = default; 
        
        void from_string(std::string& s) {
            for(std::string& txt: split_str(s, '\n'))
                _rows.push_back(CSVRow(txt));                 

             _set_headers(); 
        }
}; 
