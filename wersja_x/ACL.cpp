#include "ACL.h"

Permissions::Permissions() {
	User u;
	Group g1, g2;
	g1.name = "administrators";
	g2.name = "users";
	u.name = "administrator";
	u.password = "admin";
	u.group = g1.name;
	g1.users_in_group.push_back(u);
	all_groups.push_back(g1);
	all_groups.push_back(g2);
	all_users.push_back(u);
	log_in_user = u;
}

Permissions::~Permissions() {}

User Permissions::return_log_in_user_name() {
	return log_in_user;
}

bool Permissions::user_exists(std::string name) {
	for (auto e : all_users)
		if (e.name == name)
			return true;
	return false;
}

bool Permissions::group_exists(std::string name) {
	for (auto e : all_groups)
		if (e.name == name)
			return true;
	return false;
}

void Permissions::add_user(std::string name, std::string password) {
	User u;
	if (!user_exists(name)) {
		u.name = name;
		u.password = password;
		u.group = "users";
		all_users.push_back(u);

		for (int i = 0; i < all_groups.size(); i++) {
			if (all_groups[i].name == "users")
				all_groups[i].users_in_group.push_back(u);
		}
	}
	else std::cout << "\nUser with this name already exists\n\n";
}

void Permissions::add_group(std::string name) {
	Group g;
	if (!group_exists(name)) {
		g.name = name;
		all_groups.push_back(g);
	}
}

void Permissions::delete_user(std::string name) {
	if (log_in_user.group == "administrators") {
		if (name != "administrator") {
			if (log_in_user.name != name) {
				std::string group_name;
				int counter = -1;
				for (int i = 0; i < all_users.size(); i++) {
					if (all_users[i].name == name) {

						group_name = all_users[i].group;
						all_users.erase(all_users.begin() + i);
					}
				}
				for (int i = 0; i < all_groups.size(); i++) {
					if (all_groups[i].name == group_name) {
						for (int j = 0; j < all_groups[i].users_in_group.size(); j++) {
							if (all_groups[i].users_in_group[j].name == name)
								all_groups[i].users_in_group.erase(all_groups[i].users_in_group.begin() + j);
						}
					}
				}
				for (auto &z : ACL_container) {
					counter = -1;
					for (auto &x : z.second.users) {
						counter++;
						if (x.name == name) {
							z.second.users.erase(z.second.users.begin() + counter);
						}
					}
				}
				std::cout << "User \"" << name << "\" was deleted" << std::endl << std::endl;
			}
			else std::cout << "\nCannot delete the logged in user\n\n";
		}
		else std::cout << "\nCannot delete the built-in administrator account\n\n";
	}
	else std::cout << "\nTo delete a user, you must belong to the administrators group\n\n";
}

void Permissions::delete_group(std::string name) {
	if (log_in_user.group == "administrators") {
		if (name != "administrators" && name != "users") {
			User u;
			std::vector<User> pom{};
			int counter = -1;

			for (int i = 0; i < all_users.size(); i++) {
				if (all_users[i].group == name) {
					all_users[i].group = "users";
				}
			}
			for (int i = 0; i < all_groups.size(); i++) {
				if (all_groups[i].name == name) {
					for (int j = 0; j < all_groups[i].users_in_group.size(); j++) {
						u.name = all_groups[i].users_in_group[j].name;
						u.password = all_groups[i].users_in_group[j].password;
						u.group = "users";
						pom.push_back(u);
					}
					all_groups.erase(all_groups.begin() + i);
				}
			}

			for (int i = 0; i < all_groups.size(); i++) {
				if (all_groups[i].name == "users") {
					for (int j = 0; j < pom.size(); j++) {
						u.name = pom[j].name;
						u.password = pom[j].password;
						u.group = "uzytkownicy";
						all_groups[i].users_in_group.push_back(u);
					}
				}
			}

			for (auto &z : ACL_container) {
				counter = -1;
				for (auto &x : z.second.groups) {
					counter++;
					if (x.name == name) {
						z.second.groups.erase(z.second.groups.begin() + counter);
					}
				}
			}
			std::cout << "Group \"" << name << "\" was deleted" << std::endl << std::endl;
		}
		else std::cout << "\nCannot delete built-in administrators and users accounts\n\n";
	}
	else std::cout << "\nTo delete a group, you must belong to the administrators group\n\n";
}

void Permissions::display_users() {
	std::cout << "\n";
	for (auto e : all_users)
		std::cout << e.name << "\n";
	std::cout << "\n";
}

