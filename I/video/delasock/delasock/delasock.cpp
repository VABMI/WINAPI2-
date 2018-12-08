// delasock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//Our main function
//void main()
int _tmain(int argc, _TCHAR* argv[])
{
//We have to start de Winsock-dll
long answer;
WSAData wsaData;
WORD DLLVERSION;
DLLVERSION = MAKEWORD (2,1);
//Stard the dll
answer = WSAStartup(DLLVERSION, &wsaData);

//The dll was started, now I use the winsock funcitions in the program

//Structure for the sockets
SOCKADDR_IN addr;
//addr = our structure
int addrlen = sizeof(addr);

//Now we have to create our sockets
//sListen = socket which is listening for incoming connection
SOCKET sListen;
//sConnect = socket which is operating if a connection was found!
SOCKET sConnect;

//Now we have to setup our sockets:
//AF_INET = means that our socket belongs to the internet family
//SOCK_STREAM = means that our socket is a connection-orientated socket
sConnect = socket(AF_INET, SOCK_STREAM, NULL);

//Now we have to setup our structure
//inet_addr = IP of our socket (I use 127.0.0.1...this is the loopback adress)
addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//Retype the family
addr.sin_family = AF_INET;
//Now we have to setup the port in the structure;
//Now our server has the IP: 127.0.0.1 and the port 1234
addr.sin_port = htons (1234);

//Now we have to setup our sListen socket
sListen = socket(AF_INET, SOCK_STREAM, NULL);
//Now we blind the socket
//The socket becomes the structure addr
bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
//We have to say that the socket is listening for an incoming connection
listen(sListen, SOMAXCONN);
//SOMAXCON means that the server is listenning without any limit

//We have to start the capture of the frames to send it
//Well first of all initialize the frames and the default camera
//Using OpenCV
CvCapture *capture = 0;
    IplImage  *frame = 0;
    int key = 0;
    capture = cvCaptureFromCAM(0);


//At last we have to say what the serve sould do if a connection was found!
//For this we create a endless loop:
for(;;)
{
    cout << "Waiting for an incoming connection" <<endl;

    //if a connection was found << "..." <<endl
    if(sConnect = accept(sListen, (SOCKADDR*)&addr, &addrlen))
    {
        cout << "A connection was found" <<endl;

        //Second part in reference to Youtube 2
        //1r: The server should send a message with the funcion send();
        //The number of the letters +1
        //Ex: Number of the letters: 14+1=15
        answer = send(sConnect, "Bonjour",8, NULL);

        //*************************Third part of the project
        //Sending an image captured from the cam
        //always check
        if ( !capture ) 
        {
            fprintf( stderr, "Cannot open initialize webcam!\n" );
            return 1;
        }
        //create a window for the video
        cvNamedWindow( "server", CV_WINDOW_AUTOSIZE );

        while( key != 'q' ) 
        {
            //get a frame
            frame = cvQueryFrame(capture);
            //always check
            if( !frame ) break;
            //display current frame
            cvShowImage( "server", frame );
            //exit if user press 'q'
            key = cvWaitKey(1);
        }

        char StartStream(IplImage *frame);
        int streamSize(IplImage *frame);
        if(frame!=0)
        {
            return sizeof(*frame->imageData);
        }
        char* buffer = new char[10000];
        int len = 10000;
        //int sent = 0;
        for(int i=0; i<len; i+= answer)
        {
            answer = send(sConnect, buffer+i, len-i, 0);
        }
    }
    //free memory
    cvDestroyWindow( "server" );
    cvReleaseCapture( &capture );
}
return 0;
}