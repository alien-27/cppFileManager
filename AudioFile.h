#pragma once
#include "File.h"

class AudioFile : public File {
private:
	int length;
public:
	int getLength();
};

