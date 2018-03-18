#ifndef FUTURAMA_FUT_INFRA_CSVPARSER_HPP_INCLUDED
#define FUTURAMA_FUT_INFRA_CSVPARSER_HPP_INCLUDED

#include <exception>
#include <fstream>
#include <limits>
#include <stdexcept>

namespace fut::infra
{
enum class ParsingStatus
{
    Good,
    EndOfFile
};

class CsvRow
{
  private:
    unsigned int parsedColumnCount;
    unsigned int columnCount;
    char columns[64][64];

  public:
    CsvRow()
      : parsedColumnCount(0)
      , columnCount(0)
    {
    }

    CsvRow(char* row)
      : parsedColumnCount(0)
      , columnCount(0)
    {
        if (strcmp(row, "") == 0)
        {
            return;
        }

        for (char* loc = strtok(row, ";\n"); loc != nullptr; loc = strtok(nullptr, ";\n"))
        {
            strcpy(columns[columnCount++], loc);
        }
    }

    ParsingStatus ParseNextColumn(char* columnBuffer, int columnBufferSize)
    {
        if (columnBuffer == nullptr)
        {
            throw std::invalid_argument("Argument 'columnBuffer' may not be null.");
        }

        if (parsedColumnCount == columnCount)
        {
            return ParsingStatus::EndOfFile;
        }

        strncpy(columnBuffer, columns[parsedColumnCount++], columnBufferSize);

        return ParsingStatus::Good;
    }

    void IgnoreNextColumn()
    {
        parsedColumnCount += 1;
    }
};

class CsvParser
{
  private:
    const char* filePath;
    bool fileOpened;

    std::ifstream fileStream;

  public:
    CsvParser();

    void OpenFile(const char* filePath);
    ParsingStatus ParseNextRow(CsvRow& rowBuffer);
    void IgnoreNextRow();

}; // class CsvParser
} // namespace fut::infra

#endif // #ifndef FUTURAMA_FUT_INFRA_CSVPARSER_HPP_INCLUDED
