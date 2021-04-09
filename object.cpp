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
#include "object.h"

void object_delete(object *o)
{
  delete o;
}

int16_t *object_get_pos(object *o)
{
  return o->position;
}

static uint32_t max_object_cells(dungeon *d)
{
  uint32_t i;
  uint32_t sum;

  for (i = sum = 0; i < d->num_rooms; i++) {
    sum += d->rooms[i].size[dim_y] * d->rooms[i].size[dim_x];
  }

  return sum;
}


#define min(x, y) ({   \
  typeof (x) _x = (x); \
  typeof (y) _y = (y); \
  _x < _y ? _x : _y;   \
})

void gen_objects(dungeon *d)
{
  uint32_t i;
  object *m;
  uint32_t room;
  pair_t p;

  d->num_objects = min(d->max_objects, max_object_cells(d));
	uint32_t list_size = d->object_descriptions.size();

  for (i = 0; i < d->num_objects; i++) {
    m = new object;
    //memset(m, 0, sizeof (*m));
		*m = object{};
		
    do {
      room = rand_range(1, d->num_rooms - 1);
      p[dim_y] = rand_range(d->rooms[room].position[dim_y],
                            (d->rooms[room].position[dim_y] +
                             d->rooms[room].size[dim_y] - 1));
      p[dim_x] = rand_range(d->rooms[room].position[dim_x],
                            (d->rooms[room].position[dim_x] +
                             d->rooms[room].size[dim_x] - 1));
    } while (d->object_map[p[dim_y]][p[dim_x]]);
    m->position[dim_y] = p[dim_y];
    m->position[dim_x] = p[dim_x];
    d->object_map[p[dim_y]][p[dim_x]] = m;
		
		uint32_t rand_list = rand() % list_size;
		uint32_t rand_rarity = 100;
		while (rand_rarity >= d->object_descriptions[rand_list].get_rarity()) {
			rand_list = rand() % list_size;
			rand_rarity = rand() % 100;
		}
		
		m->artifact = d->object_descriptions[rand_list].get_artifact();
		m->type = d->object_descriptions[rand_list].get_type();
		m->damage = d->object_descriptions[rand_list].get_damage();
		m->hit = d->object_descriptions[rand_list].get_hit().roll();
		m->dodge = d->object_descriptions[rand_list].get_dodge().roll();
		m->defense = d->object_descriptions[rand_list].get_defence().roll();
		m->weight = d->object_descriptions[rand_list].get_weight().roll();
		m->speed = d->object_descriptions[rand_list].get_speed().roll();
		m->attribute = d->object_descriptions[rand_list].get_attribute().roll();
		m->value = d->object_descriptions[rand_list].get_value().roll();
		m->rarity = d->object_descriptions[rand_list].get_rarity();
		m->color_index = d->object_descriptions[rand_list].get_color();
		m->has_seen = 0;

    d->object_map[p[dim_y]][p[dim_x]] = m;
  }
}

uint32_t dungeon_has_objects(dungeon *d)
{
  return d->num_objects;
}

char object_get_symbol(const object *o)
{
	switch (o->type) {
		case 1:
			return '|';
			break;
		case 2:
			return ')';
			break;
		case 3:
			return '}';
			break;
		case 4:
			return '_';
			break;
		case 5:
			return '[';
			break;
		case 6:
			return ']';
			break;
		case 7:
			return '(';
			break;
		case 8:
			return '{';
			break;
		case 9:
			return '\\';
			break;
		case 10:
			return '\"';
			break;
		case 11:
			return '=';
			break;
		case 12:
			return '~';
			break;
		case 13:
			return '?';
			break;
		case 14:
			return '!';
			break;
		case 15:
			return '$';
			break;
		case 16:
			return '/';
			break;
		case 17:
			return ',';
			break;
		case 18:
			return '-';
			break;
		case 19:
			return '%';
			break;
		case 20:
			return '&';
			break;
		default:
			return '*';
	}
}