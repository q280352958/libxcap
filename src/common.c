#include "common.h"
#include "ezxml.h"
#include <string.h>

struct _common_conf
{
    char *username;
    char *password;
    char *xcap_host;
    char *xcap_root;
    char *xcap_auid;
    char *xcap_xui;
    char *xcap_home_directory;
};

common_conf *common_config;

common_conf *
common_conf_new()
{
    common_conf *l_return = NULL;
    l_return = malloc(sizeof(common_conf));
    memset(l_return, 0, sizeof(common_conf));
    return l_return;
}

void
common_conf_destroy(common_conf *a_conf)
{
    if (a_conf->username)
    {
        free(a_conf->username);
        a_conf->username = NULL;
    }
    if (a_conf->password)
    {
        free(a_conf->password);
        a_conf->password = NULL;
    }
    if (a_conf->xcap_host)
    {
        free(a_conf->xcap_host);
        a_conf->xcap_host = NULL;
    }
    if (a_conf->xcap_root)
    {
        free(a_conf->xcap_root);
        a_conf->xcap_root = NULL;
    }
    if (a_conf->xcap_auid)
    {
        free(a_conf->xcap_auid);
        a_conf->xcap_auid = NULL;
    }
    if (a_conf->xcap_xui)
    {
        free(a_conf->xcap_xui);
        a_conf->xcap_xui = NULL;
    }
    if (a_conf->xcap_home_directory)
    {
        free(a_conf->xcap_home_directory);
        a_conf->xcap_home_directory = NULL;
    }
    free(a_conf);
}

common_conf *
common_get_instance()
{
    if (common_config == NULL)
    {
        common_config = common_conf_new();
    }
    return common_config;
}

void
common_read_conf(common_conf *a_conf)
{
    ezxml_t conf = ezxml_parse_file("libxcap.conf");
    ezxml_t username;
    ezxml_t password;
    ezxml_t host;
    ezxml_t root;
    ezxml_t auid;
    ezxml_t xui;
    ezxml_t home_directory;

    username = ezxml_child(conf, "username");
    password = ezxml_child(conf, "password");
    host = ezxml_child(conf, "host");
    root = ezxml_child(conf, "root");
    auid = ezxml_child(conf, "auid");
    xui = ezxml_child(conf, "xui");
    home_directory = ezxml_child(conf, "home-directory");

    a_conf->username = strdup(username->txt);
    a_conf->password = strdup(password->txt);
    a_conf->xcap_host = strdup(host->txt);
    a_conf->xcap_root = strdup(root->txt);
    a_conf->xcap_auid = strdup(auid->txt);
    a_conf->xcap_xui = strdup(xui->txt);
    a_conf->xcap_home_directory = strdup(home_directory->txt);

    ezxml_free(conf);
}

char *
common_get_username(common_conf *a_conf)
{
    return a_conf->username;
}

char *
common_get_password(common_conf *a_conf)
{
    return a_conf->password;
}

char *
common_get_host(common_conf *a_conf)
{
    return a_conf->xcap_host;
}

char *
common_get_root(common_conf *a_conf)
{
    return a_conf->xcap_root;
}

char *
common_get_auid(common_conf *a_conf)
{
    return a_conf->xcap_auid;
}

char *
common_get_xui(common_conf *a_conf)
{
    return a_conf->xcap_xui;
}

char *
common_get_home_directory(common_conf *a_conf)
{
    return a_conf->xcap_home_directory;
}