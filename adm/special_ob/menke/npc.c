
inherit NPC;
#include "pfms.h"
int doing_quest();
int end_quest();
void create()
{
	set_name("门客", ({ "menke" }));
	set("age", 22);
	set("gender", "男性");
	set("long", "。\n");
	set("attitude", "peaceful");

	set("str", 30);
	set("dex", 30);
    set("con", 30);
    set("int", 30);
	// 标记为门客
	set("is_menke", 1);
                
	set("combat_exp", 1000000);
	set("shen_type", 1);

	set_temp("apply/attack", 30);
	set_temp("apply/defense", 30);
	set_temp("apply/damage", 30);
	set_temp("apply/armor", 30);

	// 设置心跳
	keep_heart_beat();

	setup();
	carry_object("/clone/cloth/cloth")->wear();
}


// 门客撤退函数
void retreat()
{
	object me = this_object();
	object ob;
	ob = find_player(me->query("master_id"));

	// 如果门客的主人在线
	if (objectp(ob))
	{
		// 门客离开房间后，主人会收到消息
		tell_object(ob, "你的门客返回了。\n");
	}

	if (objectp(environment(me)))
	{
		// 门客离开房间
		message_vision("$N匆匆离开了。\n", me);
	}
	destruct(me);
}

// 初始化属性
void init_attr(int level)
{
	object me = this_object();
	mixed *fight_pfms = ({});
	// 门客的等级
	me->set("level", level);

	// 门客的属性
	me->set("str", 30 + level / 50);
	me->set("int", 30 + level / 50);
	me->set("con", 30 + level / 50);
	me->set("dex", 30 + level / 50);

	// 设定自身的技能等级为level,并恢复满状态
	me->set_skill("force", level);
	me->set("max_qi", level * 100);
	me->set("eff_qi", level * 100);
	me->set("qi", level * 100);
	me->set("max_jing", level * 100);
	me->set("eff_jing", level * 100);
	me->set("jing", level * 100);
	me->set("max_neili", level * 100);
	me->set("neili", level * 100);
	me->set("jiali", level);


	// 经验为等级 * 1万
	me->set("combat_exp", (level * level * level) / 10);

	foreach (string skill in keys(me->query_skills()))
	{
		me->set_skill(skill, level);
	}

	// 处理可以释放的技能
	foreach (string exert_name in pfms[me->query("paixi")]["exert_function"])
	{
		fight_pfms += ({(: exert_function, exert_name :)});
	}

	foreach (string perform_name in pfms[me->query("paixi")]["perform_action"])
	{
		fight_pfms += ({(: perform_action, perform_name :)});
	}

	set("chat_chance_combat", 80);
	set("chat_msg_combat", fight_pfms);

	me->set("level", level);

	// 门客的附加属性
	me->set_temp("apply/attack", 300 + level);
	me->set_temp("apply/defense", 30 + level);
	me->set_temp("apply/damage", 300 + level);
	me->set_temp("apply/armor", 30 + level);
}

// 门客升级函数
void upgrade(int level)
{
	object me = this_object();

	// 初始化门客的属性
	init_attr(level);

	// 门客升级后，在地图上显示：xx感到一股热流在体内涌动，这是武艺即将突破的前兆。xx紧闭双眼，全神贯注地引导着这股热流。他的身体周围渐渐泛起淡淡的光晕，这是武艺提升的明显迹象。经过一番努力，他成功地突破了瓶颈，武艺更上一层楼
	message_vision("$N感到一股热流在体内涌动，这是武艺即将突破的前兆。\n", me);
	message_vision("$N紧闭双眼，全神贯注地引导着这股热流。\n", me);
	message_vision("碧云的身体周围渐渐泛起淡淡的光晕，这是武艺提升的明显迹象。\n", me);
	message_vision("经过一番努力，$N成功地突破了瓶颈，武艺更上一层楼。\n", me);

	// 门客说：谢主公提携，在下终于突破了瓶颈，武艺更上一层楼。
	command("say 谢主公提携，在下终于突破了瓶颈，武艺更上一层楼。");

}

