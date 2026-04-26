
// STATE DESIGN PATTERN

// This pattern allows an object to alter its behavior when its internal state changes by 
// delegating state-specific behaviors to separate classes. 
// It promotes cleaner code, easier maintenance, and better scalability.

#include<iostream>
using namespace std;

class TrafficLightState;
class RedState;
class YellowState;
class GreenState;
class TrafficLightContext;

class TrafficLightState{
  
    public:
    virtual TrafficLightState* next()=0;
    virtual string getColor() = 0;
};
class RedState : public TrafficLightState{
    public:
    TrafficLightState* next() override;
     
    string getColor() override{
       return "RED";
    }
};

class GreenState : public TrafficLightState{
    public:
    TrafficLightState* next() override;
     
    string getColor() override{
       return "GREEN";
    }
};




class YellowState : public TrafficLightState{
    public:
    TrafficLightState* next() override;
     
    string getColor() override{
         return "YELLOW";
    }
};

TrafficLightState* RedState::next(){
    cout<<"Red to Yellow"<<endl;
    return new YellowState();
 }

 TrafficLightState* GreenState::next() {
    cout<<"Green TO Red"<<endl;
    return new RedState();
 }
TrafficLightState* YellowState::next() {
    cout<<"Yellow To Green"<<endl;
    return new GreenState(); 
 }


class TrafficLightContext{
    protected:
    TrafficLightState* currentState;
    
    public:

    TrafficLightContext(){
        currentState=new RedState();
    }


    void next(){
        currentState=currentState->next();
    }


    string getColor(){
        return currentState->getColor();
    }

};

int main(){

    TrafficLightContext* trafficLight=new TrafficLightContext();
    trafficLight->next();
    trafficLight->next();
    trafficLight->next();
    trafficLight->next();

return 0;
}
