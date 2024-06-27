

inherit NPC;

string ask_lilian();
string ask_jieshu();
string ask_baotu();
string ask_pay();
string ask_yao();
string ask_newgift();
string ask_buchang();
string ask_xinwu();
void ask_newgift1();
void create()
{
	set_name(HIW"混江湖使者"NOR, ({ "diyu shizhe", "shizhe" }));
	set("nickname", HBCYN"武林使者"NOR);
	set("long", "这是一位混江湖官方派遣的使者，负责处理混江湖玩家的事情。\n");
	set("gender", "男性");
	set("age", 30);
	set("per", 24);
	set("str", 40);
	set("int", 40);
	set("con", 40);
	set("dex", 40);
	set("qi",5000);
	set("jingli",6000);
	set("max_qi", 8000);
	set("max_jing", 5000);
	set("eff_jingli", 6000);
	set("jiali", 190);
	set("combat_exp", 9000000);
	set("shen", 25000);

	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: exert_function, "taiji" :),
		(: perform_action, "sword.chan" :),
		(: perform_action, "cuff.zhen" :),
		(: perform_action, "cuff.zhan" :),
		(: perform_action, "cuff.ji" :)
	}));

	set("inquiry", ([
		"历练" : (: ask_lilian :),
		"结束" : (: ask_jieshu :),
		"贡献" : (: ask_pay :),
		"护心丹" : (: ask_yao :),
		"藏宝图" : (: ask_baotu :),
		"开服大礼包" : (: ask_newgift :),
		"新手大礼包" : (: ask_newgift1 :),
		"补偿" : (: ask_buchang :),
		"瑾墨青花" : (: ask_xinwu :),
	]));
	setup();
}


string ask_newgift1()
{
	object ob = this_player();
	object gift;
 
	//if (!wizardp(ob))
	//	return ("正式开站才可以领取。");
	if (ob->query("newgift_give_box1"))
		return ("你已经领取过新手大礼包了，不能再次领取，感谢您的支持。");
	
	command("nod "+ob->query("id"));
	command("say 我这就发给你。");

	gift = new("/clone/gift/new_gift1");

	tell_object(ob,HIM"你获得了"+gift->short()+"。"NOR"\n");  
	log_file("new_gift/lingqu", sprintf("%s：%s(%s)领取了%s。\n", 
			ctime(time()),ob->query("name"),ob->query("id"),gift->short()));
	
	ob->set("newgift_give_box1", time());
	gift->move(ob);
	return "祝你游戏愉快！";
}


string ask_xinwu()
{
	object ob;
	mapping myfam;
	object nang;

	ob = this_player();
	myfam = (mapping)ob->query("family");
	
	if (ob->query("combat_exp") < 1500000)
		return "凭你的能力根本不配领取瑾墨青花。\n";

	if ( present("jinmo qinghua", ob))
		return "你身上不是有瑾墨青花吗？别贪得无厌！\n";

	nang=new("/clone/weapon/yupei");
	nang->set("owner_id", ob->query("id"));
	nang->move(ob);
	ob->set("yupei/qinghua", 1);
	write("你得到了一块"+nang->name(1)+"\n");
	return "这件东西我就送给你了，如果掉了还可以找我领取。";
}

string ask_buchang()
{
	object ob = this_player();
	object gift;
 
	mixed today;
	
	/*if (!wizardp(ob))
		return ("测试完成才可以领取。");*/
	today = localtime(time());
	if ((today[4]+1)==5 && today[3] >= 30 || (today[4]+1)==6 && today[3] <= 2) {
		if (ob->query("buchang_give"))
			return ("你已经领取过补偿礼包了，不能再次领取，感谢您的支持和理解。");
		
		command("nod "+ob->query("id"));
		command("say 我这就发给你。");

		gift = new("/clone/gift/buchang_gift");

		tell_object(ob,HIM"你获得了"+gift->short()+"。"NOR"\n");  
		log_file("new_gift/buchang", sprintf("%s：%s(%s)领取了%s。\n", 
				ctime(time()),ob->query("name"),ob->query("id"),gift->short()));
		
		ob->set("buchang_give", time());
		gift->move(ob);
		return "祝你游戏愉快！";
	}
	return "对不起，暂时没有补偿礼包，祝你游戏愉快！";
}

