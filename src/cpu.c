#include <u.h>
#include <limits.h>
#include <libcpu.h>
#include <assert.h>
#include <uart.h>

#define CPUSEG_DATARW 0x00000200
#define CPUSEG_CODERX 0x00000900
#define CPUSEG_S	  0x00001000
#define CPUSEG_P      0x00008000
#define CPUSEG_DB     0x00400000
#define CPUSEG_G      0x00800000

static int initialized = 0;

// TODO(wgr): jump to ref file instead of commenting here
// local ref: file:///usr/wgr/lib/pdf/intel-arch-ref.pdf#G41.31794
// online ref: access: (Tue Dec 18 03:28:57 -02 2018) https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf#G41.31794
typedef struct cpuDescSegment cpuDescSegment;
struct cpuDescSegment {
	u32int low, high;
};

typedef struct cpuRegSegment cpuRegSegment;
struct cpuRegSegment {
	u16int limit;
	u32int base;
// TODO(wgr): do i need to pack?
}__attribute__((packed));

typedef void (*handle)(void) fnHandler;

static cpuDescSegment cpu_ldts[NCPUIDT];
static cpuDescSegment cpu_gdts[3];

static void init_gdtnil(uint i, fnHandler f){
	assert(i < NCPUIDT);
	cpu_ldts[i].low = 0;
	cpu_ldts[i].high = 0;
}

static void init_gdtcode(int i, fnHandler f){
	// base: 0, limit: 0xffffffff
	// priv level: 0 (always super visor)
	cpu_ldts[i].low = 0xffff;
	cpu_ldts[i].high = CPUSEG_G|CPUSEG_DB|(0xf<<16)
		|CPU_SEGP|CPU_SEGS|CPUSEG_CODERX;
}

static void init_gdtdata(int i, fnHandler f){
	// base: 0, limit: 0xffffffff
	// priv level: 0 (always super visor)
	cpu_ldts[i].low = 0xffff;
	cpu_ldts[i].high = CPUSEG_G|CPUSEG_DB|(0xf<<16)
		|CPU_SEGP|CPU_SEGS|CPUSEG_DATARW;
}

static void init_ldt(int i, fnHandler f){
	cpu_ldts[i].low = 0;
	cpu_ldts[i].high = 0;
}

static void std_int_handler(void){
	uart·println("reached");
	for(;;);
}

static void init_gdts(void){

}

static void init_ldts(void){
	int i;
	for(i=0; i<NCPUIDT; i++)
		init_ldt(i);
}

static void cpu_init(void){
	init_ldts();
	init_gdts();
}