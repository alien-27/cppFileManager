#pragma once

#include "File.h"

#include<vector>

class Sort
{
	private:
		std::vector<File> fileList;

		void sortByName(std::string order);
		void sortByDate(std::string order);
		void sortBySize(std::string order);
		void sortByExtension(std::string order);
	public:
		Sort(std::vector<File> fv);
		std::vector<File> sortList(std::string value, std::string ord);
};

