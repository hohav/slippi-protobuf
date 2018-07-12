#include <stdio.h>
#include <stdlib.h>
#include "slippi.pb-c.h"

#define PLAYER_COUNT 2

#define sset(a, b, c) do { (a).has_ ## b = 1; (a).b = (c); } while (0)
#define pset(a, b, c) do { (a)->has_ ## b = 1; (a)->b = (c); } while (0)

int main (int argc, const char * argv[]) {
	Slippi__Start__Player **players = malloc(PLAYER_COUNT * sizeof (Slippi__Start__Player*));
	for (unsigned i = 0; i < PLAYER_COUNT; i++) {
		Slippi__Start__Player *player = malloc(sizeof (Slippi__Start__Player));
		slippi__start__player__init(player);
		pset(player, port, i);
		pset(player, type, SLIPPI__START__PLAYER__TYPE__HUMAN);
		pset(player, character, SLIPPI__START__PLAYER__CSS_CHARACTER__MARTH);
		pset(player, stocks, 4);
		pset(player, costume, 0);
		players[i] = player;
	}

	Slippi__Start start = SLIPPI__START__INIT;
	sset(start, is_teams, 1);
	sset(start, stage, SLIPPI__STAGE__FOUNTAIN_OF_DREAMS);
	sset(start, random_seed, 12345);
	start.n_players = PLAYER_COUNT; start.players = players;

	unsigned len = slippi__start__get_packed_size(&start);
	void *buf = malloc(len);
	slippi__start__pack(&start, buf);

	fprintf(stderr,"Writing %d serialized bytes\n", len); // See the length of message
	fwrite(buf, len, 1, stdout); // Write to stdout to allow direct command line piping

	free(buf); // Free the allocated serialized buffer
	return 0;
}