string ask_newgift()
{
	object ob = this_player();
	object gift;
 
	
	//if (!wizardp(ob))
	//	return ("正式开站才可以领取。");
	if (ob->query("newgift_give_box"))
		return ("你已经领取过开服大礼包了，不能再次领取，感谢您的支持。");
	
	command("nod "+ob->query("id"));
	command("say 我这就发给你。");

	gift = new("/clone/gift/new_gift");

	tell_object(ob,HIM"你获得了"+gift->short()+"。"NOR"\n");  
	log_file("new_gift/lingqu", sprintf("%s：%s(%s)领取了%s。\n", 
			ctime(time()),ob->query("name"),ob->query("id"),gift->short()));
	
	ob->set("newgift_give_box", time());
	gift->move(ob);
	return "祝你游戏愉快！";
}

void init()
{
	object ob;
	::init();//继承上一级
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;

	if( ob->query("zjvip/times") > 0 && !ob->query("lilian/start")) {
		command("hi "+ob->query("id"));
		command("whisper "+ob->query("id")+" "HIC"\n这位" + RANK_D->query_respect(ob) +"你是我们月卡玩家的成员，\n"+
			"你还没有在我这里"HIC""ZJURL("cmds:ask shizhe about 历练")+ZJSIZE(20)"登记"NOR""HIR"历练"HIC"，\n"+
			"赶紧开始你的"HIR"历练"HIC"，领取丰厚的家族奖励吧！"NOR"");
	}
	switch( random(2) ) {
	case 0:
		say( "混江湖使者恳求道：\n"
			"这位" + RANK_D->query_respect(ob) + "，义父如果方便的话给混江湖一个评价吧，寻找群管理可以获得礼包码领取奖励哦。\n");
		break;
	case 1:
		say( "混江湖使者说道：\n"
			"这位" + RANK_D->query_respect(ob) + "，义父如果方便的话给混江湖一个评价吧，寻找群管理可以获得礼包码领取奖励哦。\n");
		break;
	}

}



string ask_lilian()
{ 
	object me = this_object();
	object ob = this_player();

        if (ob->query("vip/all_pay")>0) {
            ob->add("zjvip/all_pay",ob->query("vip/all_pay"));
            ob->delete("vip/all_pay");
            }

        if (ob->query("zjvip/times") <1) return "对不起，我只处理月卡玩家的事情！\n";

        if (ob->query("lilian/start")) return "我已经记录了你的历练信息，放心去吧。\n";

	message_vision(HIG"$N翻开记事簿，对$n点了点头，说道：好吧，我这就为你记上。"NOR"\n",me,ob);

	ob->set("lilian/start",time());

	return "别忘了在六个时辰内找我结束历练。\n"; 
}

string ask_jieshu()
{
	  object me = this_object();
	  object ob = this_player();
        int time3, paid,exp,gold;

        time3=time()-(int)ob->query("lilian/start");

        if (ob->query("zjvip/times") <1) return "对不起，我只处理月卡玩家的事情！\n";

        if (!ob->query("lilian/start")) return "我这里没有你的历练记录。\n";

        paid=ob->query("zjvip/all_pay");

        tell_object(ob,HIC"你的累计历练时间是"+CHINESE_D->chinese_time(time3)+"。"NOR"\n");  

        if (time3>43200) time3=43200;

        tell_object(ob,HIC"你的有效历练时间是"+CHINESE_D->chinese_time(time3)+"。"NOR"\n");  
	  message_vision(HIY"$N结束了$n的本次历练！"NOR"\n",me,ob);
        ob->add("balance",time3*2);
        ob->add("combat_exp",time3/4);
        ob->add("potential",time3/28);
        ob->delete("lilian/start");
        tell_object(ob,"你被奖励了\n"
                       "白银："+time3*2/100+" 两，\n"
                       "经验："+time3/4+" 点，\n"
                       "潜能："+time3/28+" 点。"NOR"\n");  


        exp=time3*paid/1000;
        if (exp>time3) exp=time3;
        gold=time3*paid/1000;
        if (gold>time3) gold=time3;

        if (ob->query("id")=="12898983") {
            ob->add("combat_exp", time3*5/4);
            }

        ob->add("balance",gold*2);
        ob->add("combat_exp",exp/4);
        //tell_object(ob,"根据你的贡献度，你额外获得了"+gold*2/100+"两白银和"+exp/4+"点经验。"NOR"\n"); 

	  return "根据你的贡献度，额外奖励你"+gold*2/100+"两白银和"+exp/4+"点经验。"NOR"\n";
}

