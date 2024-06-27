// human.c
#define BASE_WEIGHT 40000

inherit F_DBASE;
inherit F_SKILL;

mapping *combat_action = ({
([      "action":	       "$N挥拳攻击$n的$l",
	"damage_type":  "瘀伤",
]),
([      "action":	       "$N往$n的$l一抓",
	"damage_type":  "抓伤",
]),
([      "action":	       "$N往$n的$l狠狠地踢了一脚",
	"damage_type":  "瘀伤",
]),
([      "action":	       "$N提起拳头往$n的$l捶去",
	"damage_type":  "瘀伤",
]),
([      "action":	       "$N对准$n的$l用力挥出一拳",
	"damage_type":  "瘀伤",
]),
});

void create()
{
	seteuid(getuid());
}

void setup_human(object ob)
{
	mapping my;
	int s;
	int x, y;
	int xflv,level, level_old;
	string xinfa;

	if(xinfa = ob->query_skill_mapped("xinfa"))
		xflv = ob->query_skill(xinfa,1);
	else
		xflv = 0;

	my = ob->query_entire_dbase();

	ob->set_default_action(__FILE__, "query_action");
	if (! stringp(my["unit"])) my["unit"] = "位";
	if (! stringp(my["gender"])) my["gender"] = "男性";
	if (undefinedp(my["can_speak"])) my["can_speak"] = 1;
	if (! stringp(my["attitude"])) my["attitude"] = "peaceful";
	if (! pointerp(my["limbs"])) my["limbs"] = ({
		"头部", "颈部", "胸口", "后心", "左肩", "右肩", "左臂",
		"右臂", "左手", "右手", "腰间", "小腹", "左腿", "右腿",
		"左脚", "右脚"
	});

	if (undefinedp(my["age"])) my["age"] = 14;
	if (undefinedp(my["str"])) my["str"] = 10 + random(21);
	if (undefinedp(my["con"])) my["con"] = 10 + random(21);
	if (undefinedp(my["dex"])) my["dex"] = 10 + random(21);
	if (undefinedp(my["int"])) my["int"] = 10 + random(21);
	if (undefinedp(my["per"])) my["per"] = 10 + random(21);

	//如果是玩家重新分配精神
	if (userp(ob) || undefinedp(my["max_jing"]))
	{
		s = ob->query_int();
		my["max_jing"] = 200;//基础精神200
		if (undefinedp(my["born"]))
		{
			my["max_jing"] = 200;
		}
		else
		{
			//根据年龄重新计算精神。14-40岁之间，每一岁增加10点精神
			if (my["age"] > 14 && my["age"] < 40)
			{
				my["max_jing"] += (my["age"] - 14) * 10;
			}
			else //40岁以上，固定增加200点精神
			{
				my["max_jing"] += 200;
			}
		}

		//每一点悟性增加精神30点
		my["max_jing"] += s * 30;

		//每3点精力增加1点精神
		if ((int)my["max_jingli"] > 0)
			my["max_jing"] += (int)my["max_jingli"] / 3;

		//通脉增加精神3000点
		if (my["breakup"])
			my["max_jing"] += 3000;

		//元婴增加精神3500点
		if (my["animaout"])
			my["max_jing"] += 3500;

		//基础吐纳心法每级增加精神10点
		if (xflv)
		{
			my["max_jing"] += xflv * 10;
		}

		//最大精神上限为10000000
		if(my["max_jing"]>10000000)
			my["max_jing"] = 10000000;
	}

	if (userp(ob) || undefinedp(my["max_qi"]))
	{
		s = ob->query_con() + ob->query_str();
		//基础气血600
		my["max_qi"] = 600;
		if (undefinedp(my["born"]))
		{
			my["max_qi"] = 600;
		}
		{
			//根据年龄重新计算气血。14-40岁之间，每一岁增加20点气血
			if (my["age"] > 14 && my["age"] < 40)
			{
				my["max_qi"] += (my["age"] - 14) * 20;
			}
			else //40岁以上，每一岁固定增加400点气血
			{
				my["max_qi"] += 400;
			}
		}

		//每一点根骨和力量增加气血30点
		my["max_qi"] += s * 30;

		//取消原先的门派加血机制，重新划分加血机制
		//道学心法加气血，每级增加15点
		if (x = (int)ob->query_skill("taoism", 1))
		{
			my["max_qi"] += x * 15;
		}

		//周天功加气血，每级增加15点
		if (x = (int)ob->query_skill("xiantian-gong", 1))
		{
			my["max_qi"] += x * 15;
		}

		//龙象般若功加气血，每级增加15点
		if (x = (int)ob->query_skill("longxiang", 1))
		{
			my["max_qi"] += x * 15;
		}

		//太极神功加气血，每级增加15点
		if (x = (int)ob->query_skill("taiji-shengong", 1))
		{
			my["max_qi"] += x * 15;
		}

		//通脉增加气血5000点
		if (my["breakup"])
		{
			my["max_qi"] += 5000;
		}

		if (ob->query("titlesa/max_qi"))
			my["max_qi"] += my["titlesa/max_qi"];
		if (xflv > 180)
		{
			my["max_qi"] += (xflv-180)*10 + my["max_qi"]*((xflv-180)/5) / 100;
		}

		//最大气血上限为10000000
		if(my["max_qi"]>10000000)
		{
			my["max_qi"] = 10000000;
		}

		//鬼脉削弱30%气血
		if (ob->query("special_skill/ghost"))
		{
			my["max_qi"] = my["max_qi"] * 7 / 10;
		}
	}

	// 为什么要乘以0.7？这是因为背人只需要70%的负重。
	if (! ob->query_weight())
		ob->set_weight((BASE_WEIGHT + (my["str"] - 10) * 2000) * 7 / 10);
	 level_old = ob->query_temp("mark/hubo");
	if ((level = ob->query_skill("zuoyou-hubo", 1)) > 0 && level_old != level)
	 {
		ob->set_temp("mark/hubo",level);
		ob->add_temp("apply/parry", -(level - level_old) / 4);
	 }
}

mapping query_action()
{
	return combat_action[random(sizeof(combat_action))];
}
