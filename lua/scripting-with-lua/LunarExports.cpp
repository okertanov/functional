#include "LunarExports.h"

namespace Lunar {
    int LunarExports::Cmul(Lua::LuaState* lstate) {
        auto __attribute__((unused)) nargs = lua_gettop(lstate);
        auto a = luaL_checknumber(lstate, 1);
        auto b = luaL_checknumber(lstate, 2);
        auto m = a * b;
        Lua::Push(lstate, m);
        return 1;
    }
}