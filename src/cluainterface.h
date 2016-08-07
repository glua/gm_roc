class CLuaInterface
{
private:
	template<typename t>
	inline t get(unsigned short which)
	{
		return t((*(char ***)(this))[which]);
	}
};