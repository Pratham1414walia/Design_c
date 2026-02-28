#include<iostream>
#include<mutex>
using namespace std;


//For singleton class
// https://medium.com/@dharshithasrimal/singleton-design-pattern-the-solution-for-efficient-resource-management-f2e882f8ea67


// in class the default access modifier is Private
// while in struct the default access modifier in Public
class Singleton{
 
    private:
    static Singleton* instance;
    static mutex mtx;

    //Why Private?  So that no one can create or initialize the instance from outside
    Singleton(){
         cout<<"Singleton Pattern was called"<<endl;
    }

    public:
    // It should be static because we are  calling without creating an object
    static Singleton* getInstance(){
        
        if(instance==nullptr){
           // For Thread safety this lock is required 
            lock_guard<mutex> lock(mtx);

            if(instance==nullptr){
                instance = new Singleton();
            }
            return instance;
        }
        return instance; 
    }
};

// initializing static variables
Singleton* Singleton::instance=nullptr;
mutex Singleton::mtx;
// Why it is not initialized with a value
// C++ automatically calls the default constructor of std::mutex.

// So internally it's initialized into a valid, unlocked state.

// You don’t give it a value because a mutex is not a data container — it’s a synchronization primitive.

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