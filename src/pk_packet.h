/*
 * Airown - packet handling
 *
 * Copyright (C) 2010 sh0 <sh0@yutani.ee>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef H_AO_PACKET
#define H_AO_PACKET

// Int inc
#include "ao_config.h"
#include "ao_main.h"

/* ether types: http://standards.ieee.org/regauth/ethertype/eth.txt */
#define LLC_TYPE_IPV4 0x0008
#define LLC_TYPE_IPV6 0xDD86
#define LLC_TYPE_ARP 0x0608

// TCP timestamp
struct t_tcp_timestamp {
    guint32 time_a;
    guint32 time_b;
} __attribute__ ((packed));
typedef struct t_tcp_timestamp st_tcp_timestamp;

// Layer 2
#define AO_M2_NONE 0
#define AO_M2_IEEE80211 1
// Layer 3
#define AO_M3_NONE 0
#define AO_M3_IPV4 1
#define AO_M3_IPV6 2
#define AO_M3_ARP 3
// Layer 4
#define AO_M4_NONE 0
#define AO_M4_TCP 1
#define AO_M4_UDP 2

// Packet
struct t_ao_packet {
    // Airown
    st_ao_inst* ao_inst;
        
    // Lorcon
    lorcon_t* lor_ctx;
    lorcon_packet_t* lor_pck;
    
    // Layer 2
    union {
        struct {
            struct ieee80211_hdr* iw;
            struct libnet_802_2snap_hdr* llc;
            guint8* addr4;
            struct ieee80211_qos* qos;
        } dot11;
    } m2;
    guint32 m2_type;
    guint8* m2_data;
    guint32 m2_size;
    
    // Layer 3
    union {
        struct {
            struct libnet_ipv4_hdr* hdr;
        } ipv4;
        struct {
            struct libnet_ipv6_hdr* hdr;
        } ipv6;
    } m3;
    guint32 m3_type;
    guint8* m3_data;
    guint32 m3_size;
    
    // Layer 4
    union {
        struct {
            struct libnet_tcp_hdr* hdr;
            st_tcp_timestamp* ts;
        } tcp;
        struct {
            struct libnet_udp_hdr* hdr;
        } udp;
    } m4;
    guint32 m4_type;
    guint8* m4_data;
    guint32 m4_size;
    
    // Payload
    guint8* pl_data;
    guint32 pl_size;
};
typedef struct t_ao_packet st_ao_packet;

// Monitoring
void ao_pck_loop(lorcon_t* context, lorcon_packet_t* packet, u_char* user);
void ao_pck_log(st_ao_packet* pck);

#endif

