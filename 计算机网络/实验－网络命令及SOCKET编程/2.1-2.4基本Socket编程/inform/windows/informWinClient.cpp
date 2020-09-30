/*
 *	���������ҪĿ������˵��socket��̵Ļ������̣����Է�����/�ͻ��˵Ľ������̷ǳ��򵥣�
 *  ֻ���ɿͻ��������������һ��ѧ����Ϣ�Ľṹ��
 */
//informWinClient.cpp������ΪserverIP name age
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>

#define SERVER_PORT	5860 //�����˿�

enum OPTION{
	CONNECT,DISCONNECT,GET_TIME,GET_NAME,GET_CLIENTS,SEND_MESSAGE,EXIT;
};

//�ͻ�������������͵Ľṹ��
struct student
{
	char name[32];
	int age;
};

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int ret;
	SOCKET sClient; //�����׽���
	struct sockaddr_in saServer;//��ַ��Ϣ
	struct student stu;
	char *ptr = (char *)&stu;
	BOOL fSuccess = TRUE;
	char server_IP[16];
	BOOL isconnected = FALSE;
	enum OPTION option;
	int flag;

	 
/*	if(argc != 4)
	{
		printf("usage: informWinClient serverIP name age\n");
		return;
	}*/
	
	//WinSock��ʼ����
	wVersionRequested = MAKEWORD(2, 2);//ϣ��ʹ�õ�WinSock DLL�İ汾
	ret = WSAStartup( wVersionRequested, &wsaData );
	if (ret != 0)
	{
		printf("WSAStartup() failed!\n");
		return;
	}
	//ȷ��WinSock DLL֧�ְ汾2.2��
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
	{
		WSACleanup();
		printf("Invalid Winsock version!\n");
		return;
	}

	//����socket��ʹ��TCPЭ�飺
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() failed!\n");
		return;
	}
	
	while(1){
		printf("Please choose the option:\n");
		if(isconnected == FALSE){
			printf("1.connect the server\n2.exit\n");
			scanf("%d",&flag);
			if(flag==1){
				printf("Please input the server_IP:\n");
				scanf("%s",server_IP);
					//������������ַ��Ϣ��
				saServer.sin_family = AF_INET;//��ַ����
				saServer.sin_port = htons(SERVER_PORT);//ע��ת��Ϊ�����ֽ���
				saServer.sin_addr.S_un.S_addr = inet_addr(server_IP);
			}
			else if(flag==2){
				return;
			}
		}
		else{
			printf("1.disconnect\n2.get the time\n3.get the name\n");
			printf("4.get the clients list\n5.sned message\n6.exit\n");
			scanf("%d",&option);	
			switch(option){
				case DISCONNET:
					break;
				case GET_TIME:
					break;
				case GET_NAME:
					break;
				case GET_CLIENTS:
					break;
				case SEND_MESSAGE:
					break;
				case EXIT:
					return;
				default:
					break;
			}
		}
		
	}
	
	

	//saServer.sin_addr.S_un.S_addr = inet_addr(argv[1]);


	//���ӷ�������
	ret = connect(sClient, (struct sockaddr *)&saServer, sizeof(saServer));
	if (ret == SOCKET_ERROR)
	{
		printf("connect() failed!\n");
		closesocket(sClient);//�ر��׽���
		WSACleanup();
		return;
	}

	//����Ԥ��Э�飬�ͻ��˽�����һ��ѧ������Ϣ��
	strcpy(stu.name, argv[2]);
	stu.age = atoi(argv[3]);
	ret = send(sClient, (char *)&stu, sizeof(stu), 0);
	if(ret == SOCKET_ERROR)
	{
		printf("send() failed!\n");
	}
	else
		printf("student info has been sent!\n");

	closesocket(sClient);//�ر��׽���
	WSACleanup();
}
