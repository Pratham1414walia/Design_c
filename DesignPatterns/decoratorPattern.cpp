
//  DECORATOR PATTERN:

// Problem Statement: Extending Functionality Without Modifying the Core Code
// Full Blog : https://codewitharyan.com/tech-blogs/decorator-design-pattern

// The Problem: Each coffee type and customization combination would require a new class if we follow a traditional 
// inheritance-based approach. For example, you’d need separate classes for “EspressoWithMilk”, 
// “CappuccinoWithVanilla”, or “LatteWithMilkAndSugar”. This quickly becomes unmanageable as 
// the number of combinations grows.


// To solve these issues, we need a way to dynamically wrap additional functionality around existing objects.

// The Decorator Pattern is designed to address this problem by dynamically adding new functionalities to objects without modifying their code.
//  It allows you to wrap objects in layers of functionality, creating flexible and extensible systems.

// Advantages of Using the Decorator Design Pattern 🏆
// 1. Extensibility:
// The pattern allows you to add new functionalities (customizations) without modifying existing classes.
// 2. Flexibility:
// Customizations can be applied dynamically, in any order, to any object.
// 3. Reusability:
// Decorators are reusable across different base objects and can be combined in different ways.
// 4. Open/Closed Principle:
// The pattern adheres to the Open/Closed Principle by allowing the system to be extended without modifying existing code.

#include<iostream>
using namespace std;

// It works like a recursion

// abstract class for base coffee variant
class Coffee{
    public:
    virtual string getDescription()=0;
    virtual double getCost() = 0 ;
};

// Concrete Coffee Variants
class Espresso : public Coffee {
  
  public:
  
  string getDescription() override {
    return "Espresso";
  };
  
  double getCost() override{
   return 3.2;
  };

};

class Cappicino : public Coffee {
  
    public:
    
    string getDescription() override {
      return "Cappicino";
    };
    
    double getCost() override{
     return 2.3;
    };

};


// abstract decorator Class for base Coffeee Variants

class CoffeeDecorator : public Coffee {
  
     protected:
     Coffee* coffee;

    public:

    CoffeeDecorator(Coffee * coffee){
    this->coffee=coffee;
    }

        
    string getDescription() override {
        return coffee->getDescription();
    };
      
    double getCost() override{
       return coffee->getCost();
    };

};


class MilkDecorator : public CoffeeDecorator {
  
   public:

   MilkDecorator(Coffee * coffee) : CoffeeDecorator(coffee){
   }

   string getDescription() override {
       return coffee->getDescription() + " With Milk";
   };
     
   double getCost() override{
      return coffee->getCost() + 5.2;
   };

};


class VanilaDecorator : public CoffeeDecorator {
  
    public:
 
    VanilaDecorator(Coffee * coffee) : CoffeeDecorator(coffee){
    }
 
    string getDescription() override {
        return coffee->getDescription() + " With Vanila";
    };
      
    double getCost() override{
       return coffee->getCost() + 1.2;
    };
 
 };
 

int main(){
    
    Coffee* coffee=new Espresso();

    cout<<coffee->getDescription()<<endl;
    cout<<coffee->getCost()<<endl;

    coffee=new MilkDecorator(coffee);

    cout<<coffee->getDescription()<<endl;
    cout<<coffee->getCost()<<endl;


    coffee=new VanilaDecorator(coffee);

    cout<<coffee->getDescription()<<endl;
    cout<<coffee->getCost()<<endl;
    return 0;
}