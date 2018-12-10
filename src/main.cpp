#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
namespace PhysLab
{
  enum PrintType
  {
    NOT_OutputConsole = 0,
    OutputConsole = 1
  };
  class Reader
  {
    std::fstream fstr;
    int Counter = {0};
  public:
    Reader(std::string Filename)
    {
      fstr.open(Filename.c_str(),std::ios::in|std::ios::binary);
    }
    Reader()
    {
    }
  private:
    void DetectChangingRow()
    {
      char chr;
      fstr.read(&chr,sizeof(char));
      std::string str(&chr);
      while(str.compare(std::string("\n")))
      {
        fstr.read(&chr,sizeof(char));
        str = std::string(&chr);
      }
   
    }
    template<typename DataType>
    void PrintData(DataType data)
    {
       std::cout << "Number : " << std::setw(5) << Counter++ <<" : " <<data << std::endl;
    }
 
  public:
    void ReadHeader()
    { 
      for(int i = 0 ;i < 5; i++)
      {
        DetectChangingRow();
      }
    }
    template<typename DataType>
    void ReadData(DataType& GetData,PrintType type= PrintType::NOT_OutputConsole)
    {
      std::vector<char> vecChar(sizeof(GetData)); 
      fstr.read(vecChar.data(),vecChar.size());
      GetData = *((DataType*)(vecChar.data()));
      switch(type)
      {
        case PrintType::OutputConsole:
          PrintData(GetData); 
          break;
        default:
          break;
      }
    }
  
  };
  struct DataRow
  {
     double A;
     char   B;
     friend std::ostream& operator <<(std::ostream& os,const DataRow& data)
     {
       return os << data.A;
     }
  }__attribute__ ((__packed__));
  
  class DataConverter
  {
   DataRow OneLineData;
   Reader Rdr;
   std::fstream ConvertedFile;
  public:
    DataConverter(const char* ReadFile,const char* WriteFile)
    {
       std::string str(ReadFile);
       Rdr = Reader(str);
       Rdr.ReadHeader();
       ConvertedFile = std::fstream(WriteFile,std::ios::out);
    }
    void Convert()
    { 
      Rdr.ReadData(OneLineData);
      ConvertedFile <<  OneLineData << std::endl;
    }
    
  };


}


int main()
{
  PhysLab::Reader Rdr("FileTest.bny");
  
  Rdr.ReadHeader();
  
  char a,tab; 
  Rdr.ReadData(  a,PhysLab::PrintType::OutputConsole);
  Rdr.ReadData(tab,PhysLab::PrintType::OutputConsole);
  return 0;

}
