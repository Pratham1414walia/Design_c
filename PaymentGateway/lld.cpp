#include<iostream>
#include<map>
#include<set>
#include<vector>
using namespace std;


enum class PaymentStatus{
    INITIATED,
    SUCCESS,
    FAILED,
    REFUNDED
};

enum class GatewayType{
    RAZORPAY,
    STRIPE
};

// WHY this is struct 
// PaymentRequest is a struct because it’s just a data carrier (DTO), not behavior-heavy.
struct PaymentRequest{
 
    public:
    string currency;
    string sender;
    string receiver;
    double amount;
    
    PaymentRequest(double amount,string currency,string sender,string receiver){
        this->sender=sender;
        this->amount=amount;
        this->currency=currency;
        this->receiver=receiver;
    }

};

//Interface for Banking System Processor (that will actually talk with the bank and move the money)
class BankingSystemProcessor{
    public:
    virtual bool processPayment(double amount) =0;
    virtual ~BankingSystemProcessor(){};
};

class RazorpayBankingSystemProcessor: public BankingSystemProcessor{
    public:
    bool processPayment(double amount) override{
        // success rate is 80% for payment to be done
        return rand()%100 > 20;
    }
};


class StripeBankingSystemProcessor: public BankingSystemProcessor{
    public:
    bool processPayment(double amount) override{
        // success rate is 20% for payment to be done
        return rand()%100 > 80;
    }
};


// Interface for handling multiple payment gateways
class PaymentGateway{
    public:
    BankingSystemProcessor* paymentProcessor;

    PaymentGateway(){
      this->paymentProcessor=nullptr;
    }

    // making process payment template (using template design Pattern) 
    virtual bool processPayment(PaymentRequest* payRequest){
        if(!validatePayment(payRequest)){
            cout<<"[Payment Gateway] validation failed: "<<endl;
            return false;
        }
        if(!initiatePayment(payRequest)){
            cout<<"[Payment Gateway] initiation failed: "<<endl;
            return false;
        }
        if(!confirmPayment(payRequest)){
            cout<<"[Payment Gateway] confirmation failed: "<<endl;
            return false;
        }
        return true;
    }
    public:
    virtual bool validatePayment(PaymentRequest* payRequest)=0;
    virtual bool initiatePayment(PaymentRequest* payRequest)=0;
    virtual bool confirmPayment(PaymentRequest* payRequest)=0;
};


class StripePaymentGateway : public PaymentGateway{

    public:

    StripePaymentGateway(){
        paymentProcessor=new StripeBankingSystemProcessor();
    }
    bool validatePayment(PaymentRequest* payRequest) override{
        // cout<<"Stripe VALIDATION PENDING: "<<payRequest->amount<<"  "<<payRequest->currency<<endl;
        // bool amountCondition=(payRequest->amount>0);
        // cout<<"AMOUNT CONDITION: "<<amountCondition<<endl;
        // bool currencyCondition=payRequest->currency!="INR";
        // cout<<"Currency CONDITION: "<<currencyCondition<<endl;
        // bool validationConditionResponse=(payRequest->amount>0 && payRequest->currency!="INR") ? true : false;
        // cout<<"validation Condtion response: "<<validationConditionResponse<<endl;
        return (payRequest->amount>0 && payRequest->currency!="INR") ? true : false;
    }
 
    bool initiatePayment(PaymentRequest* payRequest) override{
        return paymentProcessor->processPayment(payRequest->amount);
    }

    bool confirmPayment(PaymentRequest* payRequest) override{
        return true;
    }

};


class RazorpayPaymentGateway : public PaymentGateway{

    public:

    RazorpayPaymentGateway(){
        paymentProcessor=new RazorpayBankingSystemProcessor();
    }
    bool validatePayment(PaymentRequest* payRequest) override{
        // cout<<"Razorpay VALIDATION PENDING: "<<payRequest->amount<<"  "<<payRequest->currency<<endl;
        // bool amountCondition=(payRequest->amount>0);
        // cout<<"AMOUNT CONDITION: "<<amountCondition<<endl;
        // bool currencyCondition=payRequest->currency=="INR";
        // cout<<"Currency CONDITION: "<<currencyCondition<<endl;
        // bool validationConditionResponse=(payRequest->amount>0 && payRequest->currency=="INR") ? true : false;
        // cout<<"validation Condtion response: "<<validationConditionResponse<<endl;
        return (payRequest->amount>0 && payRequest->currency=="INR");
    }

    bool initiatePayment(PaymentRequest* payRequest) override{
        return paymentProcessor->processPayment(payRequest->amount);
    }

    bool confirmPayment(PaymentRequest* payRequest) override{
        return true;
    }

};

// Interface for the Proxy of Payment Gateway to handle Retry Mechanism
class PaymentGatewayProxy : public PaymentGateway{
    private:  
    PaymentGateway* realGateway;
    int retries;
    public:
    PaymentGatewayProxy(PaymentGateway* realGateway,int retries) {
        this->retries=retries;
        this->realGateway=realGateway;
    }

