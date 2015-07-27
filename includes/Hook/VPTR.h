#pragma once

namespace Hook {

	class VPTR {
	public:

		VPTR(void *target);

		template< typename HookFn >
		HookFn GetOriginal(int index) {
			return (HookFn)(VTable_Old[index]);
		}

		void Hook(int index, void *hook) {
			VTable_New[index] = hook;
		}

		void Unhook(int index) {
			VTable_New[index] = VTable_Old[index];
		}

		void Remove();

	private:
		
		~VPTR();

		void *Target;

		size_t VTable_Size = 0;

		void **VTable_Old;
		void **VTable_New;
	};

}