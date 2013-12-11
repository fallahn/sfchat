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


About:
------

sfchat is a server / client based chat system using the TCP protocol. It is intended as an easy to include
class for use in sfml based games, but should work in any project as long as the class's sfml dependencies
are included. sfchat is written in C++ and tested to compile on windows and mint flavoured linux(gcc).
NOTE: sfchat uses some C++11 features. GCC (4.7 and above) has been tested to work, as has Visual Studio 10.


Features:
---------

 - Logging to time stamped text file on both server and client (time is localised to machine doing the logging)
 - Team based filters so connected clients will only see public messages and messages sent to their own team
 - Cutomisable; properties such as listen port, max users and team names are easily configured
 - IRC style commands; such as /me /connect and /nick are available and configurable to be disabled or enabled
on a per-project basis
 - Flexible; keystrokes and command parsing are all done internally by the class, returning only a set of formatted
strings. These can be used by any project's sf::Text object (or any other lib that supports std::String) so that the
look and feel of the chat is managed entirely by the project's UI system.


Usage:
------

sfchat is written with the aim of being easy to use in its most basic state as well as being highly configurable. To
use sfchat first include the source files (sfchat.h and sfchat.cpp) in your project. Then:

 - Create a global chat object and two sf::Text objects for displaying chat input and output
 
 - Call the chat object Create() function to create a server, or Connect() to connect to a server (IP and port values
 can be passed to these functions).
 
 - In the input poll loop call the chat object Update() function and pass the event object to it so sfchat can hook
 keyboard input.

 - Update the sf::Text string properties with GetOutputText() and GetInputText() each logic update

 - Draw the text objects when needed.

For an example on how to use sfchat see the included visual studio 10 solution which includes projects for a simple
chat client and a console only server.


Configurable commands:
----------------------

/nick <new name> - change current username
/me <action> - perform an action
/connect <address> - attempts to connect to the address on the default port
/disconnect - disconnects from chat
/team <message> - send message only to client's team members
/kick <username> - server only. Kick client with username
/play <soundfile> - plays sound file and sends request to other clients to play sound, assuming it exists locally.
To use this you must define m_PlaySound(std::string sound) to use your sound engine (sfchat assumes no existing audio
library as some people prefer to use libs like irrKlang, portaudio or others.)

To configure sfchat modify the values of the const variables at the top of both sfchat.h and sfchat .cpp













