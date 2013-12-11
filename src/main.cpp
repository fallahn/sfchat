////////////////////////////////////////////////////////////
//
// sfchat - a class for providing in-game chat between players connected to a networked game built on SFML.
// Copyright (C) 2013 Matt Marchant
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Example application for using sfchat class.
//
// Create a global chat object and two sf::Text objects for displaying chat input and output
// (Optionally add a text object for displaying user names of connected clients)
// Call the chat object Create() function to create a server, or Connect() to connect to a server
// In the input poll loop call the chat object Update() function and pass the event object
// to it so sfchat can hook keyboard input.
// Update the sf::Text string properties with GetOutputText() and GetInputText() each logic update
// Draw the text objects when needed.
////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sfchat/sfchat.h>

//enable colour text
//#define USE_COLOUR //slower to draw, but prettier :)

//global members
std::unique_ptr<sf::Text> chatOutput, chatInput, nickList;

//chat object
sfchat::Chat chatObject;

//function for updating object logic
void Update()
{
#ifndef USE_COLOUR
	chatOutput->setString(chatObject.GetOutputText());
#endif
	chatInput->setString(chatObject.GetInputText());
	nickList->setString(chatObject.GetNickList());
}

//function for drawing objects on screen
void Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(100, 149, 237));
#ifdef USE_COLOUR
	//loop through the actual buffer and draw our colours
	//slower than drawing the string equivalent
	chatOutput->setPosition(0.f ,0.f);
	for(unsigned i = 0; i < chatObject.GetOutputBuffer().size(); i++)
	{
		chatOutput->setString(chatObject.GetOutputBuffer()[i].text);
		chatOutput->setColor(chatObject.GetOutputBuffer()[i].colour);
		window.draw(*chatOutput);
		chatOutput->move(0.f, chatOutput->getLocalBounds().height + 4.f);
	}
#else
	window.draw(*chatOutput);
#endif
	window.draw(*chatInput);
	window.draw(*nickList);

	window.display();
}

int main()
{
    //set up the text properties as they will appear on screen
	chatOutput = std::unique_ptr<sf::Text>(new sf::Text());
	chatOutput->setCharacterSize(15u);
	chatOutput->setColor(sf::Color::Red);

	chatInput = std::unique_ptr<sf::Text>(new sf::Text());
	chatInput->setCharacterSize(15u);
	chatInput->setColor(sf::Color::Blue);
	chatInput->setPosition(0.f, 500.f);

	nickList = std::unique_ptr<sf::Text>(new sf::Text());
	nickList->setCharacterSize(15u);
	nickList->setPosition(650.f, 0.f);
	
	//get some input from the console
	std::cout << "Enter 's' to start server or enter an IP address to connect to: ";
	std::string str, title;
	std::cin >> str;
	if(str == "s")
	{
		//create a server on the default port with logging to text file enabled
		chatObject.Create(sfchat::DEFAULT_PORT, true);
		title = "Running Chat Server. Press T to chat or Q to quit";
	}
	else 
	{
		//attempt to connect to server
		chatObject.Connect(sf::IpAddress(str));
		title = "Connected to: " + str + ". Press T to chat or Q to quit";
	}

	//create a window
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600), title);

    //run the program as long as the window is open
    while (window.isOpen())
    {
 		//check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            //"close requested" event: we close the window
            if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q
				&& !chatObject.WaitingInput())) //so we don't quit while typing 'Q' into the chat
                window.close();

			//send event to chat object to check for input
			chatObject.Update(event);
		}	

		//update the logic
		Update();
		//draw our stuffs
		Draw(window);  
    }

	return 0;
}