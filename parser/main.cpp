#include "lexer/lexer.h"
#include "parser/Expr.h"
#include <iostream>
#include <memory>

int main(void) {
    string chaine("(1+34)*123");

    Lexer l(chaine);

    Symbole *s;
    while (*(s = l.Consulter()) != FIN) {
        s->Affiche();
        cout << endl;
        l.Avancer();
    }

    using std::make_unique;
    using std::unique_ptr;

    unique_ptr<Expr> expr = make_unique<Add>(
        make_unique<Val>(1),
        make_unique<Mul>(make_unique<Val>(2), make_unique<Val>(3)));


    expr->print(std::cout);
    std::cout << " = " << expr->eval() << std::endl;

    return 0;
}
