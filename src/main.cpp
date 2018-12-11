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
    Reader(std::string FileName)
    {
      SetPath(FileName);
    }
    Reader()
    {
    }
  private:
    void DetectChangingRow()
    {
      char chr[1];
      fstr.read(chr,sizeof(chr));
      std::string str(chr);
      while(str.compare(std::string("\n"))==0)
      {
        fstr.read(chr,sizeof(chr));
        str = std::string(chr);
	std::cout << str << std::endl;
      }
   
    }
    template<typename DataType>
    void PrintData(DataType data)
    {
      std::cout <<
	// "Number : " <<
	std::setw(5) << Counter++ <<"\t" ;
      std::cout//  << 
	// std::hex<<
	//std::setw(4)
	<<	(int)data << std::endl;
    }
 
  public:
    void SetPath(std::string path)
    {
      fstr.open(path.c_str(),std::ios::in|std::ios::binary);
    }
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
     char A;
     friend std::ostream& operator <<(std::ostream& os,const DataRow& data)
     {
       return os << (int)data.A;
     }
  }__attribute__ ((__packed__));
  /*
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
  */  

}


int main()
{
  PhysLab::Reader Rdr;
  for(int folderloop = 1;folderloop < 4;folderloop++)
  {
   for(int fileloop = 1;fileloop < 41;fileloop++)
    {
     std::string FileName("CHAOS");
     FileName += std::to_string(folderloop);
     std::string FilePath;
     FilePath += FileName;
     FilePath += std::string("/bny/");
     FilePath += FileName +std::string("_")+ std::to_string(fileloop);
     FilePath += std::string(".bny");
  
     Rdr.SetPath(FilePath.c_str());
     char d1;
     for(int i =0 ; i< 10000000;i++)
     {
      Rdr.ReadData(d1,PhysLab::PrintType::OutputConsole);
     }
    }
  }
  return 0;

}
