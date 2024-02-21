#include "parser/Parser.h"
#include "lexer/symbole.h"
#include <iostream>
#include <memory>

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

static Rule2 R2;
static Rule3 R3;
static Rule4 R4;
static Rule5 R5;

Parser::Parser(Lexer *lexer) : lex(lexer) { execute(); }

template <typename... Ts> struct overload : Ts... {
    using Ts::operator()...;
};

template <typename... Ts> overload(Ts...) -> overload<Ts...>;

void Parser::execute() {
    bool finished = false;

    stack.push_back(&S0);

    std::unique_ptr<Symbole> nextNonTerm;
    std::unique_ptr<Symbole> savedTerm;
    std::unique_ptr<Symbole> current;

    while (!finished) {
        if (nextNonTerm) {
            // Si un non terminal a été émis, on l'utilise
            current = std::move(nextNonTerm);
            nextNonTerm = nullptr;
        } else if (savedTerm) {
            current = std::move(savedTerm);
            savedTerm = nullptr;
            // On avait sauvé un terminal pour émettre un non terminal
        } else {
            // Sinon on consulte le lexer et on avance
            current = std::unique_ptr<Symbole>(lexer().Consulter());
            lexer().Avancer();
        }

        // On regarde la transition
        TransitionResult result = stack.back()->onSymbol(*current);

        std::visit(overload{
                       [&](Shift &shift) {
                           // La transition est un shift -> on push le symbol lu
                           // et le prochain état
                           symbolStack.push_back(std::move(current));
                           stack.push_back(shift.nextState);
                       },
                       [&](Reduce &reduce) {
                           // La transition est un reduce -> on émmet un nouveau
                           // symbole non terminal en appliquant la règle
                           nextNonTerm = reduce.rule->reduce(*this);
                           savedTerm = std::move(current);
                       },
                       [&](Accept &accept) {
                           // On a reconnu l'expression, on termine notre boucle
                           finished = true;
                           auto &&exprSym = popSymbol();
                           finalExpr = std::unique_ptr<Expr>(
                               static_cast<Expr *>(exprSym.release()));
                       },
                   },
                   result);
    }
}

// Avec un peu de refactoring, j'avoue qu'on peut remplacer ces State par un grand tableau
// puisque qu'ils retournent tous des constants.
// Mais bon, je suis gentiment les consignes ;)

TransitionResult State0::onVal() { return Shift(&S3); }

TransitionResult State0::onOpenPar() { return Shift(&S2); }

TransitionResult State0::onExpr() { return Shift(&S1); }

TransitionResult State1::onAdd() { return Shift(&S4); }

TransitionResult State1::onMul() { return Shift(&S5); }

TransitionResult State1::onEOF() { return Accept(); }

TransitionResult State2::onVal() { return Shift(&S3); }

TransitionResult State2::onOpenPar() { return Shift(&S2); }

TransitionResult State2::onExpr() { return Shift(&S6); }

TransitionResult State3::onAdd() { return Reduce(&R5); }

TransitionResult State3::onMul() { return Reduce(&R5); }

TransitionResult State3::onClosePar() { return Reduce(&R5); }

TransitionResult State3::onEOF() { return Reduce(&R5); }

TransitionResult State4::onVal() { return Shift(&S3); }

TransitionResult State4::onOpenPar() { return Shift(&S2); }

TransitionResult State4::onExpr() { return Shift(&S7); }

TransitionResult State5::onVal() { return Shift(&S3); }

TransitionResult State5::onOpenPar() { return Shift(&S2); }

TransitionResult State5::onExpr() { return Shift(&S8); }

TransitionResult State6::onAdd() { return Shift(&S4); }

TransitionResult State6::onMul() { return Shift(&S5); }

TransitionResult State6::onClosePar() { return Shift(&S9); }

TransitionResult State7::onAdd() { return Reduce(&R2); }

TransitionResult State7::onMul() { return Shift(&S5); }

TransitionResult State7::onEOF() { return Reduce(&R2); }

TransitionResult State7::onClosePar() { return Reduce(&R2); }

TransitionResult State8::onAdd() { return Reduce(&R3); }

TransitionResult State8::onMul() { return Reduce(&R3); }

TransitionResult State8::onEOF() { return Reduce(&R3); }

TransitionResult State8::onClosePar() { return Reduce(&R3); }

TransitionResult State9::onAdd() { return Reduce(&R4); }

TransitionResult State9::onMul() { return Reduce(&R4); }

TransitionResult State9::onEOF() { return Reduce(&R4); }

TransitionResult State9::onClosePar() { return Reduce(&R4); }
