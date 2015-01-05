#pragma once
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <functional>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace Lunar {
    class Lua {
    public:

        typedef lua_State LuaState;
        typedef int (*LuaRegisteredFunction) (LuaState * const l);
        typedef std::function<int(void) > ArgsBuilder;

        Lua() : lstate_(luaL_newstate()) {
            lua_settop(lstate_, 0);
            luaL_openlibs(lstate_);
        }

        virtual ~Lua() {
            lua_close(lstate_);
        }

        void LoadChunk(const std::string& chunk) const {
            auto lstatus = luaL_loadbuffer(lstate_, chunk.c_str(), chunk.length(), __PRETTY_FUNCTION__);
            HandleLuaError(lstatus);
        }

        void LoadFile(const std::string& filename) const {
            auto lstatus = luaL_loadfile(lstate_, filename.c_str());
            HandleLuaError(lstatus);
        }

        template <typename T> T Exec(const std::string fn = "", ArgsBuilder argsBuilder = 0) const {
            if (!fn.empty()) {
                auto pstatus = lua_pcall(lstate_, 0, LUA_MULTRET, 0);
                HandleLuaError(pstatus);

                lua_getglobal(lstate_, fn.c_str());
                if (!lua_isfunction(lstate_, Ltop)) {
                    throw std::runtime_error(std::string("Lua binding fn failed: ") + fn.c_str());
                }
            }

            auto nargs = argsBuilder ? argsBuilder() : 0;

            auto pstatus = lua_pcall(lstate_, nargs, LUA_MULTRET, 0);
            HandleLuaError(pstatus);

            std::size_t len = 0;
            T result = T();

            if (lua_isstring(lstate_, Ltop)) {
                result = T(lua_tolstring(lstate_, Ltop, &len));
            } else if (lua_isnumber(lstate_, Ltop)) {
                std::ostringstream ss;
                ss << lua_tonumber(lstate_, Ltop);
                result = T(ss.str());
            }

            lua_pop(lstate_, lua_gettop(lstate_));

            return result;
        }

        template <typename T> void Push(const T& v) const {
            Push(lstate_, v);
        }

        void Register(std::string name, LuaRegisteredFunction fn) {
            Register(lstate_, name.c_str(), fn);
        }

        static void Push(LuaState* lstate, const int& v) {
            lua_pushnumber(lstate, v);
        }

        static void Push(LuaState* lstate, const double& v) {
            lua_pushnumber(lstate, v);
        }

        static void Push(LuaState* lstate, const std::string& v) {
            lua_pushstring(lstate, v.c_str());
        }

        static void Register(LuaState* lstate, std::string name, LuaRegisteredFunction fn) {
            lua_register(lstate, name.c_str(), fn);
        }

    private:

        void HandleLuaError(int status) const {
            if (status != LUA_OK) {
                std::string lmessage = PopLuaError();
                throw std::runtime_error(std::string("Lua ERROR: ") + lmessage);
            }
        }

        std::string PopLuaError() const {
            auto luaMsg = std::string();
            std::size_t len = 0;
            if (lua_isstring(lstate_, Ltop)) {
                luaMsg = lua_tolstring(lstate_, Ltop, &len);
            }
            lua_pop(lstate_, 1);
            lua_gc(lstate_, LUA_GCCOLLECT, 0);
            return luaMsg;
        }

    private:

        static const int Ltop = -1;
        LuaState * const lstate_;
    };
}
