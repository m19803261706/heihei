// agile.c 如鬼似魅
// Created by Doing Lu 10/7/2K

//#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "速行" NOR; }


int perform(object me, string skill)
{
	int count,second;
	int *secondList= ({60,65,70,75,100});

	message_vision(HIC "$N" HIC "脚尖一点，踢起一些尘"
		       "土，整个人顿时如同纸鹞一般飘飘忽忽。"NOR"\n", me);


	count = me->query_dex() * (me->query("myspecial/agile/level") + 1);
	

	if (me->query_temp("special_skill/agile"))
		return notify_fail("你已经在施展" + "/adm/special_ob/talnet_master"->level_name(me,"agile") + "了。\n");

	//每次施展冷却200秒
	if (time() - me->query_temp("special_skill_time/agile") < 200)
		return notify_fail("你刚刚施展过" + "/adm/special_ob/talnet_master"->level_name(me,"agile") + "，还需要等一会儿。\n");

	me->set_temp("special_skill_time/agile", time());
	//持续时间(60/65/70/75/100秒)
	second = secondList[me->query("myspecial/agile/level")];

	me->set_temp("special_skill/agile", 1);
	me->add_temp("apply/dodge", count);
   	me->start_call_out((: call_other, __FILE__, "remove_effect", me,
			      count :), second);

	return 1;
}

void remove_effect(object me, int count)
{
	me->delete_temp("special_skill/agile");
	me->add_temp("apply/dodge", -count);
	tell_object(me, "你的" + "/adm/special_ob/talnet_master"->level_name(me,"agile") + "施展完毕，身形一顿，又慢了下来。\n");
}