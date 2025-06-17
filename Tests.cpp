#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MPPlusPlus.hpp"

TEST_CASE("Testing lexic parser")
{
    std::string expr = "8293 + 5923 * 49129 - 59812"; 
    MathParser tokenizer{expr};
    TokenType tokens[] = {TokenType::Number, TokenType::Function, TokenType::Number, TokenType::Function, TokenType::Number, TokenType::Function, TokenType::Number, TokenType::End};
    std::variant<double, std::string> variants[] = {8293., "+", 5923., "*", 49129., "-", 59812., 0.};
    Token token = Token();
    int i = 0;
    while (token.token != TokenType::End)
    {
        tokenizer.next_token();
        token = tokenizer.get_token();
        CHECK(token.token == tokens[i]);
        if (const auto val(std::get_if<double>(&token.value)); val)
        {
            CHECK(*val == std::get<double>(variants[i]));
        }
        else
        {
            CHECK(std::get<std::string>(token.value) == std::get<std::string>(variants[i]));
        }
        i++;
    }
}
