#include "test_utils.h"

void testGetContentType(){
    assert(Utils::getContentType("txt") == "text/plain");
    assert(Utils::getContentType("html") == "text/html");
    assert(Utils::getContentType("css") == "text/css");
    assert(Utils::getContentType("js") == "application/javascript");
    assert(Utils::getContentType("pdf") == "text/plain"); // Test with an unrecognized extension
}

void testGetDirectory(){
     // Test cases
    assert(Utils::getDirectory("/home/user/file.txt") == "/home/user/");
    assert(Utils::getDirectory("/root/folder1/folder2/") == "/root/folder1/folder2/");
    assert(Utils::getDirectory("documents/report.docx") == "documents/");
    assert(Utils::getDirectory("file.txt") == ""); // No directory path

}

void testGetStaticFile(){
    assert(Utils::getStaticFile("/home/user/file.txt") == "file.txt");
    assert(Utils::getStaticFile("/root/folder1/folder2/") == ""); // No file name
    assert(Utils::getStaticFile("documents/report.docx") == "report.docx");
    assert(Utils::getStaticFile("file.txt") == "file.txt");
}

void testGetFileExtension(){
    assert(Utils::getFileExtension("file.txt") == "txt");
    assert(Utils::getFileExtension("document.docx") == "docx");
    assert(Utils::getFileExtension("image.jpg") == "jpg");
    assert(Utils::getFileExtension("script.js") == "js");
    assert(Utils::getFileExtension("file_without_extension") == "");

}

void runUtilsTests(){
    testGetContentType();
    testGetDirectory();
    testGetStaticFile();
    testGetFileExtension();
}