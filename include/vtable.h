#ifndef VTABLE_H
#define VTABLE_H

#define ushort_max (unsigned short(-1))

typedef char *vtindex; // sizeof(pointer) with ability to add numbers and shit 
#ifndef offset
#define offset(x,y) ((char *)(x) - (char *)(y))
#endif

class VTable
{
public:
	VTable(void *object)
	{
		original_vt = *(vtindex **)object;
		vtindex *last_index = original_vt;
		while (*last_index++);

		unsigned int size = offset(last_index, original_vt) / sizeof(*last_index);

		new_vt = new vtindex[size];
		while (--last_index >= original_vt)
			new_vt[offset(last_index, original_vt) / sizeof(*last_index)] = *last_index;

		*(vtindex **)object = new_vt;

		hooked = (void **)object;
	}
	~VTable()
	{
		*hooked = original_vt;
		delete[] new_vt;
	}

	void hook(unsigned short index, void *func)
	{
		get(index) = (vtindex)func;
	}
	void unhook(unsigned short index)
	{
		get(index) = getold(index);
	}


	vtindex &getold(unsigned short index)		{ return original_vt[index]; }

private:
	vtindex &get	(unsigned short index)		{ return new_vt[index];		 }


public:
	vtindex *original_vt;
	vtindex *new_vt;
	void **hooked;

};

#undef offset

#endif // VTABLE_H