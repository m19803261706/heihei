
//#include <ansi.h>
inherit COMBINED_ITEM;
string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIR "十连抽卡片" NOR, ({"ten card"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "这个可以进行十次抽奖的卡片\n");
		set("base_unit", "张");
//		set("no_shop", 1);
		set("no_give", 1);
		set("no_drop", 1);
		set("yuanbao", 500);
		set("base_value", 50000);
		set("base_weight", 1);
		set("action_list",([
			"抽奖":"luckdraw ten",
		]));
	}
	setup();
}
