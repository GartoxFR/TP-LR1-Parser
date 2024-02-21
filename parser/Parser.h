#pragma once

#include "lexer/lexer.h"
#include "parser/Expr.h"
#include <cstdint>
#include <memory>
#include <vector>

class State;

class Parser {
  public:
    Lexer &lexer() { return *lex; }

    void shift(State* nextState); 

    void reduce(size_t stateCount);

  private:
    void transition();
    Lexer *lex;
    std::vector<State*> stack;
};

class State {
  public:
    virtual void onVal(Parser &parser) { throw exception(); }

    virtual void onOpenPar(Parser &parser) { throw exception(); }

    virtual void onClosePar(Parser &parser) { throw exception(); }

    virtual void onAdd(Parser &parser) { throw exception(); }

    virtual void onMul(Parser &parser) { throw exception(); }

    virtual void onEOF(Parser &parser) { throw exception(); }

    virtual void onExpr(Parser &parser) {
        throw exception();
    }
};
