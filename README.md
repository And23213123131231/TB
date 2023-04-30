# TB
## _Ticket booking application_

Client application + server for booking tickets for events

- Compile it as a  standalone application or as two separate application
- Launch the application and book tickets on your computer without spending time and money on the event.

## Enviroment
    CMake VERSION 3.16
    Qt 6.4.3 + QWebSocket 
    
## Build
It is recommended to use the Qt Creator to build the application.

For standalone application please open __CMakeLists.txt__ in root project folder and compile it

If youwant to have 2 separate applications you need to build:
- server, using __ticket_server/CMakeLists.txt__
- client, using __booking_client/CMakeLists.txt__

## Run
By default __Server__ will run on 7654 port  with ability to connect from local network (switch off Firewall or provide access to this port if no connection) 
You can change the port by passing '--port number' as a startup argument, were number is any available port

__Client__ will try cennect to server automaticaly after start. If you have change server port, please pass '--addr [ip]:[port]' as a startup command to client 



## License

LGPL v3
