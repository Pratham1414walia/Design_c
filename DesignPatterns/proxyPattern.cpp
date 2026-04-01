// PROXY DESIGN PATTERN

// The Proxy Pattern is a structural design pattern that provides a surrogate or placeholder for another object to control access to it.
// It allows you to create a wrapper around the original object to add additional functionality or control access.

// Advantages of the Proxy Pattern
// 1. Lazy Initialization:
// The proxy can create the real object only when it is needed, avoiding unnecessary initialization.
// 2. Access Control:
// The proxy can add security checks before allowing access to the real object
// 3. Caching:
// The proxy can cache the results of the real object to avoid重复计算.
// 4. Logging:
// The proxy can log the requests and responses to the real object.
// 5. Performance:
// The proxy can improve the performance of the real object by caching the results.
// 6. Access Control:
// The proxy can add security checks before allowing access to the real object.



#include<iostream>
#include<map>
using namespace std;


class VideoServiceInterface{
   public:
   virtual void playVideo(string userType,string videoName)=0;
};

class RealVideoService : public VideoServiceInterface{
 
    public:
    void playVideo(string userType,string videoName) override{
        cout<<"Streaming Video : "<<videoName<<" "<<"for userType: "<<userType<<endl;
    } 

};

class ProxyVideoService: public VideoServiceInterface{
 
   private:
   VideoServiceInterface* videoService;
   map<string,int>rateLimiter;
   map<string,bool>cacheHandler;
   public:

   ProxyVideoService(VideoServiceInterface* videoService){
    this->videoService=videoService;
   }
   void playVideo(string userType,string videoName) override{
     
     if(userType!="premium"){
        cout<<"only Premium Users can access the service."<<endl;
     }

      rateLimiter[userType]++;
      if(rateLimiter[userType]>5){
        cout<<"Too Many Requests"<<endl;
        return;
      }
     
      if(cacheHandler.count(videoName)){
        cout<<"Cache Video Found: "<<videoName<<endl;
      }
      else{

        cacheHandler[videoName]=true;
        videoService->playVideo(userType,videoName);
        
      }

   }

};

int main(){


    VideoServiceInterface* realVideoService=new RealVideoService();

    ProxyVideoService* proxyVideoService=new ProxyVideoService(realVideoService);


    proxyVideoService->playVideo("premium","Spiderman");
   // for cache
    proxyVideoService->playVideo("premium","Spiderman");
    // Rate Limiting Test

    for(int i=0;i<4;i++){
        proxyVideoService->playVideo("premium","Spiderman");
    }

    return 0;
}