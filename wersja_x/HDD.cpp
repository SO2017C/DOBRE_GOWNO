#include "HDD.h"

//DICTIONARY
//DISK SIZE - disk's capacity. Number of bytes on disk. One disk = n*block, n - number of blocks, one block have 32 bytes
//BLOCK - block of 32 bytes. It is one sector on disk.
//BLOCK NUMBER - number of blocks on disk
//FIRST BLOCK INDEX - index of first empty block
//DATA CONTAINER - part of disk, where data are keeping
//BITS VECTOR - first block on disk (part of disk), where info about free blocks are keeping
//FAT TABLE - separate table, where info about files are keeping (like catalog) In oryginal disk FAT TABLE is integrated with, but this disk is to small to do it

//BASIC FUNCTIONS
bool HDD::check_file_exist(std::string file_to_save_name) {
	for (int i = 0; i < directory.size(); i++) {//iterting through the FAT TABLE
		if (directory[i].file_name == file_to_save_name) {//comparisoning file's name
			return true;//when file of this name exists
		}//end of if
	}//end of for
	return false;//when file of this name doesn't exist
}// end of check_file_exist

bool HDD::check_space(int file_to_save_size) {
	int required_blocks = ceil(file_to_save_size / 32.0) + ceil((ceil(file_to_save_size / 32.0)) / 16.0);//calculating file's real size (with block for indexes)
	int free_blocks = 0;

	for (int j = 0; j < block_number; j++) {//calculating free space on disk
		if (data_container[j] == '1') { //checking if in BITS VECTOR in position 'j' is free space (if is, program finds one free block on disk)
			free_blocks++;//when true we increace free block cunter 
		}//end of if
	}//end of for

	if (free_blocks >= required_blocks) {//checking if is space for file
		return true;//when there is free space
	}//end of if
	return false;//when there isn't free space
}// end of check_space

int HDD::check_first_empty_block() {
	for (int i = 0; i < block_number; i++) { //checking first empty block for data's index in bit's vector
		if (data_container[i] == '1') { //when sector is empty and we can save index in this position the value of cell is set to '1'
			data_container[i] = '0'; //setting value to '0'
			return i; //this block is our block for index(we find first free cell)
		}//end of if
	}//end of for
	return -1;//returning unreal value when there isn't any free space
}

void HDD::uniforming_format_of_data_index(int index_index_block, int index_data_block, int counter_tmp) {
	if (index_data_block < 10) {
		data_container[(index_index_block*block_size) + counter_tmp] = '0';
		data_container[((index_index_block*block_size) + 1) + counter_tmp] = index_data_block + '0';
	}//end of if
	else {
		data_container[(index_index_block*block_size) + counter_tmp] = (index_data_block / 10) + '0';
		data_container[((index_index_block*block_size) + 1) + counter_tmp] = (index_data_block % 10) + '0';
	}//end of else
}

