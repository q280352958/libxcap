#include "ghttp.h"
#include "http_hdrs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}

int isFileExist(char *savePath)
{
    if (!access(savePath, F_OK))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//http://www.elesos.com/index.php?title=Libghttp库使用指南

int download(char *uri, char *savePath)
{
    ghttp_request *request = NULL;
    ghttp_status status;
    FILE *pFile;
    char *buf;
    int bytes_read;
    int size;
    if (!isFileExist(savePath))
    {
        printf("savePath not exist ");
        return -1;
    }
    pFile = fopen(savePath, "wb");
    request = ghttp_request_new();
    if (ghttp_set_uri(request, uri) == -1)
        return -1;
    if (ghttp_set_type(request, ghttp_type_get) == -1)//get
        return -1;
    ghttp_prepare(request);
    status = ghttp_process(request);
    if (status == ghttp_error)
        return -1;
    printf("Status code -> %d\n", ghttp_status_code(request));
    buf = ghttp_get_body(request);
    bytes_read = ghttp_get_body_len(request);
    size = strlen(buf); //size == bytes_read
    fwrite(buf, 1, size, pFile);
    fclose(pFile);
    return 0;
}
//result地址参数传递

int netGet(char *url, char *params, int timeout, char **result, int result_len)
{
    ghttp_request *request = NULL;
    request = ghttp_request_new();

    if (params != NULL && strlen(params) > 0)
    {
        char tmp[1024];
        strcpy(tmp, url);
        if (strchr(tmp, '?') == NULL) //url不存在
        {
            strcat(tmp, "?")  ;
        }
        strcat(tmp, params) ;
        printf("%s\n", tmp);
        ghttp_set_uri(request, tmp);
    }
    else
    {
        ghttp_set_uri(request, url);
    }
    ghttp_set_type(request, ghttp_type_get); //get方法
    ghttp_set_header(request, http_hdr_Connection, "close");
    char timeout_str[10];
    sprintf(timeout_str, "%d", timeout);
    ghttp_set_header(request, http_hdr_Timeout, timeout_str);

    ghttp_prepare(request);
    ghttp_process(request);
    *result = ghttp_get_body(request);
    result_len = ghttp_get_body_len(request);
    ghttp_request_destroy(request);
    return 0;
}

int netPost(char *uri, char *params, int timeout, char **result, int result_len)
{
    char szVal[1024];
    ghttp_request *request = NULL;
    ghttp_status status;
    int len;
    printf("%s\n", params); //test
    request = ghttp_request_new();
    if (ghttp_set_uri(request, uri) == -1)
        return -1;
    if (ghttp_set_type(request, ghttp_type_post) == -1) //post
        return -1;
    ghttp_set_header(request, http_hdr_Content_Type, "application/x-www-form-urlencoded");

    char timeout_str[10];
    sprintf(timeout_str, "%d", timeout);
    ghttp_set_header(request, http_hdr_Timeout, timeout_str);
    //ghttp_set_sync(request, ghttp_sync); //set sync
    len = strlen(params);
    ghttp_set_body(request, params, len); //
    ghttp_prepare(request);
    status = ghttp_process(request);
    if (status == ghttp_error)
        return -1;
    *result = ghttp_get_body(request); //test
    result_len = ghttp_get_body_len(request);
    ghttp_clean(request);
    return 0;
}