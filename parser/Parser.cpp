#include "parser/Parser.h"
#include "lexer/symbole.h"

void Parser::shift(State* nextState) {
    stack.push_back(nextState);
    lexer().Avancer();

    Symbole *sym = lexer().Consulter();
    switch (*sym) {
        case OPENPAR:
            stack.back()->onOpenPar(*this);
            break;
        case CLOSEPAR:
            stack.back()->onClosePar(*this);
            break;
        case PLUS:
            stack.back()->onAdd(*this);
            break;
        case MULT:
            stack.back()->onMul(*this);
            break;
        case INT:
            stack.back()->onVal(*this);
            break;
    }
}

void Parser::reduce(size_t stateCount) {
    stack.resize(stack.size() - stateCount);
    stack.back()->onExpr(*this);
}
