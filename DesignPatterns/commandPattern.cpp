//COMMAND DESIGN PATTERN
// It’s about encapsulating a request as an object, which allows you to parameterize 
// objects with operations, delay execution, and queue requests. 
// The idea is that commands (actions you want to perform) are wrapped as objects,


// The pattern is named the Command pattern because it revolves around the concept of commanding an action.
//  Instead of executing a method directly, you create a command object that represents the action.


// Advantages of the Command Design Pattern 🚀
// • No Modification of Existing Code:

// We don’t need to modify the RemoteControl class every time we add a new feature. We simply create new command classes. 🛠️

// ‍

// • Separation of Concerns:

// The logic for each command is encapsulated in its own class, making the code cleaner and easier to maintain. 🧹

// ‍

// • Flexibility:

// The RemoteControl doesn’t need to know the specifics of what the commands do. It just invokes them. This makes it easy to add new commands or remove old ones without impacting the system. 🔄



#include<iostream>
#include<vector>
using namespace std;


class Command{  
    public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Light{

    public:
    Light(){
         
    };
  
    void turnOn(){
        cout<<"Light is ON"<<endl;
    } 
    void turnOff(){
         cout<<"Light is OFF"<<endl;
    }
    
};


class Fan{

    public:
    Fan(){
         
    };
  
    void turnOn(){
        cout<<"Fan is ON"<<endl;
    } 
    void turnOff(){
         cout<<"Fan is OFF"<<endl;
    }
    
};

class LightCommand : public Command{
    private:
    Light * l;
     
    public:
    LightCommand(Light* l){
     this->l=l;
    }
    
    void execute() override{
         l->turnOn();
    }
    void undo() override{
        l->turnOff();
    }
};

class FanCommand : public Command{
    private:
    Fan * f;
     
    public:
    FanCommand(Fan* f){
        this->f=f;
    }
    
    void execute() override{
         f->turnOn();
    }
    void undo() override{
        f->turnOff();
    }
};

class RemoteController{

    private:
    vector<Command*>devices;

    public:
    
    void addDevice(Command* c){
     devices.push_back(c);
    }

    void turnOn(int deviceId){
        devices[deviceId]->execute();
    }

    void turnOff(int deviceId){
        devices[deviceId]->undo();
    }
};

int main(){
    
   Command* lightCommand=new LightCommand(new Light());
   Command* fanCommand=new FanCommand(new Fan()); 
   RemoteController* remote=new RemoteController();
   
   remote->addDevice(lightCommand);
   remote->addDevice(fanCommand);


   remote->turnOn(0);
   remote->turnOff(0);

   remote->turnOn(1);
   remote->turnOff(1);

    return 0;
}
