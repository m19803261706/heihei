#include <weapon.h>


inherit CLUB;

void create()
{
	set_name(HIW "镔铁长枪" NOR, ({ "chang qiang", "qiang", "spear"}) );
	set_weight(15000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "支");
		set("value", 300);
		set("material", "silk");
	}
	init_club(10);
	setup();
}

