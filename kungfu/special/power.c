// power.c 天神降世
// Created by Doing Lu 10/7/2K

//#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "天神降世" NOR; }

int perform(object me, string skill)
{
	int count,second;
	int *secondList= ({60,65,70,75,100});


	message_vision(HIY "$N" HIY "双臂一伸一缩，膝部微弯，"
		       "作势欲扑。"NOR"\n", me);
	count = me->query_str();

	if (me->query_temp("special_skill/power", 1))
		return notify_fail("你已经尽力提升自己的战斗力了。\n");

    count = count * (me->query("myspecial/power/level") + 1);
	second = secondList[me->query("myspecial/power/level")];

	//每次施展冷却200秒
	if (time() - me->query_temp("special_skill_time/power") < 200)
	return notify_fail("你刚刚施展过" + "/adm/special_ob/talnet_master"->level_name(me,"power") + "，还需要等一会儿。\n");

	me->set_temp("special_skill_time/power", time());


	me->set_temp("special_skill/power", 1);
	me->add_temp("apply/attack", count);
   	me->start_call_out((: call_other, __FILE__, "remove_effect", me,
			      count :), second);

	return 1;
}

void remove_effect(object me, int count)
{
	me->delete_temp("special_skill/power", 1);
	me->add_temp("apply/attack", -count);
	tell_object(me, "你的" + "/adm/special_ob/talnet_master"->level_name(me,"agile") + "施展完毕，松了一口气。\n");
}

string explain()
{
	return "天神降世可以提升自己的战斗力。";
}