// magic-beast.h

/************************************************************
 * 魔幻兽生命周期则分为：卵期、幼生期、成长期、变态期和成熟期。
 * 幼生期：认主，定下魔幻兽属性（金木水火土），时间一个月；
 * 成长期：幻兽会变体附身于主人身上，必须依附主人的能量，主人
 *	 提供的自身能量越多，幻兽成长越快，同时成熟后也越强，
 *	 定幻兽魔力值，时间十个月；
 * 变态期：变态期的幻兽是幻兽一生中最脆弱的时期，这一时期的幻
 *	 兽会依旧成长及依附主人供给的能量，时间一个月；
 * 成熟期：幻兽最后的阶段成熟期就是实用期，可以铠化为防具覆盖
 *	 于主人身上，保护主人。
 * 金的明亮、木的深沉、水的清冷、火的炙热、土的厚实。
 ************************************************************/


#include <name.h>
#include <command.h>
#include <combat.h>

inherit NPC;
inherit F_SAVE;

int is_item_make() { return 1; }
int is_magic_beast() { return 1; }
int is_stay_in_room() { return 1; }

nosave mapping types = ([
	"gold"  : "金的明亮",
	"wood"  : "木的深沉",
	"water" : "水的清冷",
	"fire"  : "火的炙热",
	"soil"  : "土的厚实",
]);

protected string chinese_s(mixed arg)
{
      if (! stringp(arg)) return "无";
      if (arg == "gold")  return HIY "金";
      if (arg == "wood")  return WHT "木";
      if (arg == "water") return HIG "水";
      if (arg == "fire")  return HIR "火";
      if (arg == "soil")  return YEL "土";
}

void create()
{
	set_name("魔幻兽", ({ "luoyun beast" }));
	set("long", "玩家可以带它一起行走江湖。\n");	
	set("race", "野兽");
	set("unit", "只");
	set("str", 30);
	set("int", 30);
	set("spi", 30);
	set("con", 30);
	set("dex", 30);
	set("no_sell", "这你也要卖？你忘记当初与它的血之盟约吗？"); 
	set("owner", "luoyun");
	set("owner_name", "微笑");
	set("limbs", ({ "头部", "身体", "前心", "後背", "尾巴" }) );
	set("verbs", ({ "bite", "hoof" }) );

	set("qi", 3000);
	set("max_qi", 3000);
	set("jing", 1000);
	set("max_jing", 1000);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jingli", 1000);
	set("max_jingli", 1000);
	set("shen_type", 0);
	set("combat_exp", 50000);
	set("attitude", "peaceful"); 
	set("obedience", 2);

	set_temp("apply/attack", 50);
	set_temp("apply/damage", 50);
	set_temp("apply/defence",50);
	set_temp("apply/armor", 50);

	setup();
	if (!clonep()) return 0;

	::restore();
	if(!query("born_time"))
		set("born_time",time());
	keep_heart_beat(); 
}

string long()
{
	string result;
	string level;
	
	result = query("long");

	if (! query("magic/owner"))
	{
		result += HIW "它目前正处于幼生期，丝毫看不出来它的魔力属性。"NOR"\n";
		return result;
	} else
	{
		if (! query("magic/growup"))
			result += HIW "它目前正处于成长期，它的各项魔力属性为："NOR"\n";
		else
		if (! query("magic/become"))
			result += HIW "它目前已处于变态期，它的各项魔力属性为："NOR"\n";
		else
		if (! query("magic/beast"))
			result += HIW "它目前已处于成熟期，它的各项魔力属性为："NOR"\n";
		else
			result += HIW "它目前已是上古神兽，它的各项魔力属性为："NOR"\n";
		
		if (! query("magic/beast"))
			level = query("magic/level") + "级" + query("magic/lvl") + "阶";
		else
		{
			if (query("magic/king1"))
				level = HIY "兽王太始";
			else
			if (query("magic/king2"))
				level = HIY "兽王太初";
			else
				level = HIM "上古神兽";
		}
	}

	result += "-------------------------------------\n";
	result += HIW "幻兽等级：" + level + ""NOR"\n";
	result += HIW "防御能力：" + query("magic/armor") + ""NOR"\n";
	result += HIW "魔力属性：" + chinese_s(query("magic/type")) + ""NOR"\n";
	result += HIW "魔力数值：" + query("magic/power")  + ""NOR"\n";
	result += HIW "契 合 度：" + query("magic/blood") + ""NOR"\n";
	result += "-------------------------------------\n";

	return result;
}

