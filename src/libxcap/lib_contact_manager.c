#include <stdio.h>
#include <string.h>
#include "lib_contact_manager.h"
#include "lib_xcap.h"
#include "common.h"
#include "ezxml.h"

typedef struct xcap_request _contact_request;


contact_request *
contact_request_new()
{
    xcap_request *l_return = xcap_request_new();
    common_conf *conf = common_get_instance();
    common_read_conf(conf);
    xcap_set_host(l_return, common_get_host(conf));
    xcap_set_root(l_return, common_get_root(conf));
    xcap_set_auid(l_return, common_get_auid(conf));
    xcap_set_xui(l_return, common_get_xui(conf));
    xcap_set_home_directory(l_return, common_get_home_directory(conf));
    xcap_set_username(l_return, common_get_username(conf));
    xcap_set_password(l_return, common_get_password(conf));
    common_conf_destroy(conf);
    return (contact_request *)l_return;
}

void
contact_request_destroy(contact_request *a_request)
{
    xcap_request *request = (xcap_request *)a_request;
    xcap_request_destroy(request);
}

contact_list *
contact_list_new()
{
    contact_list *list = NULL;
    list = (contact_list *)malloc(sizeof(struct _contact_list));
    memset(list, 0, sizeof(struct _contact_list));
    return list;
}

void
contact_list_destroy(contact_list *a_list)
{
    contact_list *tmp, *next;
    tmp = a_list;
    while (tmp != NULL)
    {
        next = tmp->next;
        tmp->next = NULL;

        if (tmp->uri)
        {
            free(tmp->uri);
            tmp->uri = NULL;
        }
        if (tmp->name)
        {
            free(tmp->name);
            tmp->name = NULL;
        }
        free(tmp);
        tmp = next;
    }
}

int
contact_add(contact_request *a_request, char *a_uri, char *a_display_name)
{
    xcap_request *request = (xcap_request *)a_request;
    char body_buf[100], attr_buf[100];
    memset(body_buf, 0, 100);
    memset(attr_buf, 0, 100);
    snprintf(body_buf,
             100,
             "<entry uri=\"%s\">\r\n" \
             "<display-name>%s</display-name>\r\n" \
             "</entry>\r\n",
             a_uri,
             a_display_name
            );
    snprintf(attr_buf,
             100,
             "/~~/resource-lists/list[@name=\"friends\"]/entry[1][@uri=\"%s\"]",
             a_uri);
    printf("body = %s\n", body_buf);
    request->body_data = strdup(body_buf);
    if (xcap_put(request, attr_buf, request->body_data) == SCODE_OK)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int
contact_del(contact_request *a_request, char *a_uri)
{
    xcap_request *request = (xcap_request *)a_request;
    char attr_buf[100];
    memset(attr_buf, 0, 100);
    snprintf(attr_buf,
             100,
             "/~~/resource-lists/list[@name=\"friends\"]/entry[1][@uri=\"%s\"]",
             a_uri);
    if (xcap_del(request, attr_buf) == SCODE_OK)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int
contact_query(contact_request *a_request, contact_list *a_list)
{
    xcap_request *request = (xcap_request *)a_request;
    contact_list *p = a_list;
    if (xcap_get(request) == SCODE_OK)
    {
        ezxml_t resource_lists = ezxml_parse_str(request->io_buf, strlen(request->io_buf));
        if (resource_lists)
        {
            ezxml_t list = ezxml_child(resource_lists, "list");
            ezxml_t entry = ezxml_child(list, "entry");
            for (; entry; entry = entry->next)
            {
                contact_list *_list = (contact_list *)malloc(sizeof(struct _contact_list));
                _list->uri = strdup(ezxml_attr(entry, "uri"));
                _list->name = strdup(ezxml_child(entry, "display-name")->txt);
                p->next = _list;
                p = p->next;
            }
            ezxml_free(list);
            printf("parse success!\n");
        }
        else
        {
            printf("parse faild!\n");
        }
    }
    return 0;
}