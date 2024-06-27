inherit ROOM;

int do_drop(object me, object obj, int raw);

void create()
{
	set("short", "垃圾场");
	set("long", @LONG
垃圾场，可以丢弃无法丢弃的东西。
LONG);
	
	set("exits", ([
	"northeast" : __DIR__"guangchang",
		]));
	setup();
}

void init()
{
	add_action("do_drop_main", "drop");
	add_action("disable", "get");
}

int do_drop_main(string arg)
{
	object obj, *inv, obj2, me;
	int i, amount;
	mixed info;
	string item;
	
	me = this_player();
	if (! arg)
		return notify_fail("你要丢下什么东西？\n");

	if (sscanf(arg, "%d %s", amount, item) == 2)
	{
		if (! objectp(obj = present(item, me)))
			return notify_fail("你身上没有这样东西。\n");

		if (wiz_level(me) < 3 && !(info = obj->query("no_drop")))
		{
			tell_object(me, ( obj->name() + "不能在垃圾场丢弃。\n"));
			return 0;
		}

		if (! obj->query_amount())
			return notify_fail( obj->name() + "不能被分开丢弃。\n");

		if (amount < 1)
			return notify_fail("东西的数量至少是一个。\n");

		if (amount > obj->query_amount())
			return notify_fail("你没有那么多的" + obj->name() + "。\n");
		else if (amount == (int)obj->query_amount())
			return do_drop(me, obj, 0);
		else
		{
			obj->set_amount((int)obj->query_amount() - amount);
			obj2 = new(base_name(obj));
			obj2->set_amount(amount);
			if (! do_drop(me, obj2, 0))
			{
				obj2->move(me);
				return 0;
			}
			return 1;
		}
	}

	if (arg == "all")
	{
			write("你只能一件一件的丢弃！\n");
			return 1;

		inv = all_inventory(me);
		for(amount = 0, i = 0; i < sizeof(inv); i++)
		{
			if (! living(me)) break;
			amount += do_drop(me, inv[i], 1);
		}

		if (! amount)
		{
			write("你什么都没有丢掉。\n");
			return 1;
		}

		message("vision", me->name() + "丢下了一堆东西。\n",
			environment(me), ({ me }));
		write("丢完了。\n");
		return 1;
	}

	if (! objectp(obj = present(arg, me)))
		return notify_fail("你身上没有这样东西。\n");

	do_drop(me, obj, 0);
	return 1;
}

int do_drop(object me, object obj, int raw)
{
	mixed no_drop;
	object riding;

	if (obj == (riding = me->query_temp("is_riding")))
	{
		message_vision("$N从$n背上飞身跳下。\n", me, riding);
		me->delete_temp("is_riding");
		obj->delete_temp("is_rided_by");
		obj->move(environment(me));
		return 1;
	}

	if (!clonep(obj))
	{
		write(obj->query("name")+"化作一道流光消失了！！\n");
		destruct(obj);
		return 1;
	}

	if (wiz_level(me) < 3 && !(obj->query("no_drop")))
		{
			write("这个东西不能在垃圾场丢弃。\n");
			return 0;
		}

	if (no_drop = environment(me)->query("no_drop"))
		return notify_fail(stringp(no_drop) ? no_drop : "这里东西丢弃下去也看不见。\n");

	switch ((string)obj->query("equipped"))
	{
	case "worn":
		tell_object(me, obj->name() + "必须脱下来才能丢掉。\n");
		return 0;

	case "wielded":
		tell_object(me, obj->name() + "必须解除装备才能丢掉。\n");
		return 0;
	}
/*
	if (! obj->is_character() &&
	    ! obj->can_combine_to(environment(me)) &&
	    sizeof(filter_array(all_inventory(environment(me)),
				(: ! $1->is_character() :))) > MAX_ITEM_IN_ROOM)
	{
		tell_object(me, "这里东西太多了，你乱丢恐怕" + obj->name() + "就找不到了。\n");
		return 0;
	}*/
/*
	if (wiz_level(me) < 3 &&  obj->query("no_drop"))
	{
		tell_object(me, "这样东西不能随便丢弃。\n");
		return 0;
	}
*/
	if (obj->move(environment(me)))
	{
		if (obj->is_character() && obj->query_weight() > 20000)
			message_vision("$N将$n从背上放了下来，躺在地上。\n", me, obj);
		else
		{
			if (! raw)
				message_vision(sprintf("$N丢下%s%s$n。\n",
							obj->query_amount()?CHINESE_D->chinese_number(obj->query_amount()):"一",
						       obj->query_amount()?obj->query("base_unit"):obj->query("unit")), me, obj);
			else
				write("你丢下了"+obj->query_amount()?CHINESE_D->chinese_number(obj->query_amount()):"一" 
					+ obj->query_amount()?obj->query("base_unit"):obj->query("unit") +  obj->name() + "\n");
			destruct(obj);
			/*if (! obj->is_character() && ! obj->query("value") && ! obj->value())
			{
				//write("因为这样东西没有具体价值，所以人们并不会注意到它的存在。\n");
                        write(obj->query("name")+"掉地上消失了。\n");
				destruct(obj);
			}*/
		}
		return 1;
	}

	return 0;
}