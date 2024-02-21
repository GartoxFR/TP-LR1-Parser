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

    void shift(State *nextState);

    void reduce(size_t stateCount);

  private:
    Lexer *lex;
    std::vector<State *> stack;
};

class State {
  public:
    virtual void onVal(Parser &parser) { throw exception(); }

    virtual void onOpenPar(Parser &parser) { throw exception(); }

    virtual void onClosePar(Parser &parser) { throw exception(); }

    virtual void onAdd(Parser &parser) { throw exception(); }

    virtual void onMul(Parser &parser) { throw exception(); }

    virtual void onEOF(Parser &parser) { throw exception(); }

    virtual void onExpr(Parser &parser) { throw exception(); }
};

class State0 : public State {
  public:
    void onVal(Parser &parser) override;
    void onOpenPar(Parser &parser) override;
    void onExpr(Parser &parser) override;
};

class State1 : public State {
  public:
    void onAdd(Parser &parser) override;
    void onMul(Parser &parser) override;
    void onEOF(Parser &parser) override;
};

class State2 : public State {
  public:
    void onVal(Parser &parser) override;
    void onOpenPar(Parser &parser) override;
    void onExpr(Parser &parser) override;
};

class State3 : public State {
  public:
    void onAdd(Parser &parser) override;
    void onMul(Parser &parser) override;
    void onClosePar(Parser &parser) override;
    void onEOF(Parser &parser) override;
};

class State4 : public State {
  public:
    void onVal(Parser &parser) override;
    void onOpenPar(Parser &parser) override;
    void onExpr(Parser &parser) override;
};

class State5 : public State {
  public:
    void onVal(Parser &parser) override;
    void onOpenPar(Parser &parser) override;
    void onExpr(Parser &parser) override;
};

class State6 : public State {
  public:
    void onAdd(Parser &parser) override;
    void onMul(Parser &parser) override;
    void onClosePar(Parser &parser) override;
};

class State7 : public State {
  public:
    void onAdd(Parser &parser) override;
    void onMul(Parser &parser) override;
    void onClosePar(Parser &parser) override;
    void onEOF(Parser &parser) override;
};

class State8 : public State {
  public:
    void onAdd(Parser &parser) override;
    void onMul(Parser &parser) override;
    void onClosePar(Parser &parser) override;
    void onEOF(Parser &parser) override;
};

class State9 : public State {
  public:
    void onAdd(Parser &parser) override;
    void onMul(Parser &parser) override;
    void onClosePar(Parser &parser) override;
    void onEOF(Parser &parser) override;
};
