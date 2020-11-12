# CDR-Loader
This is the NetBeans C++ Project directory of cdr_loading binary

In production setup two instances are created. Only difference being the source directory of CDR files (ee: /CDR/HU/)
For Huawel - cdr_loader_hu
For ZTE - cdr_loader_zte

Source directory and CDR prefix should be modified before compiling which can be fount at readFilr.cpp

string DIRECTORY = ""; //Directory
string PREFIX = ""; // Prefix