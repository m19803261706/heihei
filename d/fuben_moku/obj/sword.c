// gangjian.c

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("影剑", ({ "sword" }));
	set_weight(7000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", "无数邪气凝聚而成的一柄剑。\n");
		set("no_get", 1);
		set("material", "邪气");
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
	}
	init_sword(10);
	setup();
}
