// hatred.c 杀气
// Created by Doing Lu 10/7/2K

//#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "杀气" NOR; }

int perform(object me, string skill)
{
	int count,second;
	int *secondList= ({60,65,70,75,100});


	if (me->query_temp("special_skill/hatred", 1))
		return notify_fail("你现在已经是杀气腾腾了。\n");

	message_vision(HIR "$N" HIR "眼中精光闪过，冷冷的扫过"
		       "四周，一股寒意凛然而起。"NOR"\n", me);
	switch (me->query("character"))
	{
	case "光明磊落":
		count = 30;
		break;

	case "心狠手辣":
		count = 42;
		break;

	case "狡黠多变":
		count = 38;
		break;

	case "阴险奸诈":
		count = 48;
		break;
	}

    count = count * (me->query("myspecial/hatred/level") + 1);
	//每次施展冷却200秒
	if (time() - me->query_temp("special_skill_time/hatred") < 200)
		return notify_fail("你刚刚施展过" + "/adm/special_ob/talnet_master"->level_name(me,"hatred") + "，还需要等一会儿。\n");

	me->set_temp("special_skill_time/hatred", time());
	//持续时间(60/65/70/75/100秒)
	second = secondList[me->query("myspecial/hatred/level")];

	me->set_temp("special_skill/hatred", 1);
	me->add_temp("apply/damage", count);
	me->add_temp("apply/unarmed_damage", count);
   	me->start_call_out((: call_other, __FILE__, "remove_effect", me,count :),second );

	return 1;
}

void remove_effect(object me, int count)
{
	me->delete_temp("special_skill/hatred");
	me->add_temp("apply/damage", -count);
	me->add_temp("apply/unarmed_damage", -count);
	tell_object(me, "你的" + "/adm/special_ob/talnet_master"->level_name(me,"agile") + "施展完毕,气息沉稳下来。\n");
}

string explain()
{
	return "杀气是一种心理状态，可以提高自己的攻击力。";
}