inherit COMBINED_ITEM;

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIM"小还丹"NOR, ({"xiaohuan dan"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("base_value", 100000);
		set("yuanbao", 20);
        set("no_sell",1);
		set("base_unit", "颗");
		set("long","这是一颗小还丹，"ZJURL("cmds:fu xiaohuan dan")ZJSIZE(22)"服用"NOR"之后能增加100点内力修为！注：可以连续服用，不能超出人物的内力上限。\n");
	}
	setup();
}

void init()
{
    if (environment()==this_player())
    	add_action("do_use","fu");
}

int do_use(string arg)
{
	object me=this_player();
	object ob1;
        int times;

	if (arg!="xiaohuan dan")
      		return notify_fail("你要服用什么？\n");  

    if (me->query("max_neili") > me->query_neili_limit())
      		return notify_fail("你已经不能使用小还丹来提升内力修为了。\n"); 
 
	me->add("max_neili", 100);

    message_vision(me->query("name")+"服下一颗"HIM"小还丹"NOR"，顿觉内力大增！"NOR"\n",me);
	add_amount(-1);
	// 你可以继续服用
	tell_object(me, "你还可以继续"ZJURL("cmds:fu xiaohuan dan")ZJSIZE(22)"服用"NOR"小还丹。\n");
	return 1;
}

