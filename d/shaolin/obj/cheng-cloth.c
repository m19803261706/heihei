// cheng-cloth.c
//

#include <armor.h>

inherit CLOTH;

void create()
{
	set_name("金边黑布袈裟", ({ "jia sha", "cloth" }) );
	set_weight(5000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("material", "cloth");
		set("armor_prop/armor", 10);
	}
	setup();
}

