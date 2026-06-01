#include <System/FileLib.hpp>

std::vector<std::filesystem::directory_entry> FilesList(std::string path) {

	std::vector<std::filesystem::directory_entry> result;

	for (const auto& entry :
		std::filesystem::directory_iterator(
			std::filesystem::current_path() / path,
			std::filesystem::directory_options::skip_permission_denied
		)) {
		if (entry.is_regular_file()) result.push_back(entry);
	}

	return result;
}