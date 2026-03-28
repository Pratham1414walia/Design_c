// ADAPTER DESIGN PATTERN

// Problem Statement: Connecting the Unconnectable

// The Problem: Each device uses a unique communication protocol, and your app would become a mess if you hard-code the logic for each device. It will be difficult to maintain and extend as more devices are added.

// The Challenge: How can you create a clean, scalable solution to connect all these devices?

// The Savior: Adapter Design Pattern 🦸‍♂️
// The Adapter Pattern is designed to solve this exact problem. It acts as a bridge between two incompatible interfaces,
//  allowing them to work together seamlessly without modifying their code.

// In our SmartHomeController example, the adapter provides a common interface that the controller can 
// use to interact with devices, regardless of their specific communication protocols or implementation details.


// Advantages of Using the Adapter Design Pattern 🏆
// Let’s review how the Adapter Pattern improves our solution:

// 1. Seamless Integration:

// The Adapter Pattern enables the SmartHomeController to interact with devices using different protocols (Bluetooth, Wi-Fi, Zigbee, etc.) without worrying about their implementation details.

// ‍‍

// Scalability:
// Adding a new device type (e.g., a SmartSpeaker or SecurityCamera) only requires creating a new adapter. The SmartHomeController doesn’t need any changes.

// ‍

// 3. Decoupling:

// The controller is decoupled from the specific implementations of devices, making the system more modular and maintainable.

// ‍

// 4. Flexibility:

// If a device’s protocol changes (e.g., the SmartLight switches from Wi-Fi to a cloud API), only the adapter needs to be updated, leaving the rest of the system unaffected.

// Real-life Use Cases and Examples of the Adapter Pattern 
// 1)Smart Home Systems:
// 2) Payment Gateways
// 3) Database Drivers
// 4)Media Players
#include<iostream>
using namespace std;

class ISmartDevice{
   public:
   virtual void turnOn()=0;
   virtual void turnOff()=0;
};

class AirConditioner{
    public:
     void connectViaBluetooth() {
        cout<<"Air Conditioner connected via Bluetooth."<<endl;
      }
    
       void startCooling() {
        cout<<"Air Conditioner is now cooling."<<endl;
      }
    
       void stopCooling() {
        cout<<"Air Conditioner stopped cooling."<<endl;
  
      }

       void disconnectBluetooth() {
        cout<<"Air Conditioner disconnected from Bluetooth."<<endl;
      }
     
};


class AirConditionerAdapater : public ISmartDevice{
    private:
    AirConditioner* airConditioner;
    public:
    AirConditionerAdapater(AirConditioner* airConditioner){
        this->airConditioner=airConditioner;
    }

    void turnOn() override{
        airConditioner->connectViaBluetooth();
        airConditioner->startCooling();
    }

    void turnOff() override{
        airConditioner->stopCooling();
        airConditioner->disconnectBluetooth();
    }
};



int main (){

    
    ISmartDevice* airConditioner=new AirConditionerAdapater(new AirConditioner());
   
    airConditioner->turnOn();
    airConditioner->turnOff();
    return 0;
}