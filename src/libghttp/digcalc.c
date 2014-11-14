//#include <global.h>
#include <string.h>
#include "libmd5.h"
#include "digcalc.h"

#ifdef _WIN32
#define STRICMP stricmp
#else
#define STRICMP strcasecmp
#endif

void CvtHex(
    IN HASH Bin,
    OUT HASHHEX Hex
)
{
    unsigned short i;
    unsigned char j;

    for (i = 0; i < HASHLEN; i++)
    {
        j = (Bin[i] >> 4) & 0xf;
        if (j <= 9)
            Hex[i * 2] = (j + '0');
        else
            Hex[i * 2] = (j + 'a' - 10);
        j = Bin[i] & 0xf;
        if (j <= 9)
            Hex[i * 2 + 1] = (j + '0');
        else
            Hex[i * 2 + 1] = (j + 'a' - 10);
    };
    Hex[HASHHEXLEN] = '\0';
};

/* calculate H(A1) as per spec */
void DigestCalcHA1(
    IN char *pszAlg,
    IN char *pszUserName,
    IN char *pszRealm,
    IN char *pszPassword,
    IN char *pszNonce,
    IN char *pszCNonce,
    OUT HASHHEX SessionKey
)
{
    MD5_CTX Md5Ctx;
    HASH HA1;

    MD5Init(&Md5Ctx);
    MD5Update(&Md5Ctx, pszUserName, strlen(pszUserName));
    MD5Update(&Md5Ctx, ":", 1);
    MD5Update(&Md5Ctx, pszRealm, strlen(pszRealm));
    MD5Update(&Md5Ctx, ":", 1);
    MD5Update(&Md5Ctx, pszPassword, strlen(pszPassword));
    MD5Final(HA1, &Md5Ctx);
    if (STRICMP(pszAlg, "md5-sess") == 0)
    {
        MD5Init(&Md5Ctx);
        MD5Update(&Md5Ctx, HA1, HASHLEN);
        MD5Update(&Md5Ctx, ":", 1);
        MD5Update(&Md5Ctx, pszNonce, strlen(pszNonce));
        MD5Update(&Md5Ctx, ":", 1);
        MD5Update(&Md5Ctx, pszCNonce, strlen(pszCNonce));
        MD5Final(HA1, &Md5Ctx);
    };
    CvtHex(HA1, SessionKey);
};

/* calculate request-digest/response-digest as per HTTP Digest spec */
void DigestCalcResponse(
    IN HASHHEX HA1,           /* H(A1) */
    IN char *pszNonce,        /* nonce from server */
    IN char *pszNonceCount,   /* 8 hex digits */
    IN char *pszCNonce,       /* client nonce */
    IN char *pszQop,          /* qop-value: "", "auth", "auth-int" */
    IN char *pszMethod,       /* method from the request */
    IN char *pszDigestUri,    /* requested URL */
    IN HASHHEX HEntity,       /* H(entity body) if qop="auth-int" */
    OUT HASHHEX Response      /* request-digest or response-digest */
)
{
    MD5_CTX Md5Ctx;
    HASH HA2;
    HASH RespHash;
    HASHHEX HA2Hex;

    // calculate H(A2)
    MD5Init(&Md5Ctx);
    MD5Update(&Md5Ctx, pszMethod, strlen(pszMethod));
    MD5Update(&Md5Ctx, ":", 1);
    MD5Update(&Md5Ctx, pszDigestUri, strlen(pszDigestUri));
    if (STRICMP(pszQop, "auth-int") == 0)
    {
        MD5Update(&Md5Ctx, ":", 1);
        MD5Update(&Md5Ctx, HEntity, HASHHEXLEN);
    };
    MD5Final(HA2, &Md5Ctx);
    CvtHex(HA2, HA2Hex);

    // calculate response
    MD5Init(&Md5Ctx);
    MD5Update(&Md5Ctx, HA1, HASHHEXLEN);
    MD5Update(&Md5Ctx, ":", 1);
    MD5Update(&Md5Ctx, pszNonce, strlen(pszNonce));
    MD5Update(&Md5Ctx, ":", 1);
    if (*pszQop)
    {
        MD5Update(&Md5Ctx, pszNonceCount, strlen(pszNonceCount));
        MD5Update(&Md5Ctx, ":", 1);
        MD5Update(&Md5Ctx, pszCNonce, strlen(pszCNonce));
        MD5Update(&Md5Ctx, ":", 1);
        MD5Update(&Md5Ctx, pszQop, strlen(pszQop));
        MD5Update(&Md5Ctx, ":", 1);
    };
    MD5Update(&Md5Ctx, HA2Hex, HASHHEXLEN);
    MD5Final(RespHash, &Md5Ctx);
    CvtHex(RespHash, Response);
};

void HTTPDigestGenerateCNonce(char *outbuff)
{
    int i, num;
    for (i = 0; i < 32; i++)
    {
        num = rand() % 16;
        switch (num)
        {
        case 0: case 1: case 2: case 3: case 4: case 5:
        case 6: case 7: case 8: case 9:
            outbuff[i] = '0' + num;
            break;
        case 10: case 11: case 12: case 13: case 14: case 15:
            outbuff[i] = 'a' + (num - 10);
            break;
        default:
            outbuff[i] = 'f';
        }
    }
    outbuff[32] = '\0';
}

void addElement(OUT char *entity, char *name, const char *key)
{
    int length;
    char *temp1 = ", ";
    char *temp2 = "=\"";
    char *p;
    length = strlen(entity);
    p = entity + length;
    if (length != 0)
    {
        while ((*p = *temp1++) != '\0')
        {
            p++;
        }
    }
    while ((*p = *name++) != '\0')
    {
        p++;
    }
    while ((*p = *temp2++) != '\0')
    {
        p++;
    }
    while ((*p = *key++) != '\0')
    {
        p++;
    }
    *p = '\"';
    p++;
    *p = '\0';
}

void addElementNC(OUT char *entity)
{
    int length;
    char *p;
    char *nc = ", nc=00000001";
    length = strlen(entity);
    p = entity + length;
    while ((*p++ = *nc++) != '\0');
}
