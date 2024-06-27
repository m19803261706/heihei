// invent.c


#include <command.h>
#define  SYN "\""
#define  SYC ".c"
#define  NEED_LVL   600
#define  DEBUG

inherit F_CLEAN_UP;

mapping valid_types = ([
	"unarmed":      "拳脚",
	"sword":	"剑法",
	"axe":	  "斧法",
	"blade":	"刀法",
	"staff":	"杖法",
	"hammer":       "锤法",
	"club" :	"棍法",
	"whip":	 "鞭法",
	"finger":       "指法",
	"hand":	 "手法",
	"cuff":	 "拳法",
	"claw":	 "爪法",
	"strike":       "掌法",
]);

mapping type_name = ([
	"unarmed":      "拳",
	"sword":	"剑",
	"arrow":	"箭",
	"axe":	  "斧",
	"blade":	"刀",
	"staff":	"杖",
	"hammer":       "锤",
	"club" :	"棍",
	"dodge":	"轻功",
	"whip":	 "鞭",
	"finger":       "指",
	"hand":	 "手",
	"cuff":	 "拳",
	"claw":	 "爪",
	"strike":       "掌",
]);


string *weapon_types = ({
	"sword", "arrow", "axe",
	"blade", "staff", "hammer",
	"club", "whip" , "spin",
});

string *msga = ({ 
	"冥冥之中，$N突然发现",
	"$N绞尽脑汁，似乎觉得",
	"$N灵台一片清明，想起",
	"$N苦思以前练功时的点点滴滴，似乎想起",
	"突然，$N脑海灵光一现，发现",
	"$N反复比划，发现",
});

string *msgb = ({ 
	"似有相通之处，不禁心中一亮。",
	"颇有一一印证之功，随手演练，似有所悟。",
	"似乎可以合而为一，顿时心内一阵狂喜！",
	"可以相互取长补短，开辟一种全新的境界。",
	"如果连续使出，似乎可以将威力发挥至极限。",
	"如果详加修正，可以相互弥补个中不足，创造出更完美的招式。"
});

string *banned_name = ({
	"你", "你", "我", "他", "她", "它",
	"爸", "爷", "　", "妈",
	"屎", "尿", "粪",
});

string *spe_skill_level = ({
	"0", "12", "20", "30", "40", "50", "60", "80", "100", 
});
		      
string get_skill_name(object me, string skill);
int    skill_t_number(string e_name);
void   finish_write_skill(object ob, string skill);
	
