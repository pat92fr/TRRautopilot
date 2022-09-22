/*
 * Copyright 2022 Patrick DUPUTZ
 *
 * This file is part of TRRsim.
 *
 * TRRsim is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or any later version.
 *
 * TRRsim is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * TRRsim. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <enet/enet.h>
#include "robot_autopilot.h"

#include <iostream>

struct Cclient
{
    Cclient(std::string const & address_str, int port, Cautopilot & autopilot) :
    _autopilot(autopilot)
    {
        // init
        if(enet_initialize()!= 0)
        {
            std::cout << "An error occurred while initializing ENet." << std::endl;
            return;
        }
        // client
        _client = enet_host_create(
            nullptr, /* create a client host */
            1, /* only allow 1 outgoing connection */
            2, /* allow up 2 channels to be used, 0 and 1 */
            0, /* assume any amount of incoming bandwidth */
            0  /* assume any amount of outgoing bandwidth */
        );
        if(_client == nullptr)
        {
            std::cout << "An error occurred while trying to create an ENet client host." << std::endl;
            return;
        }
        // connect to server
        ENetAddress address;
        enet_address_set_host(&address,address_str.c_str());
        address.port = port;
        _server = enet_host_connect(_client,&address,2,0);
        if(_server == nullptr)
        {
            std::cout << "No available server for initiating an ENet connection." << std::endl;
            return;
        }
        // wait up to 5 seconds for the connection attempt to succeed.
        ENetEvent event;
        if (enet_host_service(_client,&event,5000) > 0 && event.type==ENET_EVENT_TYPE_CONNECT)
        {
            std::cout << "Connection to server " << address_str << ":" << port << " succeeded." << std::endl;
            _is_connected = true;
        }
        else
        {
            enet_peer_reset(_server);
            _server = nullptr;
            std::cout << "Connection to server " << address_str << ":" << port << " failed." << std::endl;
        }
    }

    virtual ~Cclient()
    {
        if(_is_connected)
        {
            enet_peer_disconnect_now(_server,0);
            enet_host_destroy(_client);
        }
        enet_deinitialize();
    }

    void run()
    {
        ENetEvent event;
        while(_is_connected)
        {
            if(enet_host_service(_client,&event,20) > 0)
            {
                switch (event.type)
                {
                case ENET_EVENT_TYPE_RECEIVE:
                    {
                        // check incoming packet size
                        if(event.packet->dataLength==sizeof(Cautopilot_inut_sensors))
                        {
                            Cautopilot_inut_sensors in;
                            memcpy(&in,event.packet->data,sizeof(Cautopilot_inut_sensors));
                            enet_packet_destroy (event.packet);

                            Cautopilot_output_commands out;
                            _autopilot.update(in,out);

                            ENetPacket * packet = enet_packet_create (&out,sizeof(Cautopilot_output_commands),ENET_PACKET_FLAG_RELIABLE);
                            enet_peer_send(_server,0,packet);
                            enet_host_flush(_client);
                        }
                    }
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    {
                        _is_connected = false;
                        _server = nullptr;
                        std::cout << "Disconnected from server." << std::endl;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }

protected:


private:
    Cautopilot & _autopilot;
    ENetHost * _client = nullptr;
    ENetPeer * _server = nullptr;
    bool _is_connected = false;
};



#endif // CLIENT_H_INCLUDED
