#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "lib_xcap.h"
#include "ezxml.h"
#include "digcalc.h"

#if defined(TEST_GET)
int main(int argc, char *argv[])
{
    xcap_request *request = NULL;
    request = xcap_request_new();
    //http://10.35.57.251/xcap-root/pres-rules/users/sip:gaojb@10.35.57.251/index
    xcap_set_host(request, "10.35.57.251");
    xcap_set_auid(request, "pres-rules");
    xcap_set_xui(request, "sip:gaojb@10.35.57.251");
    xcap_set_home_directory(request, "index");
    xcap_set_username(request, "gaojb");
    xcap_set_password(request, "123456");
    if (xcap_get(request) == SCODE_OK)
    {
        printf("%s\n", request->io_buf);
    }
    xcap_request_destroy(request);
    return 0;
}
#elif defined(TEST_PUT)
int main(int argc, char *argv[])
{
    char pres_rules[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n" \
                        "<ruleset xmlns=\"urn:ietf:params:xml:ns:common-policy\" xmlns:pr=\"urn:ietf:params:xml:ns:pres-rules\" xmlns:cp=\"www.counterpath.com/privacy-lists\">\r\n" \
                        "<rule id=\"pres_whitelist\">\r\n" \
                        "<conditions>\r\n" \
                        "<identity>\r\n" \
                        "<one id=\"sip:bob@example.com\"/>\r\n" \
                        "<one id=\"sip:alice@example.com\"/>\r\n" \
                        "<many domain=\"ag-projects.com\">\r\n" \
                        "</many>\r\n" \
                        "</identity>\r\n" \
                        "</conditions>\r\n" \
                        "<actions>\r\n" \
                        "<pr:sub-handling>allow</pr:sub-handling>\r\n" \
                        "</actions>\r\n" \
                        "<transformations>\r\n" \
                        "<pr:provide-services>\r\n" \
                        "<pr:all-services/>\r\n" \
                        "</pr:provide-services>\r\n" \
                        "<pr:provide-persons>\r\n" \
                        "<pr:all-persons/>\r\n" \
                        "</pr:provide-persons>\r\n" \
                        "<pr:provide-devices>\r\n" \
                        "<pr:all-devices/>\r\n" \
                        "</pr:provide-devices>\r\n" \
                        "<pr:provide-all-attributes/>\r\n" \
                        "</transformations>\r\n" \
                        "</rule>\r\n" \
                        "<rule id=\"pres_blacklist\">\r\n" \
                        "<conditions>\r\n" \
                        "<identity>\r\n" \
                        "<one id=\"sip:40316600024@abc.com\"/>\r\n" \
                        "</identity>\r\n" \
                        "</conditions>\r\n" \
                        "<actions>\r\n" \
                        "<pr:sub-handling>block</pr:sub-handling>\r\n" \
                        "</actions>\r\n" \
                        "<transformations/>\r\n" \
                        "</rule>\r\n" \
                        "</ruleset>";
    xcap_request *request = NULL;
    request = xcap_request_new();
    //http://10.35.57.251/xcap-root/pres-rules/users/sip:gaojb@10.35.57.251/index
    xcap_set_host(request, "10.35.57.251");
    xcap_set_auid(request, "pres-rules");
    xcap_set_xui(request, "sip:gaojb@10.35.57.251");
    xcap_set_home_directory(request, "index");
    xcap_set_username(request, "gaojb");
    xcap_set_password(request, "123456");
    if (xcap_put(request, pres_rules) == SCODE_OK)
    {
        printf("Put success!\n");
    }
    xcap_request_destroy(request);
    return 0;
}
#elif defined(TEST_DEL)
int main(int argc, char *argv[])
{
    xcap_request *request = NULL;
    request = xcap_request_new();
    //http://10.35.57.251/xcap-root/pres-rules/users/sip:gaojb@10.35.57.251/index
    xcap_set_host(request, "10.35.57.251");
    xcap_set_auid(request, "pres-rules");
    xcap_set_xui(request, "sip:gaojb@10.35.57.251");
    xcap_set_home_directory(request, "index");
    xcap_set_username(request, "gaojb");
    xcap_set_password(request, "123456");
    if (xcap_del(request) == SCODE_OK)
    {
        printf("Delete success!\n");
    }
    xcap_request_destroy(request);
    return 0;
}
#elif defined(TEST_DIGEST)
void main(int argc, char **argv)
{

    char *pszNonce = "900334491200491001379791740285793351552551382508262014620";
    char *pszCNonce = "76931fac9dab2b36c248b87d6ae33f9a";
    char *pszUser = "gaojb";
    char *pszRealm = "10.35.57.251";
    char *pszPass = "123456";
    char *pszAlg = "md5";
    char szNonceCount[9] = "00000001";
    char *pszMethod = "PUT";
    char *pszQop = "auth";
    char *pszURI = "/xcap-root/pres-rules/users/sip:gaojb@10.35.57.251/index";
    HASHHEX HA1;
    HASHHEX HA2 = "";
    HASHHEX Response;

    DigestCalcHA1(pszAlg, pszUser, pszRealm, pszPass, pszNonce,
                  pszCNonce, HA1);
    DigestCalcResponse(HA1, pszNonce, szNonceCount, pszCNonce, pszQop,
                       pszMethod, pszURI, HA2, Response);
    printf("Response = %s\n", Response);
};
#else
int main(int argc, char *argv[])
{
    printf("Hello world!\n");
    return 0;
}
#endif
