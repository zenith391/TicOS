#include "lib.h"

void load_task(u32 *addr, u32* src, unsigned int size) {

	/* Copie du code a l'adresse specifiee */
	memcpy((char *) addr, (char *) src, size);

	/* Initialisation des registres */
	p_list[n_proc].pid = n_proc;
	p_list[n_proc].regs.ss = 0x33;
	p_list[n_proc].regs.esp = 0x40001000;
	p_list[n_proc].regs.cs = 0x23;
	p_list[n_proc].regs.eip = 0x40000000;
	p_list[n_proc].regs.ds = 0x2B;
	// p_list[n_proc].regs.cr3 = (u32) pd;

	n_proc++;
}