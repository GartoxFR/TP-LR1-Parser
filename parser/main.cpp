#include "lexer/lexer.h"
#include "parser/Expr.h"
#include "parser/Parser.h"
#include <iostream>
#include <memory>

int main(void) {
    string chaine("(1+34)*123");

    Lexer l(chaine);
    Parser p(&l);

    auto& expr = p.result();
    if (expr) {
        expr->print(std::cout);
        std::cout << " = " << expr->eval() << std::endl;
    }

    return 0;
}
