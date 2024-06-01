#include "file_handler.hpp"


// Base class FileReader

FileReader::FileReader() : pathsVec(){};

FileReader::FileReader(const std::vector<std::string>& pathsVec): pathsVec(pathsVec) {};

FileReader::~FileReader() {};
