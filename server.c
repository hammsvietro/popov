#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include <pthread.h>
#include <sys/mman.h>

void error(char* msg) {
	printf("Erro: %s\n", msg);
	exit(-1);
}


void process_client(int client_sock, Queue *queue) {
	int msg_size = 0;
	char msg_in[255], msg_out[512];
	char instructions[] = "1 - mostra fila\n2 <int> - adiciona numero a fila\n3 - remove da fila";
	while ((msg_size = read(client_sock, msg_in, sizeof(msg_in))) > 0) {
		int val;
		char op;
		char *output = malloc(sizeof(char) * 300);
		sscanf(msg_in, "%c %d", &op, &val);
		switch (op) {
			case '1':
				output = get_queue(queue);
				print_queue(queue);
				break;

			case '2':
				enqueue(val, queue);
				output = get_queue(queue);
				print_queue(queue);
				break;
			
			case '3':
				dequeue(queue);
				output = get_queue(queue);
				print_queue(queue);
				break;

			default:
				output = instructions;
				break;
		}
		sprintf(msg_out, "%s", output);
		write(client_sock, msg_out, sizeof(msg_out));
	}

	close(client_sock);
}


int main(int argc, char *argv[]) {
	int sock, client;
	unsigned int client_addr_size; 
	struct sockaddr_in addr, client_addr;
	pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;

	if (argc != 2) error("srvx <porta>\n");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons((int) atoi(argv[1]));


	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) error("socket");
	if (bind(sock,(struct sockaddr*)&addr,sizeof(addr)) < 0) error("bind");
	if (listen(sock, 5) < 0) error("listen");
	printf("Esperando conexao...\n");
	volatile Queue *queue = init_queue(100);
	while (1) {
		client_addr_size = sizeof(client_addr);
		client = accept(sock, (struct sockaddr *) &client_addr, &client_addr_size);
		if (client > 0) {
			if (fork() == 0) {
				close(sock);
				pthread_mutex_lock(&mtx);
				process_client(client, queue);
				pthread_mutex_unlock(&mtx);
				exit(0);
			}
			close(client);
		}
	}
	return 0;
}