inherit COMBINED_ITEM;

void setup()
{
	set_amount(1);
	::setup();
}
void create()
{
	set_name(HIM"回灵丹"NOR, ({"huiling dan"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("base_value", 1);
		set("base_unit", "颗");
		set("base_weight", 1);
		set("base_value", 1);
		//set("no_put", 1);
		//set("no_get", 1);
		set("no_give", 1);
		//set("no_drop", 1);
		set("no_sell", 1);
		//set("no_shop", 1);
		set("no_steal", 1);
		set("no_beg", 1);
		set("base_unit", "颗");
		set("only_do_effect", 1);
		set("long","这是一颗回灵丹，"ZJURL("cmds:fu huiling dan")ZJSIZE(22)"服用"NOR"之后能临时增加1000点内力修为！限20万经验一下使用。\n");
	}
	setup();
}

int do_effect(object me)
{
	object ob1;
    int times;

	if (me->query("combat_exp")>300000)
	{
		tell_object(me,"已超过最大使用经验[30万]，回灵丹自动销毁！\n");
		destruct(this_object());
      	return 1;  
	}

	if (me->query("combat_exp")>200000)
	{
		tell_object(me,"已超过最大使用经验[20万]，不能使用了！\n");
      	return 1;  
	}

	if(time() < (me->query_temp("last_huiling")+3))
      	return notify_fail("你慢点吃，别噎着了。\n"); 
	if (me->query("neili") > 10000) {
		tell_object(me,"你当前内力足够了，慢点用吧。\n");
      	return 1; 
	}
	me->set_temp("last_huiling",time());
	me->add("neili", 1000);

	message_vision(me->query("name")+"服下一颗"HIM"回灵丹"NOR"，顿觉内力大增！"NOR"\n",me);
	add_amount(-1);
	return 1;
}