void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object  weapon, where;
	mapping skills_map;
	string  msg, invent_skill, *skills, *mut_skills = ({});
	string  *invent;
	int     i;
	
	seteuid(getuid());
	where = environment(me);
	
	if( !arg ) {
		mapping invent_skills;

		if( !mapp( invent_skills = me->query("invent") ) )
			return notify_fail("你目前还没有自创任何武功。\n");
		
		msg = WHT "你目前共有 " HIC + chinese_number(sizeof(invent_skills)) + NOR WHT " 种自创武功：\n";
		invent = keys(invent_skills);
		
		for( i = 0; i < sizeof(invent); i++ )
		{
			msg += CYN "\n〖" HIC + to_chinese(invent[i]) + CYN "〗：" HIY +
			       to_chinese(invent_skills[invent[i]]) +
			       CYN "(" HIY + invent_skills[invent[i]] + CYN ")\n";
		}
		
		tell_object(me, msg);

		return 1;
	}

	if( arg == "?" ) {
	       msg = "以下是可以自创的技能种类：\n";

	       skills = sort_array(keys(valid_types), (: strcmp :) );
	       for (i = 0; i < sizeof(skills); i++)
			msg += sprintf("  %s (%s)\n", valid_types[skills[i]], skills[i]);
		tell_object(me, msg);

		return 1;
	} else {
		string meskill;
		
		if( sscanf(arg, "%s d", arg) == 1 ) {			
			if( !(meskill = me->query("invent/" + arg)) )
				return notify_fail("没有这种自创武功，请确认输入的基本武功英文名称。\n");

			tell_object(me, HIR "你删除了自创武功" + to_chinese(meskill) + "(" + meskill + ")。"NOR"\n");						
			CHINESE_D->remove_translate(meskill);			
			rm( SKILL_D(meskill) + SYC );			
			me->delete_skill(meskill);
			me->delete("invent/" + arg);
			if (! mapp(me->query("invent")) || 
			    sizeof(me->query("invent")) < 1)
				me->delete("invent");
			return 1;
		} else
		if( sscanf(arg, "%s ?", arg) == 1 ) {	 
			mixed  *meskills;	       			
			
			if( !(meskill = me->query("invent/" + arg)) )
				return notify_fail("没有这种自创武功，请确认输入的基本武功英文名称。\n");
			
			meskills = SKILL_D(meskill)->query_actions();
			msg =  HIW "自创武功" + to_chinese(meskill) + "的详细情况如下:"NOR"\n";
			msg += WHT "--------------------------------------------------"NOR"\n";
			msg += HIY "武功总招数：" + chinese_number(skill_t_number(meskill)) + "招"NOR"\n";
						
			for( i = 0; i < sizeof(meskills); i++ ) {
				msg += WHT "招式" + chinese_number(i + 1) + "名称：" + 
				       meskills[i]["skill_name"] + ""NOR"\n";
				msg += CYN "招式" + chinese_number(i + 1) + "描述：" + 
				       meskills[i]["action"] + ""NOR"\n";
				msg += CYN "招式" + chinese_number(i + 1) + "攻击：" + 
				       meskills[i]["attack"] + ""NOR"\n";
				msg += CYN "招式" + chinese_number(i + 1) + "伤害：" + 
				       meskills[i]["damage"] + ""NOR"\n";
				msg += CYN "附加" + chinese_number(i + 1) + "伤害：" + 
				       meskills[i]["force"] + ""NOR"\n";
				msg += CYN "招式" + chinese_number(i + 1) + "躲闪：" + 
				       meskills[i]["dodge"] + ""NOR"\n";
				msg += CYN "招式" + chinese_number(i + 1) + "招架：" + 
				       meskills[i]["parry"] + ""NOR"\n";
			}
			msg += WHT "--------------------------------------------------"NOR"\n";

			tell_object(me, msg);
			return 1; 
		}
				
	}
	   
	if( undefinedp(valid_types[arg]) ) {
		mapping invents;
		string  *invent_skills;

		if( !mapp( invents = me->query("invent") ) )
			return notify_fail("没有这个技能种类，用 invent ? 可以查看有哪些种类。\n");
		
		invent_skills = keys(invents);

		foreach(string str in invent_skills) {
			if( invents[str] == arg ) {
				arg = str;
				invent_skill = invents[str];
				break;
			}
		}

		if( !invent_skill )
			return notify_fail("没有这个技能种类，用 invent ? 可以查看有哪些种类。\n");
	} else {
		if( stringp( invent_skill = me->query("invent/" + arg ) ) )
			return notify_fail("你已经自创了一套" + to_chinese(invent_skill) + 
					   "，如果要继续为这套武功创造招式，请用invent <已创武功>\n");
	} 

	if( me->is_busy() )
		return notify_fail("你还是先忙完手头的事再说吧！\n");	 

	if( where->query("pigging") )
		return notify_fail("你还是专心拱猪吧！\n");
		
	if( !where->query("no_fight") )
		return notify_fail("在这里闭关？不太安全吧？\n");

	if( !where->query("sleep_room") )
		return notify_fail("你得找一个能够休息的地方闭关。\n");
		
	if( !ultrap(me))
		return notify_fail("你还没有到大宗师的境界，还是好好学习锻炼吧。\n");
       
	if( me->query("potential") < 10000 )
		return notify_fail("你的潜能不够，没法闭关修行。\n");

	if( (int)me->query("qi") * 100 / me->query("max_qi") < 90 )
		return notify_fail("你现在的气太少了，无法静心闭关。\n");

	if( (int)me->query("jing") * 100 / me->query("max_jing") < 90 )
		return notify_fail("你现在的精太少了，无法静心闭关。\n");

	if( (int)me->query("max_neili") < 4000 )
		return notify_fail("你觉得内力颇有不足，看来目前还难以"
				   "进行长时间的闭关修炼。\n");

	if( (int)me->query("neili") * 100 / me->query("max_neili") < 90 )
		return notify_fail("你现在的内力太少了，无法静心闭关。\n");
		
	if( !mapp(skills_map = me->query_skills() ) || sizeof(skills_map) < 1 )
		return notify_fail("你还是先去学点功夫再来吧。\n");

	if( undefinedp(skills_map[arg]) || skills_map[arg] < 1 )
		return notify_fail("你连基本的" + valid_types[arg] + "都不会，从何谈起？\n");

	if( skills_map[arg] < NEED_LVL )
		return notify_fail("你还是打好" + valid_types[arg] + "的基本功吧。\n");

	if( objectp( weapon = me->query_temp("weapon") ) ) {

		if( member_array(arg, weapon_types) == -1 && arg != "dodge" )
			return notify_fail("你必须空手才能自创" + valid_types[arg] + "。\n");

		if( member_array(arg, weapon_types) != -1 && weapon->query("skill_type") != arg )
			return notify_fail("你所使用的武器不对，无法自创" + valid_types[arg] + "。\n");
	} else if( member_array(arg, weapon_types) != -1 )
			return notify_fail("你必须拿起武器才能开始自创" + valid_types[arg] + "。\n");

	skills = keys(skills_map);

	foreach( string sk_tmp in skills ) {
		if( SKILL_D(sk_tmp)->valid_enable(arg) ) {
			mut_skills += ({ sk_tmp });
		}
	}

