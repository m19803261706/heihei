// by luoyun

inherit ROOM;

void create()
{
	set("short", "南街一号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"guangchang",
		"south" : __DIR__"nanjie2",
	]));
	set("objects", ([
	]));
	setup();
}