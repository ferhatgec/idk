#include "../wgsd.hpp"
#include "../path.hpp"

int main() {
    idk::WGSD x;
    
#ifdef _windows
    if(idk::Path(L"example.wgsd").exists())
        x.parse_file("example.wgsd");
    else // test case
        x.parse_file("idk\\io\\tests\\example.wgsd");
#else
    if(idk::Path("example.wgsd").exists())
        x.parse_file("example.wgsd");
    else // test case
        x.parse_file("idk/io/tests/example.wgsd");
#endif

    
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