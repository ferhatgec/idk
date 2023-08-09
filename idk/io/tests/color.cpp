#include "../color.hpp"
#include "../../types/stringview.hpp"

int main() {
    // adding const specifier make code compilation fails,
    // this will be fixed later.
    idk::StringViewChar x("Hello world!\n");

    idk::ColorBase::out(std::cout, 
                        "Hello world!\n", 
                        idk::ColorBase::Italic, 
                        idk::ColorBase::FgDefault, 
                        idk::ColorBase::BgBrightGreen);

    idk::ColorBase::cout(x);
    idk::ColorBase::reset();
}