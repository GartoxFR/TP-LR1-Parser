#pragma once

#include "lexer/lexer.h"
#include "parser/Expr.h"
#include <cstdint>
#include <memory>
#include <vector>

class State;

class Parser {
  public:
    Parser(Lexer *lexer);
    Lexer &lexer() { return *lex; }

    void shiftTerm(State *nextState);
    void shiftNonTerm(State *nextState);

    void transition();
    void reduce(size_t stateCount, std::unique_ptr<Symbole> &&symbol);

    std::unique_ptr<Symbole> popSymbol() {
        auto symbol = std::move(symbolStack.back());

        symbolStack.pop_back();

        return symbol;
    }

    void setNextSymbol(std::unique_ptr<Symbole> &&sym) {
        if (nextSymbol) {
            symbolStack.push_back(std::move(nextSymbol));
        }


        nextSymbol = std::move(sym);
    }

    void accept() {
        auto&& exprSym = popSymbol();
        finalExpr = std::unique_ptr<Expr>(static_cast<Expr*>(exprSym.release()));
    }

    std::unique_ptr<Expr> &result() { return finalExpr; }

  private:
    Lexer *lex;
    std::vector<State *> stack;
    std::vector<std::unique_ptr<Symbole>> symbolStack;
    std::unique_ptr<Symbole> nextSymbol;
    std::unique_ptr<Expr> finalExpr;
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
