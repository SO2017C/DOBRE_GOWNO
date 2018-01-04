#ifndef ACL_h
#define ACL_h

#include "Biblioteki.h"

struct User {
	std::string name;
	std::string password;
	std::string group;
	std::string permissions;
	std::string effective_permissions;

	User() {}
};

struct Group {
	std::string name;
	std::vector<User> users_in_group;
	std::string permissions;
	std::string effective_permissions;

	Group() {}
};

struct ACL {
	std::string owner;
	std::string group;
	std::string user_owner_permissions;
	std::string group_owner_permissions;
	std::string group_owner_effective_permissions;
	std::vector<User> users;
	std::vector<Group> groups;
	std::string mask;
	std::string others;

	ACL() {}
};

class Permissions {
private:
	std::map<std::string, ACL> ACL_container;
	std::vector<User> all_users;
	std::vector<Group> all_groups;
	User log_in_user;
	bool mask_defined = false;
public:
	Permissions();

	~Permissions();

	User return_log_in_user_name();

	bool user_exists(std::string name);

	bool group_exists(std::string name);

	void add_user(std::string name, std::string password);

	void add_group(std::string name);

	void delete_user(std::string name);

	void delete_group(std::string name);

	void display_users();

	void display_groups();

	void log_out_and_in(std::string name, std::string password);

	void add_to_group(std::string name, std::string group);

	std::string numbers_to_rwx(char right);

	void createACL(std::string file_name);

	void getfacl(std::string file_name);

	bool user_exists_in_ACL(std::string name, std::string file_name);

	bool group_exists_in_ACL(std::string name, std::string file_name);

	void delete_user_from_ACL(std::string name, std::string file_name);

	void delete_group_from_ACL(std::string name, std::string file_name);

	std::string from_normal_to_effective(std::string mask, std::string permissions);

	void set_effective_permissions(std::string permissions, std::string file_name);

	void setfacl(char parameter, std::string command, char right, std::string file_name);

	void deleteACL(std::string file_name);

	void display_all_ACLs();

	void delete_all_ACLs();

	bool read_permission(std::string file_name);

	bool write_permission(std::string file_name);

	bool exec_permission(std::string file_name);

};

#endif
