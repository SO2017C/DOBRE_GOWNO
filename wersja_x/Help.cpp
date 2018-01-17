#include "Help.h"


/// DYSK
void HELP_CLASS::CREATEFILE_H()
{
	std::cout << "Usage: cf [param1] [param2] [param3]" << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the file." << std::endl;
	std::cout << "\tparam2 - numbers of byte dedicated for the file." << std::endl;
	std::cout << "\tparam3 - optionally text written into the file." << std::endl << std::endl;
}

void HELP_CLASS::READFILE_H()
{
	std::cout << "Usage: rf [param1]" << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the file you want to read." << std::endl << std::endl;
}

void HELP_CLASS::WRITEFILE_H()
{
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the file you want write text in." << std::endl << std::endl;
	std::cout << "\tparam2 - the text that will be written into  the file." << std::endl << std::endl;
	std::cout << "\tparam3 - optionally an index asdf asd." << std::endl << std::endl;
}

void HELP_CLASS::DELETEFILE_H()
{
	std::cout << "Usage: rf [param1]" << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the file you want to delete." << std::endl << std::endl;
}

void HELP_CLASS::RENAMEFILE_H()
{
	std::cout << "Usage: rn [param1] [param2]" << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the file you want to change the name." << std::endl;
	std::cout << "\tparam2 - new name of the file." << std::endl << std::endl;
}


/// ACL
void HELP_CLASS::USERADD_H()
{
	std::cout << "Usage: useradd [param1] [param2]" << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name for the new user." << std::endl;
	std::cout << "\tparam2 - password for the new user." << std::endl << std::endl;
}

void HELP_CLASS::USERDEL_H()
{
	std::cout << "Usage: userdel [param1] " << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the user you want to delete." << std::endl << std::endl;
}

void HELP_CLASS::GROUPADD_H()
{
	std::cout << "Usage: groupadd [param1] " << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the group you want to add." << std::endl << std::endl;
}

void HELP_CLASS::GROUPDEL_H()
{
	std::cout << "Usage: groupdel [param1] " << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the group you want to delete." << std::endl << std::endl;
}

void HELP_CLASS::SWITCHUSER_H()
{
	std::cout << "Usage: su [param1] [param2] " << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the user you want to switch on." << std::endl;
	std::cout << "\tparam2 - password, leave empty if an user doesn't have one" << std::endl << std::endl;
}

void HELP_CLASS::USERMOD_H()
{
	std::cout << "Usage: usermod [param1] [param2]" << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of user you want to move." << std::endl;
	std::cout << "\tparam2 - name of the group that you want to put an user in." << std::endl << std::endl;
}

void HELP_CLASS::GETFACL_H()
{
	std::cout << "Usage: getfacl [param1]" << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the file that you want to check." << std::endl << std::endl;
}

void HELP_CLASS::SETFACL_H()
{
	std::cout << "Usage: setfacl -[param1] [param2]:[param3]:[param4] [param5]" << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - m as modification, x as deleting." << std::endl;
	std::cout << "\tparam2 - mark: u (user), g (group), m (mask), o (others),." << std::endl;
	std::cout << "\tparam3 - name of the user or group." << std::endl;
	std::cout << "\tparam4 - access right, 0-7 (R-4, W-2, X-1)." << std::endl;
	std::cout << "\tparam5 - name of the file that you want to set the file access control list." << std::endl << std::endl;
}

/// MEMORY
void HELP_CLASS::DISPLAYMEMORY_H()
{

}

/// PROCESS
void HELP_CLASS::CREATEPROCESS_H()
{
	std::cout << "Usage: cp [param1] [param2] [param3] [param4]" << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - ID of the father process." << std::endl;
	std::cout << "\tparam2 - amount of bytes dedicated for that process in memory." << std::endl;
	std::cout << "\tparam3 - name for the new process." << std::endl;
	std::cout << "\tparam4 - name of the .txt file with the program." << std::endl << std::endl;
}

void HELP_CLASS::SHOWPCB_H()
{
	std::cout << "Usage: showpcb [param1] " << std::endl << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "\tparam1 - name of the process that you want to check the pcb." << std::endl << std::endl;
}

///MY
void HELP_CLASS::HELP_F()
{
	std::cout << "You've typed wrong input." << std::endl;
	std::cout << "If you need a help, just type the name of command or the name of command and \"/?\"" << std::endl;
	std::cout << "ask the developers of this Operation System." << std::endl << std::endl;
}
