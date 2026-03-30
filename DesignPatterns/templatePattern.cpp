// TEMPLATE DESIGN PATTERN
// It provides a reliable blueprint for algorithms, ensuring consistency while still allowing for flexibility. 

//Advantages:
// 1) Reduces Code duplication
// 2) Enforces consistency
// 3) Improves Maintainability
// 4) Provides Flexibility
// 5) Enhances Code Reusability


//Use Cases:
// 1) Cooking Recipe 
// 2) Game Development
// 3)Document Processing

#include<iostream>
using namespace std;

class Beverage{
   public:
    void prepareRecipe(){
        boilWater();
        brew();
        pourInCup();
        // if customer want condiments
        if(customerWantsCondiments()){
            addCondiments();
        }
    }
    protected:
    void boilWater(){
        cout<<"Boil Water ..."<<endl;
    }

    void pourInCup(){
        cout<<"Pouring in Cup ..."<<endl;
    }

    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    virtual bool customerWantsCondiments(){
      return true;
    }
};


class Coffee: public Beverage{
 
    protected:
    void brew() override{
      cout<<"Brewing Coffee..."<<endl;
    }

    void addCondiments() override{
        cout<<"Adding sugar and milk"<<endl;
    }

    bool  customerWantsCondiments() override{
        return false;
    }

};


class Tea: public Beverage{
 
    protected:
    void brew() override{
      cout<<"Brewing Tea..."<<endl;
    }

    void addCondiments() override{
        cout<<"Adding Ginger"<<endl;
    }

    bool  customerWantsCondiments() override{
        return true;
    }

};


int main(){


    Beverage* coffee=new Coffee();
    coffee->prepareRecipe();

    Beverage* tea=new Tea();
    tea->prepareRecipe();
    return 0;
}