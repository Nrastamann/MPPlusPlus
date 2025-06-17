#include <iostream>
#include <variant>
#include <vector>
#include <iterator>
#include <string>
#include <cstdlib>
#include <unordered_map>

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

static std::unordered_map<std::string, std::variant<double, int>> functions;
// https://stackoverflow.com/questions/45715219/store-functions-with-different-signatures-in-a-map
static std::string TokenTypeToString(TokenType token) throw();

struct Token
{
    TokenType token = TokenType::None;
    std::variant<double, std::string> value;

    void print();
};

class MathParser
{
    Token current_t = Token();
    std::string_view working_str = "";
    std::string_view::const_iterator iter = working_str.cbegin();
public:
    MathParser(const std::string &working_str) : current_t(Token()), working_str(working_str), iter(this->working_str.begin()) {}

    void print_str()
    {
        std::cout << working_str << "\n";
    }

    void read_number();

    void print_token()
    {
        current_t.print();
    }

    void next_token();

    Token &get_token()
    {
        return current_t;
    }
};