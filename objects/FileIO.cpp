/*
 * FileIO.cpp
 *
 *  Created on: Oct 25, 2021
 *      Author: potts
 */

#include "../includes/FileIO.h"

FileIO::FileIO(std::string &filename):filename(filename) {
	datastream.open(filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	if (!datastream.is_open()) {
		datastream.open(filename.c_str(), std::fstream::trunc);
	}
}

void FileIO::clear() {
	close();
//	datastream.open(filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	datastream.open(filename.c_str(), std::fstream::out | std::fstream::trunc);
}

void FileIO::close() {
	if(datastream.is_open()) {
			datastream.close();
		}
}

/**
 * Append to whole file
 * @param data to write to file
 * @return Success or Fail
 */
bool FileIO::write(std::string &data) {
	if(!datastream.is_open()) {
		return false;
	}
	datastream<<data<<std::endl;
	return true;
}

/**
 * Read the whole file
 * @param data read from file
 * @return Success or Fail
 */
bool FileIO::read(std::string &data) {
	if(!datastream.is_open()) {
		return false;
	}
	// Move pointer back to beginning
	datastream.seekg(std::ios::beg);
	std::string line;
	while(!datastream.eof()) {
		getline(datastream, line);
		data += line;
	}
	return true;
}

FileIO::~FileIO() {
	close();
}