//	if( sizeof(mut_skills) < 3 )
//		return notify_fail("你的" + valid_types[arg] + "修为还不够广博，再去多学习学习！\n");

	mut_skills = filter_array(mut_skills, (: $(skills_map)[$1] >= NEED_LVL :));

//	if( sizeof(mut_skills) < 4 )
//		return notify_fail("你在" + valid_types[arg] + "方面的修为还不够高深。\n");
	
	me->delete_temp("invent");
	
	if( stringp(invent_skill) )
	{
		me->set_temp("invent/spe_skill/skill_z_number", skill_t_number(invent_skill) + 1);			
		if (skill_t_number(invent_skill) + 1 >= 10)
			return notify_fail("你的" + to_chinese(invent_skill) + 
					   "招式已经到了极限，无法再自创新招式。\n");
		
		message_vision("$N盘膝坐下，开始苦思冥想，专心的自创" + to_chinese(invent_skill) + "。\n", me);	      
	}
	else    message_vision("$N盘膝坐下，开始苦思冥想，专心的自创一种" + valid_types[arg] + "。\n", me);

	me->set_temp("invent/skill", arg);
	me->set_temp("invent/spe_skill/skill", arg); 
	me->set_temp("invent/mut_skills", mut_skills);	
	
	if( stringp(invent_skill) )
		me->set_temp("invent/invent_skill", invent_skill);
	
	me->set_short_desc("正在全神贯注地自创" + valid_types[arg] + "。");

	me->start_busy(bind((:call_other, __FILE__, "inventing" :), me),
		       bind((:call_other, __FILE__, "halt_inventing" :), me));

	CHANNEL_D->do_channel(this_object(), "rumor",
			      sprintf("%s(%s)开始闭关自创%s。\n",
			      me->name(1), me->query("id"), stringp(invent_skill) ? 
			      (to_chinese(invent_skill) + "新招式") : valid_types[arg]));
	return 1;
}


int inventing(object me)
{
	int     pot, max, i;
	string  skill, *mut_skills, *skills_tmp, skills,msg = "", *msgs = ({});
	mapping temp, s_skill;
	
	temp = me->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	
	pot = me->query("potential");
	if( pot <= 0 )
	{
		tell_object(me, "你的潜能耗尽，却一无所获，失望地站了。\n");
		message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
		me->set_short_desc(0);
		return 0;
	}

	if( me->add("learned_points", 100 + random(100)) > pot)
		me->set("learned_points", pot);

	if( random(5) != 0) return 1;

	skill = me->query_temp("invent/skill");
	mut_skills = me->query_temp("invent/mut_skills");

	if( random(10) == 1 ) {
		string *chinese_skills = ({});

		foreach(string mut_skill in mut_skills) {
			chinese_skills += ({ to_chinese(mut_skill)});
		}
		
		if( stringp( skills = me->query_temp("invent/invent_skill") ) )
		{
			s_skill["skill_e_name"] = skills;
			s_skill["skill_c_name"] = to_chinese(skills);			
						
			message_sort("猛然间$N脑中略过种种招式，将" + 
				sprintf( HIG"%s" NOR "以及" HIG "%s"NOR, 
				implode(chinese_skills[0..sizeof(chinese_skills)-2], NOR "、" HIG), 
				chinese_skills[sizeof(chinese_skills)-1])
				+ "这" + chinese_number(sizeof(mut_skills)) + "种武功的招式合而为"
				"一作为" + to_chinese(skills) + "的新招式。\n", me);
			
			me->clear_written();				   
			tell_object(me, HIC "\n\n请给" + to_chinese(skills) + "新招式起个名字(例如: " NOR HIY "悠哉" NOR HIC "):" NOR);	  
			me->set_short_desc(0);			
			
			input_to( "get_z_c_name", me );
			return 0;
		}       
		message_sort("猛然间$N脑中略过种种招式，将" + 
				sprintf( HIG"%s" NOR "以及" HIG "%s"NOR, 
				implode(chinese_skills[0..sizeof(chinese_skills)-2], NOR "、" HIG), 
				chinese_skills[sizeof(chinese_skills)-1])
				+ "这" + chinese_number(sizeof(mut_skills)) + "种武功合而为一。\n", me);

		me->clear_written();
		tell_object(me, HIW"\n\n\n你自创出了一套" + valid_types[skill] + "。"NOR"\n"
				"你可以为这套" + valid_types[skill] + "取一个名字\n\n"
				HIY"格式："HIC"<英文名> <中文名>\n"NOR"\n"
				"如输入：wuyou 无忧\n"
				"系统会产生一种无忧"HIR + type_name[skill] + NOR "(wuyou-"
				HIR + skill + NOR")的" + valid_types[skill] + "\n"
				HIW"勿用骚扰性或不雅的名字，否则将会被删除。"NOR"\n"
				"请输入：");
		me->set_short_desc(0);		       
		input_to( "input_skill_name", me );
		return 0;
	}

	skills_tmp = copy(mut_skills);

	max = 2 + random(sizeof(mut_skills)-2);
	if ( max > 5 ) max = 5;

	if( max < sizeof(mut_skills) ) {
		for( i = max; i < sizeof(mut_skills); i++ ) {
			skills_tmp -= ({ skills_tmp[random(sizeof(skills_tmp))] });
		}
	}

	foreach(string sk_tmp in skills_tmp) {
		msgs += ({ get_skill_name(me, sk_tmp) });
	}

	msg = msga[random(sizeof(msga))] + sprintf("%s" NOR "以及%s", 
	      implode(msgs[0..sizeof(msgs)-2], NOR "、"), msgs[sizeof(msgs)-1])
	      + NOR + msgb[random(sizeof(msgb))] + ""NOR"\n";

	message_sort(msg, me);

	return 1;
}

