#include <Python.h>

#include <cstdlib>

#include "util/format.hpp"

void usage() {
    eprintln("Usage: Glacier <scene_python_script_file_path>");
}

int main(int argc, char** argv) {
    if (argc != 2) {
        usage();
        return EXIT_FAILURE;
    }

    const char* path = argv[1];

    FILE* file = fopen(path, "r");

    if (file != NULL) {
        Py_Initialize();

        int result = PyRun_SimpleFile(file, path);
        fclose(file);

        if (result != 0) {
            eprintln("Error: Invalid Python script");
            return EXIT_FAILURE;
        }

        Py_Finalize();
    } else {
        eprintln("Error: Path does not point to a valid file.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
