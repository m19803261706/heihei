#include <ansi.h>

inherit F_CLEAN_UP;
void lingqu_gift(mapping gift_list, object me);     //发放物品奖励

// mapping attribute_chinese = ([
//      "skill_gem":"自选武学或宝物机会一次",
// ]);

int main(object me, string arg)
{
     //各级VIP所需要的贡献
     int * vip_gongxian = ({ 30,50,100,200,300,400, 500,600,1000, 2000/*, 3000, 4000, 5000, 6000, 7000, 9000, 10000*/});

     //item为奖励的物品，skill_gem为自选宝物或武功次数
     mapping vip_gitf = ([
          1 : ([ "item" : ([ "/clone/vip/qiankun_lingbei" : 1, "/clone/vip/dan_jiuzhuan":2,"/clone/vip/putao1":2]), ]),//30
          2 : ([ "item" : ([ "/clone/vip/butian" : 2,  "/clone/vip/dan_jiuzhuan":2,"/clone/vip/putao1":4,"/clone/baiyi/tencard":1]), ]),//50
          3 : ([ "item" : ([ "/clone/vip/dan_chongmai1" : 50,  "/clone/shizhe/mengzi":1,"/clone/vip/putao1":5,"/clone/baiyi/tencard":1]), ]),//100
          4 : ([ "item" : ([ "/clone/vip/dan_chongmai1" : 100,  "/clone/shizhe/mengzi":1,"/clone/vip/putao1":5,"/clone/baiyi/tencard":1,"/clone/shizhe/kuilei":1]), ]),//200
          5 : ([ "item" : ([ "/clone/vip/dan_chongmai1" : 150, "/clone/vip/putao1":5,"/clone/baiyi/tencard":1,"/clone/shizhe/kuilei":1]), ]),//300
          6 : ([ "item" : ([ "/clone/vip/dan_chongmai1" : 200, "/clone/vip/putao1":5,"/clone/baiyi/tencard":1,"/clone/shizhe/kuilei":1]), ]),//400
          7 : ([ "item" : ([ "/clone/vip/dan_chongmai2" : 50, "/clone/vip/putao1":5,"/clone/baiyi/tencard":1,"/clone/shizhe/kuilei":1]), ]),//500
          8 : ([ "item" : ([ "/clone/vip/dan_chongmai2" : 100, "/clone/vip/putao1":5,"/clone/baiyi/tencard":1,"/clone/shizhe/kuilei":1]), ]),//600
          9 : ([ "item" : ([ "/clone/vip/dan_chongmai3" : 100, "/clone/vip/dan_xixin":1,"/clone/baiyi/tencard":2,"/clone/shizhe/kuilei":2]), ]),//1000
          10 : ([ "item" : ([ "/clone/vip/dan_chongmai3" : 200]),"skill_gem" : 1 ]),//2000
     ]);

     string * skill_list = ({
          "jiuyang-shengong",
          // "shenzhaojing",
          "qishang-quan",
          "baihua-quan",
          "hanbing-mianzhang",
          "xuanming-zhang",
          "sougu",
          "zhuihun-jian",
          "yunlong-bian",
          "hanxing-bada",
          "bizhen-qingzhang",
          "huanyin-zhi",
          "ningxue-shenzhao",
          "sanfen-jianshu",
          "zijinbagua-dao",
     });

     string * gem_list = ({
          "/clone/aoyi_book/aoyi_book",
     });

     int vip_level = 0;
     int i;
     string sign;
     int choose_lvl;
     string str = "";
     string temp;
     string skill_id;
     string gem_file_name;
     object gem;

     //计算VIP等级
     for (i = 0; i < sizeof(vip_gongxian); i++)
     {
          if (me->query("zjvip/all_pay") >= vip_gongxian[i])
               vip_level++;
          else
               break;
     }

     if (!arg || arg == "")
     {
          string msg = "";
          
          tell_object(me, ZJOBLONG + "你当前的贡献等级为" + vip_level + "，通过每日签到和观看游戏广告可以获得游戏贡献，你要执行什么操作？\n" + ZJOBACTS2 + "查看奖励列表:new_fanli reward_list" + ZJSEP + "兑换贡献奖励:new_fanli vip" + ZJSEP + "自选宝物:new_fanli gem" + ZJSEP + "自选武功:new_fanli skill\n");
          return 1;
     }


     if  (arg == "reward_list")
     {
          // 罗列贡献奖励
          str = ZJOBLONG + "贡献等级奖励列表："ZJBR;
          str += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡"NOR + ZJBR;
          for (i = 0; i < sizeof(vip_gongxian); i++)
          {
               string single_msg = "等级" + chinese_number(i + 1) + ":" + vip_gongxian[i] + "贡献"ZJBR;

               foreach (temp in keys(vip_gitf[i + 1]["item"]))
               {
                    single_msg += "    " + load_object(temp)->query("name") + "x" + vip_gitf[i + 1]["item"][temp] + ZJBR;
               }

               if (vip_gitf[i + 1]["skill_gem"])
               {
                    single_msg += "    自选武功/宝物机会x" + vip_gitf[i + 1]["skill_gem"] + ZJBR;
               }
               single_msg += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡"NOR + ZJBR;
               str += single_msg;
          }

          str += "\n";
          str += ZJOBACTS2 + "返回:new_fanli\n";
          tell_object(me, str);
     }


     //兑换VIP奖励
     if (arg[0..2] == "vip")
     {

          if (sscanf(arg, "%*s %d %s", choose_lvl, sign) == 3)
          {
               if (sign != "y")
               {
                    tell_object(me, "领取VIP奖励时，输入参数错误，请重试。\n");
                    return 1;
               }

               lingqu_gift(vip_gitf[choose_lvl]["item"], me);    //发放物品奖励

               if (vip_gitf[choose_lvl]["skill_gem"])
               {
                    me->add("cxpay/skill_gem", vip_gitf[choose_lvl]["skill_gem"]);
                    tell_object(me, "你获得了" + vip_gitf[choose_lvl]["skill_gem"] + "次自选武功/宝物机会。\n");
               }
               log_file("cxpay/vip", ctime(time()) + me->query("name") + "(" + me->query("id") + ")领取了" + choose_lvl + "级VIP返利。\n");
               me->set("cxpay/fanli_lingqu/" + choose_lvl, 1);

               return 1;
          }
          else if (sscanf(arg, "%*s %d", choose_lvl) == 2)
          {
               if (me->query("cxpay/fanli_lingqu/" + choose_lvl))
               {
                    tell_object(me, "你已经领取过该等级的返利了。\n");
                    return 1;
               }

               tell_object(me, ZJOBLONG + "你确定兑换" + choose_lvl + "级VIP奖励吗？\n" + ZJOBACTS2 + "确定:new_fanli vip " + choose_lvl + " y\n");
               return 1;
          }
          else 
          {
               if (0 == vip_level) 
               {
                    tell_object(me, ZJOBLONG + "你目前的VIP等级为0，无法兑换。\n");
                    return 1;
               }

               str += ZJOBLONG + "你目前可以兑换的VIP返利为：\n" + ZJOBACTS2;

               for (i = 1; i <= vip_level; i++)
               {
                    str += "等级" + chinese_number(i) + ":new_fanli vip " + i + ZJSEP;
               }

               tell_object(me, str + "\n");
               return 1;
          }
     }
     // else
     // {
     //      tell_object(me,arg[0..2] + "\n");
     // }

     //自选武功
     if (arg[0..4] == "skill")
     {
          if (sscanf(arg, "%*s %s %s", skill_id, sign) == 3)
          {
               if (sign != "y")
               {
                    tell_object(me, "自选武功时，输入参数错误，请重试。\n");
                    return 1;
               }

               me->add("cxpay/skill_gem", -1);
               me->set_skill(skill_id, 180);
               log_file("cxpay/skill", ctime(time()) + me->query("name") + "(" + me->query("id") + ")兑换了" + to_chinese(skill_id) + "。\n");
               tell_object(me, "你兑换了" + to_chinese(skill_id) + "。\n");

               return 1;
          }
          else if (sscanf(arg, "%*s %s", skill_id) == 2)
          {
               if (me->query("cxpay/skill_gem") < 1)
               {
                    tell_object(me, "你的自选武功/宝物次数不够了。\n");
                    return 1;
               }

               if (me->query_skill(skill_id))
               {
                    tell_object(me, ZJOBLONG + "你已经学会了" + to_chinese(skill_id) + "你确定要兑换吗？(兑换会覆盖原等级)\n" + ZJOBACTS2 + "确定:new_fanli skill " + skill_id + " y\n");
                    return 1;
               }

               tell_object(me, ZJOBLONG + "你确定要兑换" + to_chinese(skill_id) + "吗？\n" + ZJOBACTS2 + "确定:new_fanli skill " + skill_id + " y\n");
               return 1;
          }
          else
          {
               if (!sizeof(skill_list))
               {
                    tell_object(me, ZJOBLONG + "现在还没有可兑换的武功。\n");
                    return 1;
               }

               str += ZJOBLONG + "目前可以兑换的武功有：\n" + ZJOBACTS2;

               foreach (temp in skill_list)
               {
                    str += to_chinese(temp) + ":new_fanli skill " + temp + ZJSEP;
               }

               tell_object(me, str + "\n");
               return 1;
          }
     }

     //自选宝物
     if (arg[0..2] == "gem")
     {
          if (sscanf(arg, "%*s %s %s", gem_file_name, sign) == 3)
          {
               if (sign != "y")
               {
                    tell_object(me, "自选宝物时，输入参数错误，请重试。\n");
                    return 1;
               }

               if (!objectp(gem = new(gem_file_name)))
               {
                    tell_object(me, "领取自选宝物出错，请联系管理员处理。\n");
                    return 1;
               }

               log_file("cxpay/gem", ctime(time()) + me->query("name") + "(" + me->query("id") + ")领取了" + gem->query("name") + "。\n");
               tell_object(me, "你兑换了一" + (gem->query_amount()?gem->query("base_unit"):gem->query("unit")) + gem->query("name") + "。\n");
               me->add("cxpay/skill_gem", -1);
               gem->move(me);

               return 1;
          }
          else if (sscanf(arg, "%*s %s", gem_file_name) == 2)
          {
               if (me->query("cxpay/skill_gem") < 1)
               {
                    tell_object(me, "你的自选武功/宝物次数不够了。\n");
                    return 1;
               }

               tell_object(me, ZJOBLONG + "你确定要兑换" + load_object(gem_file_name)->query("name") + "吗？\n" + ZJOBACTS2 + "确定:new_fanli gem " + gem_file_name + " y\n");
               return 1;
          }
          else
          {
               if (!sizeof(gem_list))
               {
                    tell_object(me, ZJOBLONG + "目前还没有可以兑换的宝物。\n");
                    return 1;
               }

               str += ZJOBLONG + "目前可以兑换的宝物有：\n" + ZJOBACTS2;
               foreach (temp in gem_list)
               {
                    str += load_object(temp)->query("name") + ":new_fanli gem " + temp + ZJSEP;
               }

               tell_object(me, str + "\n");
               return 1;
          }
     }

     return 1;
}


void lingqu_gift(mapping gift_list, object me)
{
     string temp;
     object gift;
     int i;

     foreach (temp in keys(gift_list))
     {
          if (!objectp(gift = new(temp)))
          {
               tell_object(me, "领取" + temp + "时出错。\n");
               continue;
          }

          if (gift->query_amount())
          {
               gift->set_amount(gift_list[temp]);
               tell_object(me, "你获得了" + gift_list[temp] + gift->query("base_unit") + gift->query("name") + "。\n");
               gift->move(me);
          }
          else
          {
               i = 0;
               do {
                    if (0 == i)
                    {
                         gift->move(me);
                         i++;
                         continue;
                    }

                    if (!objectp(gift = new(temp)))
                    {
                         tell_object(me, "领取" + temp + "时出错。\n");
                         i++;
                         break;
                    }

                    gift->move(me);
                    i++;
               } while (i < gift_list[temp]);
               tell_object(me, "你获得了" + i + gift->query("unit") + gift->query("name") + "\n");
          }
     }
}