#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MPPlusPlus.hpp"
#include <array>
#include <any>
#include <vector>
#include <span>
#include <string>
TEST_CASE("Testing lexic parser")
{
    std::string expr = "8293 + 5923 * 49129 - 59812";
    MathParser tokenizer{expr, {}};
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

TEST_CASE("TESTING BASIC FUNCTIONS WORKING")
{
    // 12.,12.
    // 24, 0, 144, 1, -12
    std::unordered_map<std::string, double> answers = {
        {"+", 24.},
        {"-", 0.},
        {"/", 1.},
        {"*", 144.},
        {"neg", -12.},
        {"log", 1.},
        {"ln", std::log(12.)},
        {"log10", std::log10(12.)},
        {"log2", std::log2(12.)},
    };

    for (const auto &x : answers)
    {
        std::vector<double> a = {12., 12.};
        if (x.first == "neg" || x.first == "ln" || x.first == "log10" || x.first == "log2")
        {
            a.resize(1);
        }
        auto ans = functions[x.first](a);
        CHECK(ans.has_value());
        if (ans.has_value())
        {
            CHECK(x.second == ans.value());
        }
    }
}

TEST_CASE("MPP_LOG TEST")
{
    std::vector<double> l2 = {static_cast<double>(LogBase::LOG2), 12.};
    std::vector<double> l10 = {static_cast<double>(LogBase::LOG10), 12.};
    std::vector<double> le = {static_cast<double>(LogBase::LN), 12.};
    std::vector<double> log = {5., 125.};

    CHECK(std::log2(12.) == *functions["log"](l2));
    CHECK(std::log10(12.) == *functions["log"](l10));
    CHECK(std::log(12.) == *functions["log"](le));
    CHECK((std::log(125.) / std::log(5.)) == *functions["log"](log));
}

TEST_CASE("FUNCTIONS PARSER")
{
    std::string expr = "neg(4.59) log(124213.5392) ln(59521.999) log10(1000000005129.5129) log2(585.85821)";
    MathParser tokenizer{expr, {}};
    TokenType tokens[] = {TokenType::Function, TokenType::LBracket, TokenType::Number, TokenType::RBracket};
    std::variant<double, std::string> variants[] = {
        "neg", 0., 4.59, 0., "log", 0., 124213.5392, 0., "ln", 0., 59521.999, 0., "log10", 0., 1000000005129.5129, 0., "log2", 0., 585.85821, 0., 0.};

    Token token = Token();
    int i = 0;
    while (token.token != TokenType::End)
    {
        tokenizer.next_token();
        token = tokenizer.get_token();

        if (token.token == TokenType::End)
        {
            break;
        }

        // if (const auto val(std::get_if<double>(&variants[i])); val)
        // {
        //     std::cout << "answer - " << *val << " token type - " << TokenTypeToString(tokens[i % 4]) << "\n";
        // }

        // if (const auto val(std::get_if<std::string>(&variants[i])); val)
        // {
        //     std::cout << "answer - " << *val << " token type - " << TokenTypeToString(tokens[i % 4]) << "\n";
        // }

        //        token.print();

        CHECK(token.token == tokens[i % 4]);

        if (const auto val(std::get_if<double>(&token.value)); val)
        {
            CHECK(*val == std::get<double>(variants[i]));
        }
        else
        {
            // token.print();
            CHECK(std::get<std::string>(token.value) == std::get<std::string>(variants[i]));
        }
        i++;
    }
}

TEST_CASE("VARIABLES PARSER")
{
    std::string expr = "(( x + x + x + y + z + y + z )) neg(x) log(y) ln(jfia_942895) log10(ffyw77676716) log2(_____fuadu)";
    MathParser tokenizer{expr, {{"x", 0.}, {"y", 0.}, {"z", 0.}, {"jfia_942895", 0.}, {"ffyw77676716", 0}, {"_____fuadu", 0}}};
    TokenType tokens[] = {
        TokenType::LBracket, TokenType::LBracket, TokenType::Variable, TokenType::Function, TokenType::Variable, TokenType::Function, TokenType::Variable, TokenType::Function, TokenType::Variable, TokenType::Function, TokenType::Variable, TokenType::Function, TokenType::Variable, TokenType::Function, TokenType::Variable, TokenType::RBracket, TokenType::RBracket, TokenType::Function, TokenType::LBracket, TokenType::Variable, TokenType::RBracket, TokenType::Function, TokenType::LBracket, TokenType::Variable, TokenType::RBracket, TokenType::Function, TokenType::LBracket, TokenType::Variable, TokenType::RBracket, TokenType::Function, TokenType::LBracket, TokenType::Variable, TokenType::RBracket, TokenType::Function, TokenType::LBracket, TokenType::Variable, TokenType::RBracket};
    std::variant<double, std::string> variants[] = {
        0., 0., "x", "+", "x", "+", "x", "+", "y", "+", "z", "+", "y", "+", "z", 0., 0., "neg", 0., "x", 0., "log", 0., "y", 0., "ln", 0., "jfia_942895", 0., "log10", 0., "ffyw77676716", 0., "log2", 0., "_____fuadu", 0., 0.};

    Token token = Token();
    int i = 0;
    while (token.token != TokenType::End)
    {
        tokenizer.next_token();
        token = tokenizer.get_token();

        if (token.token == TokenType::End)
        {
            break;
        }

        // if (const auto val(std::get_if<double>(&variants[i])); val)
        // {
        //     std::cout << "answer - " << *val << " token type - " << TokenTypeToString(tokens[i % 4]) << "\n";
        // }

        // if (const auto val(std::get_if<std::string>(&variants[i])); val)
        // {
        //     std::cout << "answer - " << *val << " token type - " << TokenTypeToString(tokens[i % 4]) << "\n";
        // }

        //        token.print();

        CHECK(token.token == tokens[i]);

        if (const auto val(std::get_if<double>(&token.value)); val)
        {
            CHECK(*val == std::get<double>(variants[i]));
        }
        else
        {
            // token.print();
            CHECK(std::get<std::string>(token.value) == std::get<std::string>(variants[i]));
        }
        i++;
    }
}