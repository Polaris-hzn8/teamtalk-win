
#ifndef TRANSFERFILE_4DABC92A_C413_4E6C_9C7C_5B43437B7076_H__
#define TRANSFERFILE_4DABC92A_C413_4E6C_9C7C_5B43437B7076_H__

#include <global_define.h>

enum Position {
	Beginning,
	Current,
	End
};

class TransferFile final
{
public:
	TransferFile(const CString &path, BOOL bsave);
    ~TransferFile();

	BOOL readBlock(UInt32 offset, UInt32 size, OUT std::string& data);
	BOOL writeBlock(UInt32 offset,UInt32 size,void* data);
	UInt32 length();
private:
	UInt32 tell() const;
	void seek(long offset, Position p = Beginning);

private:
	class FilePrivate;
	FilePrivate*				m_pfileObject;
};

#endif// TRANSFERFILE_4DABC92A_C413_4E6C_9C7C_5B43437B7076_H__
