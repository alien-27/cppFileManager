#include <iostream>
#include <fstream>
#include <vector>

#include "AudioFile.h"

int AudioFile::getLength() {
	if (getExtension() == ".wav") {
		return 1;
	}
	return 7000000;
}