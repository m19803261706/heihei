// by luoyun

inherit ROOM;

void create()
{
	set("short", "北街三号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"beijie2",
		"north" : __DIR__"beijie4",
		"east" : __DIR__"wulinyi1",
		"west" : __DIR__"wulinyi20",
	]));
	set("objects", ([
	]));
	setup();
}