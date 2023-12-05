#include <acpi.h>
#include <terminal.h>

#define RPSD_SIGNATURE "RSD PTR "

struct rspd_t* rpsd_header;

struct rspd_t* init_rspd(uint64_t rpsd_addr) {
    // TODO: Checksum check
    struct rspd_t *rpsd_hdr;
    rpsd_hdr = (struct rspd_t*)&rpsd_addr;
    if((char*)(*rpsd_hdr).signature == (char*)RPSD_SIGNATURE) {
        tprintf("good\n");
    }
    //tprintf("%x\n",(char*)(*rpsd_hdr).signature); // внимание казахстан умирает
    return rpsd_hdr;
}