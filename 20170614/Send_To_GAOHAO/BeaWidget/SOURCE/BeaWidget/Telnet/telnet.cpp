#include "telnet.h"


Telnet::Telnet(QObject *parent,int port)
{
    tcpSocket=new QTcpSocket(parent);

    this->port=port;
    echo_status=0;
    telnet_connect=0;
 }
void Telnet::set_ip(QString ip)
{
    this->serverIp=ip;
}
int Telnet::connect_server()
{
    tcpSocket->connectToHost(serverIp,port);//connect
    const int time_out=3*1000;
   if(!tcpSocket->waitForConnected(time_out))
   {
       telnet_connect=0;
       return -1;
   }

     telnet_connect=1;
     return 1;
}
int Telnet::get_connected()
{
    return telnet_connect;
}

int Telnet::deal_telnet_protocol(unsigned char * receive_server)
{
    if(telnet_connect==1)
    {
        char client_send[NEGONATION_LENGTH];

        client_send[0]=receive_server[0];
        client_send[2]=receive_server[2];

        switch(receive_server[1])            //echo on:xieshang echo on client
        {
           case WILL:
            {
                if(receive_server[2]==ECHO)
                {
                    if(echo_status==SERVER_ECHO_OFF)
                    {
                        client_send[1]=DO;
                        echo_status=SERVER_ECHO_ON;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                     client_send[1]=DONT;
                }
                break;
            }
            case WONT:
            {
                if(receive_server[2]==ECHO)
                {
                    if(echo_status==SERVER_ECHO_ON)
                    {
                        client_send[1]=DONT;
                        echo_status=SERVER_ECHO_OFF;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    client_send[1]=DONT;
                }
                break;
            }
            case DO:
            {
                client_send[1]=WONT;
                break;

            }
            case DONT:
            {
                client_send[1]=WONT;
                break;
            }
            default:
            {
                return -1;
            }
        }
       if(tcpSocket->write(client_send,NEGONATION_LENGTH)<0) //send nagonation
       {
           return -2;
       }
    }
   return 0;
}

  unsigned char * Telnet::cs_communicate()
  {
      if(telnet_connect==1)
      {
      int re_recv=-1;
      int k=0;
      int deal_length;
      unsigned char * p_server=NULL;
      unsigned char * server_data=new unsigned char[MAX_RECEIVE];
      unsigned char * return_data=new unsigned char[MAX_RECEIVE];
      unsigned char  server_negonation[NEGONATION_LENGTH];

      re_recv=tcpSocket->read((char *)server_data,MAX_RECEIVE);//receive data
      const int time_out=5*1000;
      if(!tcpSocket->waitForReadyRead(time_out))
      {

          return NULL;
      }
      if(re_recv>0) //char numbers recved
      {

          deal_length=0;
          p_server=server_data;
          while(deal_length<re_recv)
          {
              if((*p_server ==IAC) && (*(p_server+1)!=IAC))//if receive xie shang yu ju
              {
                  memcpy(server_negonation,p_server,NEGONATION_LENGTH);
                  deal_telnet_protocol(server_negonation);//deal xieshang yuju from server
                  p_server+=NEGONATION_LENGTH;
                  deal_length+=NEGONATION_LENGTH;
              }
              else //receive data
              {

                      switch(*p_server)
                         {
                           case '\r':
                                return_data[k++]='\r';
                                return_data[k++]='\n';
                                break;
                           case '\n':
                              break;
                           default:
                             return_data[k++]=*p_server;
                         }

                  }
                  p_server++;
                  deal_length++;
          }
      }
      else
      {
          return_data=NULL;
      }

      return return_data;
      }
      else
      {
          return NULL;
      }
  }
   int Telnet::send_usrcommond(char * send_data)
   {
       if(telnet_connect==1)
       {
       int64_t res= tcpSocket->write(send_data,strlen(send_data));
       const int time_out=5*1000;
       if(!tcpSocket->waitForBytesWritten(time_out))
       {

           return -1;
       }

       if(res<0)
       {
           return -1;
       }
       if(tcpSocket->write("\r\n",2)<0)
       {

       return -1;
       }
       }
       return 0;
   }
   void Telnet::close_socket()
   {
       if(telnet_connect==1)
       {
           telnet_connect=0;
           tcpSocket->close();
       }
   }

   Telnet::~Telnet(){

   }
