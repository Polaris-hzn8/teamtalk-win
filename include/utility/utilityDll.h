/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef UTILITYDLL_3CAE310A_4FC9_4250_9C38_B28359D07706_H__
#define UTILITYDLL_3CAE310A_4FC9_4250_9C38_B28359D07706_H__

#ifndef UTILITY_DLL
	#define UTILITY_API			__declspec( dllimport )
	#define UTILITY_CLASS		__declspec( dllimport )
#else
	#define UTILITY_API			__declspec( dllexport )
	#define UTILITY_CLASS		__declspec( dllexport )
#endif

#endif// UTILITYDLL_3CAE310A_4FC9_4250_9C38_B28359D07706_H__

