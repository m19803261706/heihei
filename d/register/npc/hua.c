// hua

inherit NPC;

void greeting(object me);

void create()
{
	set_name("花中平", ({ "hua tiegan", "hua"}));
	set("long", "他一脸来上去大义凛然，却总让感觉有点什么不对。\n");
	set("gender", "男性");
	set("age", 41);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("per", 24);

	setup();
	carry_object("/clone/cloth/cloth.c")->wear();
}

void init()
{
	object me;

	::init();
	me = this_player();
	if (! objectp(me) || ! userp(me))
		return;

	remove_call_out("greeting");
	call_out("greeting", 0, me);
}

void greeting(object me)
{
	if (! objectp(me) || environment(me) != environment(this_object()))
		return;

	command("look " + me->query("id"));
	command("say 这位" + RANK_D->query_respect(me) +
		"，这年头做那种什么正人君子太吃亏啦，看看我？看看岳步群老哥，那才是做人的道理，由此处前去阎罗殿，你就能做一个阴险奸诈的人，别犹豫啦！");
}

void check_leave(object me, string dir)
{
	if (dir == "out")
	{
		message_vision("$N对$n奸笑道：上路吧！\n", this_object(), me);
		me->set("character", "阴险奸诈");
	} else
	if (dir == "east")
	{
		command("grin");
		command("say 哼，没眼光！");
	}
}
