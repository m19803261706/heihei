

inherit COMBINED_ITEM;

void create()
{
	set_name(HIW"大云丹"NOR, ({"dayun dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("base_unit", "粒");
		set("base_value", 60);
		set("only_do_effect", 1);
	}
	setup();
	set_amount(1);
}

int do_effect(object me)
{
	mapping my;
	int jl, mj;

	if (time() - me->query_temp("last_eat/dan(C)") < 180)
	{
		write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
		return 1;
	}

	my = me->query_entire_dbase();
	jl = (int)me->query("jingli") + 150;
	mj = (int)me->query("max_jingli") * 2;

	if (jl > mj)
	{
		write("你现在精力修为无需服用" + name() + "。\n");
		return 1;
	}

	me->set_temp("last_eat/dan(C)", time());

	message_vision(HIW "$N吃下一粒大云丹，精神随之一震，精力有所提高。"NOR"\n", me);
	me->add("jingli", 150);

	me->start_busy(3);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
