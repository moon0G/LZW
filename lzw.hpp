#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <sstream>

class lzw 
{
    int dSize = 256;

    bool checkKeyE(std::unordered_map<std::string, int> m, std::string key) // check if key exists in dict
    {
        if(m.find(key) == m.end()) { return false; }
        else { return true; }
    }

    bool checkKeyD(std::unordered_map<int, std::string> m, int key) // check if key exists in dict
    {
        if(m.find(key) == m.end()) { return false; }
        else { return true; }
    }

    std::unordered_map<std::string, int> populateE() // populate encode dict
    {
        std::unordered_map<std::string, int> dict;

        for(int i=0; i<dSize; i++) {
            char c = static_cast<char>(i);
            std::string s(1, c);

            dict[s] = i;
        }

        return dict;
    }

    std::unordered_map<int, std::string> populateD() // populate decode dict
    {
        std::unordered_map<int, std::string> dict;
        for(int i=0; i<dSize; i++) {
            char c = static_cast<char>(i);
            std::string s(1, c);

            dict[i] = s;
        }

        return dict;
    }

    public:

        std::vector<int> encode(std::string contents) // encoding function
        {
            std::unordered_map<std::string, int> dict = populateE();

            std::string found = "";
            std::vector<int> result = {};

            if (!contents.empty())  // do the check on contents here
            { // encode first char here to remove duplicates
                char firstChar = contents[0];
                std::string found = std::string(1, firstChar);
                result.push_back(dict[found]);
            }
            else 
            {
                exit(1);
            }

            for(size_t i = 1; i < contents.size(); i++)
            {
                char c = contents[i];

                std::string cToAdd = found + c;

                if(checkKeyE(dict, cToAdd))
                {
                    found = cToAdd;
                }
                else
                {
                    result.push_back(dict[found]);

                    dict[cToAdd] = dSize++;

                    found = std::string(1, c);
                }
            }
            
            result.push_back(dict[found]);

            return result;
        }



        std::string decode(std::vector<int> encoded)
        {
            std::unordered_map<int, std::string> dict = populateD();

            std::string result = "";
            
            int prev_code = encoded[0];
            std::string entry = dict[prev_code];
            result.push_back(prev_code);

            for (size_t i = 1; i < encoded.size(); ++i) 
            {
                int code = encoded[i];

                if (checkKeyD(dict, code)) 
                {
                    // Entry is in the dictionary
                    std::string new_entry = dict[code];
                    result.push_back(code);
                    dict[dict.size()] = entry + new_entry[0];
                    entry = new_entry;
                } 
                else 
                {
                    // Entry is not in the dictionary
                    std::string new_entry = entry + entry[0];
                    result.push_back(dict.size());
                    dict[code] = entry + entry[0];
                    entry = new_entry;
                }
            }

            return result;
        }
        
        void compOutput(std::vector<int> outVec, std::string fn) 
        {
            std::ofstream file(fn);
            std::string output = "";

            for(size_t i = 0; i < outVec.size(); i++)
            {
                file << outVec[i];

                if(i != outVec.size() - 1)
                    file << ",";
            }

            file.close();
        }

        std::vector<int> compInput(std::string fn)
        {
            std::ifstream file(fn);
            std::vector<int> ret;
            std::string line;
            
            if(std::getline(file, line))
            {
                std::stringstream ss(line);
                std::string number;

                while(std::getline(ss, number, ','))
                {
                    ret.push_back(std::stoi(number));
                }
            }

            file.close();

            return ret;
        }
};
