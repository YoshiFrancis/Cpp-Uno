#include <string>

namespace Helper {

    bool compareStrings(std::string& str1, std::string& str2) {
        if (str1.size() != str2.size()) 
            return false;

        for (int idx = 0; idx < str1.size(); ++idx) {
            if (std::tolower(str1[idx]) != std::tolower(str2[idx])) 
                return false;
        }

        return true;
    }

    

    void capitalizeOnly(std::string& str) {
        for (char& c : str) 
            c = std::tolower(c);
        str[0] = std::toupper(str[0]);
    }
}