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

Parser::Parser(Lexer *lexer) : lex(lexer) {
    shiftTerm(&S0);
}

void Parser::transition() {

    switch (*nextSymbol) {
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
        case EXPR:
            stack.back()->onExpr(*this);
            break;
        case FIN:
            stack.back()->onEOF(*this);
            break;
    }
}

void Parser::shiftTerm(State* nextState) {
    stack.push_back(nextState);

    lexer().Avancer();

    Symbole *sym = lexer().Consulter();
    setNextSymbol(std::unique_ptr<Symbole>(sym));
    transition();
}

void Parser::shiftNonTerm(State* nextState) {
    stack.push_back(nextState);
    Symbole *sym = lexer().Consulter();
    setNextSymbol(std::unique_ptr<Symbole>(sym));
    transition();
}

void Parser::reduce(size_t stateCount, std::unique_ptr<Symbole> &&symbol) {
    stack.resize(stack.size() - stateCount);

    // On oublie le symbole sur la tête de lecture, on le relira plus tard avec le lexer
    // On sait que c'est forcément un symbol terminal car il n'y a jamais de reduce sur un non terminal

    (void) nextSymbol.release();
    nextSymbol = nullptr;

    setNextSymbol(std::move(symbol));
    transition();
}

void State0::onVal(Parser &parser){
    parser.shiftTerm(&S3);
}

void State0::onOpenPar(Parser &parser){
    parser.shiftTerm(&S2);
}

void State0::onExpr(Parser &parser){
    parser.shiftNonTerm(&S1);
}

void State1::onAdd(Parser &parser){
    parser.shiftTerm(&S4);
}

void State1::onMul(Parser &parser){
    parser.shiftTerm(&S5);
}

void State1::onEOF(Parser &parser){
    parser.accept();
}

void State2::onVal(Parser &parser){
    parser.shiftTerm(&S3);
}

void State2::onOpenPar(Parser &parser){
    parser.shiftTerm(&S2);
}

void State2::onExpr(Parser &parser){
    parser.shiftNonTerm(&S6);
}

void State3::onAdd(Parser &parser){
    auto&& valSymbol = parser.popSymbol();

    int32_t value = static_cast<Entier*>(valSymbol.get())->value();
    parser.reduce(1, std::make_unique<Val>(value));
}

void State3::onMul(Parser &parser){
    auto&& valSymbol = parser.popSymbol();

    int32_t value = static_cast<Entier*>(valSymbol.get())->value();
    parser.reduce(1, std::make_unique<Val>(value));
}

void State3::onClosePar(Parser &parser){
    auto&& valSymbol = parser.popSymbol();

    int32_t value = static_cast<Entier*>(valSymbol.get())->value();
    parser.reduce(1, std::make_unique<Val>(value));
}

void State3::onEOF(Parser &parser){
    auto&& valSymbol = parser.popSymbol();

    int32_t value = static_cast<Entier*>(valSymbol.get())->value();
    parser.reduce(1, std::make_unique<Val>(value));
}

void State4::onVal(Parser &parser){
    parser.shiftTerm(&S3);
}

void State4::onOpenPar(Parser &parser){
    parser.shiftTerm(&S2);
}

void State4::onExpr(Parser &parser){
    parser.shiftNonTerm(&S7);
}

void State5::onVal(Parser &parser) {
    parser.shiftTerm(&S3);
}
void State5::onOpenPar(Parser &parser) {
    parser.shiftTerm(&S2);
}
void State5::onExpr(Parser &parser) {
    parser.shiftNonTerm(&S8);
}

void State6::onAdd(Parser &parser) {
    parser.shiftTerm(&S4);
}

void State6::onMul(Parser &parser) {
    parser.shiftTerm(&S5);
}

void State6::onClosePar(Parser &parser) {
    parser.shiftTerm(&S9);
}

void State7::onAdd(Parser &parser) {
    auto&& rightSym = parser.popSymbol();
    parser.popSymbol();
    auto&& leftSym = parser.popSymbol();

    auto rightExpr = std::unique_ptr<Expr>(static_cast<Expr*>(rightSym.release()));
    auto leftExpr = std::unique_ptr<Expr>(static_cast<Expr*>(leftSym.release()));

    parser.reduce(3, std::make_unique<Add>(std::move(leftExpr), std::move(rightExpr)));
}

