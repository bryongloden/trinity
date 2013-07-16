#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <linux/netlink.h>
#include <stdlib.h>
#include "net.h"
#include "random.h"

void gen_netlink(unsigned long *addr, unsigned long *addrlen)
{
	struct sockaddr_nl *nl;

	nl = malloc(sizeof(struct sockaddr_nl));
	if (nl == NULL)
		return;

	nl->nl_family = PF_NETLINK;
	nl->nl_pid = rand();
	nl->nl_groups = rand();
	*addr = (unsigned long) nl;
	*addrlen = sizeof(struct sockaddr_nl);
}

void netlink_rand_socket(struct proto_type *pt)
{
	if (rand_bool())
		pt->type = SOCK_RAW;
	else
		pt->type = SOCK_DGRAM;

	pt->protocol = rand() % (NETLINK_CRYPTO + 1);       // Current highest netlink socket.
}
