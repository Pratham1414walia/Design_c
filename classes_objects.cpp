#include<iostream>
using namespace std;


// By default the access modifier is private
class Car{
 
   public:  
   int wheels;
   string model;

   Car(int wheels,string model){
      this->wheels=wheels;
      this->model=model;
   }

   void startCar(){
    cout<<"Car starts"<<endl;
   }

};

int main(){
    
    Car* maruti=new Car(4,"Maruti & Suzuki");

    // Maruti is a pointer so either (*maruti).wheels or maruti->wheels
    cout << maruti->wheels << endl;
    cout << (*maruti).wheels << endl;
    maruti->startCar() ;
    return 0;
}