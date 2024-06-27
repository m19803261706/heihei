// usersd.c


#include <mudlib.h>
#include <dbase.h>

inherit F_DBASE;
inherit F_SAVE;

mapping vips;
mapping qiandao;
mapping paym;
mapping vdata;
mapping daoshi;

void create()
{
	seteuid(ROOT_UID);
	if( !restore() )
	{
		vips= ([]);
		qiandao = ([]);
		vdata = ([]);
		paym = ([]);
		daoshi = ([]);
	}
	if( !mapp(vips) )
		vips = ([]);
	if( !mapp(qiandao) )
		qiandao = ([]);
	if( !mapp(vdata) )
		vdata = ([]);
	if( !mapp(paym) )
		paym = ([]);
	if( !mapp(daoshi) )
		daoshi = ([]);
}

int remove()
{
	save();
	return 1;
}

string query_save_file() { return DATA_DIR + "vipd"; }

int add_order(string name)
{
	if( undefinedp(vips["order"]) ) vips["order"]=({});
	vips["order"] += ({name});
	save();
	return 1;
}

int delete_order(string name)
{
	vips["order"] -= ({name});
	save();
	return 1;
}

mixed set_vips(string prop, mixed data)
{
	if( !mapp(vips ) ) vips = ([]);

	if( strsrch(prop, '/')!=-1 )
		return _set( vips , explode(prop, "/"), data );

	return vips[prop] = data;
}

mixed query_vips(string prop)
{
	mixed data;

	if( !mapp(vips) ) return 0;

	if( undefinedp(vips[prop]) && (strsrch(prop, '/')!=-1) )
		data = _query(vips, explode(prop, "/"));
	else
		data = vips[prop];

	return data;
}

mixed set_daoshi(string prop, mixed data)
{
	if( !mapp(daoshi ) ) daoshi = ([]);

	if( strsrch(prop, '/')!=-1 )
		return _set( daoshi , explode(prop, "/"), data );

	return daoshi[prop] = data;
}

int delete_daoshi(string prop)
{
	if( !mapp(daoshi) ) return 0;

	if( (strsrch(prop, '/')!=-1) )
		return _delete(daoshi, explode(prop, "/"));
	else
	{
		map_delete(daoshi,prop);
		return 1;
	}
}

string *list_daoshi()
{
 

	if( !mapp(daoshi) ) return 0;

	return keys(daoshi);
}

mixed query_daoshi(string prop)
{
	mixed data;

	if( !mapp(daoshi) ) return 0;

	if( undefinedp(daoshi[prop]) && (strsrch(prop, '/')!=-1) )
		data = _query(daoshi, explode(prop, "/"));
	else
		data = daoshi[prop];

	return data;
}

mixed set_qian(string prop, mixed data)
{
	if( !mapp(qiandao ) ) qiandao = ([]);

	if(intp(data)&&data > 3000 && strsrch(prop,"/jf_used")==-1)
		data = 3000;
	if( strsrch(prop, '/')!=-1 )
		return _set( qiandao , explode(prop, "/"), data );

	return qiandao[prop] = data;
}

mixed query_qian(string prop)
{
	mixed data;

	if( !mapp(qiandao) ) return 0;

	if( undefinedp(qiandao[prop]) && (strsrch(prop, '/')!=-1) )
		data = _query(qiandao, explode(prop, "/"));
	else
		data = qiandao[prop];

	return data;
}

string *list_qian()
{
 

	if( !mapp(qiandao) ) return 0;

	return keys(qiandao);
}
int delete_qian(string prop)
{
	if( !mapp(qiandao) ) return 0;

	if( (strsrch(prop, '/')!=-1) )
		return _delete(qiandao, explode(prop, "/"));
	else
	{
		map_delete(qiandao,prop);
		return 1;
	}
}
mixed set_paym(string prop, mixed data)
{
	if( !mapp(paym) ) paym = ([]);

	if( strsrch(prop, '/')!=-1 )
		return _set( paym , explode(prop, "/"), data );

	return paym[prop] = data;
}

mixed query_paym(string prop)
{
	mixed data;

	if( !mapp(paym) ) return 0;

	if( undefinedp(paym[prop]) && (strsrch(prop, '/')!=-1) )
		data = _query(paym, explode(prop, "/"));
	else
		data = paym[prop];

	return data;
}

int add_paym(string t,mapping paym)
{
	set_paym(t,paym);
	save();
	return 1;
}

int save_vdata(object me)
{
	vdata[me->query("id")] = ([]);
	vdata[me->query("id")]["yuanbao"] = me->query("yuanbao");
	vdata[me->query("id")]["vtime"] = me->query("zjvip/times");
	vdata[me->query("id")]["vipgift"] = me->query("zjvip/vipgift");
	vdata[me->query("id")]["all_pay"] = me->query("zjvip/all_pay");
	save();
	return 1;
}

int restore_vdata(object me)
{
	if(undefinedp(vdata[me->query("id")])) return 1;

	me->set("yuanbao",vdata[me->query("id")]["yuanbao"]);
	me->set("zjvip/times",vdata[me->query("id")]["vtime"]);
	me->set("zjvip/vipgift",vdata[me->query("id")]["vipgift"]);
	me->set("zjvip/all_pay",vdata[me->query("id")]["all_pay"]);
	map_delete(vdata,me->query("id"));
	save();
	return 1;
}