    bool processPayment(PaymentRequest* payRequest) override {
          for(int i=0;i<retries;i++){
              cout<<"TRY for doing Payment "<<i+1<<" time"<<endl;
              if(realGateway->processPayment(payRequest)){
               return true;
              }
          }
           cout<<"PAyment Cannot be done as bank is busy."<<endl;
          return false;
    }

    bool validatePayment(PaymentRequest* payRequest) override{
        return realGateway->validatePayment(payRequest);
    }
    bool initiatePayment(PaymentRequest* payRequest) override{
        return realGateway->initiatePayment(payRequest);
    }
    bool confirmPayment(PaymentRequest* payRequest) override{
        return realGateway->confirmPayment(payRequest);
    }

};


//GAteway for payment Factory
class GatewayFactory{
 
     public:

     static PaymentGateway* getPaymentGateway(GatewayType type){

         if(type==GatewayType::STRIPE){
             return new PaymentGatewayProxy(new StripePaymentGateway(),3);
         }
         else if(type==GatewayType::RAZORPAY){
            return new PaymentGatewayProxy(new RazorpayPaymentGateway(),5);
         }
         
            cout<<"Invalid Payment Gateway"<<endl;
            return nullptr;
     }

};


class IdempotencyService{

    private:
    set<string>processed;
    public:
    bool isDuplicate(string id){
        if(processed.count(id)){
            return true;
        }
       
        processed.insert(id);
        return false;
    }
};

class Transaction{
 
    public:
    PaymentRequest* req;
    string txnId;
    PaymentGateway* gateway;
    PaymentStatus status;

    Transaction(PaymentRequest* request,string transactionId,PaymentGateway* paymentGateway){
        this->req=request;
        this->txnId=transactionId;
        this->gateway=paymentGateway;
        this->status=PaymentStatus::INITIATED;
    }
};

class TransactionRepository{

    private:
    map<string,Transaction*>db;

    public:

    void save(Transaction* txn){
       db[txn->txnId]=txn;
    }

    Transaction* get(string &txnId){
        if(db.count(txnId)){
            return db[txnId];
        }
        return nullptr;
    }

    vector<Transaction*> getAll() {
         vector<Transaction*>res;
         for(auto &it:db){
            res.push_back(it.second);
         }
         return res;
    }

};

// The class that will actually manage the payment
class PaymentService{
    private:
    IdempotencyService* idem;
    TransactionRepository* txnRepo;
    public:
    PaymentService(){
        txnRepo=new TransactionRepository();
        idem=new IdempotencyService();
    }

   
    bool processPayment(string txnId,PaymentRequest* payRequest,PaymentGateway* gateway){

        if(idem->isDuplicate(txnId)){
            cout << "Duplicate Transaction!"<<endl;
            return false;
        }
         Transaction* txn=new Transaction(payRequest,txnId,gateway);
         txnRepo->save(txn);

         bool res=gateway->processPayment(payRequest);
         
        Transaction* stored=txnRepo->get(txnId);

        if(stored){
            stored->status=(res) ? PaymentStatus::SUCCESS : PaymentStatus::FAILED;
        }

         return res;
    }

    void refund(string txnId){
       Transaction* txn=txnRepo->get(txnId);
       if(txn && txn->status==PaymentStatus::SUCCESS){
          txn->status=PaymentStatus::REFUNDED;
          cout<<"Refund Success"<<endl; 
       }
       else{
        cout<<"Refund Failed"<<endl;
       }
    }
     
    void showHistory(){
        cout << "\n--- Transaction History ---\n";
        for (auto &t : txnRepo->getAll()) {
            cout << t->txnId << " | "
                 << t->req->sender << " -> "
                 << t->req->receiver << " | "
                 << t->req->amount << " | Status: "
                 << (int)t->status << "\n";
        }
    }

};



class PaymentController{
    PaymentService* paymentService;
    public:
    PaymentController(){
        paymentService=new PaymentService();
    }
    void makePayment(string txnId,PaymentRequest* req,GatewayType gateway){
       PaymentGateway* selectedGateway=GatewayFactory::getPaymentGateway(gateway);  
       bool  res=paymentService->processPayment(txnId,req,selectedGateway);
       cout<<(res ? "SUCCESS" : "FAILED")<<endl;
    }

    void refund(string txnId){
        paymentService->refund(txnId);
    }

    void showHistory(){
       paymentService->showHistory();
    }

};

int main(){

    PaymentRequest* paymentRequest1=new PaymentRequest(1000,"INR","SENDER1","RECEIVER1");
    PaymentRequest* paymentRequest2=new PaymentRequest(2000,"US","SENDER2","RECEIVER2");
    PaymentController* controller=new PaymentController();

   controller->makePayment("txn1",paymentRequest1,GatewayType::RAZORPAY);

    // Duplicate test
    controller->makePayment("txn2",paymentRequest2,GatewayType::STRIPE);

    // Refund
    controller->refund("txn1");

    // History
    controller->showHistory();
    return 0;
}