// beastseller.c

inherit NPC;
inherit F_DEALER;

#define BEAST_OB	 "/clone/npc/magic-beast.c"
#define BEAST_DIR	 "/data/beast/"

void get_subtype(string arg, object ob);
void get_gender(string arg, object ob);
void get_id(string arg, object ob);
void get_name(string arg, object ob);
void get_desc(string arg, object ob);
void build_beast(object ob);
int check_legal_name(string name, int max_len);
int check_legal_id(string arg);
string ask_form(string name);

string* beast_type_name = ({
	"马", "驴", "骡", "驼", "牛", "象",
	"狮", "虎", "豹", "鹿", "鹤", "雕",
	"羊", "猴", "熊", "狼", "狐", "貂",
	"驹", "兽", "龙",
});

string* beast_id_surfix = ({
	"ma", "lv", "luo", "tuo", "niu", "xiang",
	"shi", "hu", "bao", "lu", "he", "diao",
	"yang", "hou", "xiong", "lang", "hu", "diao",
	"ju", "shou", "long",
});

string* beast_unit_name=({
	"匹", "头", "头", "头", "头", "头",
	"只", "只", "只", "头", "只", "只",
	"头", "只", "只", "条", "只", "只",
	"匹", "头", "条",
});

void create()
{	
	set_name("宠物商人", ({ "shang ren", "ren", "shangren" }) );
	set("gender", "男性" );
	set("age", 21);
	set("long",@LONG
幻兽商人从来没人知道他从什么地方来的，只知道他突然出现在
这里，出售各种各种幻兽，幻兽具有各种神奇的功能，你如果喜
欢的话，不妨也选(choose)一只。
LONG );
	set("title",HIW"魔幻兽商人"NOR);
	set("combat_exp", 5);
	set("inquiry", ([ 
		"〖魔幻兽〗"	: "只要给我一百两黄金，你就能拥有魔幻兽了！", 
		"〖幻兽哨〗"	: (: ask_form ,"shoushao" :),
	]));
	set("skill_huanshou", 1);
	set_skill("training", 400);    
	set_skill("huisheng-jue", 400);    
	set("chat_chance", 15);
	set("attitude", "friendly");
	set("vendor_goods", ({
		"/clone/misc/shi",
	}));
	setup();
	carry_object("/clone/cloth/cloth")->wear();
	create_family("万兽山庄", 1, "使者");	 
}

void init()
{	  
	object ob;
	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_choose", "choose");
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

string ask_form(string name)
{
	object me;
	object ob;

	me = this_player();
	if (present(name, this_player()))
		return RANK_D->query_respect(this_player()) + "你身上不是已经有了吗！";
	if(me->query("can_whistle"))
	{
		ob = new("/clone/misc/huanshou_shao");
		ob->move(me);
		tell_object( me, HIG"幻兽商人神秘地笑了笑。"NOR"\n" );
		return "你拿好这根「幻兽哨」吧。" ;
	}
	else
	{
		return "你连幻兽都没有，要它做什么！！！" ;
	}
	
}
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(5) ) {
		case 0:
			say( "幻兽商人说道：这位" + RANK_D->query_respect(ob) + "，要魔幻兽么？\n");
			break;
		case 1:
			say( "幻兽商人说道：这位" + RANK_D->query_respect(ob) + "，魔幻兽可以铠化，保护主人的哦。\n");
			break;
	}
}

int do_choose(string arg)
{
	object me = this_player();

	if (me->is_busy())
		return notify_fail("你上一个动作还没有完成。\n");
		
	if (file_size(me->query_save_file() + "-beast.o") > 0 && mapp(me->query("can_whistle")))
		return notify_fail("你已经拥有你心爱的魔幻兽了。\n");
				   
	if (me->query_skill("training", 1) < 30)
		return notify_fail("你的驭兽术（training）太低了，即使养了魔幻兽，也会背弃你而去。先找商人学习吧！\n");
	
	if (! me->query_temp("beast/money"))
	{
		command("say 这位" + RANK_D->query_respect(me) + "，每只魔幻兽一百两黄金，你必须先给钱！");
		return 1;
	}

	write("您要养哪类魔幻兽：\n");
	write(" 1. 马   2. 驴   3. 骡   4. 驼  5. 牛  6. 象\n");
	write(" 7. 狮   8. 虎   9. 豹  10. 鹿 11. 鹤 12. 雕\n");
	write("13. 羊  14. 猴  15. 熊  16. 狼 17. 狐 18. 貂\n");
	write("19. 驹  20. 兽  21. 龙\n");
	write("请选择数字代号：(q 键取消)");

	input_to( (: get_subtype :), me);
	return 1;
}