int heal_up()
{
	object env,ob;
	string type;

	if (present("energy stone", this_object()))
		command("eat energy stone");

	if (! (env = environment()) || ! objectp(ob = find_player(query("owner"))))
	{
		save();
		if(env)
			message_vision("$N一闪就不见了。\n", this_object());
		destruct(this_object());
		return 1;
	}

	if (environment(ob) != env)
	{
		message_vision("$N一闪就不见了。\n", this_object());
		move(environment(ob));
	}

	if (query("mud_age") >= 36000 && ! query("magic/owner"))
	{
		if (! query("magic/level"))
			set("magic/level", 1);
		if (! query("magic/lvl"))
			set("magic/lvl", 1);

		if (environment(ob) != env)
			tell_object(ob, HIW "你内心深处隐隐约约的感应到你的魔幻兽(" + name() + HIW ")目前急于认主。"NOR"\n");
		else
		{
			message_sort(HIW "原本温驯的$N" HIW "突凶性大发，狠狠的咬了$n的右手臂一口，而"
				"且还吸了一大口血，吞了下去，然后跳出$n的怀中，发出了怪异的吼声，在怪"
				"叫之后，竟浑身浮出无数的金线，一个飞扑，全身“分解”，包住$n的右手手腕"
				"至手肘处，仅接着又层层脱落，然后扭曲聚合变化，恢复原形。"NOR"\n", this_object(), ob);
			
			tell_object(ob, HIY + name() + HIY "竟在此时认你为主了，且同时进入成长期。"NOR"\n");	
			set("magic/owner", ob->query("id"));		       
			set("magic/armor", 1);
			set("magic/power", 1);
			set("magic/blood", 1);
			set("ridable", 1); // 这个时候才可以做为坐骑的功能
			add("combat_exp",50000);  //有经验

			switch(random(5))
			{
				case 0 : type = "gold"; break;
				case 1 : type = "wood"; break;
				case 2 : type = "water"; break;
				case 3 : type = "fire"; break;
				case 4 : type = "soil"; break;
			}

			set("magic/type", type);
			tell_object(ob, HIY + name() + HIY "附体的刹那，你感觉到一种" + types[type] + "。"NOR"\n");
			save();
		}
	} else
	if (query("mud_age") > 36000 && query("mud_age") <= 396000)
	{
		if (random(10) == 1)   
		tell_object(ob, HIW "你内心深处隐隐感应到你的魔幻兽(" + name() + HIW ")需要你把你的能量灌输（upgrade）给它。"NOR"\n");  
	} else
	if (query("mud_age") > 396000 && query("mud_age") < 432000)  
	{
		if (! query("magic/growup"))
		{
			set("magic/growup", 1);    
			tell_object(ob, HIY + name() + HIY "成功进入变态期，这个时期它比较脆弱，需要你的保护。"NOR"\n");    
		}      

		if (random(10) == 1)   
		tell_object(ob, HIW "你内心深处隐隐感应到你的魔幻兽(" + name() + HIW ")需要你把你的能量灌输（upgrade）给它。"NOR"\n");     
	} else
	if (query("mud_age") >= 432000)
	{
		if (! query("magic/become"))
		{
			set("magic/become", 1);			     
			tell_object(ob, HIY + name() + HIY "成功进入成熟期，终于拥有了铠化的功能。"NOR"\n");     
		}
	}  

	if (!query("last_age_set")) 
		set("last_age_set", time());

	add("mud_age", time() - query("last_age_set"));
	set("last_age_set", time());	       
	set("age", (int)query("mud_age") / 43200);
	
	save();  	

	return 1;
}

