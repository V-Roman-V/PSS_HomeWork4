#include "commoninterface.h"
#include <ctime>

using namespace std;

CommonInterface::CommonInterface():person(nullptr){srand(time(0));}

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
    static const vector<string> Actions_order = {"See_history","Change_payment_method","Add_pinned_address","See_current_order","exit"};//...

    string input;
    while(true){
        clear();
        print("You are successfully logged in as:");
        print(person->getFullInfo());
        const auto& Act = person->hasActiveOrder()?Actions_order:Actions;
        print("Select the option: "+getListOptions(Act));
        getInput(input);
        int num = calculateInput(input,Act);
        if(num ==-1) continue; // try Again
        if(num == (Act.size()-1)) return false;
        switch(num){
            case 0: See_History();break;
            case 1: ChangePay();break;
            case 2: AddPinAddr();break;
            case 3: person->hasActiveOrder()?SeeOrder():MakeOrder();break;
        }
    }
}

void CommonInterface::See_History()
{
    person->printOrderHistory();
    waitENTER();
}

void CommonInterface::ChangePay()
{
    static const vector<string> Type = {PayType(0),PayType(1),"back"};
    string input;
    Passenger* pass = static_cast<Passenger*>(person);
    while(true){
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
    string input;
    Order order;
    try {
        order.from  = ChooseAddr(true);
        order.to    = ChooseAddr(false);
        order.car   = ChooseCar();
        order.time  = QTime(rand()%3,rand()%60);
        order.price = order.time.hour()*60 + order.time.minute() + order.car.number()*100; // time + car*100
        order.date  = Date::getNowDate();
        CreateOrder(order);
        order.number = getNextOrderNumber();
        person->setCurrentOrder(order);
        // TODO: save new address to the excel
    }  catch (int exit) {}
}

Address CommonInterface::ChooseAddr(bool from)
{
    string input;
    Passenger* pass = static_cast<Passenger*>(person);
    while(true){
        int num = pass->getPinnedAddresses().size();
        string choose_text = num==0?"No pinned addresses":num==1?"0":("0 - "+to_string(num-1));
        string address_text = from?"current":"target";
        print("Enter your " + address_text + " address or choose it ("+choose_text+") or \"(-)back\"");
        cout<<'>';if(from)cin.get();
        getline(cin,input);
        if(input == "back" or input == "-") throw -1;
        if(isNumber(input)){
            int addr = stoi(input);
            if (addr>num-1) continue;
            return pass->getPinnedAddresses().at(addr);
        }
        return input;
    }
    throw -1;
}

CarType CommonInterface::ChooseCar()
{
    string input;
    const vector<string> types = CarType::getList();
    while(true){
        print("Choose type of car " + getListOptions(types) + " or \"(-)back\"");
        getInput(input);
        int num = calculateInput(input,types);
        if(num == -1) continue;
        if(input == "back" or input == "-") throw -1;
        return CarType(num);
    }
    throw -1;
}

void CommonInterface::CreateOrder(const Order& order)
{
    static const vector<string> consent = {"confirm", "cancel"};
    string input;
    while(true){
        clear();
        print("Your order is: ");
        order.print();
        print("Create order?"+getListOptions(consent));
        getInput(input);
        int answer = calculateInput(input,consent);
        if(answer == -1)continue;
        if(answer == 1) throw -1;
        break;
    }
}

void CommonInterface::SeeOrder()
{
    string input;
    clear();
    print("Your current order is: ");
    person->getCurrentOrder().print();
    print("If you want cancel it, print \"yes\" or type ENTER to return");
    cout<<'>';cin.get();
    getline(cin,input);
    if(input == "yes")
            person->deleteCurrentOrder();
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
