/********************************************************************
	created:	2013/08/03
	created:	3:8:2013   17:29
	filename: 	e:\hanryGitHub\module\include\BaseDefine.h
	file path:	e:\hanryGitHub\module\include
	file base:	BaseDefine
	file ext:	h
	author:		hanry.liao
	
	purpose:	基本数据类型定义
*********************************************************************/

#ifndef __BASE_DEFINE__
#define __BASE_DEFINE__

#include <time.h>

namespace wmp
{
namespace base
{
typedef unsigned char        ui8;
typedef unsigned short       ui16;
typedef unsigned int		  ui32;
typedef unsigned __int64     ui64;
typedef ui32                uid;
typedef time_t              ttime;
}
}



#endif // __BASE_DEFINE__