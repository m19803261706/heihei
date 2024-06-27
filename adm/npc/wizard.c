inherit NPC;

#include <vip_skill.h>

string ask_baibao();
int ask_character(string arg);
int ask_fanli();
int ask_xiandan();
int ask_illness();
int ask_kuilei();
int ask_mengzi();
int ask_buchang();
int ask_gift();
int ask_viplv();

void create()
{
        set_name("巫师",({  "wizard", "wushi" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long", "这是一个成天无所事事的巫师。\n");

        set("str", 17);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("shen_type", 1);
        set("combat_exp", 100);
        set("attitude", "peaceful");

        setup();

        set("inquiry", ([
              "储物袋": (: ask_baibao :),
            //   "弟子贡献": (: ask_fanli :),
              "仙丹": (: ask_xiandan :),
              "孟子": (: ask_mengzi :),
              "替身傀儡": (: ask_kuilei :),
            //   "贡献成就": (: ask_viplv :),
        ]) );

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	//add_action("ask_character","washme");
	add_action("do_getvip","getvip");
	add_action("do_getsk","getsk");
}

int ask_viplv()
{
 
	object me;
	string str;

	me = this_player();
	str = ZJOBLONG"合理消费，快乐游戏，坚持签到每天来江湖中走一遭，终有一天你会成为一代宗师，加油！"ZJBR"你的贡献成就如下：\n";
	str += ZJOBACTS2+ZJMENUF(1,1,10,30);
	str += "VIP2[洗心丹1颗]["+((me->query("zjvip/level")>1)?"已达成":"未达成")+"]["
			+(me->query("zjvip/vipgift/vip2")?"已领取":"未领取")
			+"]:getvip 2"ZJSEP;
	str += "VIP3[公共技能随机奖励]["+((me->query("zjvip/level")>2)?"已达成":"未达成")+"]["
			+(me->query("zjvip/vipgift/vip3")?"已领取":"未领取")
			+"]:getvip 3"ZJSEP;
	str += "VIP4[公共技能自选1次]["+((me->query("zjvip/level")>3)?"已达成":"未达成")+"]["
			+(me->query("zjvip/vipgift/vip4")?"已领取":"未领取")
			+"]:getvip 4"ZJSEP;
	str += "VIP5[50颗极品冲脉丹]["+((me->query("zjvip/level")>4)?"已达成":"未达成")+"]["
			+(me->query("zjvip/vipgift/vip5")?"已领取":"未领取")
			+"]:getvip 5"ZJSEP;
	str += "VIP6[100颗极品冲脉丹]["+((me->query("zjvip/level")>5)?"已达成":"未达成")+"]["
			+(me->query("zjvip/vipgift/vip6")?"已领取":"未领取")
			+"]:getvip 6"ZJSEP;
	str += "VIP7[极品冲脉丹+洗点卡]["+((me->query("zjvip/level")>6)?"已达成":"未达成")+"]["
			+(me->query("zjvip/vipgift/vip7")?"已领取":"未领取")
			+"]:getvip 7"ZJSEP;
	str += "VIP8[极品冲脉丹+天性丹]["+((me->query("zjvip/level")>7)?"已达成":"未达成")+"]["
			+(me->query("zjvip/vipgift/vip8")?"已领取":"未领取")
			+"]:getvip 8"ZJSEP;
	str += "VIP9[未开放]"
			+":getvip 9"ZJSEP;
	str += "VIP10[未开放]"
			+":getvip 10";
	tell_object(me,str+"\n");
}

int do_getvip(string arg)
{
	int i,lv;
	object ob,me;
	string sk,str;

	me = this_player();
	if(!me->query("zjvip/times"))
	{
		tell_object(me,"你没有vip，不能领取贡献成就！\n");
		return 1;
	}
	lv = me->query("zjvip/level");
	if(lv<2)
	{
		tell_object(me,"加油，达到vip2你就可以领取成就奖励了哦！\n");
		return 1;
	}
	if(!arg)
	{
		tell_object(me,"你要干什么！\n");
		return 1;
	}
	else if(arg=="2")
	{
		if(lv<2)
		{
			tell_object(me,"加油，达到vip2你就可以领取成就奖励了哦！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip2"))
		{
			tell_object(me,"你已经领取过vip2成就奖励了！\n");
			return 1;
		}
		ob = new("/clone/shizhe/dan_xixin");
		tell_object(me,"你领取到了一颗洗心丹！\n");
		log_ufile(me,"viplvgift","领取到了一颗洗心丹！\n");
		me->set("zjvip/vipgift/vip2",1);
		ob->move(me);
	}
	else if(arg=="3")
	{
		if(lv<3)
		{
			tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip3"))
		{
			tell_object(me,"你已经领取过vip3成就奖励了！\n");
			return 1;
		}
		if(random(30)==10)
			sk = "jiuyang-shengong";
		else
			sk = sk_list[random(sizeof(sk_list))];
		
		
		for(i=0;i<10;i++) {//随机选10次
			sk = sk_list[random(sizeof(sk_list))];
			if (SKILL_D(sk)->valid_learn(me)) {
				break;
			}
		}
		
		if (!SKILL_D(sk)->valid_learn(me)) {
			tell_object(me,"你抽中了"+to_chinese(sk)+"，只可惜你不符合学习条件！\n");
			return 1;
		}
		
		me->set("zjvip/vipgift/vip3",1);
		if(me->query_skill(sk,1))
		{
			tell_object(me,"你抽中了"+to_chinese(sk)+"，只可惜你已经会了！\n");
			return 1;
		}
		me->set_skill(sk, 50);

		log_ufile(me,"viplvgift","随机领取到了"+sk+"！\n");
		if(sk=="jiuyang-shengong")
		{
			tell_object(me, "你得到了一本九阳秘录！\n" );
			ob = new("/clone/book/jiuyang-copy");
			ob->move(me, 1);
		}
		tell_object(me, "你的"+to_chinese(sk)+"提升到了50级！\n" );
	}
	else if(arg=="4")
	{
		if(lv<4)
		{
			tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip4"))
		{
			tell_object(me,"你已经领取过vip4成就奖励了！\n");
			return 1;
		}
		str = ZJOBLONG"请选择你想要的技能：\n";
		str += ZJOBACTS2+ZJMENUF(2,2,10,30);
		for(i=0;i<sizeof(sk_list2);i++)
		{
			if (!SKILL_D(sk_list2[i])->valid_learn(me))//不符合学习条件的跳过
				continue;
			str += to_chinese(sk_list2[i])+":getsk "+sk_list2[i];
			if(i<(sizeof(sk_list2)-1)) str += ZJSEP;
		}
		tell_object(me,str+"\n");
	}
	else if(arg=="5")
	{
		if(lv<5)
		{
			tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip5"))
		{
			tell_object(me,"你已经领取过vip5成就奖励了！\n");
			return 1;
		}

		me->set("zjvip/vipgift/vip5",1);

		log_ufile(me,"viplvgift","领取到了50颗极品冲脉丹！\n");
		tell_object(me, "你得到了50颗极品冲脉丹！\n" );
		ob = new("/clone/shizhe/dan_chongmai4");
		ob->set_amount(50);
		ob->move(me, 1);
	}
	else if(arg=="6")
	{
		if(lv<6)
		{
			tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip6"))
		{
			tell_object(me,"你已经领取过vip6成就奖励了！\n");
			return 1;
		}

		me->set("zjvip/vipgift/vip6",1);

		log_ufile(me,"viplvgift","领取到了100颗极品冲脉丹！\n");
		tell_object(me, "你得到了100颗极品冲脉丹！\n" );
		ob = new("/clone/shizhe/dan_chongmai4");
		ob->set_amount(100);
		ob->move(me, 1);
	}
	else if(arg=="7")
	{
		if(lv<7)
		{
			tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip7"))
		{
			tell_object(me,"你已经领取过vip7成就奖励了！\n");
			return 1;
		}

		me->set("zjvip/vipgift/vip7",1);

		log_ufile(me,"viplvgift","领取到了100颗极品冲脉丹！\n");
		tell_object(me, "你得到了100颗极品冲脉丹！\n" );
		ob = new("/clone/shizhe/dan_chongmai4");
		ob->set_amount(100);
		ob->move(me, 1);
		
		ob = new("/clone/vip/xidianka");
		ob->move(me, 1);
		log_ufile(me,"viplvgift","领取到了1张洗点卡！\n");
		tell_object(me, "你得到了1张洗点卡！\n" );
	}
	else if(arg=="8")
	{
		if(lv<8)
		{
			tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip8"))
		{
			tell_object(me,"你已经领取过vip8成就奖励了！\n");
			return 1;
		}

		me->set("zjvip/vipgift/vip8",1);

		log_ufile(me,"viplvgift","领取到了100颗极品冲脉丹！\n");
		tell_object(me, "你得到了100颗极品冲脉丹！\n" );
		ob = new("/clone/shizhe/dan_chongmai4");
		ob->set_amount(100);
		ob->move(me, 1);
		
		ob = new("/clone/vip/tianxingdan");
		ob->move(me, 1);
		log_ufile(me,"viplvgift","领取到了1颗天性丹！\n");
		tell_object(me, "你得到了1颗天性丹！\n" );
	}

	return 1;
}

int do_getsk(string arg)
{
 int lv;
	object ob,me;
 

	me = this_player();
	if(!me->query("zjvip/times"))
	{
		tell_object(me,"你没有vip，不能领取贡献成就！\n");
		return 1;
	}
	lv = me->query("zjvip/level");
	if(!arg || member_array(arg,sk_list2)==-1)
	{
		tell_object(me,"你要干什么！\n");
		return 1;
	}
	if(lv<4)
	{
		tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
		return 1;
	}
	else if(me->query("zjvip/vipgift/vip4"))
	{
		tell_object(me,"你已经领取过vip4成就奖励了！\n");
		return 1;
	}
	if (!SKILL_D(arg)->valid_learn(me)) {
		tell_object(me,"你选择了"+to_chinese(arg)+"，只可惜你不符合学习条件！\n");
		return 1;
	}
	if(me->query_skill(arg,1))
	{
		tell_object(me,"你选择了"+to_chinese(arg)+"，只可惜你已经会了，请换一个吧！\n");
		return 1;
	}

	me->set("zjvip/vipgift/vip4",1);
	me->set_skill(arg, 50);
	log_ufile(me,"viplvgift","自选领取到了"+arg+"！\n");

	if(arg=="jiuyang-shengong")
	{
		tell_object(me, "你得到了一本九阳秘录！\n" );
		ob = new("/clone/book/jiuyang-copy");
		ob->move(me, 1);
	}
	tell_object(me, "你的"+to_chinese(arg)+"提升到了50级！\n" );
	return 1;
}
/*
int ask_buchang()
{
    object ob = this_player();

    if (ob->query("zjvip/buchang171024")>0) {
        command("say 你已经领取过相应补偿了！");
        return 1;
    }

    command("nod "+ob->query("id"));
    command("say 我这就发给你。");
    ob->add("zjvip/buchang171024",1);
    ob->delete("zjvip/buchang171001");
	ob->delete("zjvip/buchang170901");
	ob->delete("zjvip/buchang");
    ob->add("potential",40000);
    tell_object(ob,HIC"你获得了40000点潜能的补偿，并祝你游戏快乐！"NOR"\n");  

	log_file("buchang", sprintf("%s：%s(%s)领取了17-10-24的宕机补偿。\n",ctime(time()),ob->query("name"),ob->query("id")));
    return 1;
        
}
int ask_character(string arg)
{
	object me = this_player();
	string msg, type, cs;

	if (! wizardp(me) )
		return notify_fail("暂时关闭此功能。\n");
		
	if (!arg || arg == 0) {
		msg = ZJOBLONG+
		      "心狠手辣，宗师心法-九阴神功，提高攻击"ZJBR
			"光明磊落，宗师心法-南海玄功，增加防御"ZJBR
			"狡黠多变，宗师心法-不败神功，提高命中"ZJBR
			"阴险奸诈，宗师心法-葵花魔功，增加闪避"ZJBR
			"请选择你的性格：\n";
		
		msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
		msg += "光明磊落:washme 光明磊落";
		msg += ZJSEP"狡黠多变:washme 狡黠多变";
		msg += ZJSEP"阴险奸诈:washme 阴险奸诈";
		msg += ZJSEP"心狠手辣:washme 心狠手辣";
		
		write(msg + "\n");
		
	} else {
		if(sscanf(arg,"%s %s", type, cs) == 2)
		{
			if (me->query("character") == type) {
				tell_object(me, "你本来就是这种性格。\n");
				return 1;
			}

			if (cs == "yes") {
				if (type == "光明磊落" && me->query("character") == "心狠手辣") {
					me->set("character", type);
					tell_object(me, "你成功将性格改变为"+type+"。\n");
				} else if (type == "心狠手辣" && me->query("character") == "光明磊落") {
					me->set("character", type);
					tell_object(me, "你成功将性格改变为"+type+"。\n");
				} else if (type == "光明磊落" || type == "心狠手辣" || type == "狡黠多变" || type == "阴险奸诈") {
					tell_object(me, "对不起，你不符合改变性格的条件。\n");
                              return 1;
				} else {
					tell_object(me, "没有这种性格，请认真选择。\n");
					return 1;
				}
			} 
		} else {
			msg = ZJOBLONG+"你确定选择性格为"+HIG+arg+NOR"吗？\n";			
			msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
			msg += "确定:washme "+arg + " yes";
			msg += ZJSEP"取消: ";
			
			write(msg + "\n");
		}
	}
	return 1;
}
*/
int ask_fanli()
{
        int i;
        object ob = this_player();
        i=ob->query("zjvip/dizi_pay");
     
        if(ob->query("zjvip/dizi_pay")<1){
                command("say 你目前的弟子贡献太低，无法领取奖励。");
                message_vision("$N已累计获得了"+ob->query("zjvip/dizi_fanli")+"个元宝的奖励。\n",ob,  this_object());
                return 1;
        }
        else {
                command("nod "+ob->query("id"));
                command("say 你已符合领取弟子贡献奖励条件。");
	        ob->add("yuanbao",i);
                ob->add("zjvip/dizi_pay",-i);
                ob->add("zjvip/dizi_fanli",i);
                message_vision("$N获得了"+i+"个元宝的奖励。\n",ob,  this_object());
                message_vision("$N已累计获得了"+ob->query("zjvip/dizi_fanli")+"个元宝的奖励。\n",ob,  this_object());
                return 1;
        }
}

int ask_xiandan()
{
    int a,b,c,d;
    object ob = this_player();

	a=ob->query("gift/xiandan");
	b=ob->query("gift/unknowdan");
	c=ob->query("gift/shenliwan");
	d=ob->query("gift/xisuidan");
     
	if (ob->query("zjvip/times") <1) {
        command("say 对不起，我只处理地狱家族的事情！");
        return 1;
    }
    else {
    command("nod "+ob->query("id"));
    command("say 我来帮你查一下记录。");
    command("say 这位" + RANK_D->query_respect(ob) +"，你已经吃了："+chinese_number(a)+"颗"HIY"醍醐仙丹"NOR"，"+chinese_number(b)+"颗"HIR"火红仙丹"NOR"，"+chinese_number(c)+"颗"HIG"神力丸"NOR"，"+chinese_number(d)+"颗"YEL"洗髓丹"NOR"。");
	return 1;
    }
}

int ask_illness()
{
        int a,b,c,d;
        object ob = this_player();

	a=ob->query("gift/xiandan_fail");
	b=ob->query("gift/unknowdan_fail");
	c=ob->query("gift/shenliwan_fail");
	d=ob->query("gift/xisuidan_fail");
     
	if (ob->query("zjvip/times") <1) {
                command("say 对不起，我只处理地狱家族的事情！");
                return 1;
        }
        else {
                command("nod "+ob->query("id"));
                command("say 我来帮你查一下记录。");
                command("say 这位" + RANK_D->query_respect(ob) +"，你吃了"HIY "醍醐仙丹" NOR"有"+chinese_number(a)+"处暗疾，吃了"HIR "火红仙丹" NOR"有"+chinese_number(b)+"处暗疾，吃了"HIG "神力丸" NOR"有"+chinese_number(c)+"处暗疾，吃了"YEL "洗髓丹" NOR"有"+chinese_number(d)+"处暗疾。");
                return 1;
        }
}

string ask_baibao()
{
	object ob;
	mapping myfam;
	object nang;

	ob = this_player();
	myfam = (mapping)ob->query("family");
	
	if (ob->query("combat_exp") < 10000)
		return "虽然我这里有只储物袋，可是你战斗经验这么差，被人抢走了怎么办？\n";
/*
	if (ob->query("chuwudai"))
		return "你之前不是已经领过了吗？你还是赶紧联系管理员去处理一下吧。\n";
	*/
	if ( present("chuwu dai", ob))
		return "你已经有了一个储物袋，别贪得无厌！\n";

	nang=new("/clone/misc/baibao");
	nang->set("owner_id", ob->query("id"));
	nang->move(ob);
	ob->set("chuwudai", 1);
	write("你得到一个储物袋!\n");
	return "这可是个宝贝，好好利用它吧。";
}


int ask_kuilei()
{
    object ob = this_player();
    object yao;
	int m = localtime(time())[4]+1,m1,m2,m3;
	m1= m-1;
	m2= m1-1;
	m3= m2-1;
     
	if (ob->query("zjvip/times") <1) {
        command("say 对不起，我只处理地狱家族的事情！");
        return 1;
    }
	if ((ob->query("zjvip/all_pay")+ob->query("gongxians"))<1000) {
        command("say 对不起，你的贡献不够，不符合领取替身傀儡的条件！");
        return 1;
    }
	if (ob->query("zjvip/kuilei"+m)>=((ob->query("zjvip/all_pay")+ob->query("gongxians"))/1000)) {
        command("say 以你目前的贡献只能领"+chinese_number((ob->query("zjvip/all_pay")+ob->query("gongxians"))/1000)+"个替身傀儡！");
        return 1;
    }

	command("nod "+ob->query("id"));
    command("say 我这就给你。");
    yao = new("/clone/shizhe/kuilei");
    yao->move(ob);
    ob->add("zjvip/kuilei"+m,1);
    ob->delete("zjvip/kuilei"+m1);
    ob->delete("zjvip/kuilei"+m2);
    ob->delete("zjvip/kuilei"+m3);
    message_vision("$N给了$n一个" + yao->query("name") + "。\n",this_object(),ob);
	log_file("gift", sprintf(ob->query("id")+"在%s：领取了一个替身傀儡。\n",ctime(time())));
    return 1;
        
}

int ask_mengzi()
{
        object ob = this_player();
        object yao;

     
	if (ob->query("zjvip/times") <1) {
                command("say 对不起，我只处理地狱家族的事情！");
                return 1;
        }
	if (ob->query("zjvip/all_pay")+ob->query("gongxians")<1000) {
                command("say 对不起，你的贡献不够，不符合领取《孟子》的条件！");
                return 1;
        }

	if ( present("mengzi book", ob)) {
                command("say 你已经有了一本《孟子》了，别贪得无厌！");
                return 1;
        }

                command("nod "+ob->query("id"));
                command("say 我这就给你。");
        yao = new("/clone/shizhe/mengzi");
        yao->move(ob);
        message_vision("$N给了$n一本《" + yao->query("name") + "》。\n",this_object(),ob);
                return 1;
        
}