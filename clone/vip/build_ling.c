// build_ling.c


inherit COMBINED_ITEM;
void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIC"建设令牌"NOR, ({"build ling"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "这是一个可以"ZJURL("cmds:crroom")+ZJSIZE(22)"扩建"NOR"场景的令牌。\n");
		set("base_unit", "个");
		set("base_value", 5000000);
            set("no_sell",1);
		set("base_weight", 1);
	}
	set_amount(1);
	setup();
}
