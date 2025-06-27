#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MPPlusPlus.hpp"
#include <array>
#include <any>
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
TEST_CASE("TESTING ERASURE")
{
    FunctionPointer a(2);
    CHECK(a.cast<int>() == 2);
    //FunctionPointer test(&sum);
    //functions["+"] = test;

}/*
TEST_CASE("TESTING FUNCTIONS ERASURE")
{
    const std::unordered_map<std::string_view, double> function_results = {{"+", 24.}, {"*", 144.}, {"-", 0.}, {"/", 1.}};
    auto key = std::string_view("neg");
    auto &par = typeid(double (*)(double, double));
    auto &x = (functions<par>.at("neg"));
    for (auto &x : functions<double, double>)
    {
        x.first;
        x.second(12.);
        double res = x.second(12., 12.);
        CHECK(res == function_results.at(x.first));
    }
}*/