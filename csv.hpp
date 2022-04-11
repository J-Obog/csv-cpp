#pragma once
#include <vector>
#include <string>

std::vector<std::string> split_commas(const std::string& s) {
    std::vector<std::string> v; 
    std::string buf; 
    int pos = 0; 

    while(pos < s.length()) {
        if(s[pos] == ',') {
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
            _vec = split_commas(s);
            _raw = s;  
        }
}; 