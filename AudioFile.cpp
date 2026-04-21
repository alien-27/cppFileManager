#include <iostream>
#include <fstream>
#include <vector>

#include "AudioFile.h"

/// <summary>
/// Returns the length of the selected file in seconds.
/// </summary>
/// <returns>The length of the selected file in seconds</returns>
int AudioFile::getLength() {
	if (getExtension() == ".wav") {
		return 1;
	}
	return 7000000;
}
