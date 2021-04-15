#include "commoninterface.h"
using namespace std;

CommonInterface::CommonInterface():person(nullptr){}

CommonInterface::~CommonInterface()
{
    if(person)
        delete person;
}

//Passenger: 89959280771
//Driver   : 89192484803


bool CommonInterface::start()
{
//    waitENTER();
    return Hello() &&
           Login() &&
           Menu();
}

bool CommonInterface::Hello()
{
    static const vector<string> Roles = {PersonType(0),PersonType(1),"exit"};
    string input;
    while(true){
        clear();
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
    string input;
    while(true){
        clear();
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

bool CommonInterface::Menu()
{
    assert(person != nullptr);
    if(type == PersonType(0))
        return PassMenu();
    if(type == PersonType(1))
        return DrivMenu();
    return false;
}

bool CommonInterface::PassMenu()
{
    static const vector<string> Actions = {"See_history","Change_payment_method","Add_pinned_address","Make_order","exit"};//...
    string input;
    while(true){
        clear();
        print("You are successfully logged in as:");
        print(person->getFullInfo());
        print("Select the option: "+getListOptions(Actions));
        getInput(input);
        int num = calculateInput(input,Actions);
        if(num ==-1) continue; // try Again
        if(num == (Actions.size()-1)) return false;
        switch(num){
            case 0: See_History();break;
            case 1: ChangePay();break;
            case 2: AddPinAddr();break;
            case 3: MakeOrder();break;
        }
    }
}

void CommonInterface::See_History()
{
//    print(person->getName() + " order history:");
    person->printOrderHistory();
    waitENTER();
}

void CommonInterface::ChangePay()
{
    static const vector<string> Type = {PayType(0),PayType(1),"back"};
    string input;
    while(true){
        Passenger* pass = static_cast<Passenger*>(person);
        clear();
        print("You pay method is: "+static_cast<string>(pass->getPayMethod()));
        print("Select the new type: "+getListOptions(Type));
        getInput(input);
        int num = calculateInput(input,Type);
        if(num ==-1) continue; // try Again
        if(num == 2) return;
        pass->setPayMethod(PayType(num));
        return;
    }
}

void CommonInterface::AddPinAddr()
{
    string input;
    print("Enter address to pin or go \"(-)back\"");
    cout<<'>';cin.get();
    getline(cin,input);
    if(input == "back" or input == "" or input == "-")return;
    Address address = input;
    print("If you want you may write the name of the address");
    cout<<'>';
    getline(cin,input);
    if (input.size()>0)
        address.setName(input);
    static_cast<Passenger*>(person)->addPinAddress(address);
    // TODO: save new address to the excel
}

void CommonInterface::MakeOrder()
{

}


bool CommonInterface::DrivMenu()
{

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