bool HDD::check_file_status(std::string file_name) {
	for (int i = 0; i < directory.size(); i++) {
		if (directory[i].file_name == file_name) {
			if (directory[i].flag == 1) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
}

int HDD::check_file_index(std::string file_name) {
	for (int i = 0; i < directory.size(); i++) {
		if (directory[i].file_name == file_name) {
			return i;
		}
	}
}
//EXTENSIONS
void HDD::detailed_disk_view() {

	std::cout << "Detailed disk view:\n";
	for (int i = 0; i < data_container.size(); i++) {
		std::cout << "[" << data_container[i] << "]";
		if ((i + 1) % block_size == 0) {
			std::cout << "\n";
		}//end of if
	}//end of for
}

void HDD::bit_vector_view() {
	std::cout << "Bit vector view:\n";
	for (int i = 0; i < block_number; i++) {
		std::cout << "[" << data_container[i] << "]";
	}
	std::cout << std::endl;
}

void HDD::directory_view() {
	std::cout << "Directory view:\n";
	if (directory.size() == 0) {
		std::cout << "DIRECTORY IS EMPTY!\n";
	}//end of if
	else {
		for (int i = 0; i < directory.size(); i++) {
			std::cout << directory[i].file_name << "\t" << directory[i].file_size << "\t" << directory[i].first_block_index << "\n";
		}//end of for
	}
}

void HDD::percentage_disk_view() {
	std::cout << "Percentage occupied space on disk:\n";
	int some = 0;
	int tmp = 0;
	std::cout << "[";
	for (int j = 0; j < disc_size; j++) {

		if (data_container[j] != NULL) {
			some++;
		}
	}
	for (int i = 0; i < (some * 100 / disc_size) / 2; i++) {
		std::cout << "|";
	}
	for (int i = 0; i < 50 - ((some * 100 / disc_size) / 2); i++) {
		std::cout << " ";
	}
	std::cout << "] " << some * 100 / disc_size << "%\n";
}

void HDD::percentage_sectors_view() {
	std::cout << "Percentage occupied space in sectors:\n";
	int some = 0;
	int tmp = 0;
	for (int j = 0; j < block_number; j++) {
		some = 0;

		for (int i = block_size * j; i < block_size * (j + 1); i++) {
			if (data_container[i] != NULL) {
				some++;
			}
			else {
			}
		}
		std::cout << "[";
		for (int k = 0; k < (some * 100 / block_size) / 2; k++) {
			std::cout << "|";
		}
		for (int k = 0; k < 50 - ((some * 100 / block_size) / 2); k++) {
			std::cout << " ";
		}
		std::cout << "] " << some * 100 / block_size << "%\n";
	}
}

HDD::HDD() {
	std::fstream HDD_file;
	HDD_file.open("HDD_file.txt");
	if (HDD_file.is_open() == true) {
		//std::cout << "Z PLIKU\n";
		std::string actual_line;
		getline(HDD_file, actual_line);
		for (int i = 0; i < 1024; i++) { // loop which iterate through the bits
			data_container[i] = actual_line[i]; //filling conteiner with data
		}//end of for

		FAT_struct actual_directory;
		while (!HDD_file.eof()) {
			//getline(HDD_file, actual_line);
			//actual_directory.file_name = actual_line;
			HDD_file >> actual_directory.file_name;
			HDD_file >> actual_directory.file_size;
			HDD_file >> actual_directory.first_block_index;
			//NOWE
			actual_directory.user = "";
			actual_directory.flag = 1;
			directory.push_back(actual_directory);
		}
		directory.erase(directory.begin() + directory.size() - 1, directory.end());
	}
	else {
		for (int i = 0; i < block_number; i++) { // loop which iterate through the conteiner
			data_container[i] = '1'; //filling conteiner with ones
		}//end of for
		data_container[0] = '0'; //first block is always (there is a bit vector here)
	}
	HDD_file.close();
}

HDD::~HDD() {
}

void HDD::create_file(std::string file_to_save_name, int file_to_save_size) {
	if (check_space(file_to_save_size) == true) {//checking free space
		if (check_file_exist(file_to_save_name) == false) { //checking free name
			int first_empty_block = -1; //setting unreal value of index
			int residual_size = file_to_save_size; //setting file size
			int index_index_block = -1; //variable that holds index to file's index block
			int index_data_block = -1; //variable that holds index to file's data block
			int counter_tmp = 0; //variable that holds info about jump between position in sector (block of indexes)

								 //SEARCHING FIRST FREE BLOCK FOR DATA'S BLOCK INDEX
			index_index_block = check_first_empty_block();

			//SAVING FILE TO FAT TABLE
			FAT_struct file_to_save = { file_to_save_name, file_to_save_size, index_index_block }; // generating data from parameters to save in FAT TABLE
			file_to_save.flag = 1;
			directory.push_back(file_to_save); // saving new file to FAT table

											   //SAVING DATA
			while (residual_size > 0) { //saving data when some bits left
				if (counter_tmp >= block_size - 2 && residual_size>32) {
					int last_index_index_block = index_index_block; //temporary variable
					index_index_block = check_first_empty_block(); //searching next free block for index block

																   //UNIFORMING FORMAT OF DATA'S INDEX
					uniforming_format_of_data_index(last_index_index_block, index_index_block, counter_tmp);

					//CHANGING VARIABLES
					counter_tmp = 0; //reset counter
					index_data_block = check_first_empty_block(); //searching next free block for data packs
				}
				else {

					//SEARCHING FIRST FREE BLOCK FOR DATA
					index_data_block = check_first_empty_block();
				}

				//UNIFORMING FORMAT OF DATA'S INDEX
				uniforming_format_of_data_index(index_index_block, index_data_block, counter_tmp);

				//FILLING FREE BLOCK WITH DATA
				for (int i = 0; i < block_size; i++) { //filling sector
					if ((file_to_save_size - residual_size) >= 0 && (file_to_save_size - residual_size) != file_to_save_size) { //checking range
																																//data_container[(block_size * index_data_block) + i] = 'a';// file_to_save_text[file_to_save_text.size() - residual_size];//filling bits in block
						residual_size--; // decrease value of data to save size
					}//end of if
					else {
						break;
					}//end of else
				}//end of for

				counter_tmp = counter_tmp + 2; //set new value (jumping to next free cell for data's index)
			}//end of while
			permissions.createACL(file_to_save_name);///NOWE
			std::cout << "File was created!\n"; //displaying information about status
		}// end of if
		else {
			std::cout << "File of the same name exists!\n";//displaying information about status
		}//end of else
	}//end of if
	else {
		std::cout << "No required space on disk! File wasn't created!\n";//displaying information about status
	}//end of else
}//end of create_file

void HDD::rename_file(std::string file_old_name, std::string file_new_name) {
	if (check_file_exist(file_old_name)) {//checking existing of file
		if (permissions.read_permission(file_old_name) == true) {
			if (check_file_status(file_old_name)==1) {
				for (int i = 0; i < directory.size(); i++) {//searching index of file in FAT
					if (directory[i].file_name == file_old_name) {//looging for file's old name
						directory[i].file_name = file_new_name;//changing name
						permissions.renameACL(file_old_name, file_new_name);
						std::cout << "File's name has been changed successfully!\n";//displaying info
						break;//breaking loop and ending operation
					}
				}
			}
			else{
				std::cout << "You have to close file if you want to rename it!\n";
			}
		}
		else {
			std::cout << "User \"" << permissions.return_log_in_user_name().name << "\" does not have permissions to rename that file" << std::endl;
		}
	}
	else {
		std::cout << "File doesn't exist.\n";//displaying info when file doesn't exist
	}
}

void HDD::format_disk() {
	data_container[0] = '0';
	for (int i = 1; i < block_size; i++) {
		data_container[i] = '1';
	}
	for (int i = block_size; i < disc_size; i++) {
		data_container[i] = NULL;
	}

	directory.erase(directory.begin(), directory.end());
	permissions.delete_all_ACLs();
	std::cout << "Disk has been formated successfully!\n";
}

std::string HDD::read_file(std::string file_to_read_name) {
	int actual_index_to_read;
	int index_index_block;
	int residual_size;
	std::string file_content = "";

	/*if (permissions.read_permission(file_to_read_name) == true) {

	}
	else
	{
		std::cout << "User \"" << permissions.return_log_in_user_name().name << "\" does not have permissions to read that file" << std::endl;
	}*/

	if (check_file_exist(file_to_read_name) == true) {
		if (permissions.read_permission(file_to_read_name) == true) {
			if (check_file_status(file_to_read_name)==0) {
				for (int i = 0; i < directory.size(); i++) {
					if (directory[i].file_name == file_to_read_name) {
						index_index_block = directory[i].first_block_index;
						residual_size = directory[i].file_size;
						break;
					}//if

				}//for

				int i = 0;
				while (i < block_size - 1 && residual_size>0) {//REFAKTORYZACJA!

					if (i == (block_size - 2) && residual_size > block_size) {
						actual_index_to_read = ((data_container[(index_index_block * 32) + i] - '0') * 10) + (data_container[(index_index_block * 32) + i + 1] - '0');
						index_index_block = actual_index_to_read;
						i = 0;
					}

					actual_index_to_read = (data_container[index_index_block*block_size + i] - '0') * 10 + (data_container[index_index_block*block_size + i + 1] - '0');
					for (int j = 0; j < block_size; j++) {
						if (residual_size <= 0) {
							break;
						}
						if (data_container[actual_index_to_read*block_size + j] == NULL) {
							residual_size--;
						}
						else {
							file_content = file_content + data_container[actual_index_to_read*block_size + j];
							residual_size--;
						}

					}
					i = i + 2;
				}

				std::cout << "File was read successfully!\n";
				return file_content;
			}
			else {
				std::cout << "You have to open file before reading!\n";
				return "";
			}
		}
		else {
			std::cout << "User \"" << permissions.return_log_in_user_name().name << "\" does not have permissions to read that file" << std::endl;
			return "";
		}
	}//if
	else {
		std::cout << "File of this name doesn't exist!\n";
		return "";
	}//else
}//read_file

void HDD::write_file(std::string file_to_write_name, std::string text_to_write, int indicator_position) {
	int actual_index_to_write;
	int index_index_block;
	int text_size;
	int file_size;
	int actual_indicator_position;
	std::string file_content = "";

	if (check_file_exist(file_to_write_name) == true) {
		if (permissions.read_permission(file_to_write_name) == true) {
			if(check_file_status(file_to_write_name)==0){
				for (int i = 0; i < directory.size(); i++) {
					if (directory[i].file_name == file_to_write_name) {
						index_index_block = directory[i].first_block_index;
						file_size = directory[i].file_size;
						break;
					}//if
				}//for

				if (indicator_position < file_size) {
					text_size = text_to_write.size();
					actual_indicator_position = indicator_position;
					if (text_to_write.size() + indicator_position <= file_size) {

						int i = 0;
						while (i < block_size - 1 && text_size >= 0) {//REFAKTORYZACJA!

							if (i == (block_size - 2) && text_size > block_size) {
								actual_index_to_write = ((data_container[(index_index_block * 32) + i] - '0') * 10) + (data_container[(index_index_block * 32) + i + 1] - '0');
								index_index_block = actual_index_to_write;
								i = 0;
							}

							actual_index_to_write = (data_container[index_index_block*block_size + i] - '0') * 10 + (data_container[index_index_block*block_size + i + 1] - '0');

							for (int j = 0; j < block_size; j++) {

								if (actual_indicator_position > 0) {
									actual_indicator_position--;
								}
								else {
									if (text_size > 0) {//>= jesli pobiera bez \n
														//std::cout<<"WPISUJE: "<< text_to_write[text_to_write.size() - text_size]-48<<"KONIEC\n";
										data_container[actual_index_to_write*block_size + j] = text_to_write[text_to_write.size() - text_size];
										text_size--;
									}

								}

							}
							i = i + 2;
						}

						std::cout << "File was write successfully!\n";
					}
					else {
						std::cout << "Not enough space to write content to file (from indicator position to end of file)\n";
					}
				}
				else {
					std::cout << "Indicator position is out of range!\n";
				}
			}
			else {
				std::cout << "You have to open file before writing!\n";
			}
		}
		else {
			std::cout << "User \"" << permissions.return_log_in_user_name().name << "\" does not have permissions to write that file" << std::endl;
		}
	}//if
	else {
		std::cout << "File of this name doesn't exist!\n";
	}//else
}//write_file

void HDD::delete_file(std::string file_to_delete_name) {
	int actual_index_to_delete;
	int index_index_block;
	int residual_size;

	if (check_file_exist(file_to_delete_name) == true) {
		if (permissions.read_permission(file_to_delete_name) == true) {
			if (check_file_status(file_to_delete_name)==1) {
				for (int i = 0; i < directory.size(); i++) {
					if (directory[i].file_name == file_to_delete_name) {
						index_index_block = directory[i].first_block_index;
						residual_size = directory[i].file_size;
						data_container[index_index_block] = '1';
						std::swap(directory[i], directory[directory.size() - 1]);
						directory.erase(directory.begin() + (directory.size() - 1));
						break;
					}//if

				}//for

				int i = 0;
				while (i < block_size - 1 && residual_size>0) {//REFAKTORYZACJA!

					if (i == (block_size - 2) && residual_size > block_size) {
						actual_index_to_delete = ((data_container[(index_index_block * 32) + i] - '0') * 10) + (data_container[(index_index_block * 32) + i + 1] - '0');
						data_container[actual_index_to_delete] = '1';
						index_index_block = actual_index_to_delete;
						i = 0;
					}

					//std::cout << data_container[index_index_block*block_size + i] << "\n";//TEST
					actual_index_to_delete = (data_container[index_index_block*block_size + i] - '0') * 10 + (data_container[index_index_block*block_size + i + 1] - '0');
					data_container[actual_index_to_delete] = '1';
					residual_size = residual_size - block_size;
					i = i + 2;
				}
				permissions.deleteACL(file_to_delete_name);///NOWE
				std::cout << "File was deleted successfully!\n";
			}
			else {
				std::cout << "You have to close file before deleting!\n";
			}
		}
		else {
			std::cout << "User \"" << permissions.return_log_in_user_name().name << "\" does not have permissions to delete that file" << std::endl;
		}
	}//if
	else {
		std::cout << "File of this name doesn't exist!\n";
	}//else
}//delete_file

void HDD::open_file(std::string file_name) {
	if (check_file_exist(file_name) == true) {
		if (permissions.read_permission(file_name) == true) {
			if (check_file_status(file_name) == 1) {
				directory[check_file_index(file_name)].flag = 0;
				directory[check_file_index(file_name)].user = permissions.return_log_in_user_name().name;
					std::cout << "File has been opened successfull!\n";
			}
			else {
				std::cout << "File is already open!\n";
			}
		}
		else {
			std::cout << "User \"" << permissions.return_log_in_user_name().name << "\" does not have permissions to open that file" << std::endl;
		}
	}
	else {
		std::cout << "File of these name doesn't exist!\n";
	}
}

void HDD::close_file(std::string file_name) {
	if (check_file_exist(file_name) == true) {
		if (permissions.read_permission(file_name) == true) {
			if (check_file_status(file_name) == 0) {
				if (directory[check_file_index(file_name)].user == permissions.return_log_in_user_name().name) {
					directory[check_file_index(file_name)].flag = 1;
					std::cout << "File has been closed successfull!\n";
				}
				else {
					std::cout << "File is already opened by other user!\n";
				}
			}
			else {
				std::cout << "File is already close!\n";
			}
		}
		else {
			std::cout << "User \"" << permissions.return_log_in_user_name().name << "\" does not have permissions to close that file" << std::endl;
		}
	}
	else {
		std::cout << "File of these name doesn't exist!\n";
	}
}

//EXTENSION
void HDD::show_all_info() {
	percentage_disk_view();
	//percentage_sectors_view();
	detailed_disk_view();
	bit_vector_view();
	directory_view();
}//show_all_info

void HDD::save_to_file() {
	std::ofstream HDD_file;
	HDD_file.open("HDD_file.txt", std::ios_base::trunc);
	for (int i = 0; i < 1024; i++) {
		HDD_file << data_container[i];
	}
	HDD_file << std::endl;
	for (int j = 0; j < directory.size(); j++) {
		HDD_file << directory[j].file_name;
		HDD_file << std::endl;
		HDD_file << directory[j].file_size;
		HDD_file << std::endl;
		HDD_file << directory[j].first_block_index;
		HDD_file << std::endl;
	}
	HDD_file.close();
}

