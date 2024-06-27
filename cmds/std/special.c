// special

#include <ansi.h>
#define TALNET_MASTER "/adm/special_ob/talnet_master"
inherit F_CLEAN_UP;
string *initiactiveSpecialList = ({"agile", "hatred", "lun", "power", "self"});

int main(object me, string arg)
{
	string  msg;
	mapping ss;
	string  skill;
	object ob;
	string pro,sname;
	int i;
       
	// if (wizardp(me) && stringp(arg) &&
	//     objectp(ob = find_player(arg)))
	// 	// 查看其他玩家的特殊技能
	// 	arg = 0;
	// else
	ob = me;

	pro = (ob == me) ? "你" : ob->name(1);

	if (! ob->query("born"))
		return notify_fail(pro + "还没有出生呐，会什么特技？\n");

	if (! mapp(ss = ob->query("special_skill")) ||
	    ! sizeof(ss))
		return notify_fail(pro + "现在好像什么特技都不会哦。\n");

	if (arg && (ob == me))
	{

		string skill_name,order;

		if (sscanf(arg, "%s %s", skill_name,order) != 2)
		{
			return notify_fail("格式不正确\n");
		}

		if (order == "use")
		{
			// 有参数，运用特技。
			if (me->is_busy())
			return notify_fail("你现在忙着呢，不能使用特技。\n");


			if (! me->query("special_skill/" + skill_name))
				return notify_fail("你不会这种特技啊！\n");

			if (file_size(SPECIAL_D(skill_name) + ".c") < 0)
				return notify_fail("好像没有这种特技...\n");

			return SPECIAL_D(skill_name)->perform(me, skill_name, arg);
		}

		if (order == "desc")
		{
			msg= HIR "◎"HIY "───────天赋技能─────────" HIR "◎"NOR + ZJBR;
			msg += "天赋名称：" + TALNET_MASTER->level_name(me,skill_name) + ZJBR;
			msg += "天赋介绍：" + TALNET_MASTER->level_desc(me,skill_name) + ZJBR;
			msg+="\n"ZJOBACTS2+ZJMENUF(2,2,10,25);


			if (member_array(skill_name, initiactiveSpecialList) != -1)
			{
				msg += "使用:special "+skill_name + " use" +ZJSEP;
			}
			
			// 返回
			msg += "返回:special\n";

			msg = ZJOBLONG+msg;

			write(msg);
			return 1;
		}


	}

	if (!arg)
	{
		msg= HIR "◎"HIY "───────天赋技能─────────" HIR "◎"NOR"\n";
		msg+=ZJOBACTS2+ZJMENUF(2,2,10,25);
		foreach (skill in keys(ss))
		{
			if (file_size(SPECIAL_D(skill) + ".c") < 0)
			{
				write("不存在技能：" + skill + "\n");
				continue;
			}
			msg += TALNET_MASTER->level_name(me,skill)+"("+skill+")"+":special "+ skill + " desc" + ZJSEP;
		}
		msg += "首次自选:choose_tianfu\n";
			msg = ZJOBLONG+msg;
		msg += "\n";
		write(msg);
	}
	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : special <skill> | <玩家ID>

使用这条命令可以查看你的特技，如果要运用你的特技，则可以加上
参数指名使用什么特技。比如：special hatred，运用杀气。

巫师可以查看其他玩家所会的特殊技能。

HELP );
    return 1;
}
