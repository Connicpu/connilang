#pragma once

#include "lexer.h"
#include <vector>
#include <unordered_map>
#include <optional>
#include <functional>

namespace conni::lang::lexer::internals
{
    class Dfa;
    class EvalState;

    enum class EvalResult
    {
        Invalid,
        Valid,
    };

    class Dfa
    {
    public:
        EvalState Begin(std::string_view &view) const;
        EvalResult Advance(EvalState &state) const;

        static const size_t ROOT = 0;
        static const size_t EMPTY_TARGET = 0;

        size_t Create(std::optional<TokenType> token = std::nullopt);
        void Transition(size_t from, size_t to);
        void Transition(size_t from, size_t to, uint32_t codepoint);
        void Transition(size_t from, size_t to, uint32_t codepoint_begin, uint32_t codepoint_end);
        void Transition(size_t from, size_t to, bool(*func)(uint32_t));

    private:
        struct Edge
        {
            std::unordered_map<uint32_t, size_t> edges;
            std::vector<std::tuple<uint32_t, uint32_t, size_t>> range_edges;
            std::vector<std::pair<bool(*)(uint32_t), size_t>> func_edges;
            size_t default_edge;
            std::optional<TokenType> token;
        };

        std::vector<Edge> edges;
    };

    class EvalState
    {
    public:
        Token Finalize();

    private:
        EvalState(std::string_view &view);
        friend class Dfa;

        TokenType tt;
        std::string_view &view;
        size_t position;

        TokenType last_good_tt = TokenType::Invalid;
        size_t last_good_pos = 0;
    };
}
