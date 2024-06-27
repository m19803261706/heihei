// bamboo_sword.c

#include <weapon.h>

inherit SWORD;

void create()
{
	set_name("竹侍",({ "zhujian", "jian", "sword" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("icon", "05036");
		set("unit", "把");
		set("value", 100);
		set("material", "bamboo");
		set("long", "这是一把练习剑法用的竹侍。\n");
		set("wield_msg", "$N拿出一把$n，握在手中。\n");
		set("unequip_msg", "$N放下手中的$n。\n");
	}
	init_sword(3);
	setup();
}

