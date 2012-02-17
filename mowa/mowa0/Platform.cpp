/**
    @file       Platform.cpp
    @brief      Platform-specific code.

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#include "Platform.h"

namespace mowa0
{

std::string WtoA(const mowa0::String& in)
{
#ifdef _UNICODE
    std::vector<char> buffer_ansi(in.length());

    std::locale locale("");

    const std::codecvt<wchar_t, char, std::mbstate_t> &codecvt =
        std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>
            (locale);

    std::mbstate_t init_state = std::mbstate_t();

    const wchar_t* from_next  = nullptr;
    char* to_next             = nullptr;

    std::codecvt_base::result cvt_res =
        codecvt.out(init_state, in.c_str(), in.c_str() + in.length(), from_next,
                    &buffer_ansi[0], &buffer_ansi[0] + buffer_ansi.size(), to_next);

    switch (cvt_res)
    {
        case  std::codecvt_base::ok:
        break;
        case  std::codecvt_base::partial:
        break;
        case  std::codecvt_base::error:
        throw std::logic_error(WHERE);
        break;
        case  std::codecvt_base::noconv:
        throw std::logic_error(WHERE);
        break;
        default:
        throw std::logic_error(WHERE);
        break;
    }

    return std::string(buffer_ansi.begin(), buffer_ansi.end());
#else
    return in;
#endif
}

}