void init()
{
	if (this_player()->query("id") == query("owner"))
	{
		add_action("do_modify", "modify");
		add_action("do_teach", "teach");
		add_action("do_shape", "shape");
		add_action("do_upgrade", "upgrade");
		set_leader(this_player());
	}

}

int do_modify(string arg)
{
	string item, msg;
	object me = this_player();
	if(!arg || sscanf(arg,"%s %s",item,msg) != 2)
		return notify_fail("SYNTAX: modify 款项 内容\n");
	if(item == "flee")
	{
		set("env/wimpy", atoi(msg));
		write("ＯＫ\n");
		save();
		return 1;
	}

	if(CHINESE_D->check_control(msg))
		return notify_fail("描述不可有控制符！\n");
	if(CHINESE_D->check_space(msg))
		return notify_fail("描述必需不含空格！\n");
	if(CHINESE_D->check_return(msg))
		return notify_fail("描述必需不含回车键！\n");

	msg = replace_string(msg, "$BLK$", BLK);
	msg = replace_string(msg, "$RED$", RED);
	msg = replace_string(msg, "$GRN$", GRN);
	msg = replace_string(msg, "$YEL$", YEL);
	msg = replace_string(msg, "$BLU$", BLU);
	msg = replace_string(msg, "$MAG$", MAG);
	msg = replace_string(msg, "$CYN$", CYN);
	msg = replace_string(msg, "$WHT$", WHT);
	msg = replace_string(msg, "$HIR$", HIR);
	msg = replace_string(msg, "$HIG$", HIG);
	msg = replace_string(msg, "$HIY$", HIY);
	msg = replace_string(msg, "$HIB$", HIB);
	msg = replace_string(msg, "$HIM$", HIM);
	msg = replace_string(msg, "$HIC$", HIC);
	msg = replace_string(msg, "$HIW$", HIW);
	msg = replace_string(msg, "$NOR$", NOR);
	msg = replace_string(msg, "$S$", BLINK);
	switch(item)
	{
	case "desc":
		if(CHINESE_D->check_length(msg) > 100)
		return notify_fail("描述太长！\n"); 
		set("long",msg+ NOR"\n");
		write("ＯＫ\n");
		save();
		return 1;
	case "nickname" :
		if(CHINESE_D->check_length(msg) > 20)
		return notify_fail("描述太长！\n");
		set("nickname",msg+NOR);
		write("ＯＫ\n");
		save();
		return 1;
	case "title" :
		if(CHINESE_D->check_length(msg) > 20)
		return notify_fail("描述太长！\n");
		set("title",msg+NOR);
		write("ＯＫ\n");
		save();
		return 1;
	case "arrive_msg" :
		if(CHINESE_D->check_length(msg) > 60)
		return notify_fail("描述太长！\n");
		set("arrive_msg",msg+NOR);
		write("ＯＫ\n");
		save();
		return 1;
	case "leave_msg" :
		if(CHINESE_D->check_length(msg) > 60)
		return notify_fail("描述太长！\n");
		set("leave_msg",msg+NOR);
		write("ＯＫ\n");
		save();
		return 1;

	}
	return notify_fail("你要修改什么？\n");

}