int halt_inventing(object me)
{
	me->set_short_desc(0);
	me->delete_temp("invent");
	tell_object(me, "你中止了自创。\n");
	message_vision(HIY "$N" HIY "起身站立，神情充满了失望。"NOR"\n", me);
	return 1;
}

string get_skill_name(object me, string skill)
{
	mapping actions;
	string  skill_name, action;
	int     a, b;

	if( !find_object(SKILL_D(skill)) && !load_object(SKILL_D(skill)) )
		return HIG + to_chinese(skill);

	if( !mapp( actions = SKILL_D(skill)->query_action(me, me->query_temp("weapon")) ) )
		return HIG + to_chinese(skill);

	if( !undefinedp(actions["skill_name"]) )
		return HIG + actions["skill_name"];

	if( undefinedp(actions["action"]) )
		return HIG + to_chinese(skill);

	action = actions["action"];

	if( strsrch(action, "「") != -1 && strsrch(action, "」") != -1 ) {
		a = strsrch(action, "「");
		b = strsrch(action, "」");
		skill_name = action[a..b+1];
		return HIG + to_chinese(skill) + NOR + (random(2)?"的一招"YEL:"中的"YEL) + skill_name + NOR;
	} else if( strsrch(action, "【") != -1 && strsrch(action, "】") != -1 ) {
		a = strsrch(action, "【");
		b = strsrch(action, "】");
		skill_name = action[a..b+1];
		return HIG + to_chinese(skill) + NOR + (random(2)?"的一招"YEL:"中的"YEL) + skill_name + NOR;
	} else if( strsrch(action, "“") != -1 && strsrch(action, "”") != -1 ) {
		a = strsrch(action, "“");
		b = strsrch(action, "”");
		skill_name = action[a..b+1];
		return HIG + to_chinese(skill) + NOR + (random(2)?"的一招"YEL:"中的"YEL) + skill_name + NOR;
	} else return HIG + to_chinese(skill);
}

int skill_t_number(string e_name)
{
	/*
	string *list;
	int    i, flag, total_z_number;

	if( !SKILL_D(e_name)->is_invent_skill() )
		return 0;
		
	list = explode(read_file(SKILL_D(e_name) + SYC), "\n");

	for( i = sizeof(list) - 1; i > 0; i-- )
	{
		if (! stringp(list[i])) continue;
		if (sscanf(list[i], "// ZHAOSHI : %d", total_z_number) == 1)
		{
			flag = 1;
			break;
		}
	}
	
	if( !flag )
	{
		write(HIR "可能出现异常了，请找巫师帮助解决。"NOR"\n");  
		return 0;    
	}
		
	return total_z_number;
	*/
	return sizeof(SKILL_D(e_name)->query_actions());
}

