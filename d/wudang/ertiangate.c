//Room: ertiangate.c 二天户
//Date: Sep 22 1997

inherit ROOM;

void create()
{
      set("short","二天户");
      set("long",@LONG
这里是“二天户”，金光灿灿的金顶就在眼前了。
LONG);
      set("exits",([ /* sizeof() == 1 */
	  "northdown": __DIR__"toutiangate",
	  "southup"  : __DIR__"santiangate",
      ]));
      set("outdoors", "wudang");
      set("no_clean_up", 0);
      setup();
      //replace_program(ROOM);
}
