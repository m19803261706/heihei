// summon. 取回兵器


#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
	object ob;
	string file;

	if (! str)
		return notify_fail("你要召唤什么物品？\n");

	if (me->is_busy())
		return notify_fail("你现在正忙，等你有空了再说吧。\n");

	sscanf(str, ".%s", str);

	if (! stringp(file = me->query("can_summon/" + str)))
		return notify_fail("你不知道如何召唤这个物品。\n");

	if (file_size(file + ".c") < 0 && file_size(file) < 0)
		return notify_fail("你不知道如何召唤这个物品。\n");

	if (me->is_ghost())
		return notify_fail("等你还了阳再召唤吧。\n");

	call_other(file, "???");
	ob = find_object(file);
	if (! ob || ! ob->receive_summon(me))
	{
		message_vision(HIM "$N" HIM "扬起手来，口中念念有词。\n然而什么也没有发生 :)\n", me);
	}

	if (me->is_fighting())
		me->start_busy(2 + random(3));

	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : summon <物品的ID>

此指令可让你把某些物品呼唤过来并装备上，当然你得有一定的
精力施展仙术才行。
HELP );
	return 1;
}
