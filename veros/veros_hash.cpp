#include <string.h>
//#include "common.h"
#include "veros_hash.h"

void (*CVerosHash::haraka512Function)(unsigned char *out, const unsigned char *in);

void CVerosHash::Hash(void *result, const void *data, size_t _len)
{
    unsigned char buf[128];
    unsigned char *bufPtr = buf;
    int nextOffset = 64;
    uint32_t pos = 0, len = _len;
    unsigned char *bufPtr2 = bufPtr + nextOffset;
    unsigned char *ptr = (unsigned char *)data;

    // put our last result or zero at beginning of buffer each time
    memset(bufPtr, 0, 32);

    // digest up to 32 bytes at a time
    for ( ; pos < len; pos += 32)
    {
        if (len - pos >= 32)
        {
            memcpy(bufPtr + 32, ptr + pos, 32);
        }
        else
        {
            int i = (int)(len - pos);
            memcpy(bufPtr + 32, ptr + pos, i);
            memset(bufPtr + 32 + i, 0, 32 - i);
        }
        (*haraka512Function)(bufPtr2, bufPtr);
        bufPtr2 = bufPtr;
        bufPtr += nextOffset;
        nextOffset *= -1;
    }
    memcpy(result, bufPtr, 32);
};

void CVerosHash::init()
{
   
        haraka512Function = &haraka512_port_zero;
    
}

CVerosHash &CVerosHash::Write(const unsigned char *data, size_t _len)
{
    unsigned char *tmp;
    uint32_t pos, len = _len;

    // digest up to 32 bytes at a time
    for ( pos = 0; pos < len; )
    {
        uint32_t room = 32 - curPos;

        if (len - pos >= room)
        {
            memcpy(curBuf + 32 + curPos, data + pos, room);
            (*haraka512Function)(result, curBuf);
            tmp = curBuf;
            curBuf = result;
            result = tmp;
            pos += room;
            curPos = 0;
        }
        else
        {
            memcpy(curBuf + 32 + curPos, data + pos, len - pos);
            curPos += len - pos;
            pos = len;
        }
    }
    return *this;
}

// to be declared and accessed from C
void veros_hash(void *result, const void *data, size_t len)
{
    return CVerosHash::Hash(result, data, len);
}

void (*CVerosHashV2::haraka512Function)(unsigned char *out, const unsigned char *in);
void (*CVerosHashV2::haraka512KeyedFunction)(unsigned char *out, const unsigned char *in, const u128 *rc);
void (*CVerosHashV2::haraka256Function)(unsigned char *out, const unsigned char *in);

void CVerosHashV2::init()
{
    if (IsCPUVerosOptimized())
    {
        load_constants();
        haraka512Function = &haraka512;
        haraka512KeyedFunction = &haraka512_keyed;
        haraka256Function = &haraka256;
    }
    else
    {
        // load the haraka constants
        load_constants_port();
        haraka512Function = &haraka512_port;
        haraka512KeyedFunction = &haraka512_port_keyed;
        haraka256Function = &haraka256_port;
    }
}

void CVerosHashV2::Hash(void *result, const void *data, size_t len)
{
    unsigned char buf[128];
    unsigned char *bufPtr = buf;
    int pos = 0, nextOffset = 64;
    unsigned char *bufPtr2 = bufPtr + nextOffset;
    unsigned char *ptr = (unsigned char *)data;

    // put our last result or zero at beginning of buffer each time
    memset(bufPtr, 0, 32);

    // digest up to 32 bytes at a time
    for ( ; pos < len; pos += 32)
    {
        if (len - pos >= 32)
        {
            memcpy(bufPtr + 32, ptr + pos, 32);
        }
        else
        {
            int i = (int)(len - pos);
            memcpy(bufPtr + 32, ptr + pos, i);
            memset(bufPtr + 32 + i, 0, 32 - i);
        }
        (*haraka512Function)(bufPtr2, bufPtr);
        bufPtr2 = bufPtr;
        bufPtr += nextOffset;
        nextOffset *= -1;
    }
    memcpy(result, bufPtr, 32);
};

CVerosHashV2 &CVerosHashV2::Write(const unsigned char *data, size_t len)
{
    unsigned char *tmp;

    // digest up to 32 bytes at a time
    for ( int pos = 0; pos < len; )
    {
        int room = 32 - curPos;

        if (len - pos >= room)
        {
            memcpy(curBuf + 32 + curPos, data + pos, room);
            (*haraka512Function)(result, curBuf);
            tmp = curBuf;
            curBuf = result;
            result = tmp;
            pos += room;
            curPos = 0;
        }
        else
        {
            memcpy(curBuf + 32 + curPos, data + pos, len - pos);
            curPos += len - pos;
            pos = len;
        }
    }
    return *this;
}

// to be declared and accessed from C
void veros_hash_v2(void *result, const void *data, size_t len)
{
    return CVerosHashV2::Hash(result, data, len);
}
