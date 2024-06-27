// huagu.c


#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "huagu"; }

string chinese_name() { return "化骨掌伤"; }

string update_msg_others()
{
       return HIC "$N" HIC "的身子突然晃了两晃，几乎跌倒。"NOR"\n";
}

string update_msg_self()
{
	return HIR "忽然浑身一阵剧痛，你中的销骨绵掌毒发了！"NOR"\n";
}

string die_reason()
{
	return "筋断骨碎，死的惨不堪言";
}
