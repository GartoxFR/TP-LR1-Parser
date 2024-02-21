#pragma once

#include <memory>
#include "lexer/symbole.h"

class Parser;

class Rule {
  public:
    virtual std::unique_ptr<Symbole> reduce(Parser &parser) const = 0;
};

class Rule2 : public Rule {
    public:
        std::unique_ptr<Symbole> reduce(Parser &parser) const override;
};

class Rule3 : public Rule {
    public:
        std::unique_ptr<Symbole> reduce(Parser &parser) const override;
};

class Rule4 : public Rule {
    public:
        std::unique_ptr<Symbole> reduce(Parser &parser) const override;
};

class Rule5 : public Rule {
    public:
        std::unique_ptr<Symbole> reduce(Parser &parser) const override;
};
