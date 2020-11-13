#include "events.hpp"
sf::Thread host_snd_thread(&host_keyboard_send_Func);
sf::Thread host_rcv_thread(&host_keyboard_receive_Func);
sf::Thread client_snd_thread(&client_keyboard_send_Func);
sf::Thread client_rcv_thread(&client_keyboard_receive_Func);

// Объявляем классы героя, врагов
Player p(tileset, false);	//Mario
Player l(tileset, true);	//Luigi
//Enemy enemy;
///Player p(tileset);
Enemy enemy[5];
//----------------------------HOST----------------------------------
void host_keyboard_send_Func()
{
	//socket == send to client
	//client == send to host
	while(im_host==true)
	{
	if (Keyboard::isKeyPressed(Keyboard::Left)){ 
		if(client.send("LEFT", (strlen("LEFT")*sizeof(char))) != sf::Socket::Done) 
			printf("host_keyboard_send: error\n");}				// Левая стрелка
	if (Keyboard::isKeyPressed(Keyboard::Right)){
		if(client.send("RIGHT", (strlen("RIGHT")*sizeof(char))) != sf::Socket::Done) 
			printf("host_keyboard_send: error\n");}				// Правая стрелка
	if (Keyboard::isKeyPressed(Keyboard::Up)){
		if(client.send("UP", (strlen("UP")*sizeof(char))) != sf::Socket::Done) 
			printf("host_keyboard_send: error\n");} 				// Прыжок
	}
}
char host_receive_data[255];
void host_keyboard_receive_Func()
{
	cout<<"host receive thread is start\n";
	while(im_host==true)
	{
		sf::Packet packet;
		std::size_t received;
		memset(host_receive_data, 0, sizeof(host_receive_data));
		if(client.receive(host_receive_data, sizeof(host_receive_data), received) != sf::Socket::Done) printf("host_keyboard_receive: error\n");
		else{
			if(strcmp(host_receive_data, "LEFT")==0){
				cout<<"LEFT\n";
				l.dx = -0.1;
			}
			else if(strcmp(host_receive_data, "RIGHT")==0){
				cout<<"RIGHT\n";
				l.dx = 0.1;
			}
			else if(strcmp(host_receive_data, "UP")==0){
				cout<<"UP\n";
				if(!l.mode){ l.dy = -0.5; l.onGround = false; }//sound.play(); } 
				if(l.mode){ l.dy = -0.7; l.dx +=0.1; l.onGround = false; }//sound.play(); }
			}
			else if(strcmp(host_receive_data, "QUIT")==0){
				im_host==false;
				break;
				//client.disconnect();
			}
		}
	}
}
//---------------------CLIENT--------------------------------------
void client_keyboard_send_Func()
{
}
char client_receive_data[255];
void client_keyboard_receive_Func()
{
	cout<<"client receive thread is start\n";
	while(im_client==true)
	{
		sf::Packet packet;
		std::size_t received;
		memset(client_receive_data, 0, sizeof(client_receive_data));
		if(socket.receive(client_receive_data, sizeof(client_receive_data), received) != sf::Socket::Done) printf("client_keyboard_receive: error\n");
		else{
			if(strcmp(client_receive_data, "LEFT")==0){
				cout<<"LEFT\n";
				p.dx = -0.1;;
			}
			else if(strcmp(client_receive_data, "RIGHT")==0){
				cout<<"RIGHT\n";
				p.dx = 0.1;
			}
			else if(strcmp(client_receive_data, "UP")==0){
				cout<<"UP\n";
				if(!p.mode){ p.dy = -0.5; p.onGround = false; }//sound.play(); } 
				if(p.mode){ p.dy = -0.7; p.dx +=0.1; p.onGround = false; }//sound.play(); }
			}
			else if(strcmp(client_receive_data, "QUIT")==0){
				im_client==false;
				break;
			}
		}
	}
}
//****************************************************************************************
//****************************************************************************************

void host_script(){  
  printf("HOST_SCRIPT\n");
	im_host=true;
	sf::IpAddress PublicIP = sf::IpAddress::getLocalAddress();
	std::cout <<  "Public IP:" << PublicIP << std::endl;
	std::cout <<  "Public IP:" << sf::IpAddress::getPublicAddress() << std::endl;

  sf::TcpListener listener;
  listener.listen(1998);
  if(listener.listen(1998) != sf::Socket::Done){
    printf("Listen: err\n");
  }
  else
		printf("Listen: success\n");
 
  //sf::TcpSocket client;
  if(listener.accept(client) != sf::Socket::Done){
    printf("Accept: err\n");
		exit(EXIT_FAILURE);
  }
  else
		printf("Accept: success\n");
   
  std::cout << "New client connected: " << client.getRemoteAddress() << std::endl;
  // Receive a message from the client
  char data[255];
	sf::Packet packet;
	std::size_t received;
	if(client.receive(data, sizeof(data), received) == sf::Socket::Done){
		printf("\treceived: %s\n", data);
		
		//game_state=1;
		//game_cycle();
		
	}
	//host_snd_thread.launch();
	host_rcv_thread.launch();
	cout<<"play multiplayer\n";
	game_state=1;
	start_var=true;
	health=3;
	scores=0;
	game_cycle();


	/*
	while(true){
		sf::Packet packet;
		std::size_t received;
    memset(data, 0, sizeof(data));
		if(client.receive(data, sizeof(data), received) == sf::Socket::Done)
			printf("\treceived:	%s\n", data);
	}
	*/
}

void client_script(){  
	
  if(im_client==false)
	{	
		sf::Socket::Status status = socket.connect("127.0.0.1", 1998);
		if (status != sf::Socket::Done){
			printf("Connect: err\n");
			exit(EXIT_FAILURE);
		}
		else
			printf("connect: success\n");
		im_client=true;
	}
 
	char data[255]="CLIENT_CONNECT";
  if(socket.send(data, sizeof(data)) != sf::Socket::Done)
	{
		printf("send: error\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("send: success\n");
		//client_snd_thread.launch();
		//client_rcv_thread.launch();
		client_rcv_thread.launch();
		cout<<"play multiplayer\n";
		game_state=1;
		start_var=true;
		health=3;
		scores=0;
		game_cycle();
	}
  
}
