#include "../path.hpp"
#include <iostream>

int main() {
#ifdef _windows
    idk::Path x(L"C:\\Users\\gech\\Desktop\\idk\\idk\\io\\tests\\color.cpp");

    if(idk::Path(L"path.cpp").is_file()) // it's false because it's not absolute path, just filename.
        std::cerr << "[FAIL] !idk::Path(L\"path.cpp\").is_file()\n";
    else
        std::cout << "[OK] idk::Path(L\"path.cpp\").is_file()\n";

    if(idk::Path(L"path.cpp").exists())
        std::cerr << "[FAIL] !idk::Path(L\"path.cpp\").exists()\n";
    else
        std::cout << "[OK] !idk::Path(L\"path.cpp\").exists()\n";

    if(idk::Path(L"path.txt.cpp").extension().as_str() != L".cpp")
        std::cerr << "[FAIL] idk::Path(L\"path.txt.cpp\").extension().as_str() != L\".cpp\"\n";
    else
        std::cout << "[OK] idk::Path(L\"path.txt.cpp\").extension().as_str() != L\".cpp\"\n";

    if(!((idk::Path(L"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp").file_name() == idk::Path(L"C:\\color.cpp").file_name()) &&
        (idk::Path(L"..\\color.cpp").file_name() == idk::Path(L"..\\color.cpp").file_name())))
        std::cerr << "[FAIL] !((idk::Path(L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp\").file_name() == idk::Path(L\"C:\\color.cpp\").file_name()) &&"
                     "(idk::Path(L\"..\\color.cpp\").file_name() == idk::Path(L\"..\\color.cpp\").file_name()))\n";
    else
        std::cout << "[OK] !((idk::Path(L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp\").file_name() == idk::Path(L\"C:\\color.cpp\").file_name()) &&"
                     "(idk::Path(L\"..\\color.cpp\").file_name() == idk::Path(L\"..\\color.cpp\").file_name()))\n";

    if(idk::Path(L"C:\\color.cpp").remove_file_name().as_str() != L"C:\\")
        std::cerr << "[FAIL] idk::Path(L\"C:\\color.cpp\").remove_file_name().as_str() != L\"C:\\\"\n";
    else
        std::cout << "[OK] idk::Path(L\"C:\\color.cpp\").remove_file_name().as_str() != L\"C:\\\"\n";

    
    if(idk::Path(L"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\").remove_file_name().as_str() != L"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\")
        std::cerr << "[FAIL] idk::Path(L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\\").remove_file_name().as_str() != L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\\"\n";
    else
        std::cout << "[OK] idk::Path(L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\\").remove_file_name().as_str() != L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\\"\n";
    
    if(!idk::Path(L"path.cpp").remove_file_name().as_str().is_empty())
        std::cerr << "[FAIL] !idk::Path(L\"path.cpp\").remove_file_name().as_str().is_empty()\n";
    else
        std::cout << "[OK] !idk::Path(L\"path.cpp\").remove_file_name().as_str().is_empty()\n";

    if(idk::Path(L"path.cpp").replace_file_name(L"color.cpp").as_str() != L"color.cpp")
        std::cerr << "[FAIL] idk::Path(L\"path.cpp\").replace_file_name(L\"color.cpp\").as_str() != L\"color.cpp\"\n";
    else
        std::cout << "[OK] idk::Path(L\"path.cpp\").replace_file_name(L\"color.cpp\").as_str() != L\"color.cpp\"\n";

    if(idk::Path(L"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp").replace_file_name(L"path.cpp").as_str() != L"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\path.cpp")
        std::cerr << "[FAIL] idk::Path(L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp\").replace_file_name(L\"path.cpp\").as_str() != L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\path.cpp\"\n";
    else
        std::cout << "[OK] idk::Path(L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp\").replace_file_name(L\"path.cpp\").as_str() != L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\path.cpp\"\n";

    if(idk::Path(L"color.cpp").remove_extension().as_str() != L"color")
        std::cerr << "[FAIL] idk::Path(L\"color.cpp\").remove_extension().as_str() != L\"color\"\n";
    else
        std::cout << "[OK] idk::Path(L\"color.cpp\").remove_extension().as_str() != L\"color\"\n";


    if(idk::Path(L"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp").remove_extension().as_str() != L"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color")
        std::cerr << "[FAIL] idk::Path(L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp\").remove_extension().as_str() != L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color\"\n";
    else
        std::cout << "[OK] idk::Path(L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp\").remove_extension().as_str() != L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color\"\n";
    
    if(idk::Path(L"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp").replace_extension(L".cxx").as_str() != L"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cxx")
        std::cerr << "[FAIL] idk::Path(L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp\").replace_extension(L\".cxx\").as_str() != L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cxx\"\n";
    else
        std::cout << "[OK] idk::Path(L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cpp\").replace_extension(L\".cxx\").as_str() != L\"C:\\Users\\...\\...\\idk\\idk\\io\\tests\\color.cxx\"\n";

        
#else
    idk::Path x("/home/gech/Desktop/idk/idk/io/tests/color.cpp");

     if(idk::Path("path.cpp").is_file()) // it's false because it's not absolute path, just filename.
        std::cerr << "[FAIL] !idk::Path(\"path.cpp\").is_file()\n";
    else
        std::cout << "[OK] idk::Path(\"path.cpp\").is_file()\n";

    if(idk::Path("path.cpp").exists())
        std::cerr << "[FAIL] !idk::Path(\"path.cpp\").exists()\n";
    else
        std::cout << "[OK] !idk::Path(\"path.cpp\").exists()\n";

    if(idk::Path("path.txt.cpp").extension().as_str() != ".cpp")
        std::cerr << "[FAIL] idk::Path(\"path.txt.cpp\").extension().as_str() != \".cpp\"\n";
    else
        std::cout << "[OK] idk::Path(\"path.txt.cpp\").extension().as_str() != \".cpp\"\n";

    if(!((idk::Path("/home/gech/Desktop/idk/idk/io/tests/color.cpp").file_name() == idk::Path("/home/gech/color.cpp").file_name()) &&
        (idk::Path("../color.cpp").file_name() == idk::Path("../color.cpp").file_name())))
        std::cerr << "[FAIL] !((idk::Path(\"/home/gech/Desktop/idk/idk/io/tests/color.cpp\").file_name() == idk::Path(\"/home/gech/color.cpp\").file_name()) &&"
                     "(idk::Path(\"../color.cpp\").file_name() == idk::Path(\"../color.cpp\").file_name()))\n";
    else
        std::cout << "[OK] !((idk::Path(\"/home/gech/Desktop/idk/idk/io/tests/color.cpp\").file_name() == idk::Path(\"/home/gech/color.cpp\").file_name()) &&"
                     "(idk::Path(\"../color.cpp\").file_name() == idk::Path(\"../color.cpp\").file_name()))\n";

    if(idk::Path("/home/gech/color.cpp").remove_file_name().as_str() != "/home/gech/")
        std::cerr << "[FAIL] idk::Path(\"/home/gech/color.cpp\").remove_file_name().as_str() != \"/home/gech/\"\n";
    else
        std::cout << "[OK] idk::Path(\"/home/gech/color.cpp\").remove_file_name().as_str() != \"/home/gech/\"\n";

    
    if(idk::Path("/home/gech/Desktop/idk/idk/io/tests/").remove_file_name().as_str() != "/home/gech/Desktop/idk/idk/io/tests/")
        std::cerr << "[FAIL] idk::Path(\"/home/gech/Desktop/idk/idk/io/tests/\").remove_file_name().as_str() != \"/home/gech/Desktop/idk/idk/io/tests/\"\n";
    else
        std::cout << "[OK] idk::Path(\"/home/gech/Desktop/idk/idk/io/tests/\").remove_file_name().as_str() != \"/home/gech/Desktop/idk/idk/io/tests/\"\n";
    
    if(!idk::Path("path.cpp").remove_file_name().as_str().is_empty())
        std::cerr << "[FAIL] !idk::Path(\"path.cpp\").remove_file_name().as_str().is_empty()\n";
    else
        std::cout << "[OK] !idk::Path(\"path.cpp\").remove_file_name().as_str().is_empty()\n";

    if(idk::Path("path.cpp").replace_file_name("color.cpp").as_str() != "color.cpp")
        std::cerr << "[FAIL] idk::Path(\"path.cpp\").replace_file_name(\"color.cpp\").as_str() != \"color.cpp\"\n";
    else
        std::cout << "[OK] idk::Path(\"path.cpp\").replace_file_name(\"color.cpp\").as_str() != \"color.cpp\"\n";

    if(idk::Path("/home/gech/Desktop/idk/idk/io/tests/color.cpp").replace_file_name("path.cpp").as_str() != "/home/gech/Desktop/idk/idk/io/tests/path.cpp")
        std::cerr << "[FAIL] idk::Path(\"/home/gech/Desktop/idk/idk/io/tests/color.cpp\").replace_file_name(\"path.cpp\").as_str() != \"/home/gech/Desktop/idk/idk/io/tests/path.cpp\"\n";
    else
        std::cout << "[OK] idk::Path(\"/home/gech/Desktop/idk/idk/io/tests/color.cpp\").replace_file_name(\"path.cpp\").as_str() != \"/home/gech/Desktop/idk/idk/io/tests/path.cpp\"\n";

    if(idk::Path("color.cpp").remove_extension().as_str() != "color")
        std::cerr << "[FAIL] idk::Path(\"color.cpp\").remove_extension().as_str() != \"color\"\n";
    else
        std::cout << "[OK] idk::Path(\"color.cpp\").remove_extension().as_str() != \"color\"\n";


    if(idk::Path("/home/gech/Desktop/idk/idk/io/tests/color.cpp").remove_extension().as_str() != "/home/gech/Desktop/idk/idk/io/tests/color")
        std::cerr << "[FAIL] idk::Path(\"/home/gech/Desktop/idk/idk/io/tests/color.cpp\").remove_extension().as_str() != \"/home/gech/Desktop/idk/idk/io/tests/color\"\n";
    else
        std::cout << "[OK] idk::Path(\"/home/gech/Desktop/idk/idk/io/tests/color.cpp\").remove_extension().as_str() != \"/home/gech/Desktop/idk/idk/io/tests/color\"\n";
    
    if(idk::Path("/home/gech/Desktop/idk/idk/io/tests/color.cpp").replace_extension(".cxx").as_str() != "/home/gech/Desktop/idk/idk/io/tests/color.cxx")
        std::cerr << "[FAIL] idk::Path(\"/home/gech/Desktop/idk/idk/io/tests/color.cpp\").replace_extension(\".cxx\").as_str() != \"/home/gech/Desktop/idk/idk/io/tests/color.cxx\"\n";
    else
        std::cout << "[OK] idk::Path(\"/home/gech/Desktop/idk/idk/io/tests/color.cpp\").replace_extension(\".cxx\").as_str() != \"/home/gech/Desktop/idk/idk/io/tests/color.cxx\"\n";
#endif

   
    std::cout 
#ifndef _windows
               << idk::Path("color.cpp").append("/home/.../").as_str()
               << '\n'
#else
               << ""
#endif
                ;
}