int do_teach(string arg)
{
	object me;
	int gin_cost,amount;
	int myskill, itskill;
	me = this_player();
	if(!myskill = me->query_skill(arg,1))
		return notify_fail("这项技能你好象还不会呢！\n");
	if(arg != "unarmed" && arg != "literate" && arg != "dodge")
		return notify_fail("它学不会这项技能的！\n");
	itskill = query_skill(arg,1);
	if(myskill <= itskill)
		return notify_fail(name()+"以嘲笑的目光望着你。\n");
	if((int)me->query("potential")-(int)me->query("learned_points") < 1)
		return notify_fail("你的潜能不够！\n");
	gin_cost = 100/ (int) query_int();
	if((int)me->query("jing") < gin_cost)
		return notify_fail("你显然太累了没有办法教！\n");
	me->receive_damage("jing",gin_cost);
	me->add("potential",-1);
	amount = (int)me->query_int() * (int) query_int();
	message_vision(sprintf("$N不厌其烦地教$n「%s」。\n",to_chinese(arg)),me,this_object());
	if(random(100) < query("obedience") )
		command("emote 很不情愿地哼了一声。");
	else 
	{
		improve_skill(arg,amount);
		message_vision(sprintf("$N似乎真的学会了一些「%s」！\n",to_chinese(arg)),this_object());
	}
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

int do_shape(string arg)
{	
	mapping my;
	string shape;
	int at_pt, pa_pt, do_pt;
	int at_temp,do_temp;
	my = query_entire_dbase();
	printf(HIC"≡"HIY"────────────────────────────"HIC"≡"NOR"\n");
	printf(HIR"〖气血〗%s%6d/%6d %s(%3d%%)"NOR,status_color(my["qi"],my["eff_qi"]),my["qi"],my["eff_qi"],
		status_color(my["eff_qi"],my["max_qi"]),my["eff_qi"]*100/my["max_qi"]);
    printf(HIC" 〖食物〗%s%6d/%6d [%3d%%]"NOR"\n",status_color(my["food"],max_food_capacity()),my["food"], max_food_capacity(),my["food"]*100/max_food_capacity());
    printf(HIR"〖精神〗%s%6d/%6d %s(%3d%%)"NOR,status_color(my["jing"],my["eff_jing"]),my["jing"],
		my["eff_jing"],status_color(my["eff_jing"],my["max_jing"]),my["eff_jing"]*100/my["max_jing"]);
    printf(HIC" 〖饮水〗%s%6d/%6d [%3d%%]"NOR"\n",status_color(my["water"], max_water_capacity()), my["water"], max_water_capacity(),my["water"]*100/max_water_capacity());
      
     //   printf("主人： %s\n", my["owner"]);
     //   printf("经验： %d\t\t杀气： %d\n",my["combat_exp"],my["bellicosity"]);
     //   printf("智慧： %d\t\t体质： %d\n",query_int(), query_con());
     //   printf("体态： %d\t\t力量： %d\n", query_per(), query_str() );
    //    printf("速度： %d\n",query_dex() );
	at_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_ATTACK);
	pa_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_DEFENSE);
	do_pt= COMBAT_D->skill_power(this_object(), "dodge", SKILL_USAGE_DEFENSE);
	at_temp=at_pt+1;
	do_temp=pa_pt/2+do_pt/2+1;
	printf(HIM"〖攻击〗%9s      "NOR,chinese_number(at_temp));
	printf(HIM"      〖防御〗%7s "NOR"\n",chinese_number(do_temp));
	printf(RED"〖主人〗%7s      "NOR,my["owner_name"]);
	printf(RED"	〖杀气〗%6d "NOR"\n",my["bellicosity"]);

      //  printf("攻击： %d\t\t防御： %d\n\n",at_pt+1, pa_pt/2+do_pt/2+1);
	printf(HIC"≡"HIY"────────────────────────────"HIC"≡"NOR"\n");
	return 1;
}

