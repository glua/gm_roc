#pragma once

namespace Hook {

	void SetVTable(void *object, void *VTable);
	void **GetVTable(void *object);
	void *GetMethod(void *object, int offset);

	size_t GetVTableSize(void **VTable);

}