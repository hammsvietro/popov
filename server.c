#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>


void error(char* msg) {
	printf("Erro: %s\n", msg);
	exit(-1);
}


void process_client(int client_sock) {
	int msg_size = 0;
	char msg_in[255], msg_out[512];

	while ((msg_size = read(client_sock, msg_in, sizeof(msg_in))) > 0) {
		msg_in[msg_size] = '\0';
		printf("%s\n", msg_in);
		sprintf(msg_out, "retorno [%s]", msg_in);
		write(client_sock, msg_out, sizeof(msg_out));
	}

	close(client_sock);
}


int main(int argc, char *argv[]) {
	int sock, client, client_addr_size;
	struct sockaddr_in addr, client_addr;

	if (argc != 2) error("srvx <porta>\n");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons((int) atoi(argv[1]));


	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) error("socket");
	if (bind(sock,(struct sockaddr*)&addr,sizeof(addr)) < 0) error("bind");
	if (listen(sock, 5) < 0) error("listen");

	while (1) {
		printf("Esperando conexao...\n");
		client_addr_size = sizeof(client_addr);
		client = accept(sock, (struct sockaddr *) &client_addr, &client_addr_size);
		if (client > 0) {
			if (fork() == 0) {
				close(sock);
				process_client(client);
				exit(0);
			}
			close(client);
		}
	}
	return 0;
}