#include <combat.h>
#define TALNET_MASTER "/adm/special_ob/talnet_master"
inherit F_CLEAN_UP;

string display_attr(int gift, int value);
string status_color(int current, int max);
string date_string(int date);
int shuxing(object ob,string arg);

mapping oprank = ([
	"宗师"     : HIW "宗师境界  ",
	"登峰造极" : HIY "★★★★☆",
	"超凡脱俗" : HIY "★★★★  ",
	"臻至化境" : HIR "★★★☆  ",
	"炉火纯青" : HIR "★★★    ",
	"已有大成" : HIC "★★☆    ",
	"非同凡响" : HIC "★★      ",
	"出类拔萃" : HIG "★☆      ",
	"身手不凡" : HIG "★	",
	"已有小成" : HIM "☆	",
]);

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
	object ob;
	mapping my,mci;
	int age,i;
	string line, race,*skill_str;
	

	seteuid(getuid(me));
	if (! arg)
		ob = me;

	else if (wizardp(me))
	{
		ob = present(arg, environment(me));
		if (! ob || ! ob->is_character()) ob = find_player(arg);
		if (! ob || ! ob->is_character()) ob = find_living(arg);
		if (! ob || ! ob->is_character())
			return notify_fail("你要察看谁的状态？\n");
	} else
		return notify_fail("只有巫师能察看别人的状态。\n");

	my = ob->query_entire_dbase();
	mci = my["combat"];
	if (! mci) mci = ([ ]);

	if (playerp(ob) && (! stringp(my["born"]) || ! my["born"]))
		return notify_fail("尚未踏入江湖，何来状态可言？\n");

	if (my["max_jing"] < 1 || my["max_qi"] < 1)
		return notify_fail("无法察看" + ob->name(1) + "的状态。\n");
	line=ZJOBLONG;
	line += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡"NOR"\n";
	line += sprintf( BOLD "  %s" NOR "\n  称号：%s\n",ob->short(1), RANK_D->query_rank(ob));

	if (playerp(ob))
	{
		age = ob->query("age");
		if (ob->query("gender") == "无性")
			race = "阉人";
		else
			race = ob->query("gender");

		line += sprintf("  年龄：%s岁",chinese_number(age));
		if(ob->query("month"))
			line += sprintf("%s月",chinese_number(ob->query("month")));
		line += race + "。\n";
	}
	else
		line += sprintf(WHT "\n  这是一%s%s岁的%s%s。\n",ob->query("unit"),chinese_number(ob->query("age")),ob->query("gender"),ob->query("race"));

	if (mapp(my["family"]))
	{
		if (my["family"]["master_name"])
			line += sprintf("  师父：%s。"NOR"\n",my["family"]["master_name"]);
		else
			line += "  师父：尚未拜师"NOR"\n";
	} else
		line += "\n  师父：尚未拜师"NOR"\n";
	line += sprintf(
		HIY " 【膂力】：[%i]"+HIG" (+%2d)"+GRN" (+"HIM"%2d"GRN")\n"+HIY" 【悟性】：[%i]"+HIG" (+%2d)"+GRN" (+"HIM"%2d"GRN")\n"+HIY" 【根骨】：[%i]"+HIG" (+%2d)"+GRN" (+"HIM"%2d"GRN")\n"+HIY" 【身法】：[%i]"+HIG" (+%2d)"+GRN" (+"HIM"%2d"GRN")"NOR"\n", 
		my["str"],ob->query_str()-my["str"]-ob->query_temp("suit_eff/strength"),ob->query_temp("suit_eff/strength"),
		my["int"],ob->query_int()-my["int"]-ob->query_temp("suit_eff/intelligence"),ob->query_temp("suit_eff/intelligence"),
		my["con"],ob->query_con()-my["con"]-ob->query_temp("suit_eff/constitution"),ob->query_temp("suit_eff/constitution"),
		my["dex"],ob->query_dex()-my["dex"]-ob->query_temp("suit_eff/spirituality"),ob->query_temp("suit_eff/spirituality")
	);

	if (playerp(ob))
	{
		if (my["born_family"] && my["born_family"] != "没有")
		{
			line += HIW "  你出生在" + my["born_family"] +"，天性【" + my["character"]+"】";
		}
		else if (stringp(my["born"]) && my["born"])
		{
			line += HIW "  你是" + my["born"] +"，天性【" + my["character"]+"】";
		}
		else
			line += HIW "  你尚未出生";

		skill_str=keys(ob->query("special_skill"));
		line +=HIG"\n  你的天赋技能有：\n"NOR;
		for(i=0; i<sizeof(skill_str); i++)
		{
			
			line +=HIG" 【"+TALNET_MASTER->level_name(me,skill_str[i])+HIG"】\n";
		}

		if ((int)ob->query("zjvip/times") > 0)
		{
			line += HIY "  你的会员时间："+CHINESE_D->short_time(ob->query("zjvip/times"))+ "。"NOR"\n";
			line += HIY "  会员等级："+ob->query("zjvip/level")+ "级。"NOR"\n";
		}
		line += HIY "  贡献:"+ob->query("zjvip/all_pay")+"，签到经验:"+ob->query("zjvip/sign_exp")+"。"NOR"\n";

		if ((int)ob->query("yuanbao") > 0)
			line += HIY "  你目前的元宝：" + (ob->query("yuanbao")) + "个。"NOR"\n";

		if ((int)ob->query("balance") > 0)
			line += HIY "  你目前的存款：" + MONEY_D->money_str((int)ob->query("balance")) + "。"NOR"\n";
		else
			line += HIY "  你目前没有存款。"NOR"\n";

		if (ob->query("gender") != "无性")
		{
			if (! ob->query("couple/name"))
			{
				if (ob->query("gender") == "女性")
					line += HIC "  你尚未婚配。" NOR;
				else
					line += HIC "  你尚未娶妻。" NOR;
			} else
				line += HIC "  你的伴侣是" + ob->query("couple/name") + "(" +
					ob->query("couple/id") + ")。" NOR;
	
			if (! (int)ob->query("sex/times"))
			{
				if (ob->query("gender") == "女性")
					line += HIG "  还是个处女。" NOR;
				else
					line += HIC "  还是个童男。" NOR;
			} 
			else
			{
				if (ob->query("gender") == "女性")
					line += HIG "  你已非处女之身。" NOR;
				else
					line += HIC "  你已非童子之身。" NOR;
			}

		}
	}

	if (playerp(ob))
	{
		if (! ((int)mci["MKS"] + (int)mci["PKS"]))
		{
			line += HIY "\n  你到目前为止尚未沾染杀戮。" ;
		} else
		{
			line += sprintf(HIR "\n  你到目前为止总共杀生%s次。",chinese_number(mci["MKS"] + mci["PKS"]));
		}
	}

	if ((int)mci["dietimes"])
	{
		line += sprintf(HIR "\n  你总共到黑白无常那里串门%s次。"NOR"\n", chinese_number(mci["dietimes"]));
		line += sprintf(HIR "  上次遇害：%s。"NOR"\n", ob->query("combat/last_die"));
		line += "";
	} else
	if (playerp(ob))

		line += HIC "\n  你到目前为止尚无死亡记录。"NOR"\n";

	while (playerp(ob))
	{
  

		line += HIY "  任督二脉：   " NOR;
		if (my["breakup"])
			line += HIC "○" NOR;
		else
			line += HIR "×" NOR;

		line += HIY "		 元婴出世：   " NOR;
		if (my["animaout"])
			line += HIC "○" NOR;
		else
			line += HIR "×" NOR;

		line += HIY "\n  生死玄关：   " NOR;
		if (ob->query("relife/zhuanshi"))
			line += HIC "○" NOR;
		else
			line += HIR "×" NOR;

		line += HIY "		 转世重生：   " NOR;
		if (ob->query("relife/zhuanshi"))
			line += HIC "○" NOR;
		else
			line += HIR "×" NOR;

		line += ""NOR"\n";
		break;
	}

	while (playerp(ob))
	{
		string op;
		if (ultrap(ob))
		{
			line += HIC "  你现在已经成为武学大宗师。"NOR"\n";
			break;
		}

		line += WHT "  拳脚功夫：  " NOR;
		if (op = ob->query("opinion/unarmed"))
			line += oprank[op] + "	";
		else
			line += CYN "无评价	    ";

		line += NOR WHT " 兵器运用：  " NOR;
		if (op = ob->query("opinion/weapon"))
			line += oprank[op] + "	";
		else
			line += CYN "无评价";

		line += NOR WHT "\n  内家功夫：  " NOR;
		if (op = ob->query("opinion/force"))
			line += oprank[op] + "	";
		else
			line += CYN "无评价	    ";

		line += NOR WHT " 轻身功夫：  " NOR;
		if (op = ob->query("opinion/dodge"))
			line += oprank[op] + "	";
		else
			line += CYN "无评价";

		line += ""NOR"\n";
		break;
	}
	 line += sprintf(WHT "  江湖阅历： " HIC "%7d\t    " NOR, my["score"]);
	 line += sprintf(WHT "  门派贡献： " HIW "%7d"NOR"\n", my["gongxian"]);

	if (playerp(ob))
	{
		line += sprintf(NOR + HIR "  戾    气： " HIW "%7d\t    " NOR, my["total_hatred"]); 
		line += sprintf(WHT "  江湖威望： " HIC "%7d"NOR"\n", my["weiwang"]);
	}

	if (my["shen"] >= 0)
		line += sprintf(WHT "  正    气： " HIY "%7d\t    " NOR, my["shen"]);
	else
		line += sprintf(WHT "  邪    气： " HIR "%7d\t    " NOR, -ob->query("shen"));

	line += sprintf(HIM "  灵    慧： %s%7d"NOR"\n",
			my["magic_points"] < 100 ? HIY : HIM,
		       (my["magic_points"] - my["magic_learned"]));

	line += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡"NOR"\n";
	if (wiz_level(me) > 3) {
		line += HIG "  贡献："+HIM+ob->query("zjvip/all_pay")+NOR"\n";
		if (ob->query("birthday"))
			line += HIG "  注册时间："+CHINESE_D->chinese_date(ob->query("birthday"),2)+NOR+"\n";
		
		line += HIG "  先天属性：总计("+(ob->query("str")+ob->query("int")+ob->query("con")+ob->query("dex"))+")，升级+"+(ob->query("level")/10-ob->query("tianfu_point"))+"、雷劈+"+ob->query("gift/lighting")+"、吃丹+"+(ob->query("str")+ob->query("int")+ob->query("con")+ob->query("dex")-(ob->query("gift/lighting")+80+ob->query("level")/10-ob->query("tianfu_point")))+NOR"\n";
		line += HIW "  吃丹次数：醍醐("+ob->query("gift/xiandan")+")、洗髓("+ob->query("gift/xisuidan")+")、火红("+ob->query("gift/unknowdan")+")、神力("+ob->query("gift/shenliwan")+")"NOR"\n";
		line += HIW "  废丹次数：醍醐("+ob->query("gift/xiandan_fail")+")、洗髓("+ob->query("gift/xisuidan_fail")+")、火红("+ob->query("gift/unknowdan_fail")+")、神力("+ob->query("gift/shenliwan_fail")+")"NOR"\n";
		line += GRN "  隐藏属性：容貌("+ob->query_per()+"/"+ob->query("per")+")、福源("+ob->query("kar")+")"NOR"\n";
	}
	line = replace_string(line,"\n",ZJBR);
	if(line[(strlen(line)-4)..(strlen(line)-1)]=="$br#")
		line = line[0..(strlen(line)-5)];
	line += "\n";
	write(line);
	return 1;
}

string display_attr(int gift, int value)
{
	if (value > gift)
		return sprintf(HIY "%3d" NOR, value);
	else
	if (value < gift)
		return sprintf(CYN "%3d" NOR, value);
	else
		return sprintf("%3d", value);
}

string status_color(int current, int max)
{
	int percent;

	if (max) percent = current * 100 / max;
	else percent = 100;

	if (percent > 100) return HIC;
	if (percent >= 90) return HIG;
	if (percent >= 60) return HIY;
	if (percent >= 30) return YEL;
	if (percent >= 10) return HIR;
	return RED;
}