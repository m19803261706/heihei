

inherit COMBINED_ITEM;

void create()
{
	set_name(WHT"大补丹"NOR, ({"dabu dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("base_unit", "粒");
		set("base_value", 70);
		set("only_do_effect", 1);
	}
	setup();
	set_amount(1);
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/dan(B)") < 10)
	{
		write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
		return 1;
	}

	my = me->query_entire_dbase();
	if (my["qi"] == my["max_qi"])
	{
		write("你现在体力充沛，无需服用" + name() + "。\n");
		return 1;
	}

	me->set_temp("last_eat/dan(B)", time());

	message_vision(WHT "$N吃下一粒大补丹，感到内息得到了比较大的调整。"NOR"\n", me);
	me->receive_curing("qi", 300);
	me->receive_heal("qi", 300);

	me->start_busy(3);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
