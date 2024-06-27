// xianglong.c

inherit ITEM;
inherit F_UNIQUE;



void setup()
{
}

void init()
{
	add_action("do_du", "yandu");
}

void create()
{
	set_name(CYN "镇岳锁龙劲秘笈" NOR, ({ "xianglong miji", "book", "miji"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("material", "paper");
		set("no_sell", 1);
		set("no_give", 1);
		set("no_put", 1);
		set("long",
	"乃大侠郭大侠所编写，记载了丐帮的绝学镇岳锁龙劲。\n"
	"为武林至高无上的武学。\n", );
	}
}

int do_du(string arg)
{
	object me = this_player();
	object where = environment(me);
	object ob;
	mapping skill;
	int pxlevel; 

	if (! (arg == "xianglong " || arg == "book" || arg == "miji"))
		return 0;

	if (me->is_busy())
	{
		write("你现在正忙着呢。\n");
		return 1;
	}

	if (me->is_fighting())
	{
		write("你无法在战斗中专心下来研读新知！\n");
		return 1;
	}

	if (! id(arg))
	{
		write("你要读什么？\n");
		return 1;
	}

	if (me->query("family/family_name") !="丐帮")
	{
		write("镇岳锁龙劲乃是我丐帮绝学，不外传。\n");
		return 1;
	}
	if ((int)me->query("str") < 31)
	{
		write("就你这身子骨还练镇岳锁龙劲？小心弄折了胳膊.\n");
		return 1;
	}

	if ((int)me->query("con") < 24)
	{
		write("算了吧，你先天根骨不好，别强学了。\n");
		return 1;
	}

	if ((int)me->query_skill("force") < 150)
	{
		write("你的内功火候不够，无法学习镇岳锁龙劲。\n");
		return 1;
	}

	if ((int)me->query("max_neili") < 1500)
	{
		write("你的内力这么差，怎能融会贯通镇岳锁龙劲？\n");
		return 1;
	}

	if ((int)me->query_skill("strike", 1) < 30)
	{
		write("你的基本掌法火候不够，无法学习镇岳锁龙劲。\n");
		return 1;
	}

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("dragon-strike", 1))
	{
		write("你的基本掌法水平有限，无法领会更高深的镇岳锁龙劲。\n");
		return 1;
	}

	if (! me->query_skill("literate", 1))
	{
		write("你是个文盲，先学点文化(literate)吧。\n");
		return 1;
	}

	if ((me->query("potential") - me->query("learned_points")) < 10)
	{
		write("你的潜能不足。\n");
		return 1;
	}

	message("vision", me->name() + "正专心地研读镇岳锁龙劲秘笈。\n", environment(me), me);

	if ((int)me->query("neili") < 100)
	{
		write("你现在内力不足，无法专心下来研读新知。\n");
		return 1;
	}

	if ((int)me->query("jing") < 100)
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
	    me->force_me("exert regenerate");
		return 1;
	}

	if ((int)me->query("qi") < 100)
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
       	me->force_me("exert recover");
		return 1;
	}

	pxlevel = me->query_skill("dragon-strike", 1);

	if ((int)me->query("combat_exp") < 100000)
	{
		write("你的实战经验不足，无法看懂镇岳锁龙劲秘笈中的内容。\n");
		return 1;
	}

	if (! me->can_improve_skill("dragon-strike"))
	{
		write("你的实战经验不足，无法看懂镇岳锁龙劲秘笈中的内容。\n");
		return 1;
	}

	if (me->query_skill("dragon-strike", 1) > 199)
	{
		write("你研读了一会儿，但是发现秘笈中的内容对"
		      "你而言都太浅了，没有学到任何东西。\n");
		return 1;
	}

	me->receive_damage("qi", 100);
	me->receive_damage("jing", 100);
	me->add("learned_points", 10);
	me->improve_skill("dragon-strike", (1 + random(me->query("str")))*10);
	write("你仔细研读镇岳锁龙劲秘笈，颇有心得。\n");
	return 1;
}

