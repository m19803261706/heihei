inherit ROOM;

void create()
{
	set("short", "中央广场");
	set("long", @LONG
这里是城市的正中心，一个很宽阔的广场。中央有一棵大榕树，据传已有千年的树龄，是这座城市的历史见证。树干底部有一个很大
的树洞。
LONG );
	set("no_sleep_room",1);
	set("outdoors", "city");
	set("item_desc", ([
		"【树洞】" : "这是一个黑不溜湫的大洞，里面不知道有些什么古怪。\n"
		ZJOBACTS2"钻洞:enter dong\n",
	]));

	set("exits", ([
		"northeast" : __DIR__"shengxiantang",
		"northwest" : __DIR__"banghui",
		"southeast" : __DIR__"heishi",
		"east" : __DIR__"dongdajie1",
		"south" : __DIR__"nandajie1",
		"west" : __DIR__"xidajie1",
		"north" : __DIR__"beidajie1",
		"southwest" : __DIR__"lajichang",
	]));

	set("objects", ([
		__DIR__"npc/liapo" : 1,
	     
	]));

	setup();
}

void init()
{
	add_action("do_enter", "enter");
}

int do_enter(string arg)
{
	object me;
	me = this_player();

	if (! arg || arg == "")
		return 0;

	if (arg == "dong")
	{
		if (me->is_busy())
			return notify_fail("你的动作还没有完成，不能移动。\n");

		message("vision",
			me->name() + "一弯腰往洞里走了进去。\n",
			environment(me), ({me}) );
		me->move("/d/gaibang/inhole");
		message("vision",
			me->name() + "从洞里走了进来。\n",
			environment(me), ({me}) );
		return 1;
	}
}       
