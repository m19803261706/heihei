// breakup.c



inherit F_CLEAN_UP;

int breaking(object me);
int halt_breaking(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object where, *dan,yao;
	int i;
	string msg, name, dname, xue, bskill, *yang, *yin;

	seteuid(getuid());
	where = environment(me);
	
	if (!arg)
	{
		msg = ZJOBLONG +"请选择试图打通的经脉：\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
		msg += MERIDIAN_D->do_score(me);
		tell_object(me, msg+ "\n");
		return 1;
	}

	yang = ({"sword","blade","whip","staff","throwing","unarmed","strike","cuff","finger","hand","leg"});
	yin = ({"force","dodge","parry"});

	if (! where->query("no_fight") && ! where->query("owner_special"))
		return notify_fail("在这里冲击奇经八脉？不太安全吧？\n");

	if (me->is_busy())
		return notify_fail("你现在正忙着呢。\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("你觉得自己的内功火候还有限，看来需要先锻炼好内功才行。\n");

	if ((int)me->query("qi") * 100 / me->query("max_qi") < 90)
		return notify_fail("你现在的气太少了，无法静心冲脉。\n");

	if ((int)me->query("jing") * 100 / me->query("max_jing") < 90)
		return notify_fail("你现在的精太少了，无法静心冲脉。\n");

	if ((int)me->query("neili") * 100 / me->query("max_neili") < 90)
		return notify_fail("你现在的内力太少了，无法静心冲脉。\n");

	if(sscanf(arg, "%s with %s", name, dname) == 2)
	{
		xue = MERIDIAN_D->get_xue(name,me->query("meridian/" + name));
		if (xue=="")
			return notify_fail("没有可冲击的穴位了。\n");
		if (((name == "阴跷脉"&&!me->query("meridian/dp")) || (name == "阳跷脉"&&!me->query("meridian/ap")))&&(sscanf(dname, "%s for %s", dname, bskill) != 2))
		{
			msg = "请选择你要冲脉加强的技能类型(一经选定暂时不能更改，请慎重选择)：\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
			if(name == "阳跷脉")
				msg += 	"剑法:beat "+arg+" for sword"ZJSEP
					"刀法:beat "+arg+" for blade"ZJSEP
					"鞭法:beat "+arg+" for whip"ZJSEP
					"杖法:beat "+arg+" for staff"ZJSEP
					"暗器:beat "+arg+" for throwing"ZJSEP
					"拳脚:beat "+arg+" for unarmed"ZJSEP
					"掌法:beat "+arg+" for strike"ZJSEP
					"拳法:beat "+arg+" for cuff"ZJSEP
					"指法:beat "+arg+" for finger"ZJSEP
					"手法:beat "+arg+" for hand"ZJSEP
					"腿法:beat "+arg+" for leg";
			else if(name == "阴跷脉")
				msg += 	"轻功:beat "+arg+" for dodge"ZJSEP
					"招架:beat "+arg+" for parry"ZJSEP
					"内功:beat "+arg+" for force";
			tell_object(me, ZJOBLONG +msg+ "\n");
			return 1;
		}
		if (!objectp(yao=present(dname,me))||!yao->query("needle/level"))
			return notify_fail("这东西不能用来辅助冲脉！\n");
		if (yao->query("needle/level")<=me->query("meridian/" + name))
			return notify_fail("丹药品级不够，这样冲脉会有危险的！\n");
		me->set_temp("meridian/xue",xue);
		me->set_temp("meridian/name",name);
		me->set_temp("meridian/dname",dname);
		if(bskill)
		{
			if(name == "阳跷脉" && !me->query("meridian/ap"))
			{
				if(member_array(bskill,yang)==-1)
				{
					tell_object(me, "错误的参数！\n");
					return 1;
				}
				me->set("meridian/ap",bskill);
			}
			else if(name == "阴跷脉" && !me->query("meridian/dp"))
			{
				if(member_array(bskill,yin)==-1)
				{
					tell_object(me, "错误的参数！\n");
					return 1;
				}
				me->set("meridian/dp",bskill);
			}
		}
	}
	else
	{
		msg = MERIDIAN_D->do_score(me,arg);
		if(msg=="")
			return notify_fail("你要冲击什么经脉？\n");
		msg = replace_string(msg,"\n",ZJBR);
		if(msg[(strlen(msg)-4)..(strlen(msg)-1)]=="$br#")
			msg = msg[0..(strlen(msg)-5)];
		dan = filter_array(all_inventory(me),(:$1->query("needle/level")>0:));
		if(sizeof(dan))
		{
			msg += ZJBR"你可以选择辅助丹药进行冲脉：\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
			for(i=0;i<sizeof(dan);i++)
			{
				msg += dan[i]->query("name")+":beat "+arg+" with "+file_name(dan[i]);
				if(i<(sizeof(dan)-1)) msg += ZJSEP;
			}
		}
		else
		{
			msg += ZJBR"你身上现在没有冲脉辅助丹药，不能进行冲脉！";
		}
		tell_object(me, ZJOBLONG +msg+ "\n");
		return 1;
	}

	message_vision("$N盘膝坐下，开始冥神运功，冲击【"+name+"】，试图打通【"+xue+"穴】。\n", me);
	me->start_busy(bind((:call_other, __FILE__, "breaking" :), me),
		       bind((:call_other, __FILE__, "halt_breaking" :), me));
	return 1;
}

int breaking(object me)
{
	string msg,name,dname,xue;

	name = me->query_temp("meridian/name");
	dname = me->query_temp("meridian/dname");
	xue = me->query_temp("meridian/xue");
	if (random(60) < 30)
	{
		tell_object(me, HIR "你觉得内力在丹田源源而生，不断冲击【"+name+"】的【"+xue+"穴】，浑身燥热难当，几欲大声呼喊。"NOR"\n");
		MERIDIAN_D->do_through(me);
		return 0;
	}

	switch (random(5))
	{
	case 0:
		msg = "你默默运转内力，隐隐有些感觉。\n";
		break;

	case 1:
		msg = "你将内力运出丹田，过紫宫、入泥丸、透十二重楼，遍布【"+name+"】，然后收回丹田。\n";
		break;

	case 2:
		msg = "你将内力运经诸穴，抵四肢百骸，然后又回收丹田。\n";
		break;

	case 3:
		msg = "你在丹田中不断积蓄内力，只觉得浑身燥热。\n";
		break;

	default:
		msg = "你缓缓呼吸吐纳，将空气中水露皆收为己用。\n";
		break;
	}

	tell_object(me, msg);
	return 1;
}

int halt_breaking(object me)
{
	CLOSE_D->user_opened(me);
	tell_object(me, "你中止了冲击经脉。\n");
	message_vision(HIY "$N" HIY "轻轻叹了一口气，缓缓的睁开眼。"NOR"\n", me);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : breakup

闭关修行以打通任督二脉，需要非常深厚的内力和内功功底才能做到。
而且会消耗潜能。一旦打通了任督二脉可以同时扩展精、气、精力、
内力的上限。

HELP );
	return 1;
}
