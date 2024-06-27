 
#include <combat.h>
inherit F_CLEAN_UP;
string status_color(int current, int max);
int potential_lv(int exp);
int main(object me, string arg)
{
	object ob;
	int craze;
	mapping my;
 string str;
 
 
	
	seteuid(getuid());
	if(!arg) ob = me;
	else if (wizardp(me)) 
	{ 
	     ob = present(arg, environment(me));
	     if (!ob) ob = find_player(arg);
	     if (!ob) ob = find_living(arg);
	     if (!ob) return notify_fail("您要察看谁的状态？\n");
	} 
	else return notify_fail("只有巫师才可以察看别人的状态。\n");
	
	my = ob->query_entire_dbase();

	if (my["max_jing"] < 1 || my["max_qi"] < 1)
		return notify_fail("无法察看" + ob->name(1) + "的状态。\n");

	str = ZJOBLONG;
	str += sprintf("姓名：%s ("HIG"%s"NOR") "NOR,ob->name(),capitalize(ob->query("id")));
	str += (HIY"	Level : "+HIG+ob->query("level")+NOR"\n");
	str += sprintf("一一一一一一一一一一一一一一一一一一一一\n");
	str += sprintf(HIR"〖气血〗：%s%d/%d%s(%d%%)\n"NOR,status_color(my["qi"],my["eff_qi"]),my["qi"],my["eff_qi"],
		status_color(my["eff_qi"],my["max_qi"]),my["eff_qi"]*100/(my["max_qi"]+ob->query_gain_qi()));
	
	str += sprintf(HIR"〖内力〗：%s%d/%d(+%d)"NOR"\n",status_color(my["neili"], my["max_neili"]), my["neili"], my["max_neili"],my["jiali"]);
   
	str += sprintf(HIR"〖精神〗：%s%d/%d%s(%d%%)\n"NOR,status_color(my["jing"],my["eff_jing"]),my["jing"],
		my["eff_jing"],status_color(my["eff_jing"],my["max_jing"]),my["eff_jing"]*100/my["max_jing"]);
	str += sprintf(HIR"〖精力〗：%s%d/%d(+%d)"NOR"\n",status_color(my["jingli"],my["max_jingli"]),
		 my["jingli"],my["max_jingli"],my["jiajing"]);
	str += sprintf(CYN"〖食物〗：%s%d/%d[%d%%]\n"NOR,status_color(my["food"], ob->max_food_capacity()),
		my["food"], ob->max_food_capacity(),my["food"]*100/ob->max_food_capacity());
	str += sprintf(CYN"〖饮水〗：%s%d/%d[%d%%]\n"NOR,status_color(my["water"], ob->max_water_capacity()),
		my["water"], ob->max_water_capacity(),my["water"]*100/ob->max_water_capacity());
	str += sprintf(CYN"〖潜能〗：%s%d/%d(max)"NOR"\n",HIY,(int)ob->query("potential") - (int)ob->query("learned_points"),(int)ob->query_potential_limit() - (int)ob->query("learned_points"));
	str += sprintf(CYN"〖经验〗：%s%d/%d(up)"NOR"\n",HIM,my["combat_exp"],F_LEVEL->level_max_exp(ob));
	str += sprintf("一一一一一一一一一一一一一一一一一一一一\n");
	
	if (craze = ob->query_craze())
	{
		if (ob->is_most_craze())
		{ 
			str += (HIR"【愤　"+HIY"　怒"+NOR+HIR"】"+NOR);
			str += sprintf("%s", ob->query("character") == "光明磊落" ? MAG"  竖发冲冠  ( burning 燃烧怒气 )"+NOR+"\n"
										    : HIM"  怒火中烧  ( burning 燃烧怒气 )"+NOR+"\n");
		}
		else
		{
			str += sprintf(HIR "【愤　　怒】：%d/%d(+%d)\n",craze, ob->query_max_craze(),
				      ob->query("jianu"));
		}
	} 
      else
	{
		 str += sprintf(MAG "【心平气和】：一一一一一一一一一一一\n"+NOR);
	}
     
	 
	str += sprintf(MAG "【实战体会】：%s%d/%d\n【内精极限】：%s%d/%d"NOR"\n",
		HIM,my["experience"] - my["learned_experience"],ob->query_experience_limit() - my["learned_experience"] ,HIM,ob->query_neili_limit(),ob->query_jingli_limit());
  	 
     
	str += sprintf("一一一一一一一一一一一一一一一一一一一一\n");
	str += sprintf(HIG"★"HIY"天赋点"NOR"/"HIM"技能点"HIG"★( "HIY+ob->query("tianfu_point")+NOR"/"HIM+ob->query("skill_point")+NOR+HIG" )"NOR"\n");

	str = replace_string(str,"\n",ZJBR);
	if(str[(strlen(str)-4)..(strlen(str)-1)]=="$br#")
		str = str[0..(strlen(str)-5)];
	str += "\n";
	message("vision", str, me);
	return 1;
}
string status_color(int current, int max)
{
	int percent;
	if( max>0 ) percent = current * 100 / max;
	else percent = 100;
	if( percent > 100 ) return HIC;
	if( percent >= 90 ) return HIG;
	if( percent >= 60 ) return HIY;
	if( percent >= 30 ) return YEL;
	if( percent >= 10 ) return HIR;
	return RED;
}
int potential_lv(int level)
{
	int grade;
	grade =level/5+1;
	return grade;
}
