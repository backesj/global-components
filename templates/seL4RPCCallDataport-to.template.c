/*#
 *# Copyright 2014, NICTA
 *#
 *# This software may be distributed and modified according to the terms of
 *# the BSD 2-Clause license. Note that NO WARRANTY is provided.
 *# See "LICENSE_BSD2.txt" for details.
 *#
 *# @TAG(NICTA_BSD)
 #*/

#include <assert.h>
#include <sel4/sel4.h>

/*- include 'seL4MultiSharedData-to.template.c' -*/

seL4_Word /*? me.to_interface.name ?*/_get_sender_id(void);

static void *get_buffer() {
    void *base = /*? me.to_interface.name ?*/_buf(/*? me.to_interface.name ?*/_get_sender_id());
    assert(base);
    return base;
}

/*- set base = 'get_buffer()' -*/
/*- set userspace_ipc = True -*/
/*- set dataport_type = configuration[me.from_instance.name].get('%s_dataport_type' % me.from_interface.name, 'Buf') -*/
/*- set trust_partner = configuration[me.to_instance.name].get('trusted') == '"true"' -*/
/*- include 'rpc-connector-common-to.c' -*/

