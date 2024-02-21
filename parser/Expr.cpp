#include "parser/Expr.h"

std::ostream &Val::print(std::ostream &o){
    o << this->value;
    return o;
}

uint32_t Val::eval(){
    return this->value;
}

std::ostream &Add::print(std::ostream &o){
    o << "(";
    this->leftExpr->print(o);
    o << " + ";
    this->rightExpr->print(o);
    o << ")";
    return o;
}
      
uint32_t Add::eval(){
    return (this->leftExpr->eval()+this->rightExpr->eval());
}

std::ostream &Mul::print(std::ostream &o) {
    o << "(";
    this->leftExpr->print(o);
    o << " * ", this->rightExpr->print(o);
    this->rightExpr->print(o);
    o << ")";
    return o;
}

uint32_t Mul::eval() {
    return this->leftExpr->eval() * this->rightExpr->eval();
} 
