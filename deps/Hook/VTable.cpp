#include <Windows.h>

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

		MEMORY_BASIC_INFORMATION mbi;

		while (true) {
			VirtualQuery(VTable[VTable_Size], &mbi, sizeof(MEMORY_BASIC_INFORMATION));

			if (mbi.Protect != PAGE_EXECUTE_READ && mbi.Protect != PAGE_EXECUTE_READWRITE) {
				break;
			}

			VTable_Size++;
		}

		return VTable_Size;
	}

}