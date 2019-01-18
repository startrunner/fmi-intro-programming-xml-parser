#pragma once
#include "token_type.h"
class token
{
    const std::string mText = "";
public:
    const token_type type = token_type::AT_SIGN;
    const text_position position = { 0, 0, 0 };

    token() {}

    token(token_type type, text_position position, std::string text = "") :
        type(type), position(position), mText(text) {}

    std::string text()const;
    bool is_terminal()const;

    std::string get_literal_value()const;
};