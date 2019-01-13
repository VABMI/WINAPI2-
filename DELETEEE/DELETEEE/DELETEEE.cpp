// DELETEEE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

/////D:\WINAPI2-\sound\Debug\sfml-audio-s.lib
///C:\\Users\\vakhoo\\Downloads\\New folder\\SFML-2.5.1\\lib\\    32a

//#pragma comment(pdb, "C:\\Users\\vakhoo\\Downloads\\New folder\\SFML-2.5.1\\lib\\sfml-audio-s-d.pdb")
#pragma comment(lib, "C:\\Users\\vakhoo\\Downloads\\New folder\\SFML-2.5.1\\lib\\sfml-audio-s.lib")
#pragma comment(lib, "C:\\Users\\vakhoo\\Downloads\\SFML-2.5.1\\lib\\sfml-audio-d.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	sf::RenderWindow Window(sf::VideoMode(640,480,32),"Recording Sounds");
	if(!sf::SoundBufferRecorder::isAvailable())
		std::cout<<"you need to install a mic"<<std::endl;

	sf::SoundBufferRecorder recorder;
	sf::SoundBuffer buffer;
	sf::Sound sound;

	while(Window.isOpen())
	{
		sf::Event Event;
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::KeyPressed:
				if(Event.key.code==sf::Keyboard::R)
					recorder.start();
				else if(Event.key.code==sf::Keyboard::S)
				{
					recorder.stop();
					buffer=recorder.getBuffer();
					sound.setBuffer(buffer);
					sound.play();

				}
			}
		}
		Window.clear(sf::Color(0,240,255));
		Window.display();
	}
	return 0;
}