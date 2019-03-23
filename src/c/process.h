struct process {
		unsigned int pid;

		struct {
				u32 eax, ecx, edx, ebx;
				u32 esp, ebp, esi, edi;
				u32 eip, eflags;
				u32 cs:16, ss:16, ds:16, es:16, fs:16, gs:16;
				u32 cr3;
		} regs __attribute__ ((packed));
} __attribute__ ((packed));

void load_task(u32 *addr, u32* src, unsigned int size);