#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> //inet_ntoa()
#include <vector>
#include <string>
#include <netdb.h> //gethostbyname
#include "naiveconfig.hpp"

void naiveconfig::remove_comment(char *str)
{
    char *p = str;
    while (*p && *p != '#')
        p++;
    *p = 0;
}

naiveconfig::naiveconfig(char *str)
{
    //   printf("%s\n", str);
    std::vector<std::string> res;
    const char *d = " \t\n";

    //protocol
    char *p_str = strtok(str, d);
    //转成大写
    if (1)
    {
        char *p = p_str;
        while (*p)
        {
            if (*p >= 'a' && *p <= 'z')
                *p -= 'a' - 'A';
            p++;
        }
    }
    if (strcmp(p_str, "TCP") == 0)
        protocol = PROTOCOL_TCP;
    else if (strcmp(p_str, "UDP") == 0)
        protocol = PROTOCOL_UDP;
    else if (strcmp(p_str, "HTTP") == 0)
        protocol = PROTOCOL_HTTP;
    else
    {
        printf("config error. support protocol: TCP/UDP/HTTP");
        return;
    }

    //proxy_server_ip
    p_str = strtok(NULL, d);
    struct in_addr pro_addr;
    if (inet_aton(p_str, &pro_addr) == 0)
    {
        perror(p_str);
        exit(errno);
    }
    proxy_ipaddr = pro_addr.s_addr;

    //proxy_server_port
    p_str = strtok(NULL, d);
    proxy_port = atoi(p_str);

    // //dest_server_ip
    p_str = strtok(NULL, d);
    if (inet_aton(p_str, &pro_addr) == 0)
    {
        struct hostent *hostp;
        hostp = gethostbyname(p_str);
        if (hostp == NULL)
        {
            perror(p_str);
            return;
            //exit(errno);
        }
        hostname = p_str;
        //hostname = hostp->h_name;
        dest_ipaddr = ((struct in_addr *)*hostp->h_addr_list)->s_addr;
    }
    else
    {
        dest_ipaddr = pro_addr.s_addr;
    }

    //dest_server_port
    p_str = strtok(NULL, d);
    if (p_str != NULL)
        dest_port = atoi(p_str);
    else
    {
        dest_port = 80;
    }
}

void naiveconfig::print()
{
    struct in_addr nproxy_server;
    nproxy_server.s_addr = proxy_ipaddr;

    struct in_addr dest_server;
    dest_server.s_addr = dest_ipaddr;
    char dest_ip[128];
    strcpy(dest_ip, inet_ntoa(dest_server));

    if (hostname.length() == 0)
    {
        //注意，inet_ntoa是不可重入的。
        printf("PROTOCOL:          %s\n"
               "nproxy_server_ip:  %s\n"
               "nproxy_port:       %d\n"
               "dest_ipaddr:       %s\n"
               "dest_port:         %d\n",
               protocol_name[protocol],
               inet_ntoa(nproxy_server),
               proxy_port,
               dest_ip,
               dest_port);
    }
    else
    {
        //注意，inet_ntoa是不可重入的。
        printf("PROTOCOL:          %s\n"
               "nproxy_server_ip:  %s\n"
               "nproxy_port:       %d\n"
               "hostname:          %s\n"
               "dest_ipaddr:       %s\n"
               "dest_port:         %d\n",
               protocol_name[protocol],
               inet_ntoa(nproxy_server),
               proxy_port,
               hostname.c_str(),
               dest_ip,
               dest_port);
    }
}