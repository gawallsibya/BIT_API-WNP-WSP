// SPY.h

#ifdef DLL_SOURCE
	#define DLLAPI extern "C" __declspec( dllexport)

#else
	#define DLLAPI extern "C" __declspec(dllimport)
#endif

// 2���� �Լ��� export
DLLAPI void Install();
DLLAPI void Uninstall();


