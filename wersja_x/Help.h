#pragma once
#include "Biblioteki.h"
class HELP_CLASS
{
public:
	/// DYSK
	void CREATEFILE_H();
	void READFILE_H();
	void WRITEFILE_H();
	void DELETEFILE_H();
	void RENAMEFILE_H();

	/// ACL
	void USERADD_H();
	void USERDEL_H();
	void GROUPADD_H();
	void GROUPDEL_H();
	void SWITCHUSER_H();
	void USERMOD_H();
	void GETFACL_H();
	void SETFACL_H();

	/// MY
	void HELP_F();
};