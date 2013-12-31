pipe.im
========

The concept of pipe.im is a communication shell that only requires a minimal feature set from its clients.

# Concept

## Configuration layer

The application will feature a webserver that allows basic registration and authentication. When authenticated all further configuration will be handled by the protocol. Server configuration only includes webserver settings, database settings and administrator identification. All further configuration will be stored in the database and loaded upon starting the server. 

## Client layer

A client will only need the ability to receive and send line based text. Optionally it can also communicate its status.

A client can use tunnels to connect from various interfaces:
* Bots that connect to various chat networks (via libpurple)
* A basic terminal like webinterface 
* A telnet (like) command line client

## Gateway layer

The gateway layer defines a basic API that enables communication with external networks and manages user and client connections to those networks.

Planned gateways:
* Chat-networks based on libpurple
* Fetching of RSS feeds
* (Fetching E-Mails)

## Protocol layer

The protocol will be similiar to shell input or related applications like bitlbee but with a bigger set of features.

Current planned features:
* Management of identities (client layer configurations)
* Management of gateways 
* Management of logging
* Management of rules 
  * Conditions like connected client, client status, time
  * Definitions of how to handle events
  * Actions to take like notification

# Implementation

Basic implementation will be based on the D programming language combined with C/C++ librarys (especially libpurple).

Components:
* Gateway manager
* Configuration database
* Log handling
* Frontend webserver
* Basic user management

# Roadmap

* ~~Sample application to interface libpurple~~
* Gateway API based on most basic needed functions
* D wrapper for libpurple based on that API
* Configuration database
* Webserver 
* Basic user management
* Protocol layer

# Installation windows

* Create ./bin folder
* Download pidgin installer and unpack it (with 7z for example)
* Copy *.dll, plugins, sasl2 and ca-certs to ./bin folder
* Run build_visuald.bat
* Open pipe.im.sln with visual studio
