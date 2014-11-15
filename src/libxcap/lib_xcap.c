#include <stdlib.h>
#include <string.h>
#include "lib_xcap.h"
#include "ghttp.h"
#include "http_resp.h"

xcap_uri *
xcap_uri_new(void)
{
    struct _xcap_uri *l_return = NULL;
    l_return = malloc(sizeof(struct _xcap_uri));
    memset(l_return, 0, sizeof(struct _xcap_uri));
    return l_return;
}

void
xcap_uri_destory(xcap_uri *a_uri)
{
    if (!a_uri)
        return;
    if (a_uri->xcap_host)
    {
        free(a_uri->xcap_host);
        a_uri->xcap_host = NULL;
    }
    if (a_uri->xcap_auid)
    {
        free(a_uri->xcap_auid);
        a_uri->xcap_auid = NULL;
    }
    if (a_uri->xcap_xui)
    {
        free(a_uri->xcap_xui);
        a_uri->xcap_xui = NULL;
    }
    if (a_uri->xcap_home_directory)
    {
        free(a_uri->xcap_home_directory);
        a_uri->xcap_home_directory = NULL;
    }
    if (a_uri->full)
    {
        free(a_uri->full);
        a_uri->full = NULL;
    }
    free(a_uri);
}

xcap_request *
xcap_request_new(void)
{
    struct _xcap_request *l_return = NULL;
    l_return = malloc(sizeof(struct _xcap_request));
    memset(l_return, 0, sizeof(struct _xcap_request));
    l_return->uri = xcap_uri_new();
    return l_return;
}

void
xcap_request_destroy(xcap_request *a_request)
{
    if (!a_request)
        return;
    if (a_request->uri)
    {
        xcap_uri_destory(a_request->uri);
    }
    if (a_request->username)
    {
        free(a_request->username);
        a_request->username = NULL;
    }
    if (a_request->password)
    {
        free(a_request->password);
        a_request->password = NULL;
    }
    if (a_request->io_buf)
    {
        free(a_request->io_buf);
        a_request->io_buf = NULL;
    }
    free(a_request);
}

void
xcap_set_host(xcap_request *a_request, const char *a_host)
{
    a_request->uri->xcap_host = strdup(a_host);
}

void
xcap_set_auid(xcap_request *a_request, const char *a_auid)
{
    a_request->uri->xcap_auid = strdup(a_auid);
}

void
xcap_set_xui(xcap_request *a_request, const char *a_xui)
{
    a_request->uri->xcap_xui = strdup(a_xui);
}

void
xcap_set_home_directory(xcap_request *a_request, const char *a_home_directory)
{
    a_request->uri->xcap_home_directory = strdup(a_home_directory);
}

void
xcap_set_username(xcap_request *a_request, const char *a_username)
{
    a_request->username = strdup(a_username);
}

void
xcap_set_password(xcap_request *a_request, const char *a_password)
{
    a_request->password = strdup(a_password);
}

void
xcap_uri_encode(xcap_uri *a_uri)
{
    const char HTTP_HEADER[] = "http://";
    const char XCAP_ROOT[] = "/xcap-root/";
    const char USERS[] = "/users/";
    const char SLASH[] = "/";
    int length = 0;
    length = strlen(HTTP_HEADER)
             + strlen(a_uri->xcap_host)
             + strlen(XCAP_ROOT)
             + strlen(a_uri->xcap_auid)
             + strlen(USERS)
             + strlen(a_uri->xcap_xui)
             + strlen(SLASH)
             + strlen(a_uri->xcap_home_directory);
    a_uri->full = (char *)malloc(length);
    memset(a_uri->full, 0, length);
    strncat(a_uri->full, HTTP_HEADER, strlen(HTTP_HEADER));
    strncat(a_uri->full, a_uri->xcap_host, strlen(a_uri->xcap_host));
    strncat(a_uri->full, XCAP_ROOT, strlen(XCAP_ROOT));
    strncat(a_uri->full, a_uri->xcap_auid, strlen(a_uri->xcap_auid));
    strncat(a_uri->full, USERS, strlen(USERS));
    strncat(a_uri->full, a_uri->xcap_xui, strlen(a_uri->xcap_xui));
    strncat(a_uri->full, SLASH, strlen(SLASH));
    strncat(a_uri->full, a_uri->xcap_home_directory, strlen(a_uri->xcap_home_directory));
}

