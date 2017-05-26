#include "lexer_states.h"

namespace conni::lang::lexer::internals
{
    EvalState Dfa::Begin(std::string_view &view) const
    {
        return EvalState(view);
    }

    EvalResult Dfa::Advance(EvalState &state) const
    {
        // TODO
        return EvalResult();
    }

    size_t Dfa::Create(std::optional<TokenType> token)
    {
        size_t id = edges.size();
        edges.emplace_back();
        return id;
    }

    void Dfa::Transition(size_t from, size_t to)
    {
        edges[from].default_edge = to;
    }

    void Dfa::Transition(size_t from, size_t to, uint32_t codepoint)
    {
        edges[from].edges[codepoint] = to;
    }

    void Dfa::Transition(size_t from, size_t to, uint32_t codepoint_begin, uint32_t codepoint_end)
    {
        edges[from].range_edges.emplace_back(codepoint_begin, codepoint_end, to);
    }

    void Dfa::Transition(size_t from, size_t to, bool(*func)(uint32_t))
    {
        edges[from].func_edges.emplace_back(func, to);
    }

    Token EvalState::Finalize()
    {
        Token tok;
        tok.token = tt;
        tok.span = view.substr(0, last_good_pos);
        view = view.substr(last_good_pos);
        return tok;
    }

    EvalState::EvalState(std::string_view &view)
        : tt(TokenType::Invalid), view(view), position(0)
    {
    }
}
