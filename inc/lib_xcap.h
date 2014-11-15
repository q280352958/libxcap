#ifndef _XCAP_H_
#define _XCAP_H_

#define SCODE_CONTINUE 100             	/* 客户必须继续发出请求 */
#define SCODE_SWITCH_PROTOCOL 101      	/* 客户要求服务器根据请求转换HTTP协议版本 */
#define SCODE_OK 200                   	/* 成功 */
#define SCODE_CREATED 201              	/* 提示知道新文件的URL */
#define SCODE_ACCEPTED 202             	/* 接受和处理、但处理未完成 */
#define SCODE_UNAUTHORITA_INFO 203     	/* 返回信息不确定或不完整 */
#define SCODE_NO_CONTENT 204           	/* 请求收到，但返回信息为空 */
#define SCODE_RESET_CONTENT 205        	/* 服务器完成了请求，用户代理必须复位当前已经浏览过的文件 */
#define SCODE_PARTIAL_CONTENT 206      	/* 服务器已经完成了部分用户的GET请求 */
#define SCODE_MULTIPLE_CHOICES 300     	/* 请求的资源可在多处得到 */
#define SCODE_MOVE 301                 	/* 删除请求数据 */
#define SCODE_FOUND 302                	/* 在其他地址发现了请求数据 */
#define SCODE_SEE_OTHER 303            	/* 建议客户访问其他URL或访问方式 */
#define SCODE_NOT_MODIFIED 304         	/* 客户端已经执行了GET，但文件未变化 */
#define SCODE_USE_PROXY 305            	/* 请求的资源必须从服务器指定的地址得到 */
#define SCODE_UNUSED 306               	/* 前一版本HTTP中使用的代码，现行版本中不再使用 */
#define SCODE_TEMPORARY 307            	/* 申明请求的资源临时性删除 */
#define SCODE_BAD_REQUEST 400          	/* 错误请求，如语法错误 */
#define SCODE_UNAUTHORIZED 401         	/* 请求授权失败 */
#define SCODE_PAYMENT_REQUIRED 402     	/* 保留有效ChargeTo头响应 */
#define SCODE_FORBIDDEN 403            	/* 请求不允许 */
#define SCODE_NOT_FOUND 404            	/* 没有发现文件、查询或URl */
#define SCODE_METHOD_NOT_ALLOWED 405   	/* 用户在Request-Line字段定义的方法不允许 */
#define SCODE_NOT_ACCEPTABLE 406       	/* 根据用户发送的Accept拖，请求资源不可访问 */
#define SCODE_PROXY_AUTHENTICATION 407 	/* 类似401，用户必须首先在代理服务器上得到授权 */
#define SCODE_REQUEST_TIMEOUT 408      	/* 客户端没有在用户指定的时间内完成请求 */
#define SCODE_CONFLICT 409             	/* 对当前资源状态，请求不能完成 */
#define SCODE_GONE 410                 	/* 服务器上不再有此资源且无进一步的参考地址 */
#define SCODE_LENGTH_REQUIRED 411      	/* 服务器拒绝用户定义的Content-Length属性请求 */
#define SCODE_PRECONDITION_FAILED 412  	/* 一个或多个请求头字段在当前请求中错误 */
#define SCODE_REQENTITY_TOO_LARGE 413  	/* 请求的资源大于服务器允许的大小 */
#define SCODE_REQ_URI_TOO_LONG 414     	/* 请求的资源URL长于服务器允许的长度 */
#define SCODE_UNSUPPORT_MEDIA_TYPE 415 	/* 请求资源不支持请求项目格式 */
#define SCODE_REQUESTED_RANGE 416      	/* 请求中包含Range请求头字段，在当前请求资源范围内没有range指示值，请求也不包含If-Range请求头字段 */
#define SCODE_EXPECTATION_FAILED 417   	/* 服务器不满足请求Expect头字段指定的期望值，如果是代理服务器，可能是下一级服务器不能满足请求 */
#define SCODE_Internal_Server_Error 500	/* 服务器产生内部错误 */
#define SCODE_NOT_IMPLEMENTED 501		/* 服务器不支持请求的函数 */
#define SCODE_BAD_GATEWAY 502			/* 服务器暂时不可用，有时是为了防止发生系统过载 */
#define SCODE_SERVICE_UNAVAILABLE 503	/* 服务器过载或暂停维修 */
#define SCODE_GATEWAY_TIMEOUT 504		/* 关口过载，服务器使用另一个关口或服务来响应用户，等待时间设定值较长 */
#define SCODE_VERSION_NOT_SUPPORT 505	/* 服务器不支持或拒绝支持请求头中指定的HTTP版本 */

typedef struct _xcap_uri xcap_uri;
struct _xcap_uri
{
    char *xcap_host;
    char *xcap_auid;
    char *xcap_xui;
    char *xcap_home_directory;
    char *full;
};

typedef struct _xcap_request xcap_request;
struct _xcap_request
{
    xcap_uri *uri;
    char *username;
    char *password;
    char *io_buf;
};

/**
 * Create an empty URI object
 *
 * \return a new URI object
 */
xcap_uri *
xcap_uri_new(void);

/**
 * Destroy URI object
 *
 * \param a_uri URI object
 */
void
xcap_uri_destory(xcap_uri *a_uri);

/**
 * Create an empty XCAP object
 *
 * \return a new XCAP object
 */
xcap_request *
xcap_request_new(void);

/**
 * Destroy XCAP object
 *
 * \param a_request XCAP object
 */
void
xcap_request_destroy(xcap_request *a_request);

/**
 * Set XCAP uri host
 *
 * \param a_request XCAP object
 * \param a_host host
 */
void
xcap_set_host(xcap_request *a_request, const char *a_host);

/**
 * Set XCAP uri auid
 *
 * \param a_request XCAP object
 * \param a_auid auid
 */
void
xcap_set_auid(xcap_request *a_request, const char *a_auid);

/**
 * Set XCAP uri xui
 *
 * \param a_request XCAP object
 * \param a_xui xui
 */
void
xcap_set_xui(xcap_request *a_request, const char *a_xui);

/**
 * Set XCAP uri home directory
 *
 * \param a_request XCAP object
 * \param a_home_directory directory
 */
void
xcap_set_home_directory(xcap_request *a_request, const char *a_home_directory);

/**
 * Set XCAP username
 *
 * \param a_request XCAP object
 * \param a_username user name
 */
void
xcap_set_username(xcap_request *a_request, const char *a_username);

/**
 * Set XCAP passwrod
 *
 * \param a_request XCAP object
 * \param a_password password
 */
void
xcap_set_password(xcap_request *a_request, const char *a_password);

/**
 * Encode XCAP uri
 *
 * \param a_uri URI object
 */
void
xcap_uri_encode(xcap_uri *a_uri);

/**
 * GET XCAP request
 *
 * \param a_request XCAP object
 * \return status code
 */
int
xcap_get(xcap_request *a_request);

/**
 * PUT XCAP request
 *
 * \param a_request XCAP object
 * \param a_body http body content
 * \return status code
 */
int
xcap_put(xcap_request *a_request, char *a_body);

/**
 * DELETE XCAP request
 *
 * \param a_request XCAP object
 * \return status code
 */
int
xcap_del(xcap_request *a_request);

#endif