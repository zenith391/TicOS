#include "events.h"
#include "list.h"

struct Entry firstEventsEntry;

struct Event newEvent(char name[20], int argc, void* argv[10]) {
	struct Event evt;
	evt.name = (char*) name;
	evt.argc = argc;
	evt.argv = (void*) argv;
	return evt;
}

void pushEvent(struct Event evt) {
	addToList(&firstEventsEntry, &evt);
}