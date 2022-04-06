#include <filesystem>
#include <fstream>
#include <iostream>

#include <UEFITool/common/basetypes.h>
#include <UEFITool/common/ffsparser.h>
#include <UEFITool/common/ffsops.h>
#include <UEFITool/common/ffsutils.h>

int main()
{
    std::vector<char> firmware;
    {
        auto path = std::filesystem::current_path() / "OVMF.fd";
        std::ifstream file(path, std::ios::binary);
        const auto size = std::filesystem::file_size(path);
        firmware.resize(size);
        file.read(firmware.data(), static_cast<std::streamsize>(size));
    }

    TreeModel model;
    FfsParser parser(&model);
    if (auto result = parser.parse(firmware))
    {
        std::cout << "FfsParser::parse failed" << std::endl;

        return result;
    }

    auto root = model.index(0, 0);
    std::set<std::pair<UModelIndex, UModelIndex>> files;
    if (auto status = FfsUtils::findFileRecursive(&model, root, "7FCBA2D6186A2F4EB43B9920A733700A", SEARCH_MODE_HEADER, files) || files.empty())
    {
        std::cout << "findFileRecursive failed" << std::endl;
        return status;
    }

    if (files.empty())
    {
        return 1;
    }

    FfsOperations operations(&model);
    // operations.rebuild();
}