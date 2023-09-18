#include "../wgsd.hpp"

int main() {
    idk::WGSD x;
    
    x.parse_file("example.wgsd");
    std::cout << x.get_value("profile1", "use_music") << '\n';

    x.change_key("profile1", "character_name", "savort");

    std::cout << x.generate() << '\n';
}