/*
 * Copyright (C) 2004-2006 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __ZLZIP_H__
#define __ZLZIP_H__

#include <abstract/shared_ptr.h>

#include "../ZLInputStream.h"
#include "../ZLDir.h"

class ZLZDecompressor;

class ZLZipInputStream : public ZLInputStream {

private:
	ZLZipInputStream(shared_ptr<ZLInputStream> &base, const std::string &name) FS_SECTION;

public:
	~ZLZipInputStream() FS_SECTION;
	bool open() FS_SECTION;
	size_t read(char *buffer, size_t maxSize) FS_SECTION;
	void close() FS_SECTION;

	void seek(int offset) FS_SECTION;
	size_t offset() const FS_SECTION;
	size_t sizeOfOpened() FS_SECTION;

private:
	shared_ptr<ZLInputStream> myBaseStream;
	std::string myCompressedFileName;
	bool myIsDeflated;

	size_t myUncompressedSize;
	size_t myAvailableSize;
	size_t myOffset;

	shared_ptr<ZLZDecompressor> myDecompressor;

friend class ZLFile;
};

class ZLGzipInputStream : public ZLInputStream {

private:
	ZLGzipInputStream(shared_ptr<ZLInputStream> stream) FS_SECTION;

public:
	~ZLGzipInputStream() FS_SECTION;
	bool open() FS_SECTION;
	size_t read(char *buffer, size_t maxSize) FS_SECTION;
	void close() FS_SECTION;

	void seek(int offset) FS_SECTION;
	size_t offset() const FS_SECTION;
	size_t sizeOfOpened() FS_SECTION;

private:
	shared_ptr<ZLInputStream> myFileStream;
	size_t myFileSize;

	size_t myOffset;

	shared_ptr<ZLZDecompressor> myDecompressor;

friend class ZLFile;
};

class ZLZipDir : public ZLDir {

private:
	ZLZipDir(const std::string &name) FS_SECTION;

public:
	~ZLZipDir() FS_SECTION;
	void collectSubDirs(std::vector<std::string>&, bool) FS_SECTION;
	void collectFiles(std::vector<std::string> &names, bool includeSymlinks) FS_SECTION;

protected:
	std::string delimiter() const FS_SECTION;

friend class ZLFile;
};

inline ZLZipDir::ZLZipDir(const std::string &name) : ZLDir(name) {}
inline ZLZipDir::~ZLZipDir() {}
inline void ZLZipDir::collectSubDirs(std::vector<std::string>&, bool) {}

#endif /* __ZLZIP_H__ */
