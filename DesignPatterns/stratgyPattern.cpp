#include<iostream>
using namespace std;

//In simple terms, the Strategy Pattern allows you to define a 
// family of algorithms or behaviors, and choose the one to use during runtime.

class PaymentStrategy{
 
     public:
     virtual void processPayment() = 0; // pure virtual function
     virtual ~PaymentStrategy(){
        // deconstructor 
        // why virtual?
        // when this is called with the base constructor like PaymentStrategy* creditCard=new CreditCardPayment();
       // CreditCardPayment deconstructor will also called
       // if not virtual then only base class construcotr is called
     };
};

class CreditCardPayment : public PaymentStrategy{
 
     public:
     void processPayment() override {
       cout<<"Payment Done With Credit Card."<<endl;
     } 
     
};

class UPIPayment : public PaymentStrategy{
 
    public:
    void processPayment() override {
      cout<<"Payment Done With UPI."<<endl;
    } 
    
};
class NetBankingPayment : public PaymentStrategy{
 
    public:
    void processPayment() override {
      cout<<"Payment Done With Net Banking."<<endl;
    } 
    
};
class DebitCardPayment : public PaymentStrategy{
 
    public:
    void processPayment() override {
      cout<<"Payment Done With Debit Card."<<endl;
    } 
    
};


class PaymentProcessor{
  
     private:
     PaymentStrategy* paymentStrategy;

     public:
     PaymentProcessor(PaymentStrategy* paymentStrategy){
        this->paymentStrategy=paymentStrategy;
     }

    void setPaymentStrategy(PaymentStrategy* paymentStrategy){
        this->paymentStrategy=paymentStrategy;
    }
    
    void processPayment(){
        this->paymentStrategy->processPayment();
    }

};

int main(){

    PaymentStrategy* creditCard=new CreditCardPayment();
    PaymentStrategy* upi=new UPIPayment();
    PaymentStrategy* debitCard=new DebitCardPayment();
    PaymentStrategy* netBanking=new DebitCardPayment();
    
    PaymentProcessor* paymentProcessor=new PaymentProcessor(creditCard);

    paymentProcessor->processPayment();
    paymentProcessor->setPaymentStrategy(upi);
    paymentProcessor->processPayment();
    paymentProcessor->setPaymentStrategy(debitCard);
    paymentProcessor->processPayment();
    paymentProcessor->setPaymentStrategy(netBanking);
    paymentProcessor->processPayment();

    delete paymentProcessor;
    return 0;
}