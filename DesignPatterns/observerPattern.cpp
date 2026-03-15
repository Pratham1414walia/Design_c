// Observer Design Pattern: How to Stay Updated Without Constantly Checking
// In programming, the Observer Pattern allows one object (the subject) to notify other objects
//  (the observers) whenever there is a change in its state.

// Advantages of the Observer Pattern 🎉 :

// 1. Decoupling: The YouTubeChannel doesn’t need to know what each observer does. It just notifies them about the update. 🎯
// 2. Scalability: Adding new types of observers (e.g., email, SMS) is as simple as implementing the Subscriber interface. 📈
// 3. Flexibility: Observers can join or leave at any time without affecting the YouTubeChannel. 🔄
// 4. Maintainability: The YouTubeChannel stays clean and simple, while the observers handle their own logic. 🔧

// Real-Life Use Cases for the Observer Pattern 🌍 : 

// 1. Social Media Notifications: When someone you follow posts something, you get a notification.
// 2. Stock Market Alerts: When stock prices change, you are notified.
// 3. Weather Apps: The app notifies you about weather changes.
// 4. Message Systems: When a new message arrives, all subscribers are notified.


#include<iostream>
#include<set>
using namespace std;

class Subscriber{
    public:
    virtual void update(string message) = 0;
  
    virtual string getName() = 0; 
    virtual ~Subscriber(){
        
    }
};


class Channel{
    public:
    virtual void addSubscriber(Subscriber* subscriber) = 0;
    virtual void removeSubscriber(Subscriber* subscriber) = 0;
    virtual void notifySubscribers() = 0;
    virtual void uploadContent(string content) = 0 ;
    virtual ~Channel(){

    }
};

class EmailSubscriber : public Subscriber{
    private:
    string subscriberName;
    void update(string message) override{
       cout<<"Email Subsriber  with name "<<subscriberName<<" notified with message: "<<message<<endl;
       return;
    }

    public:

    EmailSubscriber(string name){
        this->subscriberName=name;
    }

    string getName() override{
      return this->subscriberName;
    }
};

class SmsSubscriber : public Subscriber{
    private:
    string subscriberName;
    void update(string message) override{
       cout<<"Sms Subscriber  with name "<<subscriberName<<" notified with message: "<<message<<endl;
       return;
    }

    public:

    SmsSubscriber(string name){
        this->subscriberName=name;
    }

    string getName() override{
      return this->subscriberName;
    }
};


class YoutubeChannel : public Channel {

 private:
 set<Subscriber*>subscriberList;  

 string videoName;
 public:  
 void addSubscriber (Subscriber* sub) override{
    if(this->subscriberList.count(sub)){
        cout<<"Subsciber Named "<<sub->getName() <<" already subscribed to Youtube channel"<<endl;
        return ;
    }
    this->subscriberList.insert(sub);
    cout<<"Subsciber Named "<<sub->getName() <<" subscribed to Youtube channel"<<endl;
    return;
 }

 void removeSubscriber(Subscriber* sub) override{
    if(this->subscriberList.find(sub)==this->subscriberList.end()){
        cout<<"Subsciber Named "<<sub->getName() <<" not subscribed to Youtube channel"<<endl;
        return;
    }
    this->subscriberList.erase(sub);
    cout<<"Subsciber Named "<<sub->getName() <<" unsubscribed to Youtube channel"<<endl;
    return;
 }

 void notifySubscribers() override{
    for(Subscriber* sub:subscriberList){
        sub->update(this->videoName);
    }
 };


 void uploadContent(string content) override{
     this->videoName=content;
     notifySubscribers();
 }


};

int main(){

   Channel * youtubeChannel=new YoutubeChannel(); 
   Subscriber* emailSub=new EmailSubscriber("Email Person");
   Subscriber* smsSub=new EmailSubscriber("SMS Person");
   
   youtubeChannel->addSubscriber(emailSub);
      
//    youtubeChannel->addSubscriber(emailSub); // To check if repeated subscribers are not added
   youtubeChannel->addSubscriber(smsSub);

   youtubeChannel->uploadContent("DSA Videos");


     
   youtubeChannel->removeSubscriber(emailSub);
   youtubeChannel->uploadContent("DSA Part2 Videos");
 return 0;
}