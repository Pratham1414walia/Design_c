#include<iostream>
using namespace std;

//For singleton class
// https://medium.com/@dharshithasrimal/singleton-design-pattern-the-solution-for-efficient-resource-management-f2e882f8ea67

// in class the default access modifier is Private
// while in struct the default access modifier in Public
class Singleton{
 
    private:
    static Singleton* instance;
    //Why Private?  So that no one can create or initialize the instance from outside
    Singleton(){
         cout<<"Singleton Pattern was called"<<endl;
    }

    public:
    // It should be static because we are  calling without creating an object
    static Singleton* getInstance(){
       return instance;
    }
};

// Early Initialize ,so lock required 
// But it also has some drawbacks suppose this initialze has very high complexity
// and if this class does not used in the application then it will be a waste to call

Singleton* Singleton::instance=new Singleton();

int main(){

     Singleton* object1 = Singleton::getInstance();
     Singleton* object2 = Singleton::getInstance();

     if(object1==object2){
        cout<<"Same Instance"<<endl;
     } 
     else{
        cout<<"different Instance"<<endl;
     }
     
    return 0;
}