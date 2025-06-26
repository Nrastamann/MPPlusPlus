#include <iostream>
#include <variant>
#include <vector>
#include <iterator>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <memory>
#include <functions.hpp>

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

class FunctionPointer
{
public:
    template <typename T>
    FunctionPointer(const T &t) : held_(std::make_unique<T>(t)) {}

    template <typename U>
    U cast() const
    {
        if (typeid(U) != held_->type_info())
            throw std::runtime_error("Bad any cast");
        return static_cast<holder<U> *>(held_)->t_;
    }

private:
    struct base_holder
    {
        virtual ~base_holder() {}
        virtual const std::type_info &type_info() const = 0;
    };
    template <typename T>
    struct holder : base_holder
    {
        holder(const T &t) : t_(t) {}
        const std::type_info &type_info() const
        {
            return typeid(t_);
        }
        T t_;
    };

private:
    std::unique_ptr<base_holder> held_;
};

static const std::unordered_map<std::string, FunctionPointer> functions = {
    {"+", FunctionPointer(&sum)},
    {"-", FunctionPointer(&sub)},
    {"*", FunctionPointer(&mult)},
    {"/", FunctionPointer(&divd)},
};

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