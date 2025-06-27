#include "MPPlusPlus.hpp"
#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <cstdlib>
#include <unordered_map>

double sum(double a, double b) { return a + b; }
double divd(double a, double b) { return a / b; }
double mult(double a, double b) { return a * b; }
double sub(double a, double b) { return a - b; }
double neg(double a) { return -a; }

static std::string TokenTypeToString(TokenType token) throw()
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
    default:
        throw std::invalid_argument("No such token type");
    }
}
/*
double strtod(std::string_view::const_iterator &iter, std::string_view str){
    double answer = 0.;

    while(iter <= str.end()){
        if(!std::isdigit(*iter)){
            return 0;
        }
    }
    //ну стртод, только имплементация своя
}
*/
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
            continue;
        }

        if (std::isalpha(static_cast<unsigned char>(*iter)) || *iter == '_')
        {
            while(*iter!=' ') iter++;
            
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
            }
            // special symbols and operators, check there.
        }

        iter++;
    }
}

void MathParser::read_number()
{
    char *ptr = nullptr;

    current_t.token = TokenType::Number;
    working_str.remove_prefix(iter - working_str.begin());

    current_t.value = strtod(working_str.data(), &ptr);

    working_str.remove_prefix(ptr - working_str.begin());

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