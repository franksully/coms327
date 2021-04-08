#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "npc.h"
#include "dungeon.h"
#include "character.h"
#include "move.h"
#include "path.h"
#include "event.h"
#include "pc.h"

static uint32_t max_monster_cells(dungeon *d)
{
  uint32_t i;
  uint32_t sum;

  for (i = sum = 0; i < d->num_rooms; i++) {
    if (!pc_in_room(d, i)) {
      sum += d->rooms[i].size[dim_y] * d->rooms[i].size[dim_x];
    }
  }

  return sum;
}

#define min(x, y) ({   \
  typeof (x) _x = (x); \
  typeof (y) _y = (y); \
  _x < _y ? _x : _y;   \
})

void gen_monsters(dungeon *d)
{
  uint32_t i;
  npc *m;
  uint32_t room;
  pair_t p;

  d->num_monsters = min(d->max_monsters, max_monster_cells(d));
	uint32_t list_size = d->monster_descriptions.size();

  for (i = 0; i < d->num_monsters; i++) {
    m = new npc;
    //memset(m, 0, sizeof (*m));
		*m = npc{};
    
		for (uint32_t i = 0; i < list_size; i++) {
			d->monster_descriptions[i].unique_spawn = 0;
		}
		
    do {
      room = rand_range(1, d->num_rooms - 1);
      p[dim_y] = rand_range(d->rooms[room].position[dim_y],
                            (d->rooms[room].position[dim_y] +
                             d->rooms[room].size[dim_y] - 1));
      p[dim_x] = rand_range(d->rooms[room].position[dim_x],
                            (d->rooms[room].position[dim_x] +
                             d->rooms[room].size[dim_x] - 1));
    } while (d->character_map[p[dim_y]][p[dim_x]]);
    m->position[dim_y] = p[dim_y];
    m->position[dim_x] = p[dim_x];
    d->character_map[p[dim_y]][p[dim_x]] = m;
		
		uint32_t rand_list = rand() % list_size;
		uint32_t rand_rarity = 100;
		while ((rand_rarity >= d->monster_descriptions[rand_list].rarity) && (!d->monster_descriptions[rand_list].unique_spawn)) {
			rand_list = rand() % list_size;
			rand_rarity = rand() % 100;
		}
		
		m->hp = d->monster_descriptions[rand_list].hitpoints.roll();
    m->speed = d->monster_descriptions[rand_list].speed.roll();
		m->damage = d->monster_descriptions[rand_list].damage;
    m->alive = 1;
    m->sequence_number = ++d->character_sequence_number;
    m->characteristics = d->monster_descriptions[rand_list].abilities;
		m->color_index = d->monster_descriptions[rand_list].color[0];
		m->list_index = rand_list;
    /*    m->npc->characteristics = 0xf;*/
    m->symbol = d->monster_descriptions[rand_list].symbol;
    m->have_seen_pc = 0;
    m->kills[kill_direct] = m->kills[kill_avenged] = 0;
		
		if (m->characteristics & NPC_UNIQ) {
			d->monster_descriptions[rand_list].unique_spawn = 1;
		}

    d->character_map[p[dim_y]][p[dim_x]] = m;

    heap_insert(&d->events, new_event(d, event_character_turn, m, 0));
  }
}

uint32_t dungeon_has_npcs(dungeon *d)
{
  return d->num_monsters;
}