void get_subtype(string arg, object ob)
{
	int n;
	object me = this_player();
	if (arg == "q" || arg == "Q")    
		return;

	sscanf(arg, "%d", n);
    
	if (n <= 0 || n > 21)  
	{		  
		write("您要养哪类魔幻兽：\n");
		write(" 1. 马   2. 驴   3. 骡   4. 驼  5. 牛  6. 象\n");
		write(" 7. 狮   8. 虎   9. 豹  10. 鹿 11. 鹤 12. 雕\n");
		write("13. 羊  14. 猴  15. 熊  16. 狼 17. 狐 18. 貂\n");
		write("19. 驹  20. 兽  21. 龙\n");		  
		write("请输入纯数字代号：(q 键取消)");
		input_to( (: get_subtype :), ob);
		return;
	}
	ob->set_temp("beast/beast_type", n);
	ob->set_temp("beast/beast_gender", random(2) ? "雄性" : "雌性");
	ob->set_temp("beast/beast_id", me->query("id")+time());
	ob->set_temp("beast/beast_unit", beast_unit_name[ob->query_temp("beast/beast_type") - 1]);

	write("\n");
	write("请设定魔幻兽的中文名：(可加颜色，如：$YEL$小龙$NOR$ )");
	input_to( (: get_name :), ob);
}

void get_name(string arg, object ob)
{
	string  arg_old;
	string  result;

	arg_old = arg;
	arg = replace_string(arg, "$BLK$", "");
	arg = replace_string(arg, "$RED$", "");
	arg = replace_string(arg, "$GRN$", "");
	arg = replace_string(arg, "$YEL$", "");
	arg = replace_string(arg, "$BLU$", "");
	arg = replace_string(arg, "$MAG$", "");
	arg = replace_string(arg, "$CYN$", "");
	arg = replace_string(arg, "$WHT$", "");
	arg = replace_string(arg, "$HIR$", "");
	arg = replace_string(arg, "$HIG$", "");
	arg = replace_string(arg, "$HIY$", "");
	arg = replace_string(arg, "$HIB$", "");
	arg = replace_string(arg, "$HIM$", "");
	arg = replace_string(arg, "$HIC$", "");
	arg = replace_string(arg, "$HIW$", "");
	arg = replace_string(arg, "$NOR$", "");

	if (! check_legal_name(arg, 12))  
	{
		write("请设定魔幻兽的中文名：(可加颜色，如：$YEL$小龙$NOR$)");
		input_to( (: get_name :), ob);
		return;
	}

	if (stringp(result = NAME_D->invalid_new_name(arg)))
	{
		write("对不起，" + result);
		write(HIR "禁止使用与他人姓名相同或接近的魔幻兽名。并因循RULES中对名字的相关规定。"NOR+"\n");
		input_to( (: get_name :), ob);
		return;
	}

	arg = arg_old;
	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);

	ob->set_temp("beast/beast_name", arg);
	write("ok\n");
	build_beast(ob);
}

