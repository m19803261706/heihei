// xingxingtan.c

inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
int do_yell(string arg);
void reset();

void create()
{
	set("short", "猩猩滩");
	set("long", @LONG
只见一片长滩，山石殷红如血，水流湍急，这便是有名的猩
猩滩，对面岸边停泊着几艘小船(boat)，要过对面就要靠这几艘
小船了。
LONG    );
	set("outdoors", "heimuya");
	set("exits", ([
	    "eastup" : __DIR__"shidao2",
	]));
	set("item_desc", ([
	    "【小船】" : "一叶小舟隐藏在芦苇中，喊(yell)一声试看。\n"
			ZJOBACTS2"叫船:yell boat\n",
	]));
	set("no_clean_up", 0);
	set("outdoors", "heimuya");
	setup();
}

void init()
{
    add_action("do_yell", "yell");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
	if( !(room = find_object(__DIR__"duchuan1")) )
	    room = load_object(__DIR__"duchuan1");
	if( room = find_object(__DIR__"duchuan1") ) {
	    if((int)room->query("yell_trigger")==0 ) {
		room->set("yell_trigger", 1);
		set("exits/enter", __DIR__"duchuan1");
		room->set("exits/out", __FILE__);
		message("vision", "一叶扁舟缓缓地驶了过来，艄公将一块踏脚"
		    "板搭上堤岸，以便乘客\n上下。\n", this_object() );
		message("vision", "艄公将一块踏脚板搭上堤岸，形成一个向上"
		    "的阶梯。\n", room);
		remove_call_out("on_board");
		call_out("on_board", 15);
	    }
	    else
		message("vision", "只听得风浪中隐隐传来：“别急嘛，"
		    "这儿正忙着呐……”\n",this_object() );
	}
	else
	    message("vision", "ERROR: boat not found\n", this_object() );
    }
    else 
	message("vision", "岸边一只渡船上的艄公说道：正等着你呢，上来吧。\n",
	    this_object() );
}


void on_board()
{
    object room;

    if( !query("exits/enter") ) return;

    message("vision", "艄公把踏脚板收了起来，竹篙一点，扁舟向河中撑去。\n",
	this_object() );

    if( room = find_object(__DIR__"duchuan1") )
    {
	room->delete("exits/out");
	message("vision", "艄公把踏脚板收起来，说了一声“坐稳喽”，"
	    "竹篙一点，扁舟向\n河中撑去。\n", room );
    }
    delete("exits/enter");

    remove_call_out("arrive");
    call_out("arrive", 20);
}

void arrive()
{
    object room;
    if( room = find_object(__DIR__"duchuan1") )
    {
	room->set("exits/out", __DIR__"changtan");
	message("vision", "艄公说“到啦，上岸吧”，随即把一块踏脚板"
	    "搭上堤岸。\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"duchuan1") ) {
	room->delete("exits/out");
	message("vision","艄公把踏脚板收起来，把扁舟撑向河近岸。\n", room);
	room->delete("yell_trigger"); 
    }
}

int do_yell(string arg)
{
    

    if( !arg || arg=="" ) return 0;

    if( arg=="boat" ) arg = "船家";
    if( (int)this_player()->query("age") < 16 )
	message_vision("$N使出吃奶的力气喊了一声：“" + arg + "”\n",
	    this_player());
    else if( (int)this_player()->query("neili") > 500 )
	message_vision("$N吸了口气，一声“" + arg + "”，声音中正平和地远远传"
	    "了出去。\n", this_player());
    else
	message_vision("$N鼓足中气，长啸一声：“" + arg + "！”\n",
	    this_player());
    if( arg=="船家")
    {
	check_trigger();
	return 1;
    }
    else
	message_vision("风浪中远远传来一阵回声：“" + arg +
	    "～～～”\n", this_player());
    return 1;
}

void reset()
{
    object room;

    ::reset();
    if( room = find_object(__DIR__"duchuan1") )
	room->delete("yell_trigger"); 
}