#include <u.h>
#include <limits.h>
#include <internal/libcpu.h>
// TODO(wgr): #include <assert.h>
#include <uart.h>

#define CPUSEG_DATARW 0x00000200
#define CPUSEG_CODERX 0x00000900
#define CPUSEG_S	  0x00001000
#define CPUSEG_P      0x00008000
#define CPUSEG_DB     0x00400000
#define CPUSEG_G      0x00800000

enum GDT_INDEX {
	GDT_NIL = 0,
	GDT_CODE = 1 << 3,
	GDT_DATA = 2 << 3,
	GDT_N = 3,
};

static int initialized = 0;

// TODO(wgr): jump to ref file instead of commenting here
// local ref: file:///usr/wgr/lib/pdf/intel-arch-ref.pdf#G41.31794
// online ref: access: (Tue Dec 18 03:28:57 -02 2018) https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf#G41.31794


static cpuDescSegment cpu_idt[NCPUIDT];
static cpuDescSegment cpu_gdt[GDT_N];

static void init_gdtnil(int i){
	//TODO(wgr): assert(i < NCPUIDT);
	cpu_gdt[i].low = 0;
	cpu_gdt[i].high = 0;
}

static void init_gdtcode(int i){
	// base: 0, limit: 0xffffffff
	// priv level: 0 (always supervisor)
	cpu_gdt[i].low = 0xffff;
	cpu_gdt[i].high = CPUSEG_G|CPUSEG_DB|(0xf<<16)
		|CPUSEG_P|CPUSEG_S|CPUSEG_CODERX;
}

static void init_gdtdata(int i){
	// base: 0, limit: 0xffffffff
	// priv level: 0 (always supervisor)
	cpu_gdt[i].low = 0xffff;
	cpu_gdt[i].high = CPUSEG_G|CPUSEG_DB|(0xf<<16)
		|CPUSEG_P|CPUSEG_S|CPUSEG_DATARW;
}

static int get_gdt_by_sel(int sel){
	// skip the TI and RPL bits, see libcpu.s:10, TODO(wgr): remember to move along when
	// fix the documentation links

	// TODO(wgr): assert(i < len(cpu_gdt));

	return sel >> 3;
}

static void init_pseudo_desc(cpuRegSegment *desc, void *addr, int i){
	//TODO(wgr): assert(i < 0x10000);
	desc->limit = i-1;
	desc->base = (uintptr)addr;
}

static void init_gdt(void){
	cpuRegSegment desc;
	init_gdtnil(get_gdt_by_sel(GDT_NIL));
	init_gdtcode(get_gdt_by_sel(GDT_CODE));
	init_gdtdata(get_gdt_by_sel(GDT_DATA));
	init_pseudo_desc(&desc, cpu_gdt, sizeof cpu_gdt);
	cpu·lgdt(&desc);
}

// TODO(wgr): ref to IDT Gate Descriptors
static void init_idt_gate(cpuDescSegment *d, void (*handler)(void)) {
	d->low = (GDT_CODE << 16) | (((uintptr)handler) & 0xffff);
	d->high = (((uintptr)handler) & 0xffff0000)|CPUSEG_P|0xf00;
}

static void intr_handler(void){
	uart·println("reached");
	for(;;);
}

static void init_idt(void){
	int i;
	cpuRegSegment desc;
	for(i=0; i<NCPUIDT; i++)
		init_idt_gate(&cpu_idt[i], &intr_handler);
	init_pseudo_desc(&desc, cpu_idt, sizeof cpu_idt);
	cpu·lidt(&desc);
}

void cpu·init(void){
	init_gdt();
	init_idt();
}
