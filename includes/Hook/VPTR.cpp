
#include <stdlib.h>

#include "VPTR.h"
#include "VTable.h"

namespace Hook {

	VPTR::VPTR(void *target) {
		Target = target;

		VTable_Old = GetVTable(Target);
		VTable_Size = GetVTableSize(VTable_Old);

		VTable_New = new void *[VTable_Size];

		for (size_t i = 0; i < VTable_Size; i++) {
			VTable_New[i] = VTable_Old[i];
		}

		SetVTable(Target, VTable_New);
	}

	VPTR::~VPTR() {
		if (VTable_New) {
			delete[] VTable_New;
		}
	}

	void VPTR::Remove() {
		if (VTable_Old && Target) {
			SetVTable(Target, VTable_Old);
		}

		delete this;
	}

}
