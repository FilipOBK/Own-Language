#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Values.h"

std::variant<Number, std::shared_ptr<Error>> run(std::string text)
{
    // * Generate tokens
    Lexer lexer(text, "stdin");
    auto result = lexer.MakeTokens();
    if(auto err = std::get_if<1>(&result)) return *err;

    auto tokens = std::get<0>(result);

    // * Generate AST
    Parser parser(tokens);
    auto ast = parser.Parse();

    if(ast.error) return ast.error;

    // * Run program
    Interpreter interpreter;
    Context context("<program>");
    RuntimeResult res = interpreter.Visit(ast.node, std::make_shared<Context>(context));

    if(res.error) return res.error;
    return res.value;
}


int main()
{
    std::string input;
    while(true)
    {
        std::cout << "basic > ";
        std::getline(std::cin, input);
        
        auto result = run(input);
        if(auto err = std::get_if<1>(&result))
        {
            std::cout << err->get()->As_String() << std::endl;
            return 0;
        }
        else
        {
            Number res = std::get<0>(result);
            std::cout << res << std::endl;
        }
    }
}