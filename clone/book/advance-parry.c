// advance_parry.c

inherit ITEM;

void create()
{
	set_name("招架详解", ({ "parry book", "book" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
"封面上写著「招架详解）」\n");
		set("value", 30000);
		set("material", "paper");
		set("skill", ([
			"name": 	"parry",
			"exp_required":	1000,
			"jing_cost":	30,
			"difficulty":	25,
			"max_skill":	49,
			"min_skill":    20,
		]));
	}
}
