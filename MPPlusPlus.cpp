#include "MPPlusPlus.hpp"
#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <cstdlib>
#include <span>
#include <cmath>
#include <unordered_map>
#include <expected>

std::expected<double, Errors> sum(std::span<double> a)
{
    if (SAFETY_CHECKS && a.size() == 0)
        return std::unexpected(Errors::empty_input);
    if (UNLIMITED_ARGUMENTS)
    {
        double ans = 0.;
        for (const auto &x : a)
        {
            ans += x;
        }
        return ans;
    }
    if (SAFETY_CHECKS)
    {
        if (a.size() != 2)
        {
            return std::unexpected(Errors::invalid_input_size);
        }
    }
    return a[0] + a[1];
}

std::expected<double, Errors> divd(std::span<double> a)
{
    if (SAFETY_CHECKS && a.size() == 0)
        return std::unexpected(Errors::empty_input);
    if (UNLIMITED_ARGUMENTS)
    {
        double ans = a[0];
        for (auto i = 1; i < a.size(); i++)
        {
            if (SAFETY_CHECKS)
            {
                if (a[i] == 0)
                {
                    return std::unexpected(Errors::divide_by_zero);
                }
            }
            ans /= a[i];
        }
        return ans;
    }
    if (SAFETY_CHECKS)
    {
        if (a.size() != 2)
        {
            return std::unexpected(Errors::invalid_input_size);
        }
    }
    return a[0] / a[1];
}
std::expected<double, Errors> mult(std::span<double> a)
{
    if (SAFETY_CHECKS && a.size() == 0)
        return std::unexpected(Errors::empty_input);
    if (UNLIMITED_ARGUMENTS)
    {
        double ans = 1.0;
        for (const auto &x : a)
        {
            ans *= x;
        }
        return ans;
    }

    if (SAFETY_CHECKS)
    {
        if (a.size() != 2)
        {
            return std::unexpected(Errors::invalid_input_size);
        }
    }
    return a[0] * a[1];
}

std::expected<double, Errors> mpp_log(std::span<double> a)
{
    if (SAFETY_CHECKS && a.size() == 0)
        return std::unexpected(Errors::empty_input);

    if (SAFETY_CHECKS)
    {
        if (a.size() != 2)
        {
            return std::unexpected(Errors::invalid_input_size);
        }
    }

    if (LOGM_CHECKS)
    {
        switch (static_cast<int>(a[0]))
        {
        case static_cast<int>(LogBase::LN):
            return std::log(a[1]);
        case static_cast<int>(LogBase::LOG10):
            return std::log10(a[1]);
        case static_cast<int>(LogBase::LOG2):
            return std::log2(a[1]);
        }
    }
    return std::log(a[1]) / std::log(a[0]);
}

std::expected<double, Errors> mpp_ln(std::span<double> a)
{
    if (SAFETY_CHECKS && a.size() == 0)
        return std::unexpected(Errors::empty_input);

    if (SAFETY_CHECKS)
    {
        if (a.size() != 1)
        {
            return std::unexpected(Errors::invalid_input_size);
        }
    }
    return std::log(a[0]);
}

std::expected<double, Errors> mpp_log2(std::span<double> a)
{
    if (SAFETY_CHECKS && a.size() == 0)
        return std::unexpected(Errors::empty_input);

    if (SAFETY_CHECKS)
    {
        if (a.size() != 1)
        {
            return std::unexpected(Errors::invalid_input_size);
        }
    }
    return std::log2(a[0]);
}

std::expected<double, Errors> mpp_log10(std::span<double> a)
{
    if (SAFETY_CHECKS && a.size() == 0)
        return std::unexpected(Errors::empty_input);

    if (SAFETY_CHECKS)
    {
        if (a.size() != 1)
        {
            return std::unexpected(Errors::invalid_input_size);
        }
    }
    return std::log10(a[0]);
}

std::expected<double, Errors> sub(std::span<double> a)
{
    if (SAFETY_CHECKS && a.size() == 0)
        return std::unexpected(Errors::empty_input);

    if (UNLIMITED_ARGUMENTS)
    {
        double ans = a[0];
        for (auto i = 1; i < a.size(); i++)
        {
            ans -= a[i];
        }
        return ans;
    }

    if (SAFETY_CHECKS)
    {
        if (a.size() != 2)
        {
            return std::unexpected(Errors::invalid_input_size);
        }
    }
    return a[0] - a[1];
}

