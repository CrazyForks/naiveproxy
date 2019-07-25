
#ifndef INCLUDE_NPROXY_CONFIG
#define INCLUDE_NPROXY_CONFIG

#define MAX_CONFIG_SIZE 32
#define MAX_BUFFER_SIZE 1024
#define USER_LIMIT 20000

//C编译器可能不支持bool类型

#ifndef __cplusplus
typedef enum
{
    false = 0,
    true = 1
} bool;
#endif
typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned short uint16;

//设置4字节对齐
#pragma pack(4)

struct nproxy_config
{
    //proxy服务IP
    uint32 proxy_ipaddr;
    //目的ip地址
    uint32 dest_ipaddr;
    //proxy服务端口
    uint16 proxy_port;
    //目的端口
    uint16 dest_port;
    //IO类型 IN->OUT/OUT->IN
    uint8 io_type;
    //协议类型 TCP or UDP
    uint8 protocol;
    //填充字节
    uint16 padding;
};

enum protocol_type
{
    PROTOCOL_TCP,
    PROTOCOL_UDP,
};

enum io_type
{
    IO_TYPE_INOUT,
    IO_TYPE_OUTIN,
};

int init_nproxy_config(struct nproxy_config **cfgs_ptr);
int destroy_nproxy_config(struct nproxy_config **cfgs_ptr);
void print_one_config(struct nproxy_config *cfg);
#endif