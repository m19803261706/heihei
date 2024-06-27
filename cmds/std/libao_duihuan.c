#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
  object ob;
  string libaoma;


  ob = me;

  if (!arg)
  {
    write(INPUTTXT("请输入礼包码","libao_duihuan $txt#")+"\n");
    return 1;
  }
  else
  {
      // 读取/u/libaoma文件
    libaoma = read_file("/u/libaoma");

    // 是否有这个礼包码
    if (strsrch(libaoma, arg) == -1)
    {
      return notify_fail("没有这个礼包码。\n");
    }

    if (!ob->query("taptap2"))
    {
      object obj;
      obj = new_bind ("/clone/vip/dan_jiuzhuan");
      obj->set_amount(5);
      obj->move(ob);
      obj = new_bind ("/clone/baiyi/tencard");
      obj->set_amount(2);
      obj->move(ob);
      ob->set("taptap2", 1);
      ob->add("yuanbao",200);
      tell_object(ob, HIR "你收到了礼包奖励哦，200元宝，二个十连抽卡片，5个九转金丹，祝您游戏愉快。"NOR"\n");
    }
    else
    {
      tell_object(ob,"你已经领取过礼包了。\n");
      return 1;
    }

    // 如果有这个礼包码，删除这个礼包码
    libaoma = replace_string(libaoma, arg, "");

    // 写回/u/libaoma文件
    write_file("/u/libaoma", libaoma, 1);

    return 1;
  }




  return notify_fail("你已经领过了啊。\n");
}