#include "parser/Parser.h"
#include "lexer/symbole.h"
#include <iostream>

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

void State0::onOpenPar(Parser &parser){
    parser.shift(&S2);
}

void State0::onExpr(Parser &parser){
    parser.shift(&S1);
}

void State1::onAdd(Parser &parser){
    parser.shift(&S4);
}

void State1::onMul(Parser &parser){
    parser.shift(&S5);
}

void State1::onEOF(Parser &parser){
    cout << "accepter";
}

void State2::onVal(Parser &parser){
    parser.shift(&S3);
}

void State2::onOpenPar(Parser &parser){
    parser.shift(&S2);
}

void State2::onExpr(Parser &parser){
    parser.shift(&S6);
}

void State3::onAdd(Parser &parser){
    parser.reduce(1);
}

void State3::onMul(Parser &parser){
    parser.reduce(1);
}

void State3::onClosePar(Parser &parser){
    parser.reduce(1);
}

void State3::onEOF(Parser &parser){
    parser.reduce(1);
}

void State4::onVal(Parser &parser){
    parser.shift(&S3);
}

void State4::onOpenPar(Parser &parser){
    parser.shift(&S2);
}

void State4::onExpr(Parser &parser){
    parser.shift(&S7);
}

void State5::onVal(Parser &parser) {
    parser.shift(&S3);
}
void State5::onOpenPar(Parser &parser) {
    parser.shift(&S2);
}
void State5::onExpr(Parser &parser) {
    parser.shift(&S7);
}

void State6::onAdd(Parser &parser) {
    parser.shift(&S4);
}

void State6::onMul(Parser &parser) {
    parser.shift(&S5);
}

void State6::onClosePar(Parser &parser) {
    parser.shift(&S9);
}

void State7::onAdd(Parser &parser) {
    parser.reduce(3);
}

void State7::onMul(Parser &parser) {
    parser.shift(&S5);
}

void State7::onEOF(Parser &parser) {
    parser.reduce(3);
}

void State7::onClosePar(Parser &parser) {
    parser.reduce(3);
}

void State8::onAdd(Parser &parser) {
    parser.reduce(3);
}

void State8::onMul(Parser &parser) {
    parser.reduce(3);
}

void State8::onEOF(Parser &parser) {
    parser.reduce(3);
}

void State8::onClosePar(Parser &parser) {
    parser.reduce(3);
}

void State9::onAdd(Parser &parser) {
    parser.reduce(3);
}

void State9::onMul(Parser &parser) {
    parser.reduce(3);
}

void State9::onEOF(Parser &parser) {
    parser.reduce(3);
}

void State9::onClosePar(Parser &parser) {
    parser.reduce(3);
}

