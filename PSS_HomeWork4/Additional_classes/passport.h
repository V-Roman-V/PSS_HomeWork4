#ifndef PASSPORT_H
#define PASSPORT_H

#include <ostream>

class Passport
{
public:
    Passport(unsigned int _series = 0, unsigned int _number = 0);
    void setPassport(unsigned int _series, unsigned int _number);

    friend std::ostream& operator<<(std::ostream& os, const Passport& p);

    unsigned int getNumber() const;
    unsigned int getSeries() const;

    bool isCorrect()const;
private:
    unsigned int number;
    unsigned int series;
};

#endif // PASSPORT_H
