#include "Precompiled.h"
#include "Output.h"

void My::Output::Print(std::string _str)
{
	//나중에 디버그만 출력이나
	//로그와 연계를 위해 별도 함수로 미리 뽑아놓음
	std::cout << _str;
}

void My::Output::Log(std::string _str)
{
	//텍스트 파일 만들어서 출력
	//

}
