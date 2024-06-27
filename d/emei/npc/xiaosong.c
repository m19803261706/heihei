// xiaosong.c 宋轻舒

inherit NPC;

mixed ask_for_song();
mixed ask_for_zhou();
mixed ask_for_emei();

void create()
{
	set_name("宋轻舒", ({ "song qingshu", "song" }));
	set("long",
		"他就是宋缘乔的儿子宋轻舒。\n"
		"他今年二十岁，乃是武当第三代中出类拔萃的人物。\n");
	set("gender", "男性");
	set("age", 20);
	set("attitude", "aggressive");
	set("shen_type", 0);
	set("shen", -100000);
	set("str", 25);
	set("int", 28);
	set("con", 25);
	set("dex", 25);
	set("inquiry",([
		"宋夫人"  : (: ask_for_song :),
		"周姑娘"  : (: ask_for_zhou :),
		"掌门人"  : (: ask_for_emei :),
		"宋缘乔"  : "我爹做不成武当掌门了，哈哈。我却可以做峨嵋掌门的老公，哈哈哈！",
	]));
	set("max_qi", 1000);
	set("max_jing", 500);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 30);
	set("combat_exp", 80000);
	set("score", 10000);

	set_skill("force", 60);
	set_skill("taiji-shengong", 40);
	set_skill("dodge", 70);
	set_skill("tiyunzong", 40);
	set_skill("unarmed", 70);
	set_skill("taiji-quan", 50);
	set_skill("parry", 70);
	set_skill("sword", 70);
	set_skill("taiji-jian", 50);
	set_skill("liangyi-jian", 60);
	set_skill("taoism", 30);
	set_skill("literate", 40);

	map_skill("force", "taiji-shengong");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "liangyi-jian");

	create_family("武当派", 3, "弟子");

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/city/obj/cloth")->wear();
}

mixed ask_for_zhou()
{
	object ob;
	ob = this_player();
	command("heng");
	command("say " + ob->query("name") + "！你是什么东西？敢直呼芷若的名字？你找死！\n");
	kill_ob(this_player());
	return -1;
}

mixed ask_for_song()
{
	object ob;

	if (! stringp(query("startroom")) ||
	    find_object(query("startroom")) != environment())
		return "...";

	ob = this_player();
	command("say " + ob->query("name") + "，内子正在里面，你找她去吧！\n");
	message_vision("宋轻舒酸溜溜地看着$N走进寝宫。\n\n",ob);
	ob->move("/d/emei/qinggong");
	return -1;
}

mixed ask_for_emei()
{
	object ob;

	if (! stringp(query("startroom")) ||
	    find_object(query("startroom")) != environment())
		return "@@@";

	ob = this_player();
	ob->set_temp("marks/宋夫人",1);
	command("say " + ob->query("name") + "，内子脾气不好，你自己保重吧！\n");
	message_vision("宋轻舒不怀好意地看着$N走进寝宫。\n\n",ob);
	ob->move("/d/emei/qinggong");
	return -1;
}
