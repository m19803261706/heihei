// zhongling.c

inherit NPC;

void create()
{
	set_name("种铃", ({ "zhong ling","zhong" }) );
	set("gender", "女性" );
	set("age", 15);
	set("str", 16);
	set("con", 24);
	set("dex", 11);
	set("per", 27);
	set("int", 24);

	set("chat_chance", 1);
	set("chat_msg", ({
		"种铃自言自语道：“要是我的闪电貂在这儿就好了。”\n",
	}) );

	set("inquiry", ([
		"段羽" : "段哥哥呢？他在哪儿？",
		"种铃" : "我就是种铃啊。",
		"甘葆葆" : "甘葆葆是我妈。",
		"钟忘愁" : "钟忘愁是我爹。",
		"here" : "这里是万劫谷。",
		"沐婠清" : "沐婠清被关在后面的石屋里，快去救她！",
	]));

	set("attitude", "friendly");

	set("max_neili", 200);
	set("neili", 200);
	set("force_factor", 10);

	set("combat_exp", 3500);

	set_skill("finger", 60);
	set_skill("parry", 40);
	set_skill("dodge", 50);
	set_skill("sword", 30);
	set_skill("force", 50);
	set_skill("sun-finger",40);

	map_skill("finger", "sun-finger");
	map_skill("parry", "sun-finger");

	setup();

	carry_object("/d/wanjiegu/npc/obj/moon-dress")->wear();
	carry_object("/d/wanjiegu/npc/obj/shoes")->wear();
	carry_object("/d/wanjiegu/npc/obj/xiu-scarf")->wear();
}

void init()
{
	object ob;
	::init();
	if( interactive(ob = this_player()) ) {
	message_vision("种铃对$N说道：快去救木姐姐，木姐姐被关在后面的石屋里！\n",ob);
	}
}

int accept_object(object who, object ob)
{
	object *inv, sh;
	int i;

	inv = all_inventory(this_object());

	if (ob->name() == "闪电貂") {
	    tell_object(who,"种铃说道：谢谢你帮我找回了闪电貂！\n");
	    tell_object(who,"种铃说道：下次你见到段羽时，告诉他我已经回家了。\n");
	    if(!sizeof(inv) )
		for ( i=0; i< sizeof(inv); i++ )
		    if ( inv[i]->name() == "绣花鞋" ) {
			destruct(inv[i]);
			tell_object("who, 种铃脱下一双绣花鞋。\n");
			sh = new("/t/wanjiegu/npc/obj/shoes2");
			tell_object(who, "种铃说道：这是我的一双绣花鞋，请你带给段羽。\n");
			sh->move(who);
			return 1;
		    }
	    return 1;
	}
	return 0;
}

void die()
{
	object killer;

	if (objectp(killer = query_last_damage_from()))
		killer->set_temp("marks/murder_zhongling", 1);

	::die();
}

