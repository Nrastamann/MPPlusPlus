#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <cstdlib>
enum TokenType
{
    None,
    Number,
    Id,
    Function,
    LBracket,
    Comma,
    RBracket,
    End,
    Error,
};

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
            std::cout << TokenTypeToString(this->token) << " " << *doublePtr << "\n";
        }
        else
        {
            std::cout << TokenTypeToString(this->token) << " " << std::get<std::string>(this->value) << "\n";
        }
    }
};

class MathParser
{
    Token current_t = Token();
    std::string working_str = "";
    std::string::iterator iter = this->working_str.begin();

    // map for variables,
    // map for functions, for fast access? read by symbol
public:
    MathParser(const std::string &working_str) : current_t(Token()), working_str(working_str), iter(this->working_str.begin()) {}
    void print_str()
    {
        std::cout << working_str << "\n";
    }

    void read_number()
    {
        char *ptr = nullptr;

        this->current_t.token = TokenType::Number;
        working_str = std::string(iter, working_str.end());

        this->current_t.value = strtod(working_str.c_str(), &ptr);

        working_str = ptr;
        iter = working_str.begin();
    }

    void print_token()
    {
        current_t.print();
    }

    Token &get_token()
    {
        return current_t;
    }

    void next_token()
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
            }
            else
            {
                if (std::isalpha(static_cast<unsigned char>(*iter)))
                {
                    // chek for variable/function, if there's not such name - throw an error
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
            }
            iter++;
        }
    }
};
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
}