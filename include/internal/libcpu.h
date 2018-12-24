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

ulong cpu·eflags(void);
u8int cpu·can_int(void);
void cpu·unusetint(void);
void cpu·setint(void);
// load global descriptor table
void cpu·lgdt(cpuDescSegment *d);
