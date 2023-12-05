#include <stdint.h>

#ifndef _ACPI_H_
#define _ACPI_H_

struct rspd_t {
    uint8_t signature[8];
    uint8_t checksum;
    uint8_t oemid[6];
    uint8_t revision;
    uint32_t rsdtaddr;      // deprecated since version 2.0
 
    uint32_t length;
    uint64_t xsdtaddr;
    uint8_t extendedchecksum;
    uint8_t reserved[3];
} __attribute__ ((packed));

struct rspd_t* init_rspd(uint64_t rspd_addr);

#endif