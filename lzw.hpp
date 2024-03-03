#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

class lzw 
{
    int dSize = 256;
    std::unordered_map<std::string, int> dict;

    bool checkKey(std::unordered_map<std::string, int> m, std::string key) // check if key exists in dict
    {
        if(m.find(key) == m.end()) { return false; }
        else { return true; }
    }

    public:
        
        lzw() // constructor that populates dict
        {
            for(int i=0; i<dSize; i++) {
                char c = static_cast<char>(i);
                std::string s(1, (char)i);

                dict[s] = i;
            }
        }

        std::vector<int> encode(std::string contents) // encoding function
        {
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

                if(checkKey(dict, cToAdd))
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


        /*
        std::string decode()
        {
            
        }
        */
};