void build_beast(object ob)
{
	string fc, fn;
	object beast,obj,me;	
	string beast_id;
	string beast_name;
	string beast_unit;
	string beast_desc;
	string beast_gender;

	beast_id = ob->query_temp("beast/beast_id");
	beast_name = ob->query_temp("beast/beast_name");
	beast_name += NOR;
	beast_unit = ob->query_temp("beast/beast_unit");
	beast_desc = ob->query_temp("beast/beast_desc");
	beast_desc += NOR;
	beast_gender = ob->query_temp("beast/beast_gender");

	fc = read_file(BEAST_OB);

	fc = replace_string(fc, "BEAST_NAME", beast_name);
	fc = replace_string(fc, "BEAST_ID", beast_id);							  
	fc = replace_string(fc, "BEAST_GENDER", beast_gender);			   
	fc = replace_string(fc, "BEAST_UNIT", beast_unit);			  
	fc = replace_string(fc, "LONG_DESCRIPTION", "它是" + ob->query("name") + "的魔幻兽。\n");

	fc = replace_string(fc, "OWNER_ID", ob->query("id"));
	fc = replace_string(fc, "OWNER_NAME", ob->query("name"));

	fn = sprintf(BEAST_DIR"%c/%s/%s", beast_id[0], ob->query("id") , beast_id);

	if (file_size(fn + ".c") > 0)
	{
		if (beast = find_object(fn)) 
			destruct(beast);
		DBASE_D->clear_object(fn);
		rm(fn + ".c");
	}

	assure_file(fn);
	write_file(fn + ".c", fc); // 写入文件
	ob->set("can_whistle/" + beast_id, fn);	  

	beast = load_object(fn);
	beast->save();
	destruct(beast);
	me=this_player();
	obj = new("/clone/misc/huanshou_shao");
	obj->move(me);
	command("say 你可以使用[幻兽哨]召唤你的魔幻兽！<whistle " + beast_id +">\n");
	ob->delete_temp("beast");	
	return;
}

int accept_object(object me, object ob)
{
 
 
 

	command("xixi");
	command("say 呵呵，多谢这位" + RANK_D->query_respect(me) + " ！");

	if (me->query_skill("training", 1) < 30)
	{
		command("say 你的驭兽术不够，即使养了魔幻兽，也会离你而去！");
		return 0;
	}

	if (ob->query("money_id"))
	{
		if (ob->value() < 1000000)
		{
			command("say 这位给的未免少了点！每只魔幻兽卵要一百两黄金！");
			return 0;
		}
		else
		{
			me->set_temp("beast/money",1);
			command("say 好我收下了！");
			command("say " + me->name() + "，现在我这里有各种魔幻兽卵！");
			command("say 请选择你要的魔幻兽卵 < choose >");
			destruct(ob);
			return 1;
		}
	}
	return 0;
}

int check_legal_id(string id)
{
	int i;
 
	object ppl;   
	  
	i = strlen(id);
	
	if ((strlen(id) < 3) || (strlen(id) > 20)) 
	{
		write("对不起，英文 id 必须是 3 到 20 个英文字母。\n");
		return 0;
	}

	while(i--)
	
	if (id[i] != ' ' && (id[i] < 'a' || id[i] > 'z'))  
	{
		write("对不起，英文 id 只能用英文字母。\n");
		return 0;
	}

	ppl = LOGIN_D->find_body(id);
	
	if (ppl || id == "guest" || id == "new") 
	{
		write("这个名字与别的玩家ID相同了．．．");
		return 0;
	}

	if (file_size(sprintf("/data/user/%c/%s", id[0], id) + __SAVE_EXTENSION__) >= 0) 
	{
		write("这个名字已经被别的玩家使用了．．．");
		return 0;
	} 

	return 1;
}

int check_legal_name(string name, int max_len)
{
	int i;
 
	
	i = strlen(name);
	if ((strlen(name) < 1) || (strlen(name) > max_len )) 
	{
		write(sprintf("对不起，魔幻兽中文字必须是 1 到 %d 个中文字。\n",max_len));
		return 0;
	}
	
	if (max_len < 13 && ! is_chinese(name))
	{
		write("对不起，请您用「中文」为宠物取名字或描述。\n");
		return 0;
	}
	return 1; 
}

int attempt_apprentice(object ob)
{
	command("say 走开！别拦着我做生意！");
}

int recognize_apprentice(object me, string skill) 
{
	if (skill == "training" || skill == "huisheng-jue") 
		return 1;		
	else 
		return 0;
}
