inherit ITEM;



void setup()
{}

void init()
{
	add_action("do_du", "du");
	add_action("do_du", "study");
}

void create()
{
	set_name(HIR "《葵阳宝录》" NOR, ({ "kuihua baodian", "baodian", "book", "kuihua"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", HIR "这就是武林第一秘籍《葵阳宝录》，相传是一位宫中太监所作。你可以"
				ZJURL("cmds:study kuihua baodian")+ZJSIZE(22)+"研读"NOR+HIR"看看。"NOR"\n");
		set("value", 1);
		set("material", "paper");
		set("no_put", 1);
		set("no_sell", 1);
	}
}

int do_du(string arg)
{
	object me = this_player();
	object where = environment(me);
	object  obj;
 
	int plvl, con;
	int neili_lost;

	if (! arg || ! id(arg))
		return 0;

	if (me->is_busy())
	{
		write("你现在正忙着呢。\n");
        return 1;
	}

	if (me->is_fighting())
	{
		write("你无法在战斗中专心下来研读新知！\n");
		return 1;
	}

	if (where->query("no_fight"))
	{
		write("你无法在这里静下心来研读宝典。\n");
		return 1;
	}

	if ((string)me->query("gender") == "女性")
	{
		write("自古没有听说女人可以读《葵阳宝录》的。\n");
		return 1;
	}

	if ((string)me->query("gender") == "男性")
	{
	       write("《葵阳宝录》的第一页写着：欲练神功，必先自宫。\n");
	       return 1;
	}

	if (! me->query_skill("literate", 1))
	{
		write("你是个文盲，先学点文化(literate)吧。\n");
		return 1;
	}

	if (me->query_skill("pixie-jian", 1) >= 180)
	{
		write("这本书你已经研究得差不多了，没什么好读的了。\n");
		return 1;
	}

	if ((int)me->query("combat_exp") < 200000)
	{
			write("你的实战经验不足，再怎么读也没用。\n");
			return 1;
	}

	if ((int)me->query("max_neili") < 500)
	{
			write("你的最大内力太低，无法修炼此等神功。\n");
			return 1;
	}

	switch (random(3))
	{
	case 0:
		message("vision", me->name() + "偷偷摸摸翻出"
			"一本书在读。\n", environment(me), me);
		break;
	case 1:
		message("vision", me->name() + "边读书边骚首"
			"弄姿，好象在模仿女人。\n", environment(me), me);
		break;
	case 2:
		message("vision", me->name() + "边读书边把腰"
			"身扭来扭去，甚为诡异。\n", environment(me), me);
		break;
	}

	if ((int)me->query("jing") < 60)
	{
		//如果我拥有qiankun lingbei并且经验少于1000000，自动使用
		if (present("qiankun lingbei",me) && me->query("combat_exp")<1000000)
		{
			me->force_me("use qiankun lingbei");
		}
		else
		if (  present("huxin dan", obj) )
		{
			me->force_me("use huxin dan");
			remove_call_out("do_lian3");
			call_out("do_lian3", 2, me);
			return 1;
		} else {
			write("你现在过于疲倦，等待恢复中...\n");
			remove_call_out("do_lian3");
			call_out("do_lian3", 20, me);
			return 1;
		}
	}

	plvl = me->query_skill("pixie-jian", 1);
	if (plvl > 165) neili_lost = 100; else
	if (plvl > 150) neili_lost = 60;  else
	if (plvl > 120) neili_lost = 40;  else
	if (plvl > 100) neili_lost = 30;  else
	if (plvl > 50)  neili_lost = 20;
		   else neili_lost = 10;

	con = me->query_con();

	if ((int)me->query("neili") < 200  || me->query("jing") < 120)
	{
		if (  present("huxin dan", obj) )
		{
			tell_object(me, ZJFORCECMD("use huxin dan"));
			remove_call_out("do_lian3");
			call_out("do_lian3", 2, me);
			return 1;
		} else {
			write("你状态不佳，等待恢复中...\n");
			remove_call_out("do_lian3");
			call_out("do_lian3", 20, me);
			return 1;
		}
	}

	if (! me->can_improve_skill("pixie-jian", 1))
	{
		write("你的实战经验不足，再怎么读也没用。\n");

		return 1;
	}

	if ((plvl > 10) && (con / 2 + random(con) < 50) && random(100) == 1)
	{
		// 鬼脉之人读《葵阳宝录》不容易走火
		if (me->query("special_skill/ghost") && random(3))
		{
			tell_object(me, HIR "你依照着宝典所示运转内息，突"
					"然内息逆流而上，却不觉得有任何不"
					"妥。"NOR"\n");
		}
		else
		{		
			tell_object(me, HIR "你依照着宝典所示运转内息，突"
					"然只觉内息逆流而上，四肢冰凉，心火如\n"
					"焚，惨嚎一声，晕了过去。"NOR"\n");
			message("vision", HIR + me->name() + "突然惨"
					  "嚎一声，差点晕了过去。"NOR"\n",
				environment(me), ({ me }));
	
			if ((int)me->query("max_neili") > 10)
			{
				me->add("max_neili", -10 - random(10));
			}
		                remove_call_out("do_lian3");
	                        call_out("do_lian3", 2, me);
			//me->unconcious();
			return 1;
		}
	}

	me->receive_damage("jing", 20);
	me->add("neili", -neili_lost);
	me->improve_skill("pixie-jian", 15 + random(45));
	
	// 鬼脉之人学习胜邪剑法更快
	if (me->query("special_skill/ghost"))
	{
		me->improve_skill("pixie-jian", 2 + random(20));
	}

	me->start_busy(random(1) + 1);
	write("你研读《葵阳宝录》，颇有心得。\n");
	remove_call_out("do_lian3");
	call_out("do_lian3", 2, me);
        return 1;
        }

void do_lian3(object me)
{
	if (! objectp(me))
		return;

	// tell_object(me,ZJFORCECMD("du kuihua baodian"));
	me->force_me("du kuihua baodian");

}