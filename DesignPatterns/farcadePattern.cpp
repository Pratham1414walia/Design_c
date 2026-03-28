// FARCADE DESIGN PATTERN

// Problem Statement: Simplifying Complexity with a Unified Interface
// The Facade Design Pattern is designed to solve this problem 
// by providing a unified interface to a set of interfaces in a subsystem. 
// It simplifies the interaction between the client and the subsystems, 
// reducing complexity and decoupling the client from subsystem implementations.

#include<iostream>
#include<string>
using namespace std;

class MusicPlayer{
    public:
    void playMusic(){
      cout<<"Play music"<<endl;
    }
};

class VideoPlayer{
  public:
  void playVideo(){
    cout<<"Play Video"<<endl;
  }
};

class ImageViewer{
   public:
   void clickImage(){
    cout<<"Image Click"<<endl;
   }
};

class MediaFacade{
   private:
   MusicPlayer* media;
   VideoPlayer* video;
   ImageViewer* image;
   
   public:
   MediaFacade(MusicPlayer* media,VideoPlayer* video,ImageViewer* image){
    this->media=media;
    this->video=video;
    this->image=image;
   }
   void performAction(const string& action) {
    if (action == "Music")
        media->playMusic();
    else if (action == "Video")
        video->playVideo();
    else if (action == "Image")
        image->clickImage();
    else
        cout << "Action not found" << endl;
    }

};

int main(){

    MusicPlayer* music=new MusicPlayer();
    VideoPlayer* video=new VideoPlayer();
    ImageViewer* image=new ImageViewer();

    MediaFacade* mediaManager=new MediaFacade(music,video,image);

  string action="Music";

    mediaManager->performAction(action);

    return 0;
}