// by luoyun

inherit ROOM;

void create()
{
	set("short", "北街二号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"beijie1",
		"north" : __DIR__"beijie3",
	]));
	set("objects", ([
	]));
	setup();
}