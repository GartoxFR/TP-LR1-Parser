#pragma once

#include <cstdint>
#include <memory>
#include <ostream>

class Expr {
  public:
    virtual std::ostream &print(std::ostream &o) = 0;
    virtual uint32_t eval() = 0;
};

class Val : public Expr {
    public:
      explicit Val(uint32_t value) : value(value) {}

      std::ostream &print(std::ostream &o) override;
      uint32_t eval() override;
    private:
        uint32_t value;
};

class Add : public Expr {
    public:
      Add(std::unique_ptr<Expr> &&leftExpr, std::unique_ptr<Expr> &&rightExpr)
          : leftExpr(std::move(leftExpr)), rightExpr(std::move(rightExpr)) {}

      std::ostream &print(std::ostream &o) override;
      uint32_t eval() override;
    private:
      std::unique_ptr<Expr> leftExpr;
      std::unique_ptr<Expr> rightExpr;
};

class Mul : public Expr {
    public:
      Mul(std::unique_ptr<Expr> &&leftExpr, std::unique_ptr<Expr> &&rightExpr)
          : leftExpr(std::move(leftExpr)), rightExpr(std::move(rightExpr)) {}

      std::ostream &print(std::ostream &o) override;
      uint32_t eval() override;

    private:
      std::unique_ptr<Expr> leftExpr;
      std::unique_ptr<Expr> rightExpr;
};