int
xcap_get(xcap_request *a_request)
{
    int result = -1;
    ghttp_request *request = NULL;
    char *body_buf = NULL;
    request = ghttp_request_new();
    xcap_uri_encode(a_request->uri);
    ghttp_set_uri(request, a_request->uri->full);
    ghttp_set_header(request, http_hdr_Connection, "close");
    ghttp_prepare(request);
    ghttp_process(request);

    if (ghttp_status_code(request) == 401)
    {
        char *ghttp_digest_value = NULL;
        ghttp_request *request_new = ghttp_request_new();
        char *unauthorized_data = ghttp_get_header(request, http_hdr_WWW_Authenticate);
        ghttp_set_uri(request_new, a_request->uri->full);
        ghttp_set_header(request_new, http_hdr_Connection, "close");
        ghttp_digest_value = ghttp_digest_encode(request_new, a_request->username, a_request->password, unauthorized_data);
        ghttp_set_header(request_new,
                         http_hdr_Authorization,
                         ghttp_digest_value);
        ghttp_prepare(request_new);
        ghttp_process(request_new);
        body_buf = ghttp_get_body(request_new);
        a_request->io_buf = (char *)malloc(strlen(body_buf));
        memset(a_request->io_buf, 0, strlen(body_buf));
        memcpy(a_request->io_buf, body_buf, strlen(body_buf));
        result = ghttp_status_code(request_new);
        ghttp_request_destroy(request_new);
    }
    else
    {
        body_buf = ghttp_get_body(request);
        a_request->io_buf = (char *)malloc(strlen(body_buf));
        memset(a_request->io_buf, 0, strlen(body_buf));
        memcpy(a_request->io_buf, body_buf, strlen(body_buf));
        result = ghttp_status_code(request);
    }
    ghttp_request_destroy(request);
    return result;
}

int
xcap_put(xcap_request *a_request, char *a_body)
{
    int result = -1;
    ghttp_request *request = NULL;
    char *body_buf = NULL;
    char *io_buf = NULL;
    request = ghttp_request_new();
    xcap_uri_encode(a_request->uri);
    ghttp_set_uri(request, a_request->uri->full);
    ghttp_set_type(request, ghttp_type_put);
    ghttp_set_header(request, http_hdr_Accept_Encoding, "identity");
    ghttp_set_header(request, http_hdr_Connection, "close");
    ghttp_set_header(request, http_hdr_Content_Type, "application/x-www-form-urlencoded");
    ghttp_set_body(request, a_body, strlen(a_body));
    ghttp_prepare(request);
    ghttp_process(request);
    result = ghttp_status_code(request);
    if (ghttp_status_code(request) == 401)
    {
        char *ghttp_digest_value = NULL;
        ghttp_request *request_new = ghttp_request_new();
        char *unauthorized_data = ghttp_get_header(request, http_hdr_WWW_Authenticate);
        ghttp_set_uri(request_new, a_request->uri->full);
        ghttp_set_type(request_new, ghttp_type_put);
        ghttp_set_header(request_new, http_hdr_Accept_Encoding, "identity");
        ghttp_set_header(request_new, http_hdr_Connection, "close");
        ghttp_set_header(request_new, http_hdr_Content_Type, "application/x-www-form-urlencoded");
        ghttp_digest_value = ghttp_digest_encode(request_new, a_request->username, a_request->password, unauthorized_data);
        ghttp_set_header(request_new,
                         http_hdr_Authorization,
                         ghttp_digest_value);
        ghttp_set_body(request_new, a_body, strlen(a_body));
        ghttp_prepare(request_new);
        ghttp_process(request_new);
        result = ghttp_status_code(request_new);
        ghttp_request_destroy(request_new);
    }
    ghttp_request_destroy(request);
    return result;
}

int
xcap_del(xcap_request *a_request)
{
    int result = -1;
    ghttp_request *request = NULL;
    char *body_buf = NULL;
    char *io_buf = NULL;
    request = ghttp_request_new();
    xcap_uri_encode(a_request->uri);
    ghttp_set_uri(request, a_request->uri->full);
    ghttp_set_type(request, ghttp_type_delete);
    ghttp_set_header(request, http_hdr_Accept_Encoding, "identity");
    ghttp_set_header(request, http_hdr_Connection, "close");
    ghttp_prepare(request);
    ghttp_process(request);
    result = ghttp_status_code(request);
    if (ghttp_status_code(request) == 401)
    {
        char *ghttp_digest_value = NULL;
        ghttp_request *request_new = ghttp_request_new();
        char *unauthorized_data = ghttp_get_header(request, http_hdr_WWW_Authenticate);
        ghttp_set_uri(request_new, a_request->uri->full);
        ghttp_set_type(request_new, ghttp_type_delete);
        ghttp_set_header(request_new, http_hdr_Accept_Encoding, "identity");
        ghttp_set_header(request_new, http_hdr_Connection, "close");
        ghttp_digest_value = ghttp_digest_encode(request_new, a_request->username, a_request->password, unauthorized_data);
        ghttp_set_header(request_new,
                         http_hdr_Authorization,
                         ghttp_digest_value);
        ghttp_prepare(request_new);
        ghttp_process(request_new);
        result = ghttp_status_code(request_new);
        ghttp_request_destroy(request_new);
    }
    ghttp_request_destroy(request);
    return result;
}