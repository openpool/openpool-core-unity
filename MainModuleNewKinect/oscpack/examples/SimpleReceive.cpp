/* 
    Example of two different ways to process received OSC messages using oscpack.
    Receives the messages from the SimpleSend.cpp example.
*/

#include <iostream>

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscTypes.h"
#include "ip/UdpSocket.h"


#define PORT 7000

class ExamplePacketListener : public osc::OscPacketListener {
protected:

    virtual void ProcessMessage( const osc::ReceivedMessage& m, 
				const IpEndpointName& remoteEndpoint )
    {
        try{
            // example of parsing single messages. osc::OsckPacketListener
            // handles the bundle traversal.
            
            if( strcmp( m.AddressPattern(), "/ball" ) == 0 ){
                // example #1 -- argument stream interface
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                osc::int32 a1;
                double a2;
                double a3;
                args >> a1 >> a2 >> a3 >> osc::EndMessage;
                
                std::cout << "received '/ball' message with arguments: "
                    << a1 << " " << a2 << " " << a3 << " " << "\n";
                
            }else if( strcmp( m.AddressPattern(), "/pocket" ) == 0 ){
                // example #2 -- argument iterator interface, supports
                // reflection for overloaded messages (eg you can call 
                // (*arg)->IsBool() to check if a bool was passed etc).
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                int a1 = (arg++)->AsInt32();
                int a2 = (arg++)->AsInt32();
                int a3 = (arg++)->AsInt32();
                int a4 = (arg++)->AsInt32();
                int a5 = (arg++)->AsInt32();
                int a6 = (arg++)->AsInt32();
                if( arg != m.ArgumentsEnd() )
                    throw osc::ExcessArgumentException();
                
                std::cout << "received '/pocket' message with arguments: "
                    << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << " " << a6 << "\n";
            }
        }catch( osc::Exception& e ){
            // any parsing errors such as unexpected argument types, or 
            // missing arguments get thrown as exceptions.
            std::cout << "error while parsing message: "
                << m.AddressPattern() << ": " << e.what() << "\n";
        }
    }
};

int main(int argc, char* argv[])
{
    ExamplePacketListener listener;
    UdpListeningReceiveSocket s(
            IpEndpointName( IpEndpointName::ANY_ADDRESS, PORT ),
            &listener );

    std::cout << "press ctrl-c to end\n";

    s.RunUntilSigInt();

    return 0;
}

