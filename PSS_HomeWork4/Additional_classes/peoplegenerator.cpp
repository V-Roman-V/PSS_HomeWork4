#include "peoplegenerator.h"

PeopleGenerator::Initializer PeopleGenerator::init;
unsigned int PeopleGenerator::count = std::rand();

std::vector<PeopleGenerator::data> PeopleGenerator::names =
    {{"James", "Powers", Gender(2)},      {"Leroy", "Clark", Gender(2)},      {"Robert", "Shaw", Gender(2)},      {"Harry", "Marshall", Gender(2)},     {"David", "Bradley", Gender(2)},
    {"Valerie", "Matthews", Gender(1)}, {"Rebecca", "Rogers", Gender(1)}, {"Steven", "McDonald", Gender(2)},  {"Bobbie", "Thompson", Gender(2)},    {"Steven", "Becker", Gender(2)},
    {"Alice", "Wright", Gender(1)},     {"Marie", "Gardner", Gender(1)},  {"Robert", "Morrison", Gender(2)},  {"William", "Griffin", Gender(2)},    {"Martin", "Spencer", Gender(2)},
    {"Michelle", "Lewis", Gender(2)},     {"Kyle", "Phillips", Gender(2)},    {"Rick", "Martin", Gender(2)},      {"Joshua", "Ward", Gender(1)},      {"Thomas", "Peters", Gender(2)},
    {"Dorothy", "Martin", Gender(1)},   {"Sandra", "Jackson", Gender(1)}, {"Elsie", "Martin", Gender(1)},   {"Mark", "Walker", Gender(2)},        {"Christina", "Phelps", Gender(1)},
    {"Nathan", "Matthews", Gender(2)},    {"Mary", "Simon", Gender(1)},     {"Roger", "Gomez", Gender(2)},      {"Sean", "Scott", Gender(1)},       {"Fred", "Carpenter", Gender(2)},
    {"Ellen", "Williams", Gender(2)},     {"Joseph", "Anderson", Gender(2)},  {"Ernest", "Parsons", Gender(2)},   {"Nancy", "Craig", Gender(1)},      {"Maxine", "Harris", Gender(1)},
    {"Kim", "Hicks", Gender(2)},          {"Jason", "Hall", Gender(2)},       {"Jeffrey", "Harper", Gender(2)},   {"Deborah", "Campbell", Gender(1)}, {"Barbara", "Campbell", Gender(1)},
    {"Julie", "Ellis", Gender(1)},      {"Bonnie", "Campbell", Gender(2)},  {"Barbara", "Potter", Gender(1)}, {"Lori", "Doyle", Gender(1)},       {"Lillian", "Cobb", Gender(1)},
    {"Jim", "Curry", Gender(2)},          {"Hector", "Wright", Gender(2)},    {"Anthony", "Keller", Gender(2)},   {"Harry", "Carson", Gender(2)},       {"Ron", "Carter", Gender(2)}};

int PeopleGenerator::getDigit(int i)
{
    if(i>9)i=9;
    int digits=1+std::rand()%9;
    while(--i)
        digits = digits*10 + std::rand()%10;
    return digits;
}

People PeopleGenerator::getRandomPeople()
{
    count = (count+1)%names.size();

    unsigned short d = std::rand()%28 + 1;
    unsigned short m = std::rand()%12 + 1;
    unsigned short y = std::rand()%29 + 1975; // 1975 - 2003

    int s = getDigit(4); // 1000 - 9999
    int n = getDigit(6); // 100000 - 999999

    std::string phone = "89" + std::to_string(getDigit(9));
    return People(names[count].name,
                  names[count].surname,
                  names[count].gender,
                  Date(d,m,y),
                  Passport(s,n),
                  phone);
}



