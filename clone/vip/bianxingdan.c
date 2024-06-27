//bianxingdan.c


inherit COMBINED_ITEM;

void do_gender(object player, string gender);

void create()
{
	set_name(HIR"变性丹" NOR, ({ "bianxing dan"}) );
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("base_unit", "颗");
		set("base_unit", "颗");
		set("base_value", 1);
		set("base_weight", 1);
		set("base_value", 1);
		set("channel_id","系统");
		set("no_sell",1);
		set("no_steal",1);
		set("no_shop", 1);
		set("long","一颗红红的丹药，据说"+ZJURL("cmds:fu bianxing dan")+ZJSIZE(22)+HIG
				+"服用"NOR"后可改变自己的性别。"ZJBR+HIR"注意：只能使用一次，且不符合天性的技能会被清除，慎用！"NOR"\n");
		set("yuanbao", 1000);
	}
	set("action_list", ([
		"使用" : "fu bianxing dan",
	]));
	set_amount(1);
	setup();
	
}

void init()
{
	add_action("do_eat", "fu");
}

int do_eat(string arg)
{
	object me = this_player();		
	object ob;		
	string gender, id, id2, msg;
	
	if (me->query("fubianxingdan", 1)) {
		tell_object(me, "你已经使用过一次变性丹了，不可以再使用。\n");
		return 1;
	}
	if (sscanf(arg,"%s %s %s", gender, id, id2) != 3)
	{
		msg = ZJOBLONG +HIR"注意：只能使用一次，且不符合天性的技能会被清除，慎用！"NOR+ZJBR+
			HIY"当前性别："+me->query("gender")+ZJBR+HIG"请选择你的性别："NOR"\n";
		
		msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
		msg += "男性:fu 男性 bianxing dan";
		msg += ZJSEP"女性:fu 女性 bianxing dan";
		msg += ZJSEP"阴阳人:fu 无性 bianxing dan";
		
		write(msg + "\n");
		return 1;
	}
	if (!id(id + " " +id2))
		return 0;	
	
	if( !objectp(ob = present(id + " " +id2, me)) )
		return 0;	
		
	tell_object(me, "你一仰脖，吞下一颗" + name() +"。\n");
	
	do_gender(me, gender);

	return 1;
}

void do_gender(object player, string gender)
{
	if (gender !="男性" && gender !="女性" && gender !="无性") {
		tell_object(player, "没有这种性别！\n");
		return;
	}

	if(player->query("gender") == gender)
	{
		tell_object(player,sprintf("你本来就是%s！\n", gender));
		return;
	}

	player->set("gender", gender);
	tell_object(player,"变性为："+gender+"，成功！\n");
	//检查分配先天后的技能是否符合要求，不符合的删除
	UPDATE_D->check_skill(player);
	player->set("fubianxingdan", time());
	player->save();
	log_file("/cmds/bianxingdan", sprintf("%s %s %s\n", player->name()+"("+player->query("id")+")", "变性="+gender, CHINESE_D->chinese_date(time(), 2)));
	add_amount(-1);
}