int do_upgrade(string arg)
{
	object me;
	int b_en, b_lv, b_level;
    
	me = this_player();
    
	if (! arg || ! id(arg))
		return notify_fail("你要把你的能量用来做什么？\n");
	
	if (me->is_busy())
		return notify_fail("你正忙着呢。\n");
		
	if (! query("magic/owner"))
		return notify_fail("你的魔幻兽暂时还不需要你的能量。\n");

	if (environment(me) != environment())
		return notify_fail("你的魔幻兽并不和你处于一个房间。\n");

	if (me->query("neili") < me->query("max_neili") * 9 / 10)
		return notify_fail("你现在内力并不充沛，怎敢贸然运用？\n");

	if (me->query("jingli") < me->query("max_jingli") * 9 / 10)
		return notify_fail("你现在精力不济，怎敢贸然运用？\n");

	if (me->query_skill("force") < 200)
		return notify_fail("你的内功根基不够扎实，不能贸然传输给魔幻兽。\n");

	if (me->query("max_neili") < 8000)
		return notify_fail("你尝试运了一下内力，无法顺利运足一个周天，难以施展你的能力。\n");

	if (me->query("max_jingli") < 1000)
		return notify_fail("你试图凝神运用精力，但是感觉尚有欠缺。\n");				
		
	if (me->query("experience") < me->query("learned_experience") + 100) 
		return notify_fail("你现在积累的实战体会还太少，无法把能量灌输魔幻兽！\n");
		
	message_sort(HIR "$N集中精神，手指魔幻兽脊，同时运转丹田内力，经"
		"由奇经八脉源源由体内流出，注入魔幻兽($n" HIR ")体内。"NOR"\n", 
		me, this_object());

	if (me->query("max_neili") < me->query_neili_limit() - 400)
	{
		if (random(2) == 1)
		{
			// 内力未满警告
			message_vision(HIR "$N" HIR "脸色忽然变了变。"NOR"\n",me);
			tell_object(me, HIC "你忽然觉得丹田气息有些错乱。"NOR"\n");
		} else
		{
			message_vision(HIR "$N" HIR "忽然闷哼一声，脸上刹时大汗淋漓！"NOR"\n", me);
			tell_object(me, HIC "你感到可能是你的内力尚未锻炼到极至，结果损伤了你的内功根基。"NOR"\n");
			tell_object(me, HIC "你的基本内功下降了。\n");
			me->set_skill("force", me->query_skill("force", 1) - 10 - random(5));
			return 1;
		}
	}

	me->start_busy(1);
	
	me->add("max_neili", -100);
	me->set("neili", (int)me->query("max_neili"));
	me->add("max_jingli", -100);
	me->set("jingli", (int)me->query("max_jingli"));	
	me->add("learned_experience", 100);
	
	tell_object(me, HIW "你凝神片刻，觉得" + name() + HIW "似乎有了灵性，跳跃不休，不禁微微一笑。"NOR"\n");
	
	if (query("magic/owner") && ! query("magic/growup"))
	{
		add("magic/power", 5);
		add("magic/blood", 1);
		add("magic/armor", 2);
		message_vision(RED "$N的魔幻兽($n" RED ")魔性提升了！"NOR"\n", me, this_object());
		save();
		return 1;
	} else  
	if (query("magic/growup") && ! query("magic/become"))
	{
		add("magic/blood", 1);
		add("magic/armor", 5);
		add("magic/power", 2);  
		message_vision(RED "$N的魔幻兽($n" RED ")魔性提升了！"NOR"\n", me, this_object());
		save();
		return 1; 
	} else
	if (query("magic/become"))
	{
		b_en = (int)query("magic/energy");
		b_en++;
	
		set("magic/energy", b_en);
		add("magic/blood", 1);
		
		b_lv = (int)query("magic/lvl");
		
		if (b_en >= (b_lv * 2))
		{
			b_lv++;
			set("magic/lvl", b_lv);
		
			message_vision(HIY "魔幻兽身忽的一亮，一道金光隐入$N的身体，不见了！"NOR"\n", me);
			message_vision(HIG "$N的魔幻兽的升阶了！"NOR"\n", me);

			add("magic/power", 10);
			add("magic/armor", 10);
			set("magic/energy", 0);
		
			b_lv = (int)query("magic/lvl");
			b_level = (int)query("magic/level");       
			if (b_level <= 9 && b_lv % 9 == 0)
			{
				add("magic/power", 200);
				add("magic/armor", 200);
				add("magic/level", 1);
				set("magic/lvl", 1);
				message_vision(HIY "魔幻兽身忽的泛起红光，无数道紫光隐入$N的身体，不见了！"NOR"\n", me);
				message_vision(HIG "$N的魔幻兽的升级了！"NOR"\n", me);
			}		       

			if (b_level > 9 && ! query("magic/beast"))
			{
				set("magic/beast", 1); 
				add("magic/power", 800);
				add("magic/armor", 800);       
				message_vision(HIY "突然天空出现一道玄光与魔幻兽身泛起的红光相接，魔幻兽全体通红！"NOR"\n", me);  
				CHANNEL_D->do_channel(this_object(), "rumor","听说上古神兽" + name() + HIM + "来到了人间。");
			}

			save();
			return 1;
		}       
		message_vision(RED "$N的魔幻兽($n" RED ")魔性提升了！"NOR"\n", me, this_object());
		save();
		return 1;
	}
}

