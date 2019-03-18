#ifndef BALANCE_H_
#define BALANCE_H_

class Balance {
    public:
    std::string cents;
    Balance(): cents("0") {}
    Balance(std::string c) : cents(c) {}

    void set_cents(std::string c) {cents = c;}
    std::string get_cents(){return cents;}
};
#endif

