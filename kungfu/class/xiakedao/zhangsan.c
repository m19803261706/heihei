// zhangsan.c



inherit NPC;

int is_punisher() { return 1; }

void create()
{
	set_name("张三", ({ "zhang san", "zhang", "san" }));
	set("title", HIY "侠客岛赏善使者" NOR);
	set("gender", "男性");
	set("age", 37);
	set("long",
	      "这是个看起来三十来岁的汉子，身材肥胖，脸色红润。\n"
	);

	set("str", 36);
	set("int", 35);
	set("con", 34);
	set("dex", 37);

	set_temp("apply/armor", 1500);
	set_temp("apply/damage", 800);
	set_temp("apply/unarmed_damage", 800);

	set("qi", 9000);
	set("max_qi", 9000);
	set("jing", 20000);
	set("max_jing", 20000);
	set("neili", 85000);
	set("max_neili", 85000);
	set("jiali", 500);
	set("combat_exp", 50000000);
	set("score", 20000000);

	set_skill("force", 1200);
	set_skill("taixuan-gong", 1200);
	set_skill("dodge", 1200);
	set_skill("taixuan-gong", 1200);
	set_skill("unarmed", 1200);
	set_skill("taixuan-gong", 1200);
	set_skill("parry", 1200);
	set_skill("martial-cognize", 1200);
	set_skill("count", 1200);

	map_skill("force", "taixuan-gong");
	map_skill("dodge", "taixuan-gong");
	map_skill("unarmed", "taixuan-gong");
	map_skill("parry", "taixuan-gong");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: perform_action, "unarmed.taixuan" :),
	}) );
	create_family("侠客岛", 0, "赏善使者");
	setup();

	carry_object("/clone/misc/cloth")->wear();
}

void start_punish(object ob, string msg)
{
	set_temp("punish_ob", ob);
	move(environment(ob));
	message_vision("$N走了过来，冷冷的盯着$n。\n", this_object(), ob);
	command("chat " + ob->name() + "，你" + msg);
	command("chat " + "今天我" + name() + "要为武林除去此害！");
	command("follow " + ob->query("id"));

	if (environment(ob)->query("no_fight"))
	{
		tell_object(ob, "你看着" + name() + "的眼神，心中不禁一寒，转身逃走。\n");
		message("vision", ob->name() + "看到" + name() + "，脸色忽变，转身逃走。\n" +
			name() + "冷笑一声，紧随其后而走。\n",
			environment(ob), ({ ob }));
		ob->move("/d/city/guangchang");
		move("/d/city/guangchang");
		tell_object(ob, HIR "...这...这是哪里？好熟悉啊？"
			    "你心底一横，转过身来，索性不再走了。"NOR"\n");
		message("vision", ob->name() + "慌慌张张的跑了过来，只见有一人"
			"紧随其后而来。\n", environment(ob), ({ ob }));
	}

	kill_ob(ob);
	command("yun powerup");
}

void killed_enemy(object victim)
{
	command("chat 嘿嘿，你也有这一天，这就叫善有善报、恶有恶报，不是不报，时辰未到。");
	victim->delete("combat/need_punish");
}

varargs int receive_damage(string type, int damage, object who)
{
	return ::receive_damage(type, damage / 300, who);
}

varargs int receive_wound(string type, int wound, object who)
{
	return ::receive_wound(type, wound / 300, who);
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->receive_wound("qi", 300 + random(200), me);
	me->set("neili", me->query("max_neili"));
	return HIR "$N" HIR "轻吐一口气，掌力袭来，震得$n"
	       HIR "接连退后几步，闷哼一声。"NOR"\n";
}

void unconcious()
{
	die();
}

void die()
{
	object ob;

	ob = query_temp("punish_ob");
	if (objectp(ob) && ob == query_last_damage_from())
		ob->delete("combat/need_punish");

	command("chat 天哪！想不到我" + name() + "除害不成...反被害除...先回去练功去！");
	message_vision(HIM "$N" HIM "狂吐几口鲜血，扔下一个烟雾弹，"
		       HIM "趁着混乱逃走了。\n", this_object());
	destruct(this_object());
}

void scan()
{
	object ob;

	if (! environment())
	{
		destruct(this_object());
		return;
	}

	if (! objectp(ob = query_temp("punish_ob")) ||
	    environment(ob) != environment() ||
	    environment(ob)->query("no_fight"))
	{
		command("chat 今天我先走了，改日再来玩玩儿！");
		message_vision("$N哈哈大笑，飘然而去。\n", this_object());
		destruct(this_object());
		return;
	}

	if (! is_fighting(ob))
		kill_ob(ob);

	::scan();
}
