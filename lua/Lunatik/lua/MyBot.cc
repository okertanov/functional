// --------------------------------------------------
// MyBot.cc - lua loader
// okertanov@gmail.com (c) 2010
// --------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
//extern "C" {
#endif

#include "./lua.h"
#include "./lualib.h"
#include "./lauxlib.h"

#ifdef __cplusplus
//}
#endif


int main(int argc, char** argv)
{
    lua_State *l = 0;

    l = lua_open();
    luaopen_base(l);
    luaopen_table(l);
    luaopen_string(l);
    luaopen_math(l);
    luaL_openlibs(l);
    luaL_dofile(l, "MainBot.lua");
    lua_close(l);

    return 0;
}

