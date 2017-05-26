#pragma once

#include <string_view>
#include <cstdint>

namespace conni::lang::lexer
{
    enum class TokenType : uint8_t
    {
        #define TOKEN(name) name,
        #include "TokenTypes.inl"
        #undef TOKEN
    };

    struct Token
    {
        TokenType token;
        std::string_view span;
    };

    bool Next(std::string_view &input, Token &token);
}
