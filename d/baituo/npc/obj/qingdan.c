// more work needed to use this object to make poison

inherit ITEM;

void create()
{
	set_name("青蛇胆", ({"qing dan", "qing"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "只");
		set("long", "这是一只绿莹莹的青蛇胆。\n");
		set("value", 100);
		set("only_do_effect", 1);
	}

	setup();
}

int do_effect(object me)
{
	message_vision("$N一仰头，吃下了$n。\n", me, this_object());
	me->set_temp("die_reason", "吃了一枚蛇胆，中毒死了");
	me->die();
	destruct(this_object());
	return 1;
}
