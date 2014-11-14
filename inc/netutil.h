/*
 * File:   netutil.h
 * Author: Administrator
 *
 * Created on 2014年9月2日, 下午3:51
 */

#ifndef NETUTIL_H
#define NETUTIL_H

#ifdef  __cplusplus
extern "C" {
#endif
int isFileExist(char *savePath);
int download(char *uri, char *savePath) ;
//result地址参数传递
int netGet(char *url, char *params, int timeout, char **result, int result_len) ;
int netPost(char *uri, char *params, int timeout, char **result, int result_len) ;

#ifdef  __cplusplus
}
#endif

#endif  /* NETUTIL_H */
