#include "fut/dal/packagefilerepository.h"

using namespace fut;
using namespace fut::dal;

PackageFileRepository::PackageFileRepository(infra::RandomNumberGenerator& randomNumberGenerator)
  : randomNumberGenerator(&randomNumberGenerator)
  , packageCount(0)
{
}

void fut::dal::PackageFileRepository::ReadPackagesFromCsv(const char* filePath)
{
    infra::CsvParser parser;
    parser.OpenFile(filePath);

    infra::CsvRow row;

    while (parser.ParseNextRow(row) != infra::ParsingStatus::EndOfFile)
    {
        row.ParseNextColumn(packages[packageCount].contentsDescription,
                            sizeof(packages[packageCount].contentsDescription));
        row.ParseNextColumn(packages[packageCount++].destinationDescription,
                            sizeof(packages[packageCount++].destinationDescription));
    }
}

domain::models::Package PackageFileRepository::GetRandomPackage() const
{
    return packages[randomNumberGenerator->GenerateBetweenInclusive(0, packageCount - 1)];
}
