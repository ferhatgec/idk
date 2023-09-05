#include <iostream>
#include "../arguments.hpp"

int main(int argc, char** argv) {
    idk::Arguments args(argc, argv);

    // TODO: structured binding support. 
    for(auto& val: args) {
        std::cout << val.key() << " " << val.value() << '\n';
    }

    std::cout << args[1].try_get_value() << '\n';

    if(args.find(idk::Vec<idk::StringViewChar> { "--t", "-t", "-test", "/test", "--test" })) {
        std::cout << "Test flag found\n";
    }
}