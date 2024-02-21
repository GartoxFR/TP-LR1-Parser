#pragma once

#include "lexer/lexer.h"
#include "parser/Expr.h"
#include "parser/Rules.h"
#include <cstdint>
#include <memory>
#include <variant>
#include <vector>

class State;
class Parser;

struct Accept {};

struct Shift {
    explicit Shift(State *nextState) : nextState(nextState) {}
    State *nextState;
};

struct Reduce {
    explicit Reduce(Rule *rule) : rule(rule) {}
    Rule *rule;
};

using TransitionResult = std::variant<Shift, Reduce, Accept>;

class Parser {
  public:
    Parser(Lexer *lexer);
    Lexer &lexer() { return *lex; }

    void popStates(size_t count) { stack.resize(stack.size() - count); }

    std::unique_ptr<Symbole> popSymbol() {
        auto symbol = std::move(symbolStack.back());

        symbolStack.pop_back();

        return symbol;
    }

    std::unique_ptr<Expr> &result() { return finalExpr; }

  private:
    void execute();
    Lexer *lex;
    std::vector<State *> stack;
    std::vector<std::unique_ptr<Symbole>> symbolStack;
    std::unique_ptr<Symbole> nextSymbol;
    std::unique_ptr<Expr> finalExpr;
};

class State {
  public:
    TransitionResult onSymbol(const Symbole &symbole) {

        switch (symbole) {
        case OPENPAR:
            return onOpenPar();
            break;
        case CLOSEPAR:
            return onClosePar();
            break;
        case PLUS:
            return onAdd();
            break;
        case MULT:
            return onMul();
            break;
        case INT:
            return onVal();
            break;
        case EXPR:
            return onExpr();
            break;
        case FIN:
            return onEOF();
            break;
        }

        throw exception();
    }

    virtual TransitionResult onVal() { throw exception(); }

    virtual TransitionResult onOpenPar() { throw exception(); }

    virtual TransitionResult onClosePar() { throw exception(); }

    virtual TransitionResult onAdd() { throw exception(); }

    virtual TransitionResult onMul() { throw exception(); }

    virtual TransitionResult onEOF() { throw exception(); }

    virtual TransitionResult onExpr() { throw exception(); }
};

class State0 : public State {
  public:
    TransitionResult onVal() override;
    TransitionResult onOpenPar() override;
    TransitionResult onExpr() override;
};

class State1 : public State {
  public:
    TransitionResult onAdd() override;
    TransitionResult onMul() override;
    TransitionResult onEOF() override;
};

class State2 : public State {
  public:
    TransitionResult onVal() override;
    TransitionResult onOpenPar() override;
    TransitionResult onExpr() override;
};

class State3 : public State {
  public:
    TransitionResult onAdd() override;
    TransitionResult onMul() override;
    TransitionResult onClosePar() override;
    TransitionResult onEOF() override;
};

class State4 : public State {
  public:
    TransitionResult onVal() override;
    TransitionResult onOpenPar() override;
    TransitionResult onExpr() override;
};

class State5 : public State {
  public:
    TransitionResult onVal() override;
    TransitionResult onOpenPar() override;
    TransitionResult onExpr() override;
};

class State6 : public State {
  public:
    TransitionResult onAdd() override;
    TransitionResult onMul() override;
    TransitionResult onClosePar() override;
};

class State7 : public State {
  public:
    TransitionResult onAdd() override;
    TransitionResult onMul() override;
    TransitionResult onClosePar() override;
    TransitionResult onEOF() override;
};

class State8 : public State {
  public:
    TransitionResult onAdd() override;
    TransitionResult onMul() override;
    TransitionResult onClosePar() override;
    TransitionResult onEOF() override;
};

class State9 : public State {
  public:
    TransitionResult onAdd() override;
    TransitionResult onMul() override;
    TransitionResult onClosePar() override;
    TransitionResult onEOF() override;
};
