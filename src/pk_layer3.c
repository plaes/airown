/*
 * Airown - layer 3 analysis
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

// Int inc
#include "ao_config.h"
#include "pk_layer3.h"
#include "pk_layer4.h"

// Functions
void pck_ipv4_read(st_ao_packet* pck)
{
    // IPv4 header
    pck->m3.ipv4.hdr = NULL;
    if (pck->m3_size >= sizeof(struct iphdr)) {
    
        // Set type
        pck->m3_type = AO_M3_IPV4;
        
        // Header
        pck->m3.ipv4.hdr = (struct iphdr*)(pck->m3_data);
        
        // Data
        pck->m4_data = pck->m3_data + sizeof(struct iphdr);
        pck->m4_size = pck->m3_size - sizeof(struct iphdr);
        
        // Next layer
        switch (pck->m3.ipv4.hdr->protocol) {
            case IPPROTO_TCP:
                pck_tcp_read(pck);
                break;
            case IPPROTO_UDP:
                pck_udp_read(pck);
                break;
        }
    }
}

void pck_ipv4_free(st_ao_packet* pck)
{
    switch (pck->m4_type) {
        case AO_M4_TCP:
            pck_tcp_free(pck);
            break;
        case AO_M4_UDP:
            pck_udp_free(pck);
            break;
    }
}

void pck_ipv6_read(st_ao_packet* pck)
{
    // IPv6 header
    pck->m3.ipv6.hdr = NULL;
    if (pck->m3_size >= sizeof(struct ipv6hdr)) {
    
        // Set type
        pck->m3_type = AO_M3_IPV6;
        
        // Header
        pck->m3.ipv6.hdr = (struct ipv6hdr*)(pck->m3_data);
        
        // Data
        pck->m4_data = pck->m3_data + sizeof(struct ipv6hdr);
        pck->m4_size = pck->m3_size - sizeof(struct ipv6hdr);
        
        // Next layer
        switch (pck->m3.ipv6.hdr->nexthdr) {
            case IPPROTO_TCP:
                pck_tcp_read(pck);
                break;
            case IPPROTO_UDP:
                pck_udp_read(pck);
                break;
        }
    }
}

void pck_ipv6_free(st_ao_packet* pck)
{
    switch (pck->m4_type) {
        case AO_M4_TCP:
            pck_tcp_free(pck);
            break;
        case AO_M4_UDP:
            pck_udp_free(pck);
            break;
    }
}

