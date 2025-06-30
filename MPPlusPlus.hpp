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
class FunctionPointer
{
    const uint16_t arity;
    std::function<double(std::span<double>)> function;

public:

};
// class FunctionPointer
// {
// public:
//     template <typename T>
//     FunctionPointer(const T &t) : held_(std::make_shared<holder<T>>(t)) {}
//     ~FunctionPointer() {}

//     template <typename U>
//     U cast() const
//     {
//         if (typeid(U) != held_->type_info())
//             throw std::runtime_error("Bad any cast");
//         return static_cast<holder<U>* >(held_.get())->t_;
//     }

// private:
//     struct base_holder
//     {
//         virtual ~base_holder() {}
//         virtual const std::type_info &type_info() const = 0;
//     };
//     template <typename T> struct holder : base_holder
//     {
//         holder(const T &t) : t_(t) {}
//         const std::type_info &type_info() const
//         {
//             return typeid(t_);
//         }
//         T t_;
//     };

// private:
//     std::shared_ptr<base_holder> held_;
// };

// template<typename... Args>
// static const std::unordered_map<std::string_view, std::function<double(Args...)>> functions = {
//     {"+", std::function<double(double,double)>(&sum)},
//     {"-", std::function<double(double,double)>(&sub)},
//     {"*", std::function<double(double,double)>(&mult)},
//     {"/", std::function<double(double,double)>(&divd)},
//     {"neg", std::function<double(double)>(&neg)},
// };

// static const std::unordered_map<std::string_view, FunctionPointer> functions{
//     {"+", FunctionPointer(0)},
//     {"-", FunctionPointer(1)},
//     {"*", FunctionPointer(2)},
//     {"/", FunctionPointer(3)},
//     {"neg", FunctionPointer(4)},
// };

// https://stackoverflow.com/questions/45715219/store-functions-with-different-signatures-in-a-map
static std::string TokenTypeToString(TokenType token) throw();

double strtod();

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