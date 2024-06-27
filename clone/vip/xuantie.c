// xuantie.c 玄铁石



inherit ITEM;


void create()
{
	set_name(CYN "玄铁石" NOR, ({"xuan tie", "tie"}));
	set_weight(30000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一块黑黝黝有些泛光石头，掂在手中感到极为沉重，远胜铜铁。\n");
		set("spectxt", "制造装备的材料。\n");
		set("value", 3000000);
		set("unit", "块");
		set("weight", 10);
		set("value", 3000000);
        set("no_sell",1);
		set("item_origin", 1);
		set("material_attrib", "steel");
		set("material_name", CYN "玄铁" NOR);
		set("can_make", "all");
		set("not_make", ({ "鞭", "战衣", "锤", "腰带", "裤子" }));
		set("power_point", 70);
	}
	setup();
}
