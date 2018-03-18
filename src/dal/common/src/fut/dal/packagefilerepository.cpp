#include "fut/dal/packagefilerepository.h"

using namespace fut;
using namespace fut::dal;

PackageFileRepository::PackageFileRepository(const char* filePath)
  : packageCount(0)
{
    infra::CsvParser parser;
    parser.OpenFile(filePath);

    infra::CsvRow row;

    while (parser.ParseNextRow(row) != infra::ParsingStatus::EndOfFile)
    {
        row.ParseNextColumn(packages[packageCount].contentsDescription, 64);
        row.ParseNextColumn(packages[packageCount++].destinationDescription, 64);
    }
}

domain::models::Package PackageFileRepository::GetRandomPackage() const
{
    return domain::models::Package();
}
