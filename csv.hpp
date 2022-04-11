#pragma once
#include <vector>
#include <string>

std::vector<std::string> split_str(const std::string& s, char delim) {
    std::vector<std::string> v; 
    std::string buf; 
    int pos = 0; 

    while(pos < s.length()) {
        if(s[pos] == delim) {
            if(!buf.empty()) 
                v.push_back(buf);
            buf.clear(); 
        } else {
            buf += s[pos++];
        }
    }
    return v; 
}


class CSVRow {
    private:
        std::vector<std::string> _vec;
        std::string _raw;  

    public:
        CSVRow() = default; 
        ~CSVRow() = default; 
        CSVRow(const std::string& s) {
            _vec = split_str(s, ',');
            _raw = s;  
        }
}; 