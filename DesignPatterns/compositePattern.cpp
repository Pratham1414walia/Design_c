// COMPOSITE DESIGN PATTERN:

// The Savior: Composite Design Pattern 🦸‍♂️
// The Composite Design Pattern is specifically designed to handle hierarchies.
// It allows you to treat individual objects and groups of objects (composites) uniformly.
// In our smart home system, the pattern enables you to control individual devices, rooms, floors, 
// and even the entire house seamlessly through a single interface.

// How the Composite Design Pattern Works 🔧
// The Composite Pattern achieves this by defining a common interface for both individual objects 
// and composites (groups). Each composite can hold child components 
// (which could be either individual objects or other composites), forming a tree structure.

// Advantages of Using the Composite Design Pattern 🏆
// 1. Uniformity:

// Treat individual devices and groups (rooms, floors, etc.) uniformly using the SmartComponent interface.

// 2. Scalability:

// Easily add new components (e.g., Garage, Garden) without changing the existing code.

// 3. Decoupling:

// The controller is decoupled from the specific structure of the hierarchy, making the system more modular.

// 4. Flexibility:

// Changes in the hierarchy (e.g., adding or removing components) are easily handled by the composite structure.

// Real-Life Use Cases and Examples of the Composite Pattern 🌍
// File Systems:
// Files and directories in an operating system follow the composite pattern, where directories contain files or other directories.

// 2. Graphics Rendering:

// GUI frameworks use the composite pattern for rendering graphical components, where containers (e.g., panels) hold other components (e.g., buttons, labels).

// 3. Organization Hierarchies:

// Companies use the composite pattern to model organizational structures, where departments contain employees or other sub-departments.


#include<iostream>
#include<vector>
#include<set>
using namespace std;

class SmartComponent{
  public:
  virtual void turnOn()=0;
  virtual void turnOff()=0;
};

// Composite gets added because it inherits SmartComponent, so it can be upcast to SmartComponent*.

class AirConditioner: public SmartComponent{
  
    public:
    void turnOn() override{
        cout<<"Air Conditioner is on NOW."<<endl;
    }

    void turnOff() override{
        cout<<"Air Conditioner is off NOW."<<endl;
    }

};



class Cooler: public SmartComponent{
  
    public:
    void turnOn() override{
        cout<<"Cooler is on NOW."<<endl;
    }

    void turnOff() override{
        cout<<"Cooler is off NOW."<<endl;
    }

};


class CompositeSmartComponent : public SmartComponent{
    private:
    set<SmartComponent*>components;

    public:
    void addComponent(SmartComponent* component){
        components.insert(component);
    }

    void removeComponent(SmartComponent* component){
        components.erase(component);
    }

    void turnOn() override{
        for(SmartComponent* component:components){
            component->turnOn();
        }
    }
    void turnOff() override{
        for(SmartComponent* component:components){
            component->turnOff();
        }
    }
};

int main(){
    SmartComponent* airConditioner=new AirConditioner();
    SmartComponent* cooler=new Cooler();

    CompositeSmartComponent* room1=new CompositeSmartComponent();
    room1->addComponent(airConditioner);
    room1->addComponent(cooler);

    CompositeSmartComponent* room2=new CompositeSmartComponent();
    room2->addComponent(airConditioner);
    room2->addComponent(cooler);


    CompositeSmartComponent* floor1=new CompositeSmartComponent();
    floor1->addComponent(room1);
    floor1->addComponent(room2);

    // floor1->turnOn();


    CompositeSmartComponent* house=new CompositeSmartComponent();
    house->addComponent(floor1);

    house->turnOn();

    return 0;
}

// . Upcasting (IMPORTANT 🔥)
// floor1->addComponent(room1);
// room1 type = CompositeSmartComponent*
// addComponent() expects = SmartComponent*

// 👉 C++ automatically converts (upcasts):

// CompositeSmartComponent* → SmartComponent*

// 👉 No data change, only type view changes