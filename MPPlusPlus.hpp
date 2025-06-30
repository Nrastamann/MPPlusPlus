#include <iostream>
#include <variant>
#include <vector>
#include <iterator>
#include <string>
#include <cstdlib>
#include <any>
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <functional>
#include <span>
#include <expected>

constexpr bool UNLIMITED_ARGUMENTS{false};
constexpr bool SAFETY_CHECKS{false};

enum class Errors{
    invalid_input_size,
    empty_input,
    divide_by_zero,
};

std::expected<double, Errors> sum(std::span<double> a);
std::expected<double, Errors> divd(std::span<double> a);
std::expected<double, Errors> mult(std::span<double> a);
std::expected<double, Errors> sub(std::span<double> a);
std::expected<double, Errors> neg(std::span<double> a);

enum class TokenType
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

static std::unordered_map<std::string_view, std::function<std::expected<double, Errors>(std::span<double>)>> functions{
    {"+", sum},
    {"-", sub},
    {"*", mult},
    {"/", divd},
    {"neg", neg},
};

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