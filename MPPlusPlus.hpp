#include <iostream>
#include <variant>
#include <vector>
#include <iterator>
#include <string>
#include <any>
#include <unordered_map>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <functional>
#include <span>
#include <expected>

constexpr bool UNLIMITED_ARGUMENTS{true};
constexpr bool SAFETY_CHECKS{true};
constexpr bool LOGM_CHECKS{true};

enum class LogBase
{
    LOG10 = 0,
    LN = 1,
    LOG2 = 2,
};

enum class Errors
{
    invalid_input_size,
    empty_input,
    divide_by_zero,
};

std::expected<double, Errors> sum(std::span<double> a);
std::expected<double, Errors> divd(std::span<double> a);
std::expected<double, Errors> mult(std::span<double> a);
std::expected<double, Errors> sub(std::span<double> a);
std::expected<double, Errors> neg(std::span<double> a);
std::expected<double, Errors> mpp_log(std::span<double> a);
std::expected<double, Errors> mpp_log2(std::span<double> a);
std::expected<double, Errors> mpp_log10(std::span<double> a);
std::expected<double, Errors> mpp_ln(std::span<double> a);

enum class TokenType
{
    None,
    Number,
    Id,
    Variable,
    Function,
    LBracket,
    Comma,
    RBracket,
    End,
    Error,
};

class variable
{
public:
};
using function_mpp = std::function<std::expected<double, Errors>(std::span<double>)>;
static std::unordered_map<std::string, function_mpp> functions{
    {"+", sum},
    {"-", sub},
    {"*", mult},
    {"/", divd},
    {"neg", neg},
    {"log", mpp_log},
    {"ln", mpp_ln},
    {"log10", mpp_log10},
    {"log2", mpp_log2},
};

// https://stackoverflow.com/questions/45715219/store-functions-with-different-signatures-in-a-map
std::string TokenTypeToString(TokenType token) throw();

struct Token
{
    TokenType token = TokenType::None;
    std::variant<double, std::string> value;
    void print();
};

class MathParser
{
    Token current_t;
    std::string working_str;
    std::string::iterator iter;
    std::unordered_map<std::string, double> variables;

public:
    MathParser(std::string_view working_str, std::unordered_map<std::string, double> variables) : current_t(Token()), working_str(working_str), iter(this->working_str.begin()), variables(variables)
    {
    }

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