// 心跳函数
void heart_beat()
{
	object ob;
	object me = this_object();
	object where = environment(me);

	// 如果门客正在执行任务，调用doing_quest函数
	if (query("doing_quest"))
	{
		doing_quest();
	}

	// 我身上是否有武器，如果没有，我就去找一个
	if (!me->query_temp("weapon"))
	{
		if (me->query("weapon_path"))
		{
			carry_object(me->query("weapon_path"))->wield();
		}
	}
	

	// 如果门客在房间里，检查门客的主人是否在房间里,门客的主人的id是query("master_id"),正在执行任务不做任何处理
	if ( (where && stringp(me->query("master_id")))  && !query("doing_quest"))
	{
		ob = find_player(me->query("master_id"));

		//我的等级和主人记录等级不一样，那么我就升级，主人记录的等级：(menke_system/menke_msg/level)
		if (me->query("level") != ob->query("menke_system/menke_msg/level"))
		{
			upgrade(ob->query("menke_system/menke_msg/level"));
		}


		// 主公和我不在同一房间
		if (!objectp(ob) || environment(ob) != where)
		{
			// 如果门客的主人不在房间里，门客就离开房间
			message_vision("$N匆匆离开了。\n", me);
			retreat();
			
			destruct(me);
			return;
		}
		 else
		{
			//如果我不在战斗，主人在战斗，那么挑选一个主人的敌人，加入战斗
			if (!me->is_fighting() && (objectp(ob) && ob->is_fighting()))
			{
				object targer;
				targer = ob->select_opponent();

				if (objectp(targer))
				{
					me->kill_ob(targer);
				}

				command("say 大胆狂徒，竟敢在我主公面前撒野！");
			}
		}
	}
	else if (!query("doing_quest"))
	{
		// 如果门客不在房间里，门客就离开房间
		retreat();
		return;
	}

	// 调用父类的心跳函数
	::heart_beat();
}

// 开始执行任务
int start_shimen_quest(object player)
{
	object me;
	mapping mlist;
	string family_name;
	string family_man_path;
	me = this_object();

	// 门客先取消跟随
	command("follow none");

	mlist = QUEST_D->query_mlist();
	me->set("family", player->query("family"));//将玩家的门派信息记录在门客身上
	family_name = player->query("family/family_name");

	family_man_path = mlist[family_name];//找到门派的师傅文件路径
	me->set("shimen_accept_name",family_man_path->query("name"));//记录任务发放者的名称，后续使用门客使用walk直接传送到任务发放者处
	me->set("shimen_accept_id",family_man_path->query("id"));	// 记录任务发布者的id

	me->set("doing_quest",1);//标记门客正在执行任务
	player->set("menke_system/doing_quest",1);//标记玩家的门客正在执行任务

	//门客即将寻找xxx，执行师门任务
	tell_object(player,me->name()+"即将寻找"+me->query("shimen_accept_name")+"，执行师门任务。\n");
	return 1;
}

//任务结束，接受返回任务
int end_quest()
{
	object me = this_object();
	object master;

	me->delete("doing_quest");
	me->delete("end_quest");

	master = find_player(me->query("master_id"));

	me->move(environment(master));
	// 属下不负主公重托，已完成任务。请主公清点任务收益
	command("say 属下不负主公重托，已完成任务。请主公清点任务收益");
	MENKE_M->give_reward_master(me,master);

	return 1;
}

