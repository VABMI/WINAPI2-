#include <opencv2/core/core.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void load(CascadeClassifier &a)
{
    try{
        a.load("F:/Projects/workspace/dispimage/src/lbpcascade_frontalface.xml");
    }
    catch(cv::Exception &e) {
        std::cout<<"Cannot load the qwespecified file";
    }
    if ( a.empty() ){
        std::cout << "ERROR: Couldn't load Face Detector (";
        std::cout<<")!";
        exit(1);
    }
}

void open(VideoCapture &camera)
{
    camera.open(0);
        if(!camera.isOpened())
        {
            std::cout<<"Camera did not open";
            exit(1);
        }

        camera.set(1000, 640);
        camera.set(1000, 480);
}

int main() {

    CascadeClassifier a;
    VideoCapture camera;
    namedWindow("CamerOP",1000);
    bool b =0;

    load(a);
    open(camera);

    while (true)
    {
      // Grab the next camera frame.
        Mat cframe;
         b=camera.read(cframe);
          if (!b)
          {
            std::cerr << "ERROR: Couldn't grab a camera frame." <<std::endl;
            exit(1);
          }

          imshow("CamerOP",cframe);
    }


    std::cout<<"Haillo";

    return 1;
}