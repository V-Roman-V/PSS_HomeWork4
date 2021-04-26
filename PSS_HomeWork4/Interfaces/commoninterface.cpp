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
//Driver   : 333221234


bool CommonInterface::start()
{
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
            case 0: SeeHistory();break;
            case 1: P_ChangePay();break;
            case 2: P_AddPinAddr();break;
            case 3: person->hasActiveOrder()?P_SeeOrder():P_MakeOrder();break;
        }
    }
}

void CommonInterface::SeeHistory()
{
    person->printOrderHistory();
    waitENTER();
}

void CommonInterface::P_ChangePay()
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

void CommonInterface::P_AddPinAddr()
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
    savePinAddress(person->getPhone(),address);
}

void CommonInterface::P_MakeOrder()
{
    string input;
    Order order;
    try {
        order.from  = P_ChooseAddr(true);
        order.to    = P_ChooseAddr(false);
        order.car   = P_ChooseCar();
        order.time  = QTime(rand()%3,rand()%60);
        order.price = order.time.hour()*60 + order.time.minute() + order.car.number()*100; // time + car*100
        order.date  = Date::getNowDate();
        order.number = -1;
        P_CreateOrder(order);
        order.number = getNextOrderNumber();
        person->setCurrentOrder(order);
        saveActiveOrder(order,person->getPhone());
    }  catch (int exit) {}
}

Address CommonInterface::P_ChooseAddr(bool from)
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

CarType CommonInterface::P_ChooseCar()
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

void CommonInterface::P_CreateOrder(const Order& order)
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

void CommonInterface::P_SeeOrder()
{
    string input;
    clear();
    print("Your current order is: ");
    person->getCurrentOrder().print();
    auto pair = getOrderStatus(person->getCurrentOrder().number);
    if(pair.first == false){ // add to history
        print("Your order has been successfully completed");
        person->deleteCurrentOrder();
        waitENTER();
        return;
    }
    Status status = pair.second;
    print("Status is:"+static_cast<std::string>(status));
    if(status.number() == Status(0).number()){
        print("If you want cancel it, print \"yes\" or type ENTER to return");
        cout<<'>';cin.get();
        getline(cin,input);
        if(input == "yes"){
            deleteActiveOrder(person->getCurrentOrder());
            person->deleteCurrentOrder();
        }
    } else
        waitENTER();
}


bool CommonInterface::DrivMenu()
{
    static const vector<string> Actions = {"See_history","Set_status","See_car","take_order","exit"};//...
    static const vector<string> Actions_order = {"See_history","Set_status","See_car","See_current_order","exit"};//...

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
            case 0: SeeHistory();break;
            case 1: D_setStatus();break;
            case 2: D_SeeCar();break;
            case 3: person->hasActiveOrder()?D_SeeOrder():D_TakeOrder();break;
        }
    }
}

void CommonInterface::D_SeeCar()
{
    Driver* driver = static_cast<Driver*>(person);
    driver->getCar().print();
    waitENTER();
}

void CommonInterface::D_TakeOrder()
{
    static const vector<string> consent = {"confirm", "cancel"};
    string input;
    Driver* driver = static_cast<Driver*>(person);
    auto orders = getActiveOrder(driver->getCar().type);
    if(orders.size() == 0){
        print("There is no orders for this car type");
        waitENTER();
        return;
    }
    clear();
    print("Order List:");
    int i=1;
    for(const auto& order:orders){
        cout<<i++<<")";order.print();
    }
    print("Enter order number or \"(-)back\"");
    getInput(input);
    if(input == "-" or input == "back")return;
    if(!isNumber(input)) return;
    int num = std::stoi(input) - 1;
    if( num >= orders.size()) return;
    while(true){
        print("Your order is: ");
        orders[num].print();
        print("Take order?"+getListOptions(consent));
        getInput(input);
        int answer = calculateInput(input,consent);
        if(answer == -1)continue;
        if(answer == 1) return;
        break;
    }
    takeActiveOrder(orders[num]);
    person->setCurrentOrder(orders[num]);
}

void CommonInterface::D_SeeOrder()
{
    string input;
    clear();
    print("Your current order is: ");
    person->getCurrentOrder().print();/*
    Status status = getOrderStatus(person->getCurrentOrder().number);
    print("Status is:"+static_cast<std::string>(status));*/
    print("Do you want to close the order, print \"yes\" or type ENTER to return");
    cout<<'>';cin.get();
    getline(cin,input);
    if(input == "yes"){ //close order
        closeActiveOrder(person->getCurrentOrder(),person->getPhone());
        person->deleteCurrentOrder();
    }
}

void CommonInterface::D_setStatus()
{
    static const vector<string> statuses = {Status(0),Status(1),"back"};
    string input;
    Driver* driv = static_cast<Driver*>(person);
    while(true){
        clear();
        print("You status is: "+static_cast<string>(driv->getStatus()));
        print("Select the new status: "+getListOptions(statuses));
        getInput(input);
        int num = calculateInput(input, statuses);
        if(num ==-1) continue; // try Again
        if(num == statuses.size()-1) return;
        driv->updateStatus(Status(num));
        return;
    }
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