string ask_pay()
{
 
	object ob = this_player();

	if (ob->query("vip/all_pay")>0) {
		ob->add("zjvip/all_pay",ob->query("vip/all_pay"));
		ob->delete("vip/all_pay");
	}

	if (ob->query("zjvip/times") <1) return "我只处理月卡玩家的事情！\n";

	return "你当前贡献是"+chinese_number(ob->query("zjvip/all_pay")+ob->query("gongxians"))+"点。\n";
}

string ask_baotu()
{
	int now,last,nowfix,lastfix;
	mixed *t1,*t2;
	object tu,me = this_player();

	if (me->query("zjvip/times") <1) return "对不起，我只处理月卡玩家的事情！\n";
	if (me->query("zjvip/times") < 10*24*3600) return "对不起，会员时长已不足10天，不能领取藏波图！\n";
	last = me->query("zjvip/last_baotu");
	now = time();
	t1 = localtime(now);
	t2 = localtime(last);
	nowfix = now+(6-t1[6])*86400;
	lastfix = last+(6-t2[6])*86400;
	if(last&&(localtime(nowfix)[7]==localtime(lastfix)[7]))
		return "一周内只能领一次！\n";
	if ((me->query_encumbrance()*100 / me->query_max_encumbrance())>90)
		return "你身上的东西太多了！\n";
	if ( (time()-me->query("birthday")) < 7*86400 )
		return "你还是等下周再来领取藏宝图吧！\n";

	tu = new("/d/fuben/obj/heifeng1");
	tu->move(me);
	me->set("zjvip/last_baotu",now);
	message_vision("使者给了$N一张" + tu->query("name") + "。\n",me);
	log_file("vip_tu",ctime(time())+"："+me->query("name")+"在地狱使者那里领取一张藏宝图。\n");
	return "这可是好东西，你抽空找朋友一起去探索一下吧。\n";
}

string ask_yao()
{
	object me = this_object();
	object ob = this_player();
        object yao;

	if (ob->query("zjvip/times") <1) return "对不起，我只处理月卡玩家的事情！\n";

        if ( (time()-ob->query_temp("last_huxindan"))<1800 ) {
		    command("say 这位" + RANK_D->query_respect(ob) + "，你不是刚刚来领过天王护心丹吗，怎么又来要了？");
                ob->unconcious();
                return "真是讨打！";
            }

        if (  present("huxin dan", ob) )
                return RANK_D->query_respect(ob) + "你身上不是已经有天王护心丹了吗，怎么又来要了？ 真是贪得无厌！";

        if (objectp(present("huxin dan", environment(ob))))
                        return "曾经有一颗天王护心丹落你的眼前，你却没有好好珍惜...\n";

        if ((ob->query_encumbrance()*100 / ob->query_max_encumbrance())>90)
                return "你身上的东西太多了！\n";

        yao = new("/clone/shizhe/huxindan9");
        yao->set_amount(99);
        yao->move(ob);
        ob->set_temp("last_huxindan",time());
        message_vision("$N给了$n一些" + yao->query("name") + "。\n",me ,ob);
	return "这可是好东西，希望对你行走江湖有所帮助。\n";
}