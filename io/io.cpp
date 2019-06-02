#include "io.h"
#include "stdio.h"
#include "stdlib.h"

const int LINE_LEN = 128;

int readData(const char* filepath, int* data, int maxRecords) {
	FILE* file = fopen(filepath, "r");
	if (file == NULL) { return 0; }

	char line[LINE_LEN];
	int numRecords = 0;

	while (fgets(line, LINE_LEN, file) != NULL &&
		numRecords < maxRecords) {
		*data = atoi(line);
		data++;
		numRecords++;
	}

	fclose(file);
	return numRecords;
}

int writeData(const char* filepath, int* data, int len) {
	FILE* file = fopen(filepath, "w");
	if (file == NULL) { return 1; }

	for (int i = 0; i < len; i++) {
		if (fprintf(file, "%i\n", *data) < 0) { return 1; };
		data++;
	}

	fclose(file);
	return 0;
}