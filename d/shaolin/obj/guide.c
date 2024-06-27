

inherit ITEM;

void create()
{
	set_name( HIC "『少林拜师必读』" NOR, ({ "bidu", "guide" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
"\n		 『少林拜师必读』\n\n"
"少林位于扬州城北少室山，新玩家由南麓北上山道，沿途攀\n"
"登八里十六段的石级到达山门。女性及手持兵刃的非少林弟\n"
"子都不能进山门。按约放下兵器，由守护山门的两位知客僧\n"
"收存後，再行向上攀登。寺前是一个松柏围绕的广场，排列\n"
"着一组组石人石兽，东西各是郁郁苍苍的忪林，正前方往北\n"
"就是少林寺的正门，广场上寥寥站着几个青年僧人，他们是\n"
"清无，清为，和清法三僧，俗家弟子到此止步，可直接拜三\n"
"僧为师学些入门的少林功夫。如果愿易剃度入我佛门，取法\n"
"号後可进入少林寺，从今以後就成为一名正式的少林弟子。\n"
"穿过少林寺的三进大雄宝殿，参拜如来等诸佛後，即到达寺\n"
"前的练武场。练武场上有各种习武的设施，如木人，沙坑，\n"
"草靶以及练习硬功的砖石等，大部分慧字辈和道字辈的僧人\n"
"都在练武场上授徒，新进的少林弟子可拜师而从，学习自己\n"
"感兴趣的武功。平时可下山除暴安良，履行一名正派弟子的\n"
"职责。武功达到一定水平後可凭达摩令挑战，如能战胜高辈\n"
"弟子或师友，则可晋升为道字辈或慧字辈，与以前的师父并\n"
"列，玩家之间也可切磋技艺，以求提高。本寺弟子武艺达到\n"
"一定程度，即可以进入藏经阁进修本派武功，待时机成熟，\n"
"可以向罗汉堂玄枯，玄劫二长老提出破罗汉阵的要求。罗汉\n"
"阵由本寺十八罗汉组成，每人各擅长一种一种武功，长老同\n"
"意後十八位高僧即鱼贯而出在练武场中心布下罗汉阵，若要\n"
"破阵，玩家需承受每位罗汉僧集毕生精力之一击，玩家可凭\n"
"轻功躲避或以本身擅长的武功拆解，总之，如果能承受十八\n"
"招不死或昏迷，该弟子即升为澄字辈与十八罗汉并列，并可\n"
"获准进入达摩院研习破解别门武功的方法。并且自身的各项\n"
"属性都会有较大提高。玩家的下个目标就是等待每年正月十\n"
"五，本寺两位渡字辈长老驾临，他们将根据该弟子的根骨，\n"
"资质以及行侠仗仪的事迹，决定是否破格收录为弟子。该玩\n"
"家一但有幸成为二位长老的关门弟子，他即可与本寺五大神\n"
"僧并列玄字辈，位尊无比，并可委任为藏经阁阁主或僧监监\n"
"长一职，并可直接进入武林大会的决赛圈。其他诸多好处，\n"
"不必细表。\n");
		set("value", 100);
		set("material", "paper");
	}
	setup();
}
