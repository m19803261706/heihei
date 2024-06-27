// Room: /d/songshan/chaotian.c
inherit ROOM;

void create()
{
	set("short", "朝天户");
	set("long", @LONG
陡见双峰中断，天然出现一个门户，疾风从断绝处吹出，云雾
随风扑面而至，这里就是朝天户了。
LONG );
	set("exits", ([
		"northup"   : __DIR__"shandao6",
		"southdown" : __DIR__"shandao5",
	]));
	set("outdoors", "songshan");
	set("no_clean_up", 0);
	setup();
}

