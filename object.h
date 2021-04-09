#ifndef OBJECT_H
# define OBJECT_H

# include "dims.h"
# include "character.h"
# include "descriptions.h"
# include "dice.h"

class object {
	public:
		object_type_t type;
		dice damage;
		int32_t hit, dodge, defense, weight, speed, attribute, value, rarity;
		bool artifact;
		uint32_t color_index;
		pair_t position;
};

void object_delete(object *o);
int16_t *object_get_pos(object *o);
void gen_objects(dungeon *d);
//void object_delete(npc *n);
uint32_t dungeon_has_objects(dungeon *d);
char object_get_symbol(const object *o);

#endif
