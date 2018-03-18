#include "fut/infra/csvparser.h"

using namespace fut::infra;

CsvParser::CsvParser()
  : filePath(nullptr)
  , fileOpened(false)
{
}

void CsvParser::OpenFile(const char* filePath)
{
    if (filePath == nullptr)
    {
        throw std::invalid_argument("Argument 'filePath' may not be null.");
    }

    fileStream = std::ifstream(filePath);

    // Check if the file really opened.
    if (!fileStream.is_open())
    {
        throw std::exception("Unable to open file.");
    }

    this->filePath = filePath;
    fileOpened = true;
}

ParsingStatus CsvParser::ParseNextRow(CsvRow& rowBuffer)
{
    if (!fileOpened)
    {
        throw std::exception("No file opened.");
    }

    // If the line starts with a '#' it's a comment.
    while (fileStream.peek() == '#')
    {
        fileStream.ignore(std::numeric_limits<int>::max(), '\n');
    }

    // Read the line into a row.
    char buffer[1024];
    fileStream.getline(buffer, sizeof(buffer), '\n');

    if (fileStream.eof())
    {
        return ParsingStatus::EndOfFile;
    }

    rowBuffer = CsvRow(buffer);

    return ParsingStatus::Good;
}

void CsvParser::IgnoreNextRow()
{
    if (!fileOpened)
    {
        throw std::exception("No file opened.");
    }

    // If the line starts with a '#' it's a comment.
    while (fileStream.peek() == '#')
    {
        fileStream.ignore(std::numeric_limits<int>::max(), '\n');
    }

    fileStream.ignore(std::numeric_limits<int>::max(), '\n');
}
