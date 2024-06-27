inherit NPC;

string *dan_list = ({
	"/clone/gift/unknowdan",
	"/clone/gift/xiandan",
	"/clone/gift/xisuidan",
	"/clone/gift/shenliwan",
	});

	// 机关木人：这些木制的战士由精密的机关控制，虽然动作略显僵硬，但它们的每一次攻击都充满了力量。
	// 机关木人的身上绘有各种阵法图案，这些图案在激活时会发出微光，增强木人的战斗力。
	// 它们通常手持木剑，身着布甲，对于初入江湖的少侠来说，是一个不错的练手对象。

	// 铁甲木人：与机关木人相比，铁甲木人更为强大。
	// 它们的身体由坚硬的木材和铁片制成，行动时发出铿锵的声音。铁甲木人的眼神中没有生气，但它们的每一次挥击都足以让少侠们感受到压力。
	// 这些木人的铁甲上刻有复杂的纹路，似乎蕴含着某种神秘的力量，能够抵御更强的攻击。铁甲木人是木剑砺锋副本中的精英守卫，只有真正掌握了武学精髓的少侠才能击败它们。


mapping name_list = ([
	"机关木人" : "jiguan",
	"铁甲木人" : "tiejia",
]);

mapping desc_list = ([
	"jiguan" : "这些木制的战士由精密的机关控制，虽然动作略显僵硬，但它们的每一次攻击都充满了力量。\n它们通常手持木剑，身着布甲，对于初入江湖的少侠来说，是一个不错的练手对象。",
	"tiejia" : "与机关木人相比，铁甲木人更为强大。\n它们的身体由坚硬的木材和铁片制成，行动时发出铿锵的声音。铁甲木人的眼神中没有生气，但它们的每一次挥击都足以让少侠们感受到压力。\n这些木人的铁甲上刻有复杂的纹路，似乎蕴含着某种神秘的力量，能够抵御更强的攻击。铁甲木人是木剑砺锋副本中的精英守卫，只有真正掌握了武学精髓的少侠才能击败它们。",
]);

// 铁甲的血量是机关的两倍
// 铁甲的技能等级是机关的1.5倍
void create()
{

	string name, id, desc;

	name = keys(name_list)[random(sizeof(name_list))];

	id = name_list[name];

	desc = desc_list[id];

	set_name(name, ({id}));
	set("long", desc);

	set("combat_exp", 100000);
	set("shen",-10000);
	
	// 重新调整血量, 机关木人血量5000，铁甲木人血量10000
	if (id == "jiguan")
	{
		set("max_qi", 5000);
		set("qi", 5000);
	}
	else if (id == "tiejia")
	{
		set("max_qi", 10000);
		set("qi", 10000);
	}
	
	set("qi", 1000);
	set("max_neili", 1000);
	set("neili", 1000);
	set("max_jing", 1000);
	set("jing", 1000);
	set("fuben_caoren", 1);
	         
	set_skill("sword",100);
    set_skill("blade", 100);
    set_skill("whip", 100);
    set_skill("club", 100);
    set_skill("staff", 100);
    set_skill("throwing", 100);

    set_skill("force", 100);
    set_skill("parry", 100);
    set_skill("dodge", 100);

    set_skill("unarmed",100);
    set_skill("cuff", 100);
    set_skill("strike", 100);
    set_skill("finger", 100);
    set_skill("claw", 100);
    set_skill("hand", 100);

	setup();
}


int is_cao() { return 1; }

void die()
{
	object who = this_object()->query_last_damage_from();
	string str;
	object gift;
	int random;
	object *inv;
	str = "你获得了";
	random = random(10);
	if(random < 3)
		gift = new("/u/cx/luck/putao");
	else if(random == 5)
		gift = new("/clone/baiyi/onecard");
	else if(random == 4)
	{
		gift = new(dan_list[random(sizeof(dan_list))]);
	}
	if (objectp(gift)&&objectp(who))
	{
		str += gift->query("name") + "、";
		gift->move(who);
	}
	who->add("combat_exp", 250);
	who->add("potential", 250);
	str += "250经验和潜能。\n";
	tell_object(who, str);

	// 检查当前地图内除了玩家外是否还有其他活物
	inv = all_inventory(environment());

	//过滤掉玩家以后，如果当前地图没有了，开始计算通关时间(不是玩家且，目标对象->is_cao())
	if (sizeof(filter_array(inv, (:$1->is_cao() && living($1):))) == 0)
	{
		int finish_time;
		// 计算通关时间, 通关时间 = 当前时间 - 进入时间(fuben_caoren/last_time)
		finish_time = time() - who->query("fuben_caoren/last_time");

		//通过时间小于3分钟，奖励1w潜能，10元宝
		if (finish_time < 180)
		{
			who->add("potential", 10000);
			who->add("yuanbao", 10);
			tell_object(who, "恭喜你通关时间小于3分钟，获得了10000潜能和10元宝。\n");
		}
		else
		{
			tell_object(who, "通关时间超过3分钟，没有额外奖励。\n");
		}

		//开始检测伤害量,如果返回代表无伤通过
		if (!who->query_time_damage())
		{
			//无伤通关一次性奖励2w潜能
			who->add("potential", 20000);
			tell_object(who, "恭喜你无伤通关，获得了20000潜能。\n");
			who->set_on_damage(0);//副本结束关闭伤害记录
		}
	}


	::die();
}