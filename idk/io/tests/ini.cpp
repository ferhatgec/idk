#include "../ini.hpp"
#include "../path.hpp"

int main() {
    idk::INI x;
    
    if(idk::Path(L"example.ini").exists())
        x.parse_file("example.ini");
    else // test case
        x.parse_file("idk\\io\\tests\\example.ini");

    if(x.get_value("profile1", "use_music") != "true")
        std::cerr << "[FAIL] x.get_value(\"profile1\", \"use_music\") != \"true\"\n";
    else
        std::cout << "[OK] x.get_value(\"profile1\", \"use_music\") != \"true\"\n";

    x.change_key("profile2", "character_name", "savort");

    if(x.get_value("profile2", "character_name") != "savort")
        std::cerr << "[FAIL] x.get_value(\"profile2\", \"character_name\") != \"savort\"\n";
    else
        std::cout << "[OK] x.get_value(\"profile2\", \"character_name\") != \"savort\"\n";
}