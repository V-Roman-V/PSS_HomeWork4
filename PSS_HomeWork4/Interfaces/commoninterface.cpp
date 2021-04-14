#include "commoninterface.h"
using namespace std;

CommonInterface::CommonInterface():person(nullptr){}

//Passen: 89532136828
//Driver: 89192484803


bool CommonInterface::start()
{
    return Hello() &&
           Login() &&
           PrintInfo();
}

bool CommonInterface::Hello()
{
    while(true){
        static const vector<string> Roles = {PersonType(0),PersonType(1),"exit"};

        clear();
        string input;

        print("Welcome to our WEndex.Taxi app");
        print("Who you are? "+getListOptions(Roles));
        getInput(input);
        int num = calculateInput(input,Roles);
        if(num==-1) continue; // try Again
        if(num== 2) return false;
        type = PersonType(num);
        return true;
    }
}

bool CommonInterface::Login()
{
    while(true){
        clear();
        string input;

        print("Hello "+static_cast<string>(type)+", to log in please enter your phone number or \"-\" to exit}");
        getInput(input);
        if(input == "-" or input == "exit")return false;
        if(!isNumber(input)) continue; // try Again
        if(type == PersonType(0)){
            int num = findPassenger(input);
            if(num==-1) continue; // try Again
            person = new Passenger(getPassenger(num));
            return true;
        }
        if(type == PersonType(1)){
            int num = findDriver(input);
            if(num==-1) continue; // try Again
            person = new Driver(getDriver(num));
            return true;
        }
        assert(!"Incorrect person type");
    }
}

bool CommonInterface::PrintInfo()
{
    assert(person != nullptr);
    clear();
    print("You are successfully logged in as:");
    print(person->getFullInfo());
    return true;
}


//------------------------------------------------------------------------------------------------------
void CommonInterface::waitENTER() {
    print("return back. Press ENTER");
    cin.get();
    string s;
    getline(cin,s);
}

template<class T>
string CommonInterface::getListOptions(const vector<T>& list)
{
    string out ="{";
    for(unsigned int i=0;i<list.size();i++)
        out += "(" + ( (static_cast<string>(list[i])=="exit")?"-":to_string(i)) + ")" + static_cast<string>(list[i]) + ((i+1==list.size())?"}":"; ");
    return out;
}

template<class T>
int CommonInterface::calculateInput(const string& input, const vector<T>& list)
{
    unsigned int i=0;
    if((isNumber(input))){
        i = stoi(input);
        if( i >= list.size()) return -1;
        return i;
    }
    for(const auto& str: list){
        if(input == "-" && static_cast<string>(str) == "exit") return i;
        if(input == static_cast<string>(str)) return i;
        i++;
    }
    return -1;
}
