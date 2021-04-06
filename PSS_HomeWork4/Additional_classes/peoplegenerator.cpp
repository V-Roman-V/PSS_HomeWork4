#include "peoplegenerator.h"

PeopleGenerator::Initializer PeopleGenerator::init;
unsigned int PeopleGenerator::count = std::rand();

std::vector<PeopleGenerator::data> PeopleGenerator::names =
    {{"James", "Powers", People::Gender::male},      {"Leroy", "Clark", People::Gender::male},      {"Robert", "Shaw", People::Gender::male},      {"Harry", "Marshall", People::Gender::male},     {"David", "Bradley", People::Gender::male},
    {"Valerie", "Matthews", People::Gender::female}, {"Rebecca", "Rogers", People::Gender::female}, {"Steven", "McDonald", People::Gender::male},  {"Bobbie", "Thompson", People::Gender::male},    {"Steven", "Becker", People::Gender::male},
    {"Alice", "Wright", People::Gender::female},     {"Marie", "Gardner", People::Gender::female},  {"Robert", "Morrison", People::Gender::male},  {"William", "Griffin", People::Gender::male},    {"Martin", "Spencer", People::Gender::male},
    {"Michelle", "Lewis", People::Gender::male},     {"Kyle", "Phillips", People::Gender::male},    {"Rick", "Martin", People::Gender::male},      {"Joshua", "Ward", People::Gender::female},      {"Thomas", "Peters", People::Gender::male},
    {"Dorothy", "Martin", People::Gender::female},   {"Sandra", "Jackson", People::Gender::female}, {"Elsie", "Martin", People::Gender::female},   {"Mark", "Walker", People::Gender::male},        {"Christina", "Phelps", People::Gender::female},
    {"Nathan", "Matthews", People::Gender::male},    {"Mary", "Simon", People::Gender::female},     {"Roger", "Gomez", People::Gender::male},      {"Sean", "Scott", People::Gender::female},       {"Fred", "Carpenter", People::Gender::male},
    {"Ellen", "Williams", People::Gender::male},     {"Joseph", "Anderson", People::Gender::male},  {"Ernest", "Parsons", People::Gender::male},   {"Nancy", "Craig", People::Gender::female},      {"Maxine", "Harris", People::Gender::female},
    {"Kim", "Hicks", People::Gender::male},          {"Jason", "Hall", People::Gender::male},       {"Jeffrey", "Harper", People::Gender::male},   {"Deborah", "Campbell", People::Gender::female}, {"Barbara", "Campbell", People::Gender::female},
    {"Julie", "Ellis", People::Gender::female},      {"Bonnie", "Campbell", People::Gender::male},  {"Barbara", "Potter", People::Gender::female}, {"Lori", "Doyle", People::Gender::female},       {"Lillian", "Cobb", People::Gender::female},
    {"Jim", "Curry", People::Gender::male},          {"Hector", "Wright", People::Gender::male},    {"Anthony", "Keller", People::Gender::male},   {"Harry", "Carson", People::Gender::male},       {"Ron", "Carter", People::Gender::male}};

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