// 召唤接口
int receive_whistle(object me)
{
	object env;
	int period; 

	if ((env = environment()) && env == me)
	{
		if (me->query_temp("is_changing") && me->query_temp("is_changing") == this_object())
			write(name() + "已经铠化在你的身上了，你召唤个什么劲？\n");
		else
			write(name() + "你不是正骑着吗？你召唤个什么劲？\n");
		return 1;
	}
	if (env == environment(me))
	{
		if (is_fighting())
			remove_all_enemy(1);  
					     
		message_vision(name() + "一闪就不见了。\n", me);
		period = time() - ((int) query("last_save"));
		if (period < 0 || period > 900)
		{
			set("last_save", time());
			save(); 
		}
		me->delete_temp("pet_id");
		destruct(this_object());
		return 1;
	} else
	{
		if (env)
		{
			if (env->is_character() && environment(env))
				env = environment(env);

			message("vision", HIG "突然" + name() + HIG "化作一道光芒，" HIG "瞬间消失了！"NOR"\n", env);

			if (interactive(env = environment()))
			{
				env->delete_temp("is_riding"); 
				delete_temp("is_rided_by");
				tell_object(env, HIM + name() + HIM "忽然离你而去了！"NOR"\n");
			}
		}
		set_skill("dodge",query_skill("dodge",1)*2);  
		message_vision(HIG "$n" HIG "不知从哪里窜到$N" HIG "面前！"NOR"\n", me, this_object());
	}
	set_temp("apply/armor", query("magic/armor"));

	move(environment(me));

	if (environment() != environment(me))
		return 0;

	return 1;
}

// 铠化接口
int receive_change(object me)
{
	object ob;
	object env;

	ob = this_object();

	if (! query("magic/owner"))
		return 0;
		
	if ((env = environment()) && env == me)
	{
		if (me->query_temp("is_changing") &&
		    me->query_temp("is_changing") == ob)
			write(name() + "已经铠化在你的身上了，你还铠化个什么劲？\n");
		else
			write(name() + "你不是正骑着吗？铠化的话，先要从它身上下来。\n");
		return 1;
	}

	set_weight(1); 
	move(me);
	set("no_put", "魔幻兽已经被铠化，无法分开。");
	set("no_give", "魔幻兽已经被铠化，无法分开。");
	set("no_drop", "魔幻兽已经被铠化，无法分开。");
	set("no_steal", "魔幻兽已经被铠化，无法分开。");
	set("no_get", "魔幻兽已经被铠化，无法分开。");	
	set_temp("is_changed_by", me); 
	me->set_temp("is_changing", ob);
	
	if (! query("magic/become"))
	{
		message_sort(HIM "$n" HIM "一声长啸，身上的银光突大盛，竟浑身浮出无"
			     "数的金线，一个飞扑，全身“分解”，包住$N" HIM "的右手手腕至手肘处。"NOR"\n", me, ob);
		return 1;
	}
	me->set_temp("armor/beast", ob);
	me->add_temp("apply/armor", query("magic/armor"));
	message_sort(HIM "$n" HIM "一声长啸，身上的银光突大盛，竟浑身出现了无数的金"
		     "色花纹，瞬间，$n" HIM "立即变形拟态，开始依附到$N" HIM "的身上，$n"
		     HIM "的细胞组织不断的在$N" HIM "身上各部位不停的擩动，慢慢的，每"
		     "一个部分都开始逐渐的成形，形状象由一块块，宛如盔甲连结一起，$N"
		     HIM "整个人几乎是全包在$n" HIM "拟态后的身体中。"NOR"\n", me, ob);
	tell_object(me, sort_msg(HIC "你看见自己的整个身体和右手一样，全身处在一件闪耀金光的厚"
			"实盔甲中，外表看来好似是金属的盔甲，但是你却可以感觉到皮肤摩"
			"裟的感觉，就好似这一层盔甲原本是属于你的一部份，就像你的皮肤"
			"一样，你甚至可以感到四周流过的微风，以及阳光晒在你身上的温热。\n" 
			NOR), me, ob);
	return 1;
}	
	
