/**
    @file       Tokens.h
    @brief      Token & TokenList

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#ifndef TOKENS_H_INCLUDED
#define TOKENS_H_INCLUDED

#include "Platform.h"
#include "Exception.h"

namespace mowa0
{

/**
    @enum mowa0::TokenType
    @brief
*/
enum TokenType
{
    TOKEN_PARLEFT,      /* Left parenthesis     (       */
    TOKEN_PARRIGHT,     /* Right parenthesis    )       */
    TOKEN_BRACKLEFT,    /* Left bracket         [       */
    TOKEN_BRACKRIGHT,   /* Right bracket        ]       */
    TOKEN_NUMBER,       /* Number               0-9     */
    TOKEN_STRING,       /* String               "abc"   */
    TOKEN_SYMBOL,       /* Symbol               symbol  */
    TOKEN_DOT,          /* Dot                  .       */
    TOKEN_COMMA,        /* Comma                ,       */
    TOKEN_QUOTATION,    /* Quotation            '       */
    TOKEN_WHITESPACE,   /* Whitespace           _       */
    TOKEN_COMMENT       /* Comment              ;;      */
};

/**
    @def mowa0::L_*
    @brief Token literals
*/
#define L_NUL           _T('\x00')
#define L_TAB           _T('\x09')
#define L_SPACE         _T('\x20')
#define L_LF            _T('\x0A')
#define L_CR            _T('\x0D')
#define L_US            _T('\x1F')

#define L_PARLEFT       _T('(')
#define L_PARRIGHT      _T(')')

#define L_BRACKLEFT     _T('[')
#define L_BRACKRIGHT    _T(']')

#define L_DOT           _T('.')
#define L_COMMA         _T(',')
#define L_QUOTATION     _T('\'')

#define L_COMMENT       _T(';')

#define L_IS_CTRL(C)    (C != L_TAB && C != L_LF && C != L_CR && C<=L_US)

/**
    @typedef mowa0::TokenBody
    @brief
*/
typedef mowa0::String TokenBody;

/**
    @class mowa0::Token
    @brief Token POD class
*/
struct Token
{
    TokenType type_;
    TokenBody body_;
};

/**
    @class mowa0::Tokens
    @brief Tokens class
*/
class Tokens :
    public std::list<Token>
{
    public:
        Tokens();
        virtual ~Tokens();
};

/**
    @class mowa0::TokensException
    @brief TokensxException class
*/
class TokensException :
    public mowa0::Exception
{
    public:
        explicit TokensException(std::exception& e) :
            Exception(e)
        {
        }

        explicit TokensException(const std::string& where = WHERE, const std::string& what = "") :
            Exception(where, what)
        {
        }

        virtual ~TokensException() throw()
        {
        }
};

}

#endif // TOKENS_H_INCLUDED

