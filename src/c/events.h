#ifndef __EVENTS_H_
	#define __EVENTS_H_
	
#endif

struct Event {
	char* name;
	int argc;
	void** argv;
};

struct Event newEvent(char name[20], int argc, void* argv[10]);
void pushEvent(struct Event);