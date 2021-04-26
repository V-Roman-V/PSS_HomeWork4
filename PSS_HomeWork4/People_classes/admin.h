#ifndef ADMIN_H
#define ADMIN_H

#include "people.h"

class Admin : public People
{
public:
    Admin(const People& p);
};

#endif // ADMIN_H
