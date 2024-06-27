inherit NPC;

void end_fuben(object me);
void xuemo_pfm();
#include "fuben_init_skills.h"

void create()
{
	// 鬼影刺客：这些潜行于暗处的怪物，擅长伏击和快速攻击，他们的身影如同幽灵一般难以捉摸。
// 魔纹石像：古老的石像被邪恶力量赋予了生命，它们的身体上刻有神秘的符文，能够施放强大的攻击。
// 幽魂夜行者：被诅咒的灵魂，只能在夜晚游荡，它们发出的悲鸣声能够迷惑人心，削弱敌人的意志。
// 血煞巨魔：这些巨大的魔物以其强大的物理攻击和再生能力而著称，即使受伤也能迅速恢复。
	mapping name_list = ([
		"鬼影刺客" : "guiying",
		"魔纹石像" : "mowen",
		"幽魂夜行者" : "youhun",
		"血煞巨魔" : "xuesha",
	]);

	mapping desc = ([
		"guiying" : "这些潜行于暗处的怪物，擅长伏击和快速攻击，他们的身影如同幽灵一般难以捉摸。",
		"mowen" : "古老的石像被邪恶力量赋予了生命，它们的身体上刻有神秘的符文，能够施放强大的攻击。",
		"youhun" : "被诅咒的灵魂，只能在夜晚游荡，它们发出的悲鸣声能够迷惑人心，削弱敌人的意志。",
		"xuesha" : "这些巨大的魔物以其强大的物理攻击和再生能力而著称，即使受伤也能迅速恢复。",
	]);

	string *names = keys(name_list);
	string id, desc_str,name;
	name = names[random(sizeof(names))];
	id = name_list[name];
	desc_str = desc[id];
	
	set_name(name, ({id}));
	set("long", desc_str);
	set("combat_exp", 100000);
	set("shen",-10000);
	
	// 重新调整血量-鬼影刺客血量2w，魔纹石像血量3w，幽魂夜行者血量2w，血煞巨魔血量4w
	if (id == "guiying")
	{
		set("max_qi", 20000);
		set("qi", 20000);
	}
	else if (id == "mowen")
	{
		set("max_qi", 30000);
		set("qi", 30000);
	}
	else if (id == "youhun")
	{
		set("max_qi", 20000);
		set("qi", 20000);
	}
	else if (id == "xuesha")
	{
		set("max_qi", 40000);
		set("qi", 40000);
	}
	set("max_neili", 20000);
	set("neili", 20000);
	set("max_jing", 10000);
	set("jing", 10000);
	
	set("chat_chance_combat", 30);//每秒释放技能的概率为30%
	set("chat_msg_combat", ({
		(: xuemo_pfm :),
	}));
	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();
}

void init()
{
    object * player;
    
    if (sizeof(player = filter_array(all_inventory(environment(this_object())), (: userp($1) :))))
    {
        if (sizeof(player))
            kill_ob(player[0]);
    }
}


void die()
{
	object me, who, gift, ob;
	
	me = this_object();
	who = environment(this_object())->query("player");
	
	if (!userp(who))
	{
	    write(query("xuemo") + "出错，请联系管理员处理。\n");
	    ::die();
	}
	
	if (me->query("xuemo") >= 100)
	{
		gift = new("/clone/money/silver");
		gift->set_amount(1000);
		gift->move(who);
		// gift = new("/d/fuben_jiaofei/obj/butian_suipian");
		// gift->set_amount(5);
		// gift->move(who);
		who->add("yuanbao", 10);
		who->add("combat_exp", 1000);
		who->add("potential", 1000);
		tell_object(who, "恭喜你你完成了幽冥幻境挑战，获得了10元宝，1黄金，1000潜能和经验。\n");
		__DIR__"moku"->restore_status(who);
		who->move("/d/city/guangchang");
		::die();
	}
	else
	{
    	init_npc(me, (ob = new(__FILE__)));
    	ob->move(environment(this_object()));
    	
		gift = new("/clone/money/silver");
		gift->set_amount(50);
		gift->move(who);
		who->add("yuanbao", 1);
		who->add("combat_exp", 100);
		who->add("potential", 200);
		tell_object(who, "你击杀了" + query("name") + "获得1元宝，50两银子，100经验和200潜能。\n");
    	::die();
	}
}

void xuemo_pfm()
{
    object who = select_opponent();
	

	// 如果没有目标
	if (!who)
	{
		return;
	}

    if (random(2))
    {
		// 鬼影刺客，发动6连击(鬼影连刺)
		if (query("name") == "鬼影刺客")
		{
			for (int i = 0; i < 6; i++)
			{
				//如果有武器
				if (query_temp("weapon"))
					COMBAT_D->do_attack(this_object(), who, query_temp("weapon"));
				else
					COMBAT_D->do_attack(this_object(), who, 0, 0);
			}

			//xxx释放了
			tell_object(who,"鬼影刺客发动了鬼影连刺！\n");
		}
		// 魔纹雕像石像发动攻击，一次性减少敌方1200-3000血量
		else if (query("name") == "魔纹石像")
		{
			int damage = 1200 + random(1800);
			who->receive_damage("qi", damage, this_object());
			who->receive_wound("qi", damage, this_object());
			tell_object(who, "魔纹石像发动了魔纹撞击，你受到了" + damage + "点伤害！\n");
		}
		// 幽魂夜行者发动攻击，对地方造成2-5秒忙乱
		else if (query("name") == "幽魂夜行者")
		{
			int busy_time = 2 + random(3);
			who->start_busy(busy_time);
			tell_object(who, "幽魂夜行者发动了幽魂悲鸣，你被迷惑了" + busy_time + "秒！\n");
		}
		// 血煞巨魔发动再生，回复自身20-30%的血量
		else if (query("name") == "血煞巨魔")
		{
			int heal = query("max_qi") * (20 + random(10)) / 100;
			add("qi", heal);
			add("eff_qi", heal);
			if (query("qi") > query("max_qi"))
				set("qi", query("max_qi"));
			tell_object(who, "血煞巨魔发动了再生，回复了" + heal + "点血量！\n");
		}
	}
}