void input_skill_name(string arg, object me)
{
	string  c_name, e_name, skill;
	int     i;
 
	mapping temp, s_skill;
	
	temp = me->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	       
	if( sscanf(arg, "%s %s", arg, c_name) != 2 )
	{
		tell_object(me, "对不起，请用：<英文名> <中文名> 的格式输入。\n请重新输入：");
		input_to((: input_skill_name :), me);
		return;
	}
	
	if ((strlen(arg) < 3) || (strlen(arg) > 10))
	{
		tell_object(me, "对不起，英文名必须是 3 到 10 个英文字母。\n请重新输入：");
		input_to((: input_skill_name :), me);
		return;
	}

	while (i--)
	{
		if (arg[i] < 'a' || arg[i] > 'z' )
		{
			tell_object(me, "对不起，英文名只能用英文字母。\n请重新输入：");
			input_to((: input_skill_name :), me);
			return;
		}
	}
	
	skill = temp["invent"]["skill"];
	arg = arg + "-" + skill;
	e_name = arg;

	if( file_size(SKILL_D(arg) + SYC) > 0 
	 || get_object(SKILL_D(arg)) 
	 || arg != to_chinese(arg) ) {
			tell_object(me, "对不起，已经有("+ e_name +")这种武功存在。\n请重新输入：");
			input_to((: input_skill_name :), me);
			return;
	}

	if( !is_chinese(c_name) ) {
			tell_object(me, "对不起，请用【中文】做中文名。\n请重新输入：");
			input_to((: input_skill_name :), me);
			return;
	}

	if (member_array(c_name, banned_name) % 2 == 0)
	{
		tell_object(me, "对不起，这种名称会造成其他人的困扰。\n请重新输入：");
		input_to((: input_skill_name :), me);
		return;
	}

	if( strlen(c_name) > 20 ) {
		tell_object(me, "对不起，您设置的中文名太长，请选一个精湛一点的名字。\n请重新输入：");
		input_to((: input_skill_name :), me);
		return;
	}

	c_name += type_name[skill];
	s_skill["skill_e_name"] = e_name;
	s_skill["skill_c_name"] = c_name;
	
	if( CHINESE_D->find_skill(c_name) ) {
			tell_object(me, "对不起，已经有[" + c_name + "]这种武功存在。\n请重新输入：");
			input_to((: input_skill_name :), me);
			return;
	}


	tell_object(me, HIW"\n\n\n您成功的自创出了" HIG + c_name + "(" + e_name + ")" HIW "这套" + valid_types[skill]
				 + NOR "\n您可以为这个武功添加一段描述！\n"
				 "----------------------------------------------------------------\n\n"
				 + sort_msg("如：" + c_name + "是创自" + me->name(1) + "的绝世" + valid_types[skill] + 
					    "，招式勇往直前，大开大阖，以勇猛霸道而著称，当初江湖十大掌门"
					    "围攻" + me->name(1) + "的时候，情势万分危机，" + me->name(1)
					    + "在千钧一发之际使出这套武功，顿时风云变色，化险为夷……\n\n")
				 + "----------------------------------------------------------------\n\n"
				 + "请输入：");
	me->edit(bind((: call_other, __FILE__, "describe_done", me, skill, e_name, c_name :), me));
}

void describe_done(object me, string skill, string e_name, string c_name, string msg)
{
	mapping temp, s_skill;
	
	temp = me->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	
	if( !stringp( msg ) || msg == "" )
		tell_object(me, "您放弃为这套武功添加描述！\n");
	else {
		if( strlen(msg) > 1000 ) {
			tell_object(me, "您设定的描述太长了，请设定一个精简的描述。\n");
			me->edit(bind((: call_other, __FILE__, "describe_done", me, skill, e_name, c_name :), me));
			return;
		}
	}
	
	s_skill["skill_result"] = msg; 
	s_skill["skill_z_number"] = 1;
	
	tell_object(me, HIC "\n\n请给" + c_name + "招式起个名字(例如: " NOR HIY "悠哉" NOR HIC "):" NOR);	 
	input_to( "get_z_c_name", me );
}

void skill_init_header(object me, string e_name)
{
	string  header;
	mapping temp, s_skill;
	
	temp = me->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	e_name += SYC;
	
	header =  "// This is player's own skill (Write by Lonely@nt2)\n";
	header += "// Create by " + me->query("name") + "(" + capitalize(geteuid(me)) + ") at " + ctime(time()) + "\n";
	header += "// " + s_skill["skill_c_name"] + "(" + e_name + ")\n";
	header += @HEADER


inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
HEADER;
	
	write_file(SKILL_D(e_name), header, 1);
}

void get_z_c_name(string yn, object ob)
{
	mapping temp, s_skill;
	
	temp = ob->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
		
	if( yn == "" ) {
		tell_object(ob, HIC "\n\n请给" + s_skill["skill_c_name"] + "招式起个名字(例如: " NOR HIY "悠哉" NOR HIC "):" NOR);   
		input_to( (: get_z_c_name :), ob );
		return;
	}

	switch( yn[0] ) {
	case 'E':
	case 'Q':
		ob->delete_temp("invent");
		tell_object(ob, "你决定放弃自创武功。\n");
		return;
	}


	if( !is_chinese(yn) ) {
		tell_object(ob, "招式名称：");
		input_to( (: get_z_c_name :), ob );
		return;
	}
	
	s_skill["skill_name"] = yn;

	tell_object(ob, HIR "\n注意问题: $N 代表你 $n 代表敌人 $l 代表攻击部位 $w 代表你的武器 "NOR"\n");
	tell_object(ob, BLINK WHT "例如:(拳脚类)"NOR"\n");
	tell_object(ob, "$N两臂紧伸，腿脚尖点地，一式「同归黄泉」，死死的包住$n往半空中自旋而上\n\n");
	tell_object(ob, BLINK WHT "又例如:(带武器类)"NOR"\n"); 
	tell_object(ob, "$N纵身一跃，手握$w,顿时一招「斜阳竖月」对准$n的某部位斜斜刺出一剑\n\n");
	tell_object(ob, "招式描述：");

	input_to("get_z_c_action", ob);

}

