#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

void error(char* msg) {
	printf("Erro: %s\n", msg);
	exit(-1);
}


int main(int argc, char* argv[]) {
	int sock;
	struct sockaddr_in addr;
	struct hostent* hostPtr;
	char msg[255];


	if (argc != 4) error("Sintaxe: ./cliente <host> <port> <string>\n");
	if ((hostPtr = gethostbyname(argv[1])) == 0) error("Nao consegui obter endereco");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ((struct in_addr *) (hostPtr->h_addr))->s_addr;
	addr.sin_port = htons((short) atoi(argv[2]));

	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) error("socket");
	if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) error("Connect");

	write(sock, argv[3], 1 + strlen(argv[3]));
	read(sock, msg, sizeof(msg));
	printf("%s\n", msg);

	close(sock);
}