void Permissions::display_groups() {
	std::cout << "\n";
	for (auto e : all_groups) {
		std::cout << e.name << ": ";
		for (auto z : e.users_in_group)
			std::cout << z.name << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
}

void Permissions::log_out_and_in(std::string name, std::string password) {
	bool flag = false;
	for (int i = 0; i < all_users.size(); i++) {
		if (all_users[i].name == name) {
			if (all_users[i].password == password)
				log_in_user = all_users[i];
			else
				std::cout << "\nIncorrect password\n\n";

			flag = true;
			break;
		}
	}
	if (!flag)
		std::cout << "\nSpecified user " << "'" << name << "'" << " doesn't exist\n\n";
}

void Permissions::add_to_group(std::string name, std::string group) {
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;
	bool flag4 = false;
	User u;
	for (auto e : all_users)
		if (e.name == name && e.name != "administrator") {
			flag3 = true;
			u = e;
		}

	if (log_in_user.group == "administrators")
		flag1 = true;

	if (u.group != group)
		flag4 = true;

	for (int i = 0; i < all_groups.size(); i++)
		if (all_groups[i].name == group)
			flag2 = true;

	if (flag1 == true && flag2 == true && flag3 == true && flag4 == true) {
		for (int j = 0; j < all_groups.size(); j++) {
			if (all_groups[j].name == u.group) {
				for (int k = 0; k < all_groups[j].users_in_group.size(); k++) {
					if (all_groups[j].users_in_group[k].name == u.name) {
						all_groups[j].users_in_group.erase(all_groups[j].users_in_group.begin() + k);
					}
				}
			}
		}
	}
	if (flag1 == true && flag2 == true && flag3 == true && flag4 == true) {
		u.group = group;
		for (int i = 0; i < all_groups.size(); i++) {
			if (all_groups[i].name == group)
				all_groups[i].users_in_group.push_back(u);
		}
		for (auto &x : all_users) {
			if (x.name == name)
				x.group = group;
		}
	}
	if (!flag4)
		std::cout << "\nSpecified user already belongs to this group\n\n";
	if (!flag3)
		std::cout << "\nThis user doesn't exist\n\n";
	if (!flag2)
		std::cout << "\nThis group doesn't exist\n\n";
	if (!flag1)
		std::cout << "\n You are not allowed to perform such operation. \nLog in to the administrator's account\n\n";

}

std::string Permissions::numbers_to_rwx(char right) {
	std::string permissions;
	switch (right) {
	case '0':
		permissions = "---";
		return permissions;
	case '1':
		permissions = "--x";
		return permissions;
	case '2':
		permissions = "-w-";
		return permissions;
	case '3':
		permissions = "-wx";
		return permissions;
	case '4':
		permissions = "r--";
		return permissions;
	case '5':
		permissions = "r-x";
		return permissions;
	case '6':
		permissions = "rw-";
		return permissions;
	case '7':
		permissions = "rwx";
		return permissions;
	}
}

void Permissions::createACL(std::string file_name) {
	std::pair<std::string, ACL> pair;
	pair.first = file_name;
	pair.second.owner = log_in_user.name;
	pair.second.group = log_in_user.group;
	pair.second.user_owner_permissions = "rwx";
	pair.second.group_owner_permissions = "rwx";
	pair.second.mask = "rwx";
	pair.second.others = "r--";
	ACL_container.insert(pair);
}

void Permissions::getfacl(std::string file_name) {
	std::cout << "\n";
	if (ACL_container.find(file_name) != ACL_container.end()) {
		if (ACL_container[file_name].mask == "rwx") {
			std::cout << "# file: " << file_name << "\n";
			std::cout << "# owner: " << ACL_container[file_name].owner << "\n";
			std::cout << "# group: " << ACL_container[file_name].group << "\n";
			std::cout << "user::" << ACL_container[file_name].user_owner_permissions << "\n";
			for (auto p : ACL_container[file_name].users)
				std::cout << "user:" << p.name << ":" << p.permissions << "\n";
			std::cout << "group::" << ACL_container[file_name].group_owner_permissions << "\n";
			for (auto p : ACL_container[file_name].groups)
				std::cout << "group:" << p.name << ":" << p.permissions << "\n";
			std::cout << "mask::" << ACL_container[file_name].mask << "\n";
			std::cout << "other::" << ACL_container[file_name].others << "\n\n";
		}
		else {
			std::cout << "# file: " << file_name << "\n";
			std::cout << "# owner: " << ACL_container[file_name].owner << "\n";
			std::cout << "# group: " << ACL_container[file_name].group << "\n";
			std::cout << "user::" << ACL_container[file_name].user_owner_permissions << "\n";
			for (auto p : ACL_container[file_name].users)
				std::cout << "user:" << p.name << ":" << p.permissions << "\t\t\t#effective:" << p.effective_permissions << "\n";
			std::cout << "group::" << ACL_container[file_name].group_owner_permissions << "\t\t\t#effective:" << ACL_container[file_name].group_owner_effective_permissions << "\n";
			for (auto p : ACL_container[file_name].groups)
				std::cout << "group:" << p.name << ":" << p.permissions << "\t\t\t#effective:" << p.effective_permissions << "\n";
			std::cout << "mask::" << ACL_container[file_name].mask << "\n";
			std::cout << "other::" << ACL_container[file_name].others << "\n\n";
		}
	}
	else std::cout << "This file doesn't exist\n\n";
}

bool Permissions::user_exists_in_ACL(std::string name, std::string file_name) {
	for (auto z : ACL_container) {
		if (z.first == file_name) {
			for (auto x : z.second.users)
				if (x.name == name)
					return true;
		}
	}
	return false;
}

bool Permissions::group_exists_in_ACL(std::string name, std::string file_name) {
	for (auto z : ACL_container) {
		if (z.first == file_name) {
			for (auto x : z.second.groups)
				if (x.name == name)
					return true;
		}
	}
	return false;
}

void Permissions::delete_user_from_ACL(std::string name, std::string file_name) {
	for (int i = 0; i < ACL_container[file_name].users.size(); i++) {
		if (ACL_container[file_name].users[i].name == name)
			ACL_container[file_name].users.erase(ACL_container[file_name].users.begin() + i);
	}
}

void Permissions::delete_group_from_ACL(std::string name, std::string file_name) {
	for (int i = 0; i <ACL_container[file_name].groups.size(); i++) {
		if (ACL_container[file_name].groups[i].name == name)
			ACL_container[file_name].groups.erase(ACL_container[file_name].groups.begin() + i);
	}
}

std::string Permissions::from_normal_to_effective(std::string mask, std::string permissions) {
	std::string effective_permissions = "";
	for (int i = 0; i < 3; i++) {
		if (permissions[i] != mask[i])
			effective_permissions += '-';
		else
			effective_permissions += mask[i];
	}
	return effective_permissions;
}

void Permissions::set_effective_permissions(std::string permissions, std::string file_name) {
	std::string new_permissions = "";
	std::string mask = permissions;
	for (auto &x : ACL_container[file_name].users) {
		new_permissions = from_normal_to_effective(mask, x.permissions);
		x.effective_permissions = new_permissions;
	}
	new_permissions = from_normal_to_effective(mask, ACL_container[file_name].group_owner_permissions);
	ACL_container[file_name].group_owner_effective_permissions = new_permissions;

	for (auto &y : ACL_container[file_name].groups) {
		new_permissions = from_normal_to_effective(mask, y.permissions);
		y.effective_permissions = new_permissions;
	}
}

void Permissions::setfacl(char parameter, std::string command, char right, std::string file_name) {
	char mark = command[0];
	User u; Group g;
	std::string name = "", permissions = "";
	if (parameter == 'm') {
		switch (mark) {
		case 'u':
			name = command.substr(2, command.size() - 2);
			if (user_exists(name)) {
				permissions = numbers_to_rwx(right);
				if (!mask_defined) {
					if (!user_exists_in_ACL(name, file_name)) {
						u.name = name;
						u.permissions = permissions;
						ACL_container[file_name].users.push_back(u);
					}
					else {
						for (int i = 0; i < ACL_container[file_name].users.size(); i++) {
							if (ACL_container[file_name].users[i].name == name) {
								ACL_container[file_name].users[i].permissions = permissions;
							}
						}
					}
				}
				else {
					if (!user_exists_in_ACL(name, file_name)) {
						u.name = name;
						u.permissions = permissions;
						u.effective_permissions = from_normal_to_effective(ACL_container[file_name].mask, permissions);
						ACL_container[file_name].users.push_back(u);
					}
					else {
						for (int i = 0; i <ACL_container[file_name].users.size(); i++) {
							if (ACL_container[file_name].users[i].name == name) {
								ACL_container[file_name].users[i].permissions = permissions;
								ACL_container[file_name].users[i].effective_permissions = from_normal_to_effective(ACL_container[file_name].mask, permissions);
							}
						}
					}
				}
			}
			else {
				std::cout << "\nThis user doesn't exist\n\n";
			}
			break;
		case 'g':
			name = command.substr(2, command.size() - 2);
			if (group_exists(name)) {
				permissions = numbers_to_rwx(right);
				if (!group_exists_in_ACL(name, file_name)) {
					g.name = name;
					g.permissions = permissions;
					ACL_container[file_name].groups.push_back(g);
				}
				else {
					for (int i = 0; i < ACL_container[file_name].groups.size(); i++) {
						if (ACL_container[file_name].groups[i].name == name)
							ACL_container[file_name].groups[i].permissions = permissions;
					}
				}
			}
			else {
				std::cout << "\nThis group doesn't exist\n\n";
			}
			break;
		case 'm':
			if (right < 55) {
				permissions = numbers_to_rwx(right);
				set_effective_permissions(permissions, file_name);
				ACL_container[file_name].mask = permissions;
				mask_defined = true;
			}
			else {
				permissions = numbers_to_rwx(right);
				ACL_container[file_name].mask = permissions;
			}
			break;
		case 'o':
			permissions = numbers_to_rwx(right);
			ACL_container[file_name].others = permissions;
			break;
		}
	}
	else if (parameter == 'x') {
		switch (mark) {
		case 'u':
			name = command.substr(2, command.size() - 2);
			if (user_exists(name))
				if (user_exists_in_ACL(name, file_name))
					delete_user_from_ACL(name, file_name);
			break;
		case 'g':
			name = command.substr(2, command.size() - 2);
			if (group_exists(name))
				if (group_exists_in_ACL(name, file_name))
					delete_group_from_ACL(name, file_name);
			break;
		}
	}
}

void Permissions::rename_ACL(std::string old_file_name, std::string new_file_name) {
	std::pair<std::string, ACL> pair;
	pair.second = ACL_container[old_file_name];
	pair.first = new_file_name;
	ACL_container.erase(old_file_name);
	ACL_container.insert(pair);
}

void Permissions::deleteACL(std::string file_name) {
	if (ACL_container.find(file_name) != ACL_container.end()) {
		std::map<std::string, ACL>::iterator it;
		it = ACL_container.find(file_name);
		ACL_container.erase(it);
	}
	else std::cout << "This file doesn't exist\n\n";

}

//void Permissions::renameACL(std::string file_old_name, std::string file_new_name) {
//	if (ACL_container.find(file_old_name) != ACL_container.end()) {
//		std::map<std::string, ACL>::iterator it;
//		it = ACL_container.find(file_old_name);
//		//ACL_container[file_new_name]
//		//TU PODSTAW NOWA NAZWE
//		std::cout << "PODMIENIAM NAZWE\n";
//	}
//	else std::cout << "This file doesn't exist\n\n";
//
//}

void Permissions::display_all_ACLs()
{
	for (auto z : ACL_container)
	{
		std::cout << z.first << "\n";
	}
}

void Permissions::delete_all_ACLs()
{
	ACL_container.clear();
}

bool Permissions::read_permission(std::string file_name) {
	bool others1 = false, others2 = false, others3 = false;
	if (ACL_container.find(file_name) != ACL_container.end()) {
		if (log_in_user.name == ACL_container[file_name].owner)
			return true;

		if (mask_defined) {
			for (auto x : ACL_container[file_name].users) {
				if (x.name == log_in_user.name) {
					if (x.effective_permissions[0] == 'r') {
						return true;
					}
				}
				else
					others1 = true;
			}
			if (log_in_user.group == ACL_container[file_name].group) {
				if (ACL_container[file_name].group_owner_effective_permissions[0] == 'r')
					return true;
				else
					return false;
			}
			else others2 = true;

			for (auto x : ACL_container[file_name].groups) {
				if (x.name == log_in_user.group) {
					if (x.effective_permissions[0] == 'r')
						return true;
					else
						return false;
				}
				else others3 = true;
			}

			if (others1 == true && others2 == true && others3 == true) {
				if (ACL_container[file_name].others[0] == 'r')
					return true;
				else
					return false;
			}
		}
		else {
			for (auto x : ACL_container[file_name].users) {
				if (x.name == log_in_user.name) {
					if (x.permissions[0] == 'r') {
						return true;
					}
				}
				else
					others1 = true;
			}
			if (log_in_user.group == ACL_container[file_name].group) {
				if (ACL_container[file_name].group_owner_permissions[0] == 'r')
					return true;
				else
					return false;
			}
			else others2 = true;

			for (auto x : ACL_container[file_name].groups) {
				if (x.name == log_in_user.group) {
					if (x.permissions[0] == 'r')
						return true;
					else
						return false;
				}
				else others3 = true;
			}

			if (others1 == true && others2 == true && others3 == true) {
				if (ACL_container[file_name].others[0] == 'r')
					return true;
				else
					return false;
			}
		}
	}
}

bool Permissions::write_permission(std::string file_name) {
	bool others1 = false, others2 = false, others3 = false;
	if (ACL_container.find(file_name) != ACL_container.end()) {
		if (log_in_user.name == ACL_container[file_name].owner)
			return true;

		if (mask_defined) {
			for (auto x : ACL_container[file_name].users) {
				if (x.name == log_in_user.name) {
					if (x.effective_permissions[1] == 'w') {
						return true;
					}
				}
				else
					others1 = true;
			}
			if (log_in_user.group == ACL_container[file_name].group) {
				if (ACL_container[file_name].group_owner_effective_permissions[1] == 'w')
					return true;
				else
					return false;
			}
			else others2 = true;

			for (auto x : ACL_container[file_name].groups) {
				if (x.name == log_in_user.group) {
					if (x.effective_permissions[1] == 'w')
						return true;
					else
						return false;
				}
				else others3 = true;
			}

			if (others1 == true && others2 == true && others3 == true) {
				if (ACL_container[file_name].others[1] == 'w')
					return true;
				else
					return false;
			}
		}
		else {
			for (auto x : ACL_container[file_name].users) {
				if (x.name == log_in_user.name) {
					if (x.permissions[1] == 'w') {
						return true;
					}
				}
				else
					others1 = true;
			}
			if (log_in_user.group == ACL_container[file_name].group) {
				if (ACL_container[file_name].group_owner_permissions[1] == 'w')
					return true;
				else
					return false;
			}
			else others2 = true;

			for (auto x : ACL_container[file_name].groups) {
				if (x.name == log_in_user.group) {
					if (x.permissions[1] == 'w')
						return true;
					else
						return false;
				}
				else others3 = true;
			}

			if (others1 == true && others2 == true && others3 == true) {
				if (ACL_container[file_name].others[1] == 'w')
					return true;
				else
					return false;
			}
		}
	}
}

bool Permissions::exec_permission(std::string file_name) {
	bool others1 = false, others2 = false, others3 = false;
	if (ACL_container.find(file_name) != ACL_container.end()) {
		if (log_in_user.name == ACL_container[file_name].owner)
			return true;

		if (mask_defined) {
			for (auto x : ACL_container[file_name].users) {
				if (x.name == log_in_user.name) {
					if (x.effective_permissions[2] == 'x') {
						return true;
					}
				}
				else
					others1 = true;
			}
			if (log_in_user.group == ACL_container[file_name].group) {
				if (ACL_container[file_name].group_owner_effective_permissions[2] == 'x')
					return true;
				else
					return false;
			}
			else others2 = true;

			for (auto x : ACL_container[file_name].groups) {
				if (x.name == log_in_user.group) {
					if (x.effective_permissions[2] == 'x')
						return true;
					else
						return false;
				}
				else others3 = true;
			}

			if (others1 == true && others2 == true && others3 == true) {
				if (ACL_container[file_name].others[2] == 'x')
					return true;
				else
					return false;
			}
		}
		else {
			for (auto x : ACL_container[file_name].users) {
				if (x.name == log_in_user.name) {
					if (x.permissions[2] == 'x') {
						return true;
					}
				}
				else
					others1 = true;
			}
			if (log_in_user.group == ACL_container[file_name].group) {
				if (ACL_container[file_name].group_owner_permissions[2] == 'x')
					return true;
				else
					return false;
			}
			else others2 = true;

			for (auto x : ACL_container[file_name].groups) {
				if (x.name == log_in_user.group) {
					if (x.permissions[2] == 'x')
						return true;
					else
						return false;
				}
				else others3 = true;
			}

			if (others1 == true && others2 == true && others3 == true) {
				if (ACL_container[file_name].others[2] == 'x')
					return true;
				else
					return false;
			}
		}
	}
}