
#include <stdlib.h>

#include "VTable.h"

namespace Hook {

	void SetVTable(void *object, void *VTable) {
		*(void **)object = VTable; // Assuming first property is VPointer
	}

	void **GetVTable(void *object) {
		return *(void ***)object; // Assuming first property is VPointer
	}

	void *GetMethod(void *object, int offset) {
		void **VTable = GetVTable(object);

		return VTable[offset];
	}

	size_t GetVTableSize(void **VTable) {

		size_t VTable_Size = 0;


		while (VTable[VTable_Size])
		{
			VTable_Size++;
		}

		return VTable_Size;
	}

}
