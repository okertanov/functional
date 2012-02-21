/**
    @file       Lexer.cpp
    @brief      Lexer for the context-free grammars.
                The part of the LL(1) Parser: issued to convert Characters -> Tokens

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       Feb 2012
    @copyright  Copyright (C) 2012 Oleg Kertanov <okertanov@gmail.com>
    @license    BSD
    @see LICENSE file
*/

#include "Lexer.h"

namespace mowa0
{

Lexer::Lexer() :
    chunk_(),
    tokens_()
{
}

Lexer::~Lexer()
{
}


Lexer& Lexer::Tokenize(const mowa0::String& chunk)
{
    try
    {
        chunk_ = chunk;

        // Tokenize isn't recursive, so it is safe to clear.
        tokens_.clear();

        /**
            @class mowa0::Lexer::Tokenize::ScanContext
            @brief Scan context
        */
        struct ScanContext
        {
            // Current line.
            unsigned long current_line;

            // Single-line comment indicator.
            bool inside_comment;
        } scan_context = {1, false};

        // Closure that implements Scanner.
        auto Scan = [&scan_context]
                    (mowa0::CharType& current, mowa0::CharType& next, mowa0::Token& token) -> mowa0::TriState
                    {
                        #if 0
                        LOG(LOG_DEBUG, mowa0::String(1, current) + mowa0::String(_T(" -> ")) + mowa0::String(1, next));
                        #endif

                        // L_NUL is terminator, and it is lookahead stopper.
                        if ( current == L_NUL || next == L_NUL )
                        {
                            return token.body_.length() ? TRI_TRUE : TRI_INTERMIDIATE;
                        }

                        // Control character in the stream.
                        if ( L_IS_CTRL(current) || L_IS_CTRL(next) )
                            throw LexerException(WHERE, "Control character in the stream at file(line).");

                        // True (Unix) new Line or part of the Windows CRLF new line mark.
                        // Eat and increment line number.
                        if ( current == L_LF )
                        {
                            // Update line number.
                            scan_context.current_line++;
                            // Reset single-line comment mode.
                            scan_context.inside_comment = false;
                            return token.body_.length() ? TRI_TRUE : TRI_INTERMIDIATE;
                        }

                        // Second part of the Windows new line (in a pair with L_LF).
                        // Silently eat.
                        if ( current == L_CR )
                        {
                            return token.body_.length() ? TRI_TRUE : TRI_INTERMIDIATE;
                        }

                        // Inside single-line comment
                        if ( scan_context.inside_comment )
                        {
                            return TRI_INTERMIDIATE;
                        }

                        // Space and Tab are separators.
                        // Silently eat.
                        if ( current == L_SPACE || current == L_TAB )
                        {
                            return token.body_.length() ? TRI_TRUE : TRI_INTERMIDIATE;
                        }

                        // Parentheses and brackets and punctuations are tokens and terminals.
                        // TODO: current != one of this
                        if ( next == L_PARLEFT   || next == L_PARRIGHT   ||
                             next == L_BRACKLEFT || next == L_BRACKRIGHT ||
                             next == L_DOT       || next == L_COMMA      ||
                             next == L_QUOTATION )
                        {
                            // Accumulate last character into the token.
                            token.body_ += current;
                            return token.body_.length() ? TRI_TRUE : TRI_INTERMIDIATE;
                        }
                        // And schedule next time to consume self.
                        if ( current == L_PARLEFT   || current == L_PARRIGHT   ||
                             current == L_BRACKLEFT || current == L_BRACKRIGHT ||
                             current == L_DOT       || current == L_COMMA      ||
                             current == L_QUOTATION )
                        {
                            token.body_ = current;
                            token.type_ =   (current == L_PARLEFT ? TOKEN_PARLEFT     :
                                            (current == L_PARRIGHT ? TOKEN_PARRIGHT    :
                                            (current == L_BRACKLEFT ? TOKEN_BRACKLEFT   :
                                            (current == L_BRACKRIGHT ? TOKEN_BRACKRIGHT  :
                                            (current == L_DOT         ? TOKEN_DOT         :
                                            (current == L_COMMA        ? TOKEN_COMMA       :
                                            (current == L_QUOTATION     ? TOKEN_QUOTATION   :
                                                                           TOKEN_WHITESPACE)))))));
                            return TRI_TRUE;
                        }

                        // Single-line comments is terminal.
                        // Start eating it to the end of line.
                        if ( current == L_COMMENT )
                        {
                            scan_context.inside_comment = true;
                            return token.body_.length() ? TRI_TRUE : TRI_INTERMIDIATE;
                        }

                        // Accumulate current character into the token,
                        // assuming it is atom.
                        token.body_ += current;

                        return mowa0::TRI_INTERMIDIATE;
                    };

        mowa0::Token token = {TOKEN_ATOM, _T("")};
        mowa0::String result;

        std::transform(chunk_.begin(), chunk_.end(), chunk_.begin() + 1, std::back_inserter(result),
                [&Scan, &token, &tokens_](mowa0::CharType& current, mowa0::CharType& next)
                {
                    // Scan the stream.
                    mowa0::TriState state = Scan(current, next, token);

                    if ( state == TRI_TRUE )
                    {
                        // Got it - store and start over.
                        tokens_.push_back(token);
                        // Reset the token.
                        token.type_ = TOKEN_ATOM;
                        token.body_.clear();
                    }
                    else if ( state == TRI_INTERMIDIATE )
                    {
                        // Continue to consume the stream.
                    }
                    else
                    {
                        // Tokenize error.
                        throw LexerException(WHERE, "Lexical error at file(line).");
                    }
                    return L_NUL;
                }
        );

        // Debug output for lexemes
        #if 0
        mowa0::String dump;
        for (auto& token: tokens_)
        {
            dump += token.body_ + _T(" ");
        }
        LOG(LOG_DEBUG, dump);
        #endif
    }
    catch(std::exception& e)
    {
        throw LexerException(e);
    }
    catch(...)
    {
        throw LexerException(WHERE);
    }

    return *this;
}

const Tokens& Lexer::GetTokens() const
{
    return tokens_;
}

}

