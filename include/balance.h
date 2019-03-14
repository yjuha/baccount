#ifndef BALANCE_H_
#define BALANCE_H_

struct Balance {

    std::string euros;
    std::string cents;
    Balance(): euros("0"), cents("0") {}
    Balance(std::string e, std::string c) : euros(e), cents(c) {}

    void set_euros(std::string e) {euros = e;}
    void set_cents(std::string c) {cents = c;}
};
#endif