void get_z_c_action(string yn, object ob)
{
	string  skill_type;
	mapping temp, s_skill;
	
	temp = ob->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	
	if (yn == "") 
	{
		tell_object(ob, HIR "\n注意问题: $N 代表你 $n 代表敌人 $l 代表攻击部位 $w 代表你的武器 "NOR"\n");
		tell_object(ob, BLINK WHT "例如:(拳脚类)"NOR"\n");
		tell_object(ob, "\t$N两臂紧伸，腿脚尖点地，一式「同归黄泉」，死死的包住$n往半空中自旋而上\n\n");
		tell_object(ob, BLINK WHT "又例如:(带武器类)"NOR"\n"); 
		tell_object(ob, "\t$N纵身一跃，手握$w,顿时一招「斜阳竖月」对准$n的某部位斜斜刺出一剑\n\n");
		tell_object(ob, "招式描述：");
		input_to((: get_z_c_action :), ob);
		return;
	}
	
	// 退出自创
	switch(yn[0])
	{
	case 'e':
	case 'q':
		ob->delete_temp("invent");
		tell_object(ob, "你决定放弃自创武功招式。\n");
		return;
	}
	
	skill_type = temp["invent"]["skill"];
	
	s_skill["action"] = color_filter(yn);
	s_skill["action"] = replace_string(s_skill["action"], " ", "");
	s_skill["action"] = replace_string(s_skill["action"], "你", "$N");
	s_skill["action"] = replace_string(s_skill["action"], "老猫", "$n");	       
	s_skill["action"] = replace_string(s_skill["action"], "某部位", "$l");	      

	if ( member_array(skill_type, weapon_types) != -1 )
		s_skill["action"] = replace_string(s_skill["action"], "武器", "$w");
		
       // 自创武工的威力由武修、人物等级、智商决定
	s_skill["attack"] = ob->query("level") + ob->query("int") + 
			    sizeof(ob->query_temp("invent/mut_skills")) * 10 +
			    ob->query_skill("martial-cognize", 1) / 10;			       
	s_skill["damage"] = ob->query("level") + ob->query("str") + 
			    sizeof(ob->query_temp("invent/mut_skills")) * 10 +
			    ob->query_skill("martial-cognize", 1) / 10;
	s_skill["force"]  = ob->query("level") + ob->query("con") + 
			    sizeof(ob->query_temp("invent/mut_skills")) * 10 +    
			    ob->query_skill("martial-cognize", 1) / 10;										    
	s_skill["dodge"]  = ob->query("level") + ob->query("dex") + 
			    sizeof(ob->query_temp("invent/mut_skills")) * 10 + 
			    ob->query_skill("martial-cognize", 1) / 10;								
	s_skill["parry"]  = ob->query("level") + ob->query("con") + 
			    sizeof(ob->query_temp("invent/mut_skills")) * 10 +
			    ob->query_skill("martial-cognize", 1) / 10;

	switch(skill_type){
	case "unarmed":
		s_skill["damage_type"] = "瘀伤";
		break;
	case "sword":
	case "spin":
		s_skill["damage_type"] = "刺伤";
		break;
	case "blade":
		s_skill["damage_type"] = "割伤";
		break;
	case "strike":
		s_skill["damage_type"] = "内伤";
		break;
	default:
		s_skill["damage_type"] = "瘀伤";
		break;
	}			     
	s_skill["lvl"] = spe_skill_level[s_skill["skill_z_number"] - 1];				
	
	if (s_skill["skill_z_number"] == 1)			
		tell_object(ob, HIR "\n你自创了一套" + s_skill["skill_c_name"] + "(" + s_skill["skill_e_name"] + ")"NOR"\n"
				HIY "武功类型：" NOR HIC + valid_types[skill_type] + ""NOR"\n"
				HIY "武功描述："NOR"\n" HIC + s_skill["skill_result"] + ""NOR"\n"
				HIY "首招名称：" NOR HIC + s_skill["skill_name"] + ""NOR"\n"
				HIY "首招描述：" NOR HIC + s_skill["action"] + ""NOR"\n"
				HIY "首招攻击：" NOR HIC + s_skill["attack"] + ""NOR"\n"
				HIY "首招伤害：" NOR HIC + s_skill["damage"] + ""NOR"\n"
				HIY "附加伤害：" NOR HIC + s_skill["force"] + ""NOR"\n"
				HIY "首招招架：" NOR HIC + s_skill["parry"] + ""NOR"\n"
				HIY "首招躲闪：" NOR HIC + s_skill["dodge"] + ""NOR"\n"
				HIR "你确定吗？(Y/N)" NOR);
	else
		tell_object(ob, HIR "你自创了一套" + s_skill["skill_c_name"] + "(" + s_skill["skill_e_name"] + 
				HIR ")的第" + chinese_number(s_skill["skill_z_number"]) + "招"NOR"\n"
				HIY "此招名称：" NOR HIC + s_skill["skill_name"] + ""NOR"\n"
				HIY "此招描述：" NOR HIC + s_skill["action"] + ""NOR"\n"
				HIY "此招攻击：" NOR HIC + s_skill["attack"] + ""NOR"\n"
				HIY "此招伤害：" NOR HIC + s_skill["damage"] + ""NOR"\n"
				HIY "附加伤害：" NOR HIC + s_skill["force"] + ""NOR"\n"
				HIY "此招招架：" NOR HIC + s_skill["parry"] + ""NOR"\n"
				HIY "此招躲闪：" NOR HIC + s_skill["dodge"] + ""NOR"\n"
				HIR "你确定吗？(Y/N)" NOR); 

	input_to("decide_input", ob, skill_type, s_skill["skill_e_name"], s_skill["skill_c_name"]);
}