//接受远程任务
int accept_distance_quest()
{
	object letter;
	object me = this_object();
	object master;

	master = find_player(me->query("master_id"));


	//如果我身上有end_quest参数，接受召回结束任务
	if (me->query("end_quest"))
	{
		end_quest();
		return 1;
	}
	
	//这里有一个逻辑点，当我完成任务后，任务精灵会发放奖励，发放奖励时会清除quest参数，所以这个时候要重区分检测letter
	if (objectp(letter = present("letter", me)))
	{

		if (query("doing_quest"))
		{
			// 如果我身上有quest letter，那么我就接受远程任务
			command("accept quest");
		}
		else
		{
			command("refuse quest");
		}
		

		// 告诉主人，我完成了任务，准备进行下一个任务
		if (objectp(master))
		{
			tell_object(master, me->name() + "完成了师门任务，准备进行下一个任务。\n");
		}

		return 1;
	}

}

// 预留接口用于处理师门任务
int doing_quest()
{
	object me = this_object();
	object master;
	mapping quest;

	master = find_player(me->query("master_id"));

	// 第一步 如果当前我没有领取任务，那么我就领取任务【先检查我身上有没有quest信息，如果没有，我就去玩家师傅处领取任务】
	// 第二步 如果我身上有quest信息，开始执行任务，找到任务地点，击杀目标对象。
	// 第三步 检查我身上有没有师门信件，也就是quest letter，我就领取任务。

	//优先级是：
	// 逻辑1.检查是否有quest参数，如果有代表正在执行任务的过程中。（1.1逻辑，检查身上是否有quest/finished参数，如果有代表任务已经完成，执行逻辑2）
	// 逻辑2：检查身上是否有quest letter，接受远程任务。
	// 逻辑3：如果身上没有quest参数，前往玩家师傅处领取任务。

	// 如果我正在战斗直接return
	if (me->is_fighting())
	{
		return 1;
	}

	if (me->query("quest"))
	{
		object env;
		object target;

		quest = me->query("quest");


		// 我的身上是否有quest["finished"]参数，如果有代表任务已经完成
		if (quest["finished"])
		{
			return 1;//强判定，如果任务完成，等待远程任务发放
		}


		// 检查当前环境下是否存在quest["id"]的对象，如果有Kill掉
		env = environment(me);

		if (objectp(env) && objectp(present(quest["id"], env)))
		{
			target = present(quest["id"], env);
			command("kill " + quest["id"]);
		}
		else
		{
			target = query("quest/object");
			// 如果没有找到quest["id"]的对象，清除quest参数
			if (!objectp(target))
			{
				me->delete("quest");
				return 1;
			}
			
			me->move(environment(target));
		}

		return 1;

	}
	else 
	{

		if (me->query("end_quest"))
		{
			end_quest();
			return 1;
		}

		// 开始领取任务
		// 当前地点是否存在任务发布者shimen_accept_id
		if (objectp(present(me->query("shimen_accept_id"), environment(me))))
		{
			command("quest " + me->query("shimen_accept_id"));

			//告诉玩家，我已经到达目的地领取任务完成
			if (objectp(master))
			{
				tell_object(master, me->name() + "已经到达目的地领取任务完成。\n");
			}
		}
		else
		{
			// 如果没有找到任务发布者，那么我就去玩家师傅处领取任务
			command("walk " + me->query("shimen_accept_name"));
		}
	}

}




// 门客死亡清除所有quest
 varargs void die(object target)
{
	object me = this_object();

	// 如果有target，记录谁击败了我
	if (objectp(target))
	{
		me->set("killed_by", target->query("id"));
	}

	me->delete("quest");
	// 恢复全部状态
	me->set("eff_qi", me->query("max_qi"));
	me->set("qi", me->query("max_qi"));
	me->set("eff_jing", me->query("max_jing"));
	me->set("jing", me->query("max_jing"));
	me->set("neili", me->query("max_neili"));
	
	if (! living(me))
	{
		me->revive();
	}

	//移除所有中毒状态
	me->clear_condition();
	// 回到广场
	me->move("/d/city/guangchang");
}

// 昏迷直接die走复活流程
void unconcious()
{
	die();
}

