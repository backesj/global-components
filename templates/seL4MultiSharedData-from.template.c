/*#
 *# Copyright 2014, NICTA
 *#
 *# This software may be distributed and modified according to the terms of
 *# the BSD 2-Clause license. Note that NO WARRANTY is provided.
 *# See "LICENSE_BSD2.txt" for details.
 *#
 *# @TAG(NICTA_BSD)
 #*/

#include <camkes/dataport.h>
#include <utils/util.h>

/*? macros.show_includes(me.from_instance.type.includes) ?*/

/*- set client_id = configuration[me.from_instance.name].get("%s_attributes" % me.from_interface.name) -*/
/*- if client_id is none or re.match('"\\d+"$', client_id) is none -*/
  /*? raise(Exception('%s.%s_attributes must be set to a number' % (me.from_instance.name, me.from_interface.name))) ?*/
/*- endif -*/
/*- set client_id = client_id.strip('"') -*/
/*- set dataport_name = '%s_%s' % (me.from_interface.name, client_id) -*/
/*- set dataport_type = configuration[me.from_instance.name].get("%s_dataport_type" % me.from_interface.name, 'Buf') -*/

/*- set dataport_section = '%s_%s' % (me.from_interface.name, client_id) -*/

/*# Create a fake instance in the assembly #*/
/*- set port = lambda('x: AST.Port(type = x)')(str(dataport_type)) -*/
/*- set dataport = lambda('x, y: AST.Dataport(x, y)')(port, dataport_name) -*/

/*- do me.to_instance.type.dataports.append(dataport) -*/
/*- do me.from_instance.type.dataports.append(dataport) -*/

/*- set connection_type = lambda('x: AST.Connector(name=x, from_type="Dataport", to_type="Dataport")')(dataport_name) -*/
/*- set connection = lambda('con_type, con_name, from_inst, from_inter, to_inst, to_inter: \
                             AST.Connection(con_type, con_name, from_inst, from_inter, to_inst, to_inter)')
                     (connection_type, dataport_name, me.from_instance, dataport, me.to_instance, dataport) -*/
/*- do composition.connections.append(connection) -*/

/*- set p = Perspective(dataport=dataport_name) -*/
#define SHM_ALIGN (1 << 12)
struct {
    char content[ROUND_UP_UNSAFE(sizeof(/*? dataport_type ?*/),
        PAGE_SIZE_4K)];
} /*? p['dataport_symbol'] ?*/
        __attribute__((aligned(SHM_ALIGN)))
        __attribute__((section("shared_/*? dataport_section ?*/")))
        __attribute__((externally_visible));

/*- if suffix is not defined -*/
  /*- set suffix = '' -*/
/*- endif -*/

volatile /*? dataport_type ?*/ * /*? me.from_interface.name ?*//*? suffix ?*/  =
    (volatile /*? dataport_type ?*/ *) & /*? p['dataport_symbol'] ?*/;

/*- set isdata = lambda('x: isinstance(x, AST.Dataport)')(me.from_interface) -*/
/*- if isdata -*/
    /*- set p = Perspective(dataport=me.from_interface.name) -*/
    struct {
        char content[ROUND_UP_UNSAFE(sizeof(/*? show(me.from_interface.type) ?*/),
            PAGE_SIZE_4K)];
    } /*? p['dataport_symbol'] ?*/
            __attribute__((aligned(SHM_ALIGN)))
            __attribute__((section("shared_/*? me.from_interface.name ?*/")))
            __attribute__((externally_visible));
/*- endif -*/


int /*? me.from_interface.name ?*/_wrap_ptr(dataport_ptr_t *p, void *ptr) {
    return -1;
}

void * /*? me.from_interface.name ?*/_unwrap_ptr(dataport_ptr_t *p) {
    return NULL;
}
