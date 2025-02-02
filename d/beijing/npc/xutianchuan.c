// xutianchuan.c



inherit NPC;
inherit F_UNIQUE;

void create()
{
	set_name("徐天传", ({ "xu tianchuan", "xu", "tianchuan" }));
	set("title", HIR "天地会"HIG"青木堂"NOR"护法");
	set("nickname", "八臂猿猴");
	set("gender", "男性");
	set("long", "\n他是青木堂数一数二的好手，手上功夫十分了得，尤其擅使一套猴拳。\n");
	set("age", 55);

	set("int", 30);
	
	set("qi", 500);
	set("max_qi", 500);
	set("jing", 500);
	set("max_jing", 500);
	set("shen_type", 1);

	set("combat_exp", 75000);
	set("attitude", "friendly");

	set_skill("force", 70);
	set_skill("dodge", 70);
	set_skill("parry", 90);
	set_skill("unarmed", 90);
	set_skill("hand", 100);
	set_skill("hunyuan-yiqi", 70);
	set_skill("shaolin-shenfa", 70);
	set_skill("houquan", 100);

	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/damage", 35);
	set("env/wimpy", 50);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("hand", "houquan");
	map_skill("unarmed", "houquan");
	map_skill("parry", "houquan");

	set("chat_chance", 3);
	set("chat_msg", ({
		"徐天传想了想，说：有人想要进出皇宫，我得想个法子才好啊。\n",
		"徐天传说道: 江湖威望很重要，威望值高大有好处啊。\n",
		"徐天传突然说：自此传得众兄弟，后来相认团圆时。\n",
		"徐天传突然说：初进洪门结义兄，对天明誓表真心。\n",
	}));

	set("inquiry", ([
		"陈劲南" : "想见总舵主可不容易啊。",
		"天地会" : "只要是英雄好汉，都可以入我天地会。",
		"反清复明" : "去棺材店和回春堂仔细瞧瞧吧！",
		"暗号" : "敲三下！",
		"切口" : "敲三下！",
	]));

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 25);
}