std::expected<double, Errors> neg(std::span<double> a)
{
    if (SAFETY_CHECKS && a.size() != 1)
        return std::unexpected(Errors::invalid_input_size);

    return -a[0];
}

// const FunctionsHolder holder;

std::string TokenTypeToString(TokenType token) throw()
{
    switch (token)
    {
    case TokenType::None:
        return "None";
    case TokenType::Number:
        return "Number";
    case TokenType::Id:
        return "Id";
    case TokenType::Function:
        return "Function";
    case TokenType::LBracket:
        return "LBracket";
    case TokenType::RBracket:
        return "RBracket";
    case TokenType::End:
        return "End";
    case TokenType::Comma:
        return "Comma";
    case TokenType::Error:
        return "Error";
    case TokenType::Variable:
        return "Variable";
    default:
        throw std::invalid_argument("No such token type");
    }
}

void Token::print()
{
    if (const auto doublePtr(std::get_if<double>(&this->value)); doublePtr)
    {
        std::cout << TokenTypeToString(this->token) << " " << *doublePtr << "val\n";
    }
    else
    {
        std::cout << TokenTypeToString(this->token) << " " << std::get<std::string>(this->value) << "val\n";
    }
}

void MathParser::next_token()
{
    current_t = Token();
    while (current_t.token == TokenType::None)
    {
        if (iter + 1 >= working_str.end())
        {
            current_t.token = TokenType::End;
            return;
        }

        if ((*iter >= '0' && *iter <= '9') || *iter == '.')
        {
            this->read_number();
            return;
        }

        if (std::isalpha(static_cast<unsigned char>(*iter)) || *iter == '_')
        {
            working_str = std::string(iter, working_str.end());
            iter = working_str.begin();

            while (std::isalpha(static_cast<unsigned char>(*iter)) || *iter == '_' || std::isdigit(static_cast<unsigned char>(*iter)))
            {
                iter++;
            }
            const std::string possible_token = std::string(working_str.begin(), iter);
            if (functions.contains(possible_token))
            {
                current_t.token = TokenType::Function;
                current_t.value = possible_token;
                return;
            }
            if (variables.contains(possible_token))
            {
                current_t.token = TokenType::Variable;
                current_t.value = possible_token;
                return;
            }

            for (auto &x : variables)
            {
                std::cout << x.first << " and second " << x.second << "\n";
            }

            std::cout << "\n\nPOSSIBLE TOKEN -" << possible_token << "\n\n";

            current_t.token = TokenType::Error;
        }
        else
        {
            switch (*this->iter)
            {
            case '+':
                current_t.token = TokenType::Function;
                current_t.value = "+";
                break;
            case '-':
                current_t.token = TokenType::Function;
                current_t.value = "-";
                break;
            case '*':
                current_t.token = TokenType::Function;
                current_t.value = "*";
                break;
            case '/':
                current_t.token = TokenType::Function;
                current_t.value = "/";
                break;
            case '^':
                current_t.token = TokenType::Function;
                current_t.value = "^";
                break;
            case '%':
                current_t.token = TokenType::Function;
                current_t.value = "%";
                break;
            case ' ':
            case '\t':
            case '\n':
            case 'r':
                break;
            case '(':
                current_t.token = TokenType::LBracket;
                break;
            case ')':
                current_t.token = TokenType::RBracket;
                break;
            case ',':
                current_t.token = TokenType::Comma;
                break;
            default:
                current_t.token = TokenType::Error;
                std::cout << *this->iter;
            }
            // special symbols and operators, check there.
        }

        iter++;
    }
}

void MathParser::read_number()
{
    size_t ptr = 0;

    current_t.token = TokenType::Number;
    working_str = working_str.substr(iter - working_str.begin());

    current_t.value = std::stod(working_str.data(), &ptr);

    working_str = working_str.substr(ptr);

    iter = working_str.begin();
}
/*
int main()
{

    MathParser tokenizer{"8293 + 5923 * 49129 - 59812"};
    std::string expr = "8293 + 5923 * 49129 - 59812";

    Token token = Token();

    while (token.token != TokenType::End)
    {
        tokenizer.next_token();
        token = tokenizer.get_token();
        token.print();
    }
}*/