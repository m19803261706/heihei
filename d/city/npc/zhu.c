// zhu.c 朱熹



inherit NPC;
inherit F_DEALER;

string ask_job();
int do_answer();

void create()
{
	set_name("朱熹", ({ "zhu xi" }));
	set("long", "朱先生被称为当世第一大文学家，肚子里的墨水比海还要深。\n");
	set("gender", "男性");
	set("age", 65);
	set("no_get", 1);
	set_skill("literate", 500);
	 set("teacher",1);
	set_skill("unarmed", 80);
	set_skill("dodge", 80);
	set_skill("parry", 80);
	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 20);

	set("combat_exp", 400000);
	set("shen_type", 1);
	set("inquiry", ([
	    "买书" : (: do_answer :),
	    "抄书" : (: ask_job :),
	    "借书" : "借？你不还我到哪里找你？哼！",
	]));
	set("vendor_goods", ({
		"/clone/book/lbook1",
		"/clone/book/lbook2",
		"/clone/book/lbook3"
	}));
	setup();

	set("chat_chance", 1);
	set("chat_msg", ({
		"朱熹说道：普天之下，莫非王土；率土之滨，莫非王臣。\n",
		"朱熹说道：出家人，小过损益焉；无妄大过，未济咸困之。\n",
		"朱熹说道：大学之道，在明明德。在亲民，在止于至善。 \n",
		"朱熹说道：格物致知，诚意正心，修身齐家，治国平天下。\n",
	}) );
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}

int do_answer()
{
	::do_list();
	write(name() + HIR"在你耳边轻声说道：我这可真是货真价实，童叟无欺啊！"NOR"\n");
	return 1;
}

int recognize_apprentice(object ob)
{
	if (ob->query_temp("mark/朱") < 1)
		return 0;

	ob->add_temp("mark/朱", -1);
	return 1;
}

int accept_object(object who, object ob)
{
	if (! who->query_temp("mark/朱"))
		who->set_temp("mark/朱", 0);

	if (ob->query("money_id") && ob->value() >= 2000)
	{
		message_vision("朱熹同意指点$N一些读书写字的问题。\n", who);
		who->add_temp("mark/朱", ob->value() / 50);
		    destruct(ob);
		return 1;
	}

	command("say 看清楚学规，请教学问至少要二十两白银！");
	return 0;
}

string ask_job()
{
	object me;
 

	me = this_player();
	if (me->query("afk/file")=="chaoshu")
		return "让你抄的书你抄完了？";

	if (me->query_temp("pending/afk")||me->query("afk"))
		return "你正忙着呢！";

	if (me->query("qi") < 20)
		return "我看你脸色不行啊，先歇会儿吧，我可不想抄书抄出人命来。";

	if (! interactive(me))
		return "...";

	me->delete("afk");
	me->set("afk/file","chaoshu");
	me->set("afk/room",environment(me));
	return "好，你就帮我抄书吧！笔墨纸砚在这儿。";
}