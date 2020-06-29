#ifndef PRINT_H
#define PRINT_H

namespace My
{
	class Output : public Singleton<Output>
	{
	public:
		enum Priority
		{
			One,
			Two,
			Three,
			Four,
			End
		};
		static void Print(std::string _str);
		static void Log(std::string _str);

	};
	
	

}

#endif