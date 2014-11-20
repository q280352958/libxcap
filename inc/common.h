#ifndef _COMMON_H_
#define _COMMON_H_

typedef struct _common_conf common_conf;

common_conf *
common_conf_new();

void
common_conf_destroy(common_conf *a_conf);

common_conf *
common_get_instance();

void
common_read_conf();

char *
common_get_username(common_conf *a_conf);

char *
common_get_password(common_conf *a_conf);

char *
common_get_host(common_conf *a_conf);

char *
common_get_root(common_conf *a_conf);

char *
common_get_auid(common_conf *a_conf);

char *
common_get_xui(common_conf *a_conf);

char *
common_get_home_directory(common_conf *a_conf);

#endif