#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;


// for HLD :
// https://bytebytego.com/courses/system-design-interview/design-a-url-shortener
class TinyUrl{

     private:
     int id=1;
     string base62="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012456789";

     unordered_map<string,string>longToShortUrl;
     unordered_map<string,string>shortToLongUrl;

     string encode(int id){
        string encodedString="";
        while(id>0){
            int bit=id%62;
            encodedString+=base62[bit];
            id/=62;
        }
        return encodedString;
     }
     public:

    string generateShortUrl(string longUrl){
      if(longToShortUrl.count(longUrl)){
        return longToShortUrl[longUrl];
      }

      string shortUrlCode=encode(id++);

      string shortUrl="https://tinyUrl.com/"+shortUrlCode;
      longToShortUrl[longUrl]=shortUrlCode; 
      shortToLongUrl[shortUrl]=longUrl;
      return shortUrl;
    }

    string getOriginalUrl(string shortUrl){
       if(shortToLongUrl.count(shortUrl)){
        return shortToLongUrl[shortUrl];
       }

       return "URL does not exist";
    }

};

int main(){

    TinyUrl* tinyUrl=new TinyUrl();

    string shortUrl=tinyUrl->generateShortUrl("https://google.com/maps/location");

    cout<<"shortUrl:  "<<endl;
    cout<<shortUrl<<endl;

    string originalUrl=tinyUrl->getOriginalUrl(shortUrl);
    cout<<"Long Url :" << endl;
    cout<<originalUrl<<endl;


    return 0;
}