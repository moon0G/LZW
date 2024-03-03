#include "lzw.hpp"

int main()
{
    lzw compressor;

    std::vector<int> result = compressor.encode("Hello");

    
    std::cout<<result.size()<<"\n";

    for(auto i: result) 
    {
        std::cout<<i<<"\n";
    }
}
