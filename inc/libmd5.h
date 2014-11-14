#ifndef _MD5_H_
#define _MD5_H_

#define HTTPMD5ByteReverse(buf, len)
#define F1(x, y, z) (z ^ (x & (y ^ z)))
#define F2(x, y, z) F1(z, x, y)
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | ~z))

#ifdef __PUREC__
#define MD5STEP(f, w, x, y, z, data, s) \
    ( w += f /*(x, y, z)*/ + data,  w = w<<s | w>>(32-s),  w += x )
#else
#define MD5STEP(f, w, x, y, z, data, s) \
    ( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )
#endif

typedef struct MD5Context MD5_CTX;
struct MD5Context
{
    unsigned int buf[4];
    unsigned int bits[2];
    unsigned char in[64];
};

void
HTTPMD5Transform(unsigned int buf[4], unsigned int const in[16]);

void
HTTPMD5Init(struct MD5Context *ctx);

void
HTTPMD5Update(struct MD5Context *ctx, unsigned char const *buf, unsigned len);

void
HTTPMD5Final(unsigned char digest[16], struct MD5Context *ctx);

#endif