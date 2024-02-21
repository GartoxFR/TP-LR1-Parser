#include "lexer/lexer.h"
#include "parser/Expr.h"
#include "parser/Parser.h"
#include <iostream>
#include <memory>

int main(void) {
    string line;

    std::cout << ">> " << std::flush;
    while (getline(std::cin, line)) {

        Lexer l(line);
        Parser p(&l);

        auto& expr = p.result();
        if (expr) {
            expr->print(std::cout);
            std::cout << " = " << expr->eval() << std::endl;
        }

        std::cout << ">> " << std::flush;
    }

    return 0;
}
