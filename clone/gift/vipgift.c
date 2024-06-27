


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
	set_name("开站大礼包", ({"new gift2"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "指文游－终极地狱正式开站大礼包，感谢大家对游戏的支持，祝您游戏愉快！\n");
		set("base_unit", "个");
		set("base_weight", 1);
		set("base_value", 1000);
		set("no_put", 1);
		set("no_get", 1);
		set("no_give", 1);
		set("no_drop", 1);
		set("no_sell", 1);
		set("no_steal", 1);
		set("no_beg", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	int i;
	mapping gifts;
	string *list;
	object obj;

	gifts = ([
		"/clone/money/cash":5,
	]);

	list = keys(gifts);

	if (me->is_busy())
		return notify_fail("你正忙着呢。\n");

	if (me->is_fighting())
		return notify_fail("战斗中，不能使用"+ name() +"。\n");

	if (me->query("vipgift_box_times"))
		return notify_fail("已经使用过了，不能使用"+ name() +"。\n");
	
	message_vision("$N打开了一" + query("base_unit") + name() + "。\n", me);
	
	me->add("yuanbao", 500);
	me->add("vipgift_box_times",1);
	
	log_file("gift_all/vipgift", me->query("name")+"("+me->query("id")+")第"
				+me->query("vipgift_box_times")+"次打开了"+this_object()->short()+"   "+ctime(time())+"。\n");
	for(i=0;i<sizeof(list);i++)
	{
		obj = new(list[i]);
		if(obj->query_amount())
			obj->set_amount(gifts[list[i]]);
		tell_object(me, HIR"你发现了"+NOR+obj->short()+NOR"。\n");
		obj->move(me);
	}
	tell_object(me, HIY"恭喜你！你获得了500元宝。"NOR+HIG"指文游全体管理祝你游戏愉快！"NOR"\n");
	add_amount(-1);

	return 1;

}