// 解除铠化
int receive_recover(object me)
{
	object env;

	if (! (env = environment()) || env != me)
		return 0; 
       
	message_sort(HIM "$N身上的魔幻兽细胞层层脱落，由身上分离下来的那一"
		     "层飞离$N约一公尺左右，落在地上，然后在地上开始扭曲聚"
		     "合变化，慢慢的，出现一个你无比熟悉的形体－" + name() + 
		     HIM "。"NOR"\n", me);
       
	tell_object(me, sort_msg(HIC "你感觉到自己的身体被剥下来一层似的，那种感觉"
		"无法形容，不痛不痒，但是去掉一层皮的感觉却是如此的清晰而"
		"深刻。"NOR"\n"));
		
	move(environment(me));
	delete("no_put");
	delete("no_give");
	delete("no_drop");
	delete("no_steal");
	delete("no_get");	       
	delete_temp("is_changed_by"); 
	me->delete_temp("is_changing");   
	
	if (me->query_temp("armor/beast")&&
	    me->query_temp("armor/beast") == this_object())
	{
		me->delete_temp("armor/beast"); 
		me->add_temp("apply/armor", - query("magic/armor"));
	}
	
	if (environment() != environment(me))
		return 0;
		
	return 1;      
}

int accept_object(object me, object ob)
{
	if (me->query("id") == query("owner")) 
	{
		if (ob->query("id") == "energy stone")
		{
			command("eat energy stone");			
			return 1;
		}
	}
	return 0;
}

void die()
{	
	int i;
	object owner, *enemy;
	int jing, qi, exp;

	owner = UPDATE_D->global_find_player(query("owner")); 
	
	if (! objectp(owner)) 
		return ::die();

	if (query_temp("is_changed_by")) 
	{
		delete("no_put");
		delete("no_give");
		delete("no_drop");
		delete("no_steal");
		delete("no_get");	       
		delete_temp("is_changed_by"); 

		if (owner->query_temp("is_changing") && owner->query_temp("is_changing") == this_object()) 
			owner->delete_temp("is_changing");
		
		if (owner->query_temp("armor/beast") && owner->query_temp("armor/beast") == this_object())
		{
			owner->delete_temp("armor/beast"); 
			owner->add_temp("apply/armor", - query("magic/armor"));
		}
	}  

	UPDATE_D->global_destruct_player(owner, 1); 

	exp = (int) query("combat_exp");
	jing = (int) query("max_jing");
	qi = (int) query("max_qi");
	if (! environment()->query("no_death_penalty"))
		set("combat_exp", exp/10 * 9);
	set("eff_qi", qi);
	set("eff_jing", jing);
	set("qi", qi);
	set("jing", jing);

	save();	
	return ::die();
}

void unconcious()
{
	die();
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mixed result; 

	if (! query("magic/owner") || (query("magic/growup") && ! query("magic/become")))
		return 0;

	result = ([ "damage": -query("magic/armor") ]);  

	result += (["msg" :   HIC "$N" HIC "的攻击打在$n" HIC "厚实的护甲上。"NOR"\n" ]); 

	return result; 
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	if (! query("magic/owner") || (query("magic/growup") && ! query("magic/become")))
		return 0;

	ob->receive_wound("qi", 200 + query("magic/power"), me);

	return HIR "$N" HIR "张嘴朝着$n，" HIR "喉咙深处微微闪出光芒，一团约十公分大小的火球，自$N"
			HIR "嘴中射出，飞快的击中$n" HIR "的胸口，$n" HIR "蹬蹬蹬的倒退了几步，跪了下来。"NOR"\n";
}

string query_save_file()
{
	string id;

	if( !clonep() || !stringp(id = query("owner")) ) return 0;

	return sprintf(DATA_DIR"beast/%c/%s/%s", id[0], id, id + query("born_time"));
}
