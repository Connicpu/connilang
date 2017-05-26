#include "lexer.h"
#include "lexer_states.h"
#include "utf8_helpers.h"

namespace conni::lang::lexer::internals
{
    using namespace conni::utf8;

    struct ConniDfa : Dfa
    {
        ConniDfa()
        {
            auto root = Dfa::ROOT;

            auto whitespace = Create(TokenType::Whitespace);
            Transition(root, whitespace, is_whitespace);
            Transition(whitespace, whitespace, is_whitespace);
        }
    };

    const Dfa &GetDfa()
    {
        // Init on first use
        static const ConniDfa dfa;
        return dfa;
    }
}

bool conni::lang::lexer::Next(std::string_view &input, Token &token)
{
    return false;
}
