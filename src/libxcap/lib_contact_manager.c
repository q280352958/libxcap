#include "lib_contact_manager.h"
#include "lib_xcap.h"

struct _contact_request
{
	xcap_uri *uri;		//统一资源定位符
	char *list_name;	//联系人列表名
	char *contact_id;	//联系人ID
	char *contact_name;	//联系人名称
};

struct _contact_list
{
	char *temp;//待定
};