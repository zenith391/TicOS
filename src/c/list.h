/*
	Simple chained list system for TicOS/EternalOS
	Temporary until manual allocation is possible.
*/
struct Entry {
	struct Entry* next;
	struct Entry* previous;
	unsigned char hprevious;
	void* valuePointer;
};

void addToList(struct Entry* lastEntry, void* value) {
	struct Entry newEntry;
	newEntry.hprevious = (unsigned char) 1;
	newEntry.previous = lastEntry;
	newEntry.valuePointer = value;
	lastEntry->next = &newEntry;
}

struct Entry* getFirstEntry(struct Entry* entry) {
	if (entry->hprevious > 0) {
		struct Entry* prev = entry->previous;
		return getFirstEntry(prev);
	} else {
		return entry;
	}
}

void* getValue(struct Entry* anyEntry, unsigned int index) {
	struct Entry* entry = getFirstEntry(anyEntry);
	unsigned int i = 0;
	while (i < index) {
		entry = entry->next;
		i++;
	}
	return entry->valuePointer;
}