void decide_input(string arg, object me, string skill, string e_name, string c_name)
{
	object  ob;
	mapping temp, s_skill;
	
	temp = me->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
		
	if( arg == "y" || arg == "Y" ) {
		if( s_skill["skill_z_number"] == 1 ) {
			if( objectp( ob = get_object(SKILL_D(e_name)) ) ) {
				me->delete_temp("invent");
				tell_object(me, "BUG！请联系巫师！\n");
				return;
			}
		
			finish_write_skill(me, e_name);

			log_file("INVENT", sprintf("%s(%s) %s(%s): %d (%s)\n",
					   me->query("name"),
					   me->query("id"),
					   c_name,
					   e_name,
					   s_skill["skill_z_number"],
					   ctime(time())));

			if( get_object(SKILL_D(e_name)) ) {
				CHANNEL_D->do_channel(this_object(), "rumor",
					sprintf("%s(%s)将生平所学的" + chinese_number(sizeof(me->query_temp("invent/mut_skills")))
						+ "套" + valid_types[skill] + "合而为一，自创出一套绝世的" NOR HIW
						+ "《" + c_name + "》" NOR HIM "，从此进入"
						+ valid_types[skill] + "的全新境界 。" NOR,
						me->name(1), me->query("id")));
				me->force_me("chat* admire2 " + me->query("id"));
			
				CHINESE_D->add_translate(e_name, c_name);			
					
				me->set("invent/" + skill, e_name);
				me->set_skill(e_name, 100);
				me->delete_temp("invent");
				me->save();
			}

		} else {
			if( !objectp( ob = get_object(SKILL_D(e_name)) ) ) {
				me->delete_temp("invent");
				tell_object(me, "BUG！请联系巫师！\n");
				return;
			}			
			destruct(ob);
			finish_write_skill(me, e_name);
			get_object(SKILL_D(e_name));
			log_file("INVENT", sprintf("%s(%s) %s(%s): %d (%s)\n",
					   me->query("name"),
					   me->query("id"),
					   c_name,
					   e_name,
					   s_skill["skill_z_number"],
					   ctime(time())));
					   
			CHANNEL_D->do_channel(this_object(), "rumor",
					   sprintf("%s(%s)将生平所学融合吸收，为" NOR HIW + "《" + c_name + "》" NOR
					   HIM "创出新的招式" NOR HIC + "《" + s_skill["skill_name"] + "》" NOR + HIM "。" , 
					   me->name(1), me->query("id")));
						
			me->force_me("chat* admire2 " + me->query("id"));
			me->delete_temp("invent");
			me->save();
		} 


	} else {
		if( s_skill["skill_z_number"] == 1 ) {
			tell_object(me, HIW"请重新输入！"
					HIY"格式："HIC"<英文名> <中文名>\n"NOR"\n"
					"如输入：wuyou 无忧\n"
					"系统会产生一种无忧"HIR + type_name[skill] + NOR "(wuyou-"
					HIR + skill + NOR")的剑法\n"
					HIW"勿用骚扰性或不雅的名字"NOR"\n"
					"请输入：");
			input_to("input_skill_name", me, skill);
		} else {
			tell_object(me, HIC "\n\n请给" + c_name + "新招式起个名字(例如: " NOR HIY "悠哉" NOR HIC "):" NOR);	  
			input_to( "get_z_c_name", me ); 
		}		       
	}
}

