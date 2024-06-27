inherit NPC;
#include <localtime.h>

string ask_zhengrong();
string ask_bianxing();
void create()
{
	set_name("妙手神医", ({"shenyi"}));
	set("long", "他好像一脸猥琐的盯着你！");
	set("combat_exp", 10000);
	
	set("inquiry", ([
		"【整容】" : (: ask_zhengrong :),
		"【变性】" : (: ask_bianxing :),
		]));
	setup();
}

void init()
{
	add_action("do_zhengrong", "zhengrong");
	add_action("do_bianxing", "bianxing");
}

//封装zj弹窗
string popup(string str)
{
string msg;
 msg = ZJOBLONG+str;
 msg = replace_string(msg,"\n",ZJBR);
 return msg+"\n";
}
//带按键的zj弹窗
string popup_key(string str)
{
 str = ZJOBACTS2+ZJMENUF(2,2,9,30)+str;
return str+"\n";
}
//可输入字符串的直接弹窗
string popup_input(string str,string order)
{
 return INPUTTXT(str,order+"$txt#")+"\n";
}

string ask_zhengrong()
{
	this_player()->force_me("zhengrong");
	return "";
}

string ask_bianxing()
{
	this_player()->force_me("bianxing");
	return "";
}

int do_bianxing(string arg)
{
	object me = this_player();

	if (!arg)
	{
		string msg;
		msg = popup("你变成下面那种性别") + popup_key(sprintf("男性:%s%s女性:%s%s","bianxing 男性",ZJSEP,"bianxing 女性",ZJSEP));
		write(msg);
		return 1;
	}

	if (me->query("shenyi/bianxing"))
	{
		write("你在开玩笑吧，你已经做过手术了，对于手术来说身体情况已经不可逆了，还是找些神丹妙药吧，手术是肯定不行了！\n");
		return 1;
	}

	if (arg != "男性" || arg != "女性")
	{
		write("还是选择正常的性别比较好。\n");
	}

	me->set("gender",arg);
	me->set("shenyi/bianxing",1);

	write("你的性别成功的被神医改变成了" + arg + "。\n");

	return 1;
}

int do_zhengrong(string arg)
{
	object who = this_player();
	int last_time, num;
	
	
	last_time = who->query("shenyi_zhengrong");
	if ((localtime(last_time)[LT_MON] == localtime(time())[LT_MON]) && (localtime(last_time)[LT_MDAY] == localtime(time())[LT_MDAY]))
	{
		write(ZJOBLONG + "一天只能整容一次。\n");
		return 1;
	}
	
	if (!arg)
	{
		write(INPUTTXT("一天一次，花费1金，50万以下经验不收费。"ZJBR"你想将容貌修改为多少？(10-30)", "zhengrong $txt#") + "\n");
		return 1;
	}
	
	if (!sscanf(arg, "%d", num) || num < 10 || num > 30)
	{
		write(ZJOBLONG + "请输入一个大于10，小于30的数。\n");
		return 1;
	}
	
	if (!MONEY_D->player_pay(who, 10000) && who->query("combat_exp") > 500000)
		return notify_fail(ZJOBLONG + "你的钱不够。\n");
	
	who->set("per", num);
	who->set("shenyi_zhengrong", time());
	write("整容成功，你的容貌修改为" + num + "。\n");
	return 1;
}