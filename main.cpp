#include "lzw.hpp"


int main()
{
    lzw compressor;

    // for testing



    std::vector<int> result = compressor.encode("Hello, how are you today? Hello, Good and you?");
    
    for(int i: result)
    {
        std::cout<<i<<"\n";
    }

    /*std::string lorem = compressor.decode(result);
    
    std::cout<<lorem;*/
    
    /*
    std::cout<<result.size()<<"\n";

    compressor.compOutput(result, "o.bin");

    std::vector<int> read = compressor.compInput("o.bin");

    std::cout<<read.size();
    */
}
