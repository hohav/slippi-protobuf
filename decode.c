#include <stdio.h>
#include "slippi.pb-c.h"
#define MAX_MSG_SIZE 4096

int main(int argc, const char * argv[]) {
	uint8_t buf[MAX_MSG_SIZE]; // Input data container for bytes
	size_t size = fread(buf, 1, MAX_MSG_SIZE, stdin);
	if (size == MAX_MSG_SIZE) {
		fprintf(stderr, "message too long for allocated buffer\n");
		return 1;
	}

	Slippi__Start *start = slippi__start__unpack(NULL, size, buf);
	if (!start) {
		fprintf(stderr, "error unpacking incoming message\n");
		return 1;
	}

	printf("%d\n", start->random_seed);
	for (unsigned i = 0; i < start->n_players; i++) {
		Slippi__Start__Player *player = start->players[i];
		printf("%u: %u\n", player->port, player->character);
	}

	slippi__start__free_unpacked(start, NULL);

	return 0;
}
