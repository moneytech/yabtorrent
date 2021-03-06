
#include <stdbool.h>
#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CuTest.h"

#include <stdint.h>

#include "bt.h"
#include "bt_peermanager.h"

void TestPM_init_pm_is_empty(
    CuTest * tc
)
{
    void *pm =  bt_peermanager_new(NULL);

    CuAssertTrue(tc, 0 == bt_peermanager_count(pm));
}

void TestPM_add_peer_counts_extra_peer(
    CuTest * tc
)
{
    void *id;
    char *peerid = "0000000000000";
    char *ip = "127.0.0.1";
    void *pm =  bt_peermanager_new(NULL);

    bt_peermanager_add_peer(pm, peerid, strlen(peerid), ip, strlen(ip), 4000);
    CuAssertTrue(tc, 1 == bt_peermanager_count(pm));
}

void TestPM_cant_add_peer_twice(
    CuTest * tc
)
{
    void *id;
    char *peerid = "0000000000000";
    char *ip = "127.0.0.1";
    void *pm =  bt_peermanager_new(NULL);

    bt_peermanager_add_peer(pm, peerid, strlen(peerid), ip, strlen(ip), 4000);
    bt_peermanager_add_peer(pm, peerid, strlen(peerid), ip, strlen(ip), 4000);
    CuAssertTrue(tc, 1 == bt_peermanager_count(pm));
}

static void addone(void* caller, void* peer, void* val)
{
    int* vali = val;
    *vali += 1;
}

void TestPM_forall_works_across_all_peers(
    CuTest * tc
)
{
    void *pm;
    int mod;
    char *peerid = "0000000000000";
    char *ip = "127.0.0.1";

    mod = 0;
    pm =  bt_peermanager_new(NULL);

    bt_peermanager_add_peer(pm, peerid, strlen(peerid), ip, strlen(ip), 4000);
    bt_peermanager_forall(pm, NULL, &mod, addone);
    //bt_peermanager_add_peer(pm, peerid, strlen(peerid), ip, strlen(ip), 4000);
    CuAssertTrue(tc, 1 == mod);
}

#if 0
void T_estPM_emovePeer(
    CuTest * tc
)
{
    void *id;

    char *peerid = "0000000000000";

    char *ip = "127.0.0.1";

    id = bt_client_new();
    /*  a peer id is required for adding peers */
    //bt_client_set_peer_id(id, peerid);

    CuAssertTrue(tc, 0 == bt_client_get_num_peers(id));

    bt_client_add_peer(id, peerid, strlen(peerid), ip, strlen(ip), 4000);
    bt_client_remove_peer(id, peerid);
    CuAssertTrue(tc, 0 == bt_client_get_num_peers(id));
}
#endif

