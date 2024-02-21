#include "parser/Parser.h"
#include "lexer/symbole.h"

const State0 S0;
const State1 S1;
const State2 S2;
const State3 S3;
const State4 S4;
const State5 S5;
const State6 S6;
const State7 S7;
const State8 S8;
const State9 S9;

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
