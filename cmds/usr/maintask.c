#include <ansi.h>
inherit F_CLEAN_UP;
mapping teshe=([
"华山派":"华山派分为气宗和剑宗，可以互相来回拜师学习技能，华山剑宗弟子使用相应的剑法有剑气伤害加成拜师要求：无",
"武当派":"道学心法可以静修提高，250道学可以开始静修。武当派有额外气血加成。静修地点：武当藏经阁，消耗潜能。\n拜师要求:对悟性要求较高",
"少林派":"少林派弟子内力极限多500。少林专用技能静修（jingxiu），增加禅宗，跟后天悟性相关。拜师要求：男性",
"峨眉派":"峨嵋派前期内力多，气血多。武学需要大乘涅槃功。峨嵋派弟子内力极限多500。峨眉弟子专用技能静坐（指令jingzuo）（增加微量经验和潜能，跟大乘等级相关）（40大乘等级可以静坐）。峨眉入门收男女，只有单身女性可以出家。（出家后能学临济和各类绝招，未出家能学所有技能但没有内功和绝招。",
"桃花岛":"桃花岛的阴阳八卦属于悟性流留学的，能提高面对特殊招架特殊轻功敌人的命中率。",
"丐帮":"丐帮弟子可以直接学镇岳锁龙劲，其他门派弟子，男号可以结婚之后，老婆送食物后学习，女号只能靠倚天屠龙的降龙秘籍。",
"星宿派":"星宿激发冰蚕寒功，加力后攻击带毒。基本毒技50，化灵大法80，才能炼毒、制毒。",
"逍遥派":"悟性流适合新人的门派，北冥内功系数高，防御高，师门六阳掌前期伤害也足。",
"古墓派":"古墓的怒海狂涛内功战气，加成空手伤害。",
"全真教":"周天功特技五气朝元，可以在战斗中使用，消耗内力回复气血及上限。道学心法可以在武当藏经阁静修提高，250道学可以开始静修。",
"神龙教":"销骨绵掌的毒性叠加速度很快。",
"雪山派":"雪山派弟子内力极限多500。拜师要求：男性",
"血刀门":"血海魔功特技——祭血大法，增加伤害和激发等级。血刀门弟子内力极限多500。拜师要求：男性",
"灵鹫宫":"九天十地唯我至尊功战气加成伤害。",
"欧阳世家":"欧阳家蛤蟆功的经脉逆转，能增加抗毒疗毒能力。",
"关外胡家":"胡家妙手驱毒增加抗毒疗毒效果。",
"慕容世家":"慕容家内功差，不仅系数低，还没有护体。慕容家移星换斗算是不错的特殊招架。",
"段氏皇族":"段家内功一般，但是使用六极神剑有特效加成，100%触发特效。",					
]);

mapping task_describe=([
"一":"入得泥潭来，皆是江湖人。要想在江湖立足，就得先确定你的出身和门派，此事万万不可草率，否则悔之无及！请选择一个门派拜师！",
"二":"即已入江湖，何不学得一招半式，仗剑走天涯。请你向师傅请教，并学习一门武学。",
"三":"初入江湖的时候，手里一无钱，二无经验，这时候可以通过一些简单的工作来赚取一些钱并获得经验值和潜能。你可以自由选择做以下工作，1分钟后系统自动给予你奖励，加油吧！侠客。",
"四":"有人的地方就有江湖，请举起你手中的利剑，正式闯荡这乱世江湖吧！请完成一次师门任务！",
]);
//任务奖励列表
mapping task_reward=([
"一":(["combat_exp":30000,"potential":20000,"obj":"/clone/maintask/obj/yueka"]),
"二":(["combat_exp":10000,"potential":10000,"obj":"/clone/maintask/obj/tianxiang"]),
"三":(["potential":10000,"obj":"/clone/maintask/obj/jiuzhuan"]),
"四":(["combat_exp":30000,"potential":20000,"obj":"/clone/maintask/obj/bianxingdan"]),
]);

