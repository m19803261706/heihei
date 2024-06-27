// inherit object: liandan_lin.c

 

inherit ROOM;

int do_cai(string arg);

void init()
{
	add_action("do_cai","cai");
	set("item_desc", ([
		"【草药】" : "看起来好像是一颗小草，走进一看却又有些不同寻常。\n"
		ZJOBACTS2"采药:cai yao\n",
	]));
}

int do_cai(string arg)
{
	object me = this_player();
	object ob;
	object ob1;

	if ((int)me->query_temp("caiyao") < 1)
		return notify_fail("别在这浪费时间了，快走吧。\n");

	if (arg != "yao" && arg != "caoyao")
		return notify_fail("你要采什么。\n");

	if (me->is_busy()) {
	call_out("cai", 3 + random(5), me);
	return 1;
        }
       
	if ((int)me->query("jing") < 40)
		return notify_fail("你太疲倦了，休息一下吧。\n");

	if ((int)me->query("qi") < 40)
		return notify_fail("你太累了，休息一下吧。\n");

	if ((int)me->query_temp("caiyao") == 2) {
		tell_object(me,"是时候回药店了。\n");
		me->move("/d/beijing/huichuntang");
		tell_object(me,ZJFORCECMD("e")+ZJFORCECMD("give cao yao to xiao tong"));
		return 1;
	}

	message_vision("$N趴在地上，瞪大了眼睛在草丛中找寻着药草，生怕漏掉了目标。\n", me);
	call_out("cai", 4 + random(5), me);
	me->start_busy(2);
	return 1;
}
 
int cai(object me)
{ 
	object ob;
	object ob1;

	if (! objectp(me) ||  ! living(me) )
		return 0;

	if ( present("du she", this_object()) || present("du langzhong", this_object()) || me->is_fighting() || environment(me) != this_object() ) {
		call_out("cai", 5 + random(5), me);
		return 1;
	}

	if (random(10) < 4 )
	{
		me->receive_damage("jing", 10 + random(20));
		me->receive_damage("qi", 10 + random(20));
		message_vision(CYN "一番摸索后，草丛中似乎没有$N要找的东西，$N失望的叹了口气。"NOR"\n"
					"$N继续趴在地上，瞪大了眼睛在草丛中找寻着药草，生怕漏掉了目标。"NOR"\n", me);
		call_out("cai", 5 + random(5), me);
		return 1;
	}

	if (random(10) > 8)
	{	 
		tell_room(environment(me), HIR "草丛中一阵晃动，突然钻出一条毒蛇。"NOR"\n");
		ob = new("/d/beijing/npc/liandan_dushe");
		ob->move(this_object());
		ob->kill_ob(me);
		me->kill_ob(ob);
		call_out("cai", 5 + random(5), me);
		return 1;
	} 
	else if (random(10)>8) {	 
		tell_room(environment(me), HIR "林子后面突然跳出一个凶神恶刹的男子，手提一把短刀向你扑来！"NOR"\n");
		ob = new("/d/beijing/npc/liandan_langzhong");
		ob->move(this_object());
		ob->kill_ob(me);
		me->kill_ob(ob);
		call_out("cai", 5 + random(5), me);
		return 1;
	} 
	else { 
		ob1 = new("/d/beijing/npc/dan/caoyao");
		ob1->move(me, 1);
		me->receive_damage("jing", 10 + random(20));
		me->receive_damage("qi", 10 + random(20));
		me->set_temp("caiyao", 2);
		message_sort(HIG "$N" HIG"找了半天，终于发现其中一株草苗与其它的草略有不同，小心翼翼地将它掘了出来。"NOR"\n", me); 
		tell_object(me,"是时候回药店了。\n");
		me->move("/d/beijing/huichuntang");
		tell_object(me,ZJFORCECMD("e")+ZJFORCECMD("give cao yao to xiao tong"));
	}
	return 1;
}