void finish_write_skill(object ob, string skill)
{
	mapping temp, s_skill;
	string  action;
	string  file, *list;
	string  content;
	int     total_z_number, i, flag;
	string  *list2;
	string  header2;
	string  result;
	string  skill_type;	
	
	temp = ob->query_entire_temp_dbase();
	s_skill = temp["invent"]["spe_skill"];
	skill_type = temp["invent"]["skill"];
	header2 = "";
	result = "";
	content = "";
	action = "";  

	if( s_skill["skill_z_number"] == 1 )
		skill_init_header(ob, skill);      
	  
	action += "\n([      " + SYN + 
		  "action" + SYN + " : " + SYN + s_skill["action"] + SYN + ",\n\t" + SYN + 
		  "attack" + SYN + " : " +  s_skill["attack"] + ",\n\t" + SYN + 
		  "damage" + SYN + " : " +  s_skill["damage"] + ",\n\t" + SYN + 
		  "force" + SYN + " : " +  s_skill["force"] + ",\n\t" + SYN +
		  "dodge" + SYN + " : " + s_skill["dodge"] + ",\n\t" + SYN + 
		  "parry" + SYN + " : " + s_skill["parry"] + ",\n\t" + SYN + 
		  "lvl" + SYN + " : " + s_skill["lvl"] + ",\n\t" + SYN + 
		  "damage_type" + SYN + " : " + SYN + s_skill["damage_type"] + SYN + ",\n\t" + SYN + 
		  "skill_name" + SYN + " : " + SYN + s_skill["skill_name"] + SYN +
		  "\n ])," +
		  "\n// ZHAOSHI : " + s_skill["skill_z_number"];
	action += "\n});\n";

	file = read_file(SKILL_D(skill + SYC));
	if( (int)file != 0 )
		list = explode(file, "\n");

	if( skill_type == "unarmed" 
		|| skill_type == "strike"
		|| skill_type == "finger" )
		header2 = read_file(SKILL_MODEL_UNARMED);
	else if( skill_type=="sword" 
		|| skill_type == "blade"
		|| skill_type=="spear"
		|| skill_type=="hammer"
		|| skill_type=="whip" )
		header2 = read_file(SKILL_MODEL_WEAPON);
	else 
		header2 = read_file(SKILL_MODEL_DEFAULT);

	list2 = explode(header2, "\n");
	for( i = 0; i < sizeof(list2); i++ ) {
		list2[i]= replace_string(list2[i], "SKILL_EN_NAME", 
			  SYN + skill + SYN);
		list2[i]= replace_string(list2[i], "SKILL_CH_NAME", 
			  SYN + s_skill["skill_c_name"] + SYN);
		list2[i]= replace_string(list2[i], "SKILL_BASE_NAME", 
			  SYN + skill_type + SYN);
	}
	
	result += implode(list2, "\n");

	for( i = sizeof(list) - 1; i > 0; i-- ) {
		if (! stringp(list[i])) continue;
		if (sscanf(list[i], "// ZHAOSHI : %d", total_z_number) == 1)
		{
			flag = 1;
			break;
		}
	}
	
	if( !flag )
	{
		tell_object(ob, HIR "可能出现异常了，请找巫师帮助解决。"NOR"\n");  
		return;    
	}

	content =  implode(list[0..i-1], "\n");
	content += "\n// ZHAOSHI : " + (string)total_z_number;
	content += action;
	write_file(SKILL_D(skill) + SYC, content, 1);	
	write_file(SKILL_D(skill) + SYC, "\n" + result);
	
	if( stringp(s_skill["skill_result"]) ) {
		s_skill["skill_result"] = replace_string(s_skill["skill_result"], "\n", "");
		s_skill["skill_result"] = sort_msg(s_skill["skill_result"]);
	
		content = @CODE
string query_description()
{
CODE;
		content += "\treturn\n \"" + s_skill["skill_result"] + "\" ; \n}\n";
	
		write_file(SKILL_D(skill) + SYC, "\n" + content); 
	}       
}

int help(object me)
{
	write(@HELP
					 
指令格式: invent		查看自己自创武功的情况
	  invent ?	      查看目前可以自创的武功种类
	  invent <基本武功>     自创一种武功
	  invent <已创武功>     继续自创一种武功的招式
	  invent <基本武功> ?   查看该基本武功的已创武功
	  invent <基本武功> d   删除该基本武功的已创武功

历来武林中堪称一代宗师者，均是于武学上总结己之所学，并能
融会各家之所长，开创武林中先河者。武学虽然可能源于一脉，
但各人所学加之经历之不同，却对同一事物有不同领悟。如此，
武林才变得如今般绚丽多彩。然而，开辟武林中的新溪经并非易
事，需要耗费无数心血及精力才有可能独树一帜，成先人所未曾
想。 

HELP );
	return 1;
}