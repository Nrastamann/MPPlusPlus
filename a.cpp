#include <iostream>
#include <variant>
#include <vector>
#include <string>
enum TokenType
{
    None,
    Number,
    Id,
    Operator,
    Function,
    LBracket,
    RBracket,
};

const std::string TokenTypeToString(TokenType token) throw()
{
    switch (token)
    {
    case TokenType::None:
        return "None";
    case TokenType::Number:
        return "Number";
    case TokenType::Id:
        return "Id";
    case TokenType::Operator:
        return "Operator";
    case TokenType::Function:
        return "Function";
    case TokenType::LBracket:
        return "LBracket";
    case TokenType::RBracket:
        return "RBracket";
    default:
        throw std::invalid_argument("No such token type");
    }
}

struct Token
{
    TokenType token = TokenType::None;
    std::variant<double, std::string> value;

    void print()
    {
        if (const auto doublePtr(std::get_if<double>(&this->value)); doublePtr)
        {
            std::cout << TokenTypeToString(this->token) << " " << *doublePtr;
        }
        else
        {
            std::cout << TokenTypeToString(this->token) << " " << std::get<std::string>(this->value);
        }
    }
};

class MathParser
{
    Token current_t;
    std::string working_str = "";
    std::string::iterator iter = this->working_str.begin();

    // map for variables,
    // map for functions, for fast access? read by symbol
public:
    MathParser(const std::string &working_str) : current_t(Token()), working_str(working_str), iter(this->working_str.begin()) {}
    void next_token()
    {
        Token reading_token{TokenType::None, ""};
        std::string substr = "";
        TokenType token_type = TokenType::None;
        if ((this->working_str[0] >= '0' && this->working_str[0] <= '9') || this->working_str[0] == '.')
        {
            reading_token.value = std::stof(this->working_str);
            std::cout << "value is - " << std::get<double>(reading_token.value) << "\n";
            return;
            //we read number, must break, but need to cut string and do stuff, 
        }
        else
        {
            if (std::isalpha(static_cast<unsigned char>(this->working_str[0])))
            {
                // chek for variable/function, if there's not such name - throw an error
            }
            else
            {
                // special symbols and operators, check there.
            }
        }
    }
};

int main()
{
    MathParser tokenizer{"8293 + 5832 * 593285 - 583.59283 / 923"};
}