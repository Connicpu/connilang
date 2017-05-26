#pragma once

#include <stdint.h>
#include <string_view>

namespace conni::utf8
{
    size_t next_char(std::string_view input, uint32_t &codepoint);

    bool is_whitespace(uint32_t codepoint);
}
