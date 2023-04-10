/*
 * FileIO.h
 *
 *  Created on: Oct 25, 2021
 *      Author: potts
 */

#ifndef FILEIO_H_
#define FILEIO_H_
#include <string>
#include <fstream>

class FileIO {
private:
	std::string filename;
	std::fstream datastream;
	void close();
public:
	FileIO(std::string &filename);
	/**
	 * Empties the file
	 */
	void clear();
	/**
	 * Append to whole file
	 * @param data to write to file
	 * @return Success or Fail
	 */
	bool write(std::string &data);
	/**
	 * Read the whole file
	 * @param data read from file
	 * @return Success or Fail
	 */
	bool read(std::string &data);
	virtual ~FileIO();
};

#endif /* FILEIO_H_ */
