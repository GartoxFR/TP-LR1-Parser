#include "parser/Rules.h"
#include "parser/Parser.h"

std::unique_ptr<Symbole> Rule2::reduce(Parser &parser) const {
    parser.popStates(3);

    auto &&rightSym = parser.popSymbol();
    parser.popSymbol();
    auto &&leftSym = parser.popSymbol();

    auto rightExpr =
        std::unique_ptr<Expr>(static_cast<Expr *>(rightSym.release()));
    auto leftExpr =
        std::unique_ptr<Expr>(static_cast<Expr *>(leftSym.release()));

    return std::make_unique<Add>(std::move(leftExpr), std::move(rightExpr));
}

std::unique_ptr<Symbole> Rule3::reduce(Parser &parser) const {
    parser.popStates(3);

    auto &&rightSym = parser.popSymbol();
    parser.popSymbol();
    auto &&leftSym = parser.popSymbol();

    auto rightExpr =
        std::unique_ptr<Expr>(static_cast<Expr *>(rightSym.release()));
    auto leftExpr =
        std::unique_ptr<Expr>(static_cast<Expr *>(leftSym.release()));

    return std::make_unique<Mul>(std::move(leftExpr), std::move(rightExpr));
}

std::unique_ptr<Symbole> Rule4::reduce(Parser &parser) const {
    parser.popStates(3);

    parser.popSymbol();
    auto &&exprSym = parser.popSymbol();
    parser.popSymbol();

    return std::move(exprSym);
}

std::unique_ptr<Symbole> Rule5::reduce(Parser &parser) const {
    parser.popStates(1);

    auto &&valSymbol = parser.popSymbol();

    int32_t value = static_cast<Entier *>(valSymbol.get())->value();
    return std::make_unique<Val>(value);
}
