// CHAIN OF RESPONSIBILITY PATTERN

// a request is passed along a chain of handlers until one of them takes care of it.

// Advantages of the Chain of Responsibility Pattern

// 1. Decoupling of Request and Handler:
// The client doesn’t need to know which handler will process the request.
// 2. Flexibility:
// You can add or remove handlers at runtime without affecting the client.
// 3. Open/Closed Principle:
// You can add new handlers without modifying existing code.


// Real-Life Magic with Chain of Responsibility 🌍✨
// You might wonder, “Where else can I use this pattern?” Here are some everyday scenarios:

// • Technical Support:

// A customer’s issue is escalated from Level 1 support to higher levels until someone can resolve it. 📞🔧
// • Logging Systems:

// Log messages pass through various loggers based on severity (INFO, DEBUG, ERROR). 📝📊

// • GUI Event Handling:

// User events travel through a chain of UI components until one handles the event. 🖥️🎨

// • Authentication:
// A request is passed through several filters to validate credentials and permissions. 🔐🛡

#include<iostream>
using namespace std;

class MoneyHandler {

    protected:
    MoneyHandler* nextHandler;

    public:
    MoneyHandler(){
        this->nextHandler=nullptr;
    }

    void setNextHandler(MoneyHandler* nextHandler){
        this->nextHandler=nextHandler;
    }

    virtual void dispense(int amount) = 0;
};

class ThousandHandler : public MoneyHandler{
    
    private:
    int numNotes;

    public:
    ThousandHandler(int numNotes){
        this->numNotes=numNotes;
    }

    void dispense(int amount) override{
         int reqNotes=amount/1000;

        if(reqNotes>numNotes){
            reqNotes=numNotes;
            numNotes=0;
        }
        else{
            numNotes-=reqNotes;
        }
        
        if(reqNotes>0){
            cout << "Dispensing " << reqNotes << " x ₹1000 notes.\n";
        }
        
        int remAmount=amount-(1000*reqNotes);
        if(remAmount>0){
            if(nextHandler!=nullptr){
                nextHandler->dispense(remAmount);
            }
            else{
                cout << "Remaining amount of " << remAmount << " cannot be fulfilled (Insufficinet fund in ATM)"<<endl;
            }
        }
    }

};

class FiveHundredHandler : public MoneyHandler{
    
    private:
    int numNotes;

    public:
    FiveHundredHandler(int numNotes){
        this->numNotes=numNotes;
    }

    void dispense(int amount) override{
         int reqNotes=amount/500;

        if(reqNotes>numNotes){
            reqNotes=numNotes;
            numNotes=0;
        }
        else{
            numNotes-=reqNotes;
        }
        
        if(reqNotes>0){
            cout << "Dispensing " << reqNotes << " x ₹500 notes.\n";
        }
        
        int remAmount=amount-(500*reqNotes);
        if(remAmount>0){
            if(nextHandler!=nullptr){
                nextHandler->dispense(remAmount);
            }
            else{
                cout << "Remaining amount of " << remAmount << " cannot be fulfilled (Insufficinet fund in ATM)"<<endl;
            }
        }
    }

};


class HundredHandler : public MoneyHandler{
    
    private:
    int numNotes;

    public:
    HundredHandler(int numNotes){
        this->numNotes=numNotes;
    }

    void dispense(int amount) override{
         int reqNotes=amount/100;

        if(reqNotes>numNotes){
            reqNotes=numNotes;
            numNotes=0;
        }
        else{
            numNotes-=reqNotes;
        }
        
        if(reqNotes>0){
            cout << "Dispensing " << reqNotes << " x ₹100 notes.\n";
        }
        
        int remAmount=amount-(100*reqNotes);
        if(remAmount>0){
            if(nextHandler!=nullptr){
                nextHandler->dispense(remAmount);
            }
            else{
                cout << "Remaining amount of " << remAmount << " cannot be fulfilled (Insufficinet fund in ATM)"<<endl;
            }
        }
    }

};


int main(){


   MoneyHandler* thousandHandler=new ThousandHandler(4);
   MoneyHandler* fiveHundredHandler=new FiveHundredHandler(5);
   MoneyHandler* hundredHandler=new HundredHandler(2);
 
   thousandHandler->setNextHandler(fiveHundredHandler);
   fiveHundredHandler->setNextHandler(hundredHandler);

   thousandHandler->dispense(5000);
 
    return 0;
}