void State7::onMul(Parser &parser) {
    parser.shiftTerm(&S5);
}

void State7::onEOF(Parser &parser) {
    auto&& rightSym = parser.popSymbol();
    parser.popSymbol();
    auto&& leftSym = parser.popSymbol();

    auto rightExpr = std::unique_ptr<Expr>(static_cast<Expr*>(rightSym.release()));
    auto leftExpr = std::unique_ptr<Expr>(static_cast<Expr*>(leftSym.release()));

    parser.reduce(3, std::make_unique<Add>(std::move(leftExpr), std::move(rightExpr)));
}

void State7::onClosePar(Parser &parser) {
    auto&& rightSym = parser.popSymbol();
    parser.popSymbol();
    auto&& leftSym = parser.popSymbol();

    auto rightExpr = std::unique_ptr<Expr>(static_cast<Expr*>(rightSym.release()));
    auto leftExpr = std::unique_ptr<Expr>(static_cast<Expr*>(leftSym.release()));

    parser.reduce(3, std::make_unique<Add>(std::move(leftExpr), std::move(rightExpr)));
}

void State8::onAdd(Parser &parser) {
    auto&& rightSym = parser.popSymbol();
    parser.popSymbol();
    auto&& leftSym = parser.popSymbol();

    auto rightExpr = std::unique_ptr<Expr>(static_cast<Expr*>(rightSym.release()));
    auto leftExpr = std::unique_ptr<Expr>(static_cast<Expr*>(leftSym.release()));

    parser.reduce(3, std::make_unique<Mul>(std::move(leftExpr), std::move(rightExpr)));
}

void State8::onMul(Parser &parser) {
    auto&& rightSym = parser.popSymbol();
    parser.popSymbol();
    auto&& leftSym = parser.popSymbol();

    auto rightExpr = std::unique_ptr<Expr>(static_cast<Expr*>(rightSym.release()));
    auto leftExpr = std::unique_ptr<Expr>(static_cast<Expr*>(leftSym.release()));

    parser.reduce(3, std::make_unique<Mul>(std::move(leftExpr), std::move(rightExpr)));
}

void State8::onEOF(Parser &parser) {
    auto&& rightSym = parser.popSymbol();
    parser.popSymbol();
    auto&& leftSym = parser.popSymbol();

    auto rightExpr = std::unique_ptr<Expr>(static_cast<Expr*>(rightSym.release()));
    auto leftExpr = std::unique_ptr<Expr>(static_cast<Expr*>(leftSym.release()));

    parser.reduce(3, std::make_unique<Mul>(std::move(leftExpr), std::move(rightExpr)));
}

void State8::onClosePar(Parser &parser) {
    auto&& rightSym = parser.popSymbol();
    parser.popSymbol();
    auto&& leftSym = parser.popSymbol();

    auto rightExpr = std::unique_ptr<Expr>(static_cast<Expr*>(rightSym.release()));
    auto leftExpr = std::unique_ptr<Expr>(static_cast<Expr*>(leftSym.release()));

    parser.reduce(3, std::make_unique<Mul>(std::move(leftExpr), std::move(rightExpr)));
}

void State9::onAdd(Parser &parser) {
    parser.popSymbol();
    auto&& exprSym = parser.popSymbol();
    parser.popSymbol();

    auto expr = std::unique_ptr<Expr>(static_cast<Expr*>(exprSym.release()));
    parser.reduce(3, std::move(expr));
}

void State9::onMul(Parser &parser) {
    parser.popSymbol();
    auto&& exprSym = parser.popSymbol();
    parser.popSymbol();

    auto expr = std::unique_ptr<Expr>(static_cast<Expr*>(exprSym.release()));
    parser.reduce(3, std::move(expr));
}

void State9::onEOF(Parser &parser) {
    parser.popSymbol();
    auto&& exprSym = parser.popSymbol();
    parser.popSymbol();

    auto expr = std::unique_ptr<Expr>(static_cast<Expr*>(exprSym.release()));
    parser.reduce(3, std::move(expr));
}

void State9::onClosePar(Parser &parser) {
    parser.popSymbol();
    auto&& exprSym = parser.popSymbol();
    parser.popSymbol();

    auto expr = std::unique_ptr<Expr>(static_cast<Expr*>(exprSym.release()));
    parser.reduce(3, std::move(expr));
}

