#include "utf8_helpers.h"

size_t conni::utf8::next_char(std::string_view input, uint32_t & codepoint)
{
    // Skip over invalid middle-of-the-codepoint bytes
    while (!input.empty() && (input[0] & 0b1100'0000) == 0b1000'0000)
        input = input.substr(1);

    if (input.empty())
        return 0;

    switch (input[0] >> 4)
    {
        case 0b0000:
        case 0b0001:
        case 0b0010:
        case 0b0011:
        case 0b0100:
        case 0b0101:
        case 0b0110:
        case 0b0111:
            codepoint = input[0];
            return 1;

        case 0b1100:
        case 0b1101:
            if (input.size() < 2)
                return 0;

            codepoint =
                ((input[0] & 0b0001'1111U) << 6) |
                ((input[1] & 0b0011'1111U) << 0);
            return 2;

        case 0b1110:
            if (input.size() < 3)
                return 0;

            codepoint =
                ((input[0] & 0b0000'1111U) << 12) |
                ((input[1] & 0b0011'1111U) << 6) |
                ((input[2] & 0b0011'1111U) << 0);
            return 3;

        case 0b1111:
            if (input.size() < 4)
                return 0;

            codepoint =
                ((input[0] & 0b0000'1111U) << 18) |
                ((input[1] & 0b0011'1111U) << 12) |
                ((input[2] & 0b0011'1111U) << 6) |
                ((input[3] & 0b0011'1111U) << 0);
            return 4;

        case 0b1000:
        case 0b1001:
        case 0b1010:
        case 0b1011:
            throw "This shouldn't be reachable";
    }
}

bool conni::utf8::is_whitespace(uint32_t codepoint)
{
    switch (codepoint)
    {
        // Standard spaces
        case 9:     // CHARACTER TABULATION
        case 10:    // LINE FEED
        case 11:    // LINE TABULATION
        case 12:    // FORM FEED
        case 13:    // CARRIAGE RETURN
        case 32:    // SPACE
        case 133:   // NEXT LINE
        case 160:   // NO-BREAK SPACE
        case 5760:  // OGHAM SPACE MARK
        case 8192:  // EN QUAD
        case 8193:  // EM QUAD
        case 8194:  // EN SPACE
        case 8195:  // EM SPACE
        case 8196:  // THREE-PER-EM SPACE
        case 8197:  // FOUR-PER-EM SPACE
        case 8198:  // SIX-PER-EM SPACE
        case 8199:  // FIGURE SPACE
        case 8200:  // PUNCTUATION SPACE
        case 8201:  // THIN SPACE
        case 8202:  // HAIR SPACE
        case 8232:  // LINE SEPARATOR
        case 8233:  // PARAGRAPH SEPARATOR
        case 8239:  // NARROW NO-BREAK SPACE
        case 8287:  // MEDIUM MATHEMATICAL SPACE
        case 12288: // IDEOGRAPHIC SPACE

        // Non-standard spaces that we consider whitespace to make the compiler permissive
        case 6158:  // MONGOLIAN VOWEL SEPARATOR
        case 8203:  // ZERO WIDTH SPACE
        case 8204:  // ZERO WIDTH NON-JOINER
        case 8205:  // WORD JOINER
        case 65279: // ZERO WIDTH NON-BREAKING SPACE (BOM)
            return true;
        default:
            return false;
    }
}

