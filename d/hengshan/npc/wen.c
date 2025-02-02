// wen.c
inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("仪文", ({ "yi wen", "wen" }) );
	set("gender", "女性");
	set("class", "bonze");
	set("age", 28);
	set("attitude", "peaceful");
	set("per", 24);
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 28);

	set("neili", 1400);
	set("max_neili", 1400);
	set("jiali", 30);
	set("max_qi", 1000);
	set("max_jing", 800);
	set("combat_exp", 400000);
	set("shen_type", 1);

	set_skill("unarmed", 80);
	set_skill("sword", 80);
	set_skill("force", 80);
	set_skill("parry", 80);
	set_skill("dodge", 80);
	set_skill("hengshan-jian", 80);
	set_skill("lingxu-bu", 80);

	map_skill("sword", "hengshan-jian");
	map_skill("parry", "hengshan-jian");
	map_skill("dodge", "lingxu-bu");

	create_family("恒山派", 14, "弟子");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}

