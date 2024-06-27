// Room: /d/xiangyang/caodi1.c
inherit ROOM;


void create()
{
	set("short", "草地");
	set("long", @LONG
这是襄阳城外的草地。蒙古兵进犯以来，这里的百姓全进
城了，蒙古兵驰骋来去，以为牧场，尘土飞扬，甚是嚣张。
LONG );
	set("outdoors", "xiangyang");

	set("exits", ([
		"west"  : __DIR__"northgate2",
	]));
	set("objects", ([
		__DIR__"npc/tuolei"   : 1,
		__DIR__"npc/menggubing" : 2,
	]));
	setup();
}

