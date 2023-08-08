#include "../sourcelocation.hpp"
#include <iostream>

void function(idk::SourceLocation x = idk::SourceLocation::current()) {
    std::cout << x.column() << " " << x.file_name() << '\n';
}

int main() {
    function();
}