mapping work_place=([
"打铁":"walk 铁匠",
"分药":"walk 平易指",
"抄书":"walk 朱熹",
"炒菜":"walk 厨娘",
]);
//门派武功和飞行地点。
mapping menpai=([
"华山派":(["walk":"walk 劳有诺","skill":"九剑归一"]),
"武当派":(["walk":"walk 谷虚道长","skill":"太极拳，太极神功"]),
"少林派":(["walk":"walk 虚明","skill":"易筋经，少林七十二绝技"]),
"峨眉派":(["walk":"walk 静慧师太","skill":"临济十二庄"]),
"桃花岛":(["walk":"walk 黄岛主","skill":"云箫剑法，弹指神功"]),
"丐帮":(["walk":"walk 左全","skill":"镇岳锁龙劲"]),
"星宿派":(["walk":"walk 摘心毒手","skill":"冰蚕神功"]),
"逍遥派":(["walk":"walk 冯三","skill":"青冥神功，洛神步法"]),
"古墓派":(["walk":"walk 龙姑娘","skill":"补天剑诀"]),
"全真教":(["walk":"walk 尹至平","skill":"周天功"]),
"神龙教":(["walk":"walk 洪教主","skill":"销骨绵掌"]),
"雪山派":(["walk":"walk 葛伦布","skill":"龙象般若功"]),
"血刀门":(["walk":"walk 善勇","skill":"血河神刀"]),
"灵鹫宫":(["walk":"walk 梅侍","skill":"九天十地唯我至尊功"]),
"欧阳世家":(["walk":"walk 欧阳锋","skill":"蛤蟆功"]),
"慕容世家":(["walk":"walk 慕容柏","skill":"移星换斗，参星指"]),
"关外胡家":(["walk":"walk 胡飞","skill":"飞狐刀法，百胜刀法"]),
"段氏皇族":(["walk":"walk 段正纯","skill":"六极神剑"]),
]);
//任务完成的参数
mapping task_requirement = ([
"一":"family/master_name",//成功拜师，有师傅
"二":"study_skill",//第一次学习技能
"三":"task_work",//完成工作
"四":"shimen/lun",//有师门记录
]);
string task_msg(int task_process,string arg,object me);
int task_zt(object me);
int main(object me, string arg)
{
	int task_process = me->query("maintask");
	string guocheng;
	guocheng = chinese_number(task_process+1);
 if (task_process < sizeof(keys(task_reward)))//左右对比，完成上限
 {
  if (!arg)
   tell_object(me,task_msg(task_process+1,"task",me));   
   else
   tell_object(me,task_msg(task_process+1,arg,me));   
 }
 else
 tell_object(me,"你已经是一个真正的江湖人士了，请举起你手中的利剑，闯出浩浩荡荡的一遍天！\n");   
	return 1;
}
string task_msg(int task_process,string arg,object me)
{
string msg;
 if (task_process==1||task_process==3)
 {
 //是否是门派
 if(arg!="task")
 {
 msg = ZJOBLONG+teshe[arg]+ZJBR"特色武功："+menpai[arg]["skill"]+"\n";
msg +=ZJOBACTS2+ZJMENUF(3,3,10,35); 
msg+="选择拜师:"+menpai[arg]["walk"]+ZJSEP;
msg+="返回界面:maintask\n";
return msg;
}
 msg = ZJOBLONG+task_describe[chinese_number(task_process)]+"\n";
  msg +=ZJOBACTS2+ZJMENUF(3,3,10,35); 
  if (task_process==1)
  {
  string *all_menpai_name,menpai_name;
  all_menpai_name=keys(menpai);
  foreach (menpai_name in all_menpai_name)  
  msg+=menpai_name+":maintask "+menpai_name+ZJSEP;  
  }
  else if(task_process==3)
  {
  string *all_work_name,work_name;
  all_work_name=keys(work_place);
  foreach (work_name in all_work_name)
  msg += work_name+":"+work_place[work_name]+ZJSEP;
  //1分钟后自动给奖励
  me->set("task_work",1);
  call_out("task_zt",60,me);
  }
  
 }
 else 
 {
 msg = ZJOBLONG+task_describe[chinese_number(task_process)]+"\n";
  msg +=ZJOBACTS2+ZJMENUF(2,2,10,35); 
  msg+="快速赶往:walk "+me->query("family/master_name")+ZJSEP;
  }
  msg+="返回界面:maintask\n";
   return msg;
}
int task_zt(object me)
{
 string guocheng;
	guocheng = chinese_number(me->query("maintask")+1);
  if(me->query(task_requirement[guocheng]))//任务是否完成
   {
   	object ob;
   int bexp = task_reward[guocheng]["combat_exp"];
   int bpot = task_reward[guocheng]["potential"];
   me->add("combat_exp",bexp);
   me->add("potential",bpot);
  ob = new(task_reward[guocheng]["obj"]);
  ob->move(me);
  tell_object(me,"恭喜你完成主线任务"+guocheng+"，获得经验："+bexp+"，潜能："+bpot+"，"+ob->query("name")+"\n");
  me->add("maintask",1);
   }
   return 1;
}
int help(object me)
{
	write(@HELP
主线任务。
HELP
	);
	return 1;
}
