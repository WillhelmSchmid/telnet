#ifdef WIN32
#include <winsock2.h>
#define close closesocket
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#endif

const char msg[]={
   "                          oooo$$$$$$$$$$$$oooo\n\r"
   "                      oo$$$$$$$$$$$$$$$$$$$$$$$$o\n\r"
   "                   oo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o         o$   $$ o$\n\r"
   "   o $ oo        o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o       $$ $$ $$o$\n\r"
   "oo $ $ \"$      o$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$o       $$$o$$o$\n\r"
   "\"$$$$$$o$     o$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$o    $$$$$$$$\n\r"
   "  $$$$$$$    $$$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$$$$$$$$$$$$$$\n\r"
   "  $$$$$$$$$$$$$$$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$$$$$$  \"\"\"$$$\n\r"
   "   \"$$$\"\"\"\"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     \"$$$\n\r"
   "    $$$   o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     \"$$$o\n\r"
   "   o$$\"   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$o\n\r"
   "   $$$    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\" \"$$$$$$ooooo$$$$o\n\r"
   "  o$$$oooo$$$$$  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   o$$$$$$$$$$$$$$$$$\n\r"
   "  $$$$$$$$\"$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     $$$$\"\"\"\"\"\"\"\"\n\r"
   " \"\"\"\"       $$$$    \"$$$$$$$$$$$$$$$$$$$$$$$$$$$$\"      o$$$\n\r"
   "            \"$$$o     \"\"\"$$$$$$$$$$$$$$$$$$\"$$\"         $$$\n\r"
   "              $$$o          \"$$\"\"$$$$$$\"\"\"\"           o$$$\n\r"
   "               $$$$o                                o$$$\"\n\r"
   "                \"$$$$o      o$$$$$$o\"$$$$o        o$$$$\n\r"
   "                  \"$$$$$oo     \"\"$$$$o$$$$$o   o$$$$\"\"\n\r"
   "                     \"\"$$$$$oooo  \"$$$o$$$$$$$$$\"\"\"\n\r"
   "                        \"\"$$$$$$$oo $$$$$$$$$$\n\r"
   "                                \"\"\"\"$$$$$$$$$$$\n\r"
   "                                    $$$$$$$$$$$$\n\r"
   "                                     $$$$$$$$$$\"\n\r"
   "                                      \"$$$\"\"\"\"\n\r"
};


int main()
{

   struct sockaddr_in sockAddr;
   int sock;

#ifdef WIN32
   WORD wVersionRequested;
   WSADATA wsaData;
   wVersionRequested = MAKEWORD( 1, 1 ); 
   if(WSAStartup( wVersionRequested, &wsaData ))
   {
      return -1;
   } 
#endif

   sock = socket(AF_INET, SOCK_STREAM, 0);
   if( sock < 0) return -1;
   memset((char*)&sockAddr, 0, sizeof(struct sockaddr_in));
   sockAddr.sin_family = AF_INET;
   sockAddr.sin_port = htons(23);
   sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   if(bind(sock, (struct sockaddr*)&sockAddr, sizeof(struct sockaddr)) < 0)
      return -1;
   if(listen(sock, 5))
      return -1;

   for(;;)
   {
      int s = accept(sock, NULL, NULL);
      if(s < 0)
         return -1;
      send(s, msg, sizeof(msg), 0);
      close(s);
   }
}
