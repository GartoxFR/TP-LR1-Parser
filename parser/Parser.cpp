#include "parser/Parser.h"
#include "lexer/symbole.h"

static State0 S0;
static State1 S1;
static State2 S2;
static State3 S3;
static State4 S4;
static State5 S5;
static State6 S6;
static State7 S7;
static State8 S8;
static State9 S9;

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

void State0::onVal(Parser &parser){
    parser.shift(&S3);
}
