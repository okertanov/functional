#include <memory>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <functional>

#include "Activator.h"
#include "Lunar.h"
#include "LunarExports.h"

int main(int argc, char** argv) {
    try{
        auto lua = std::make_shared<Lunar::Lua>();

        lua->LoadChunk("print('\\tHello from Lua!')");
        std::cout << "Lua says: " << lua->Exec<std::string>() << std::endl;

        lua->LoadChunk("return string.upper('Hello!')");
        std::cout << "Lua says: " << lua->Exec<std::string>() << std::endl;

        lua->LoadChunk("function dots(x) return string.rep('.', x) end");
        std::cout << "Lua says: " << lua->Exec<std::string>("dots", [&lua]() {
            lua->Push(42);
            return 1;
        })
        << std::endl;

        lua->LoadChunk("function mul(a, b) return a * b end");
        std::cout << "Lua says: " << lua->Exec<std::string>("mul", [&lua]() {
            lua->Push(3.0);
            lua->Push(5.0);
            return 2;
        })
        << std::endl;

        lua->Register("cmul", Lunar::LunarExports::Cmul);

        lua->LoadFile("bootstraper.lua");
        std::cout << "Lua says: " << lua->Exec<std::string>("l_bootstrap")
        << std::endl;
    }

    catch(std::exception & e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

