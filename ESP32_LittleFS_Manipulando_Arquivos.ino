#include "Arduino.h"
#include "FS.h"
#include "LittleFS.h"
 
void printDirectory(File dir);
void excluirArquivo(String fileName);
void criaArquivoVazio(String fileName);
void imprimeArquivo(String fileName);
void escreveArquivo(String fileName, String coteudo);
void anexarArquivo(String fileName, String coteudo);
 
void setup()
{
    Serial.begin(115200);
 
    delay(500);
 
    Serial.println(F("Iniciando o FS..."));
    if (LittleFS.begin()){
        Serial.println(F("LittleFS Iniciado com sucesso"));
    }else{
        Serial.println(F("LittleFS Falhou ao iniciar"));
    }
    
}
 
void loop()
{
   unsigned int totalBytes = LittleFS.totalBytes();
   unsigned int usedBytes = LittleFS.usedBytes();

   Serial.println();
   Serial.println("Estado Atual da Memoria do LittleFS:");
   Serial.println();
 
   Serial.print("Espaço disponivel:      ");
   Serial.print(totalBytes);
   Serial.println(" byte");
 
   Serial.print("Espaço usado:            ");
   Serial.print(usedBytes);
   Serial.println(" byte");

   delay(500);
   Serial.println();
   Serial.println("--- Menu --- ");
   Serial.println("Digite 1 - Para Solicitar a impressão do Diretorio do LittleFS");
   Serial.println("Digite 2 - Para Excluir um arquivo especifico");
   Serial.println("Digite 3 - Para Criar um arquivo Vazio especifico");
   Serial.println("Digite 4 - Para Imprimir um arquivo especifico");
   Serial.println("Digite 5 - Para Escrever em um arquivo especifico");
   Serial.println("Digite 6 - Para Anexar a escrita em um arquivo especifico");
   while(Serial.available() == 0) {
   }
   String str = Serial.readString();
   delay(10);
   Serial.println("");
   Serial.print("Input → ");
   Serial.println(str);
          
   if (str == "1") { 
     delay(500);
     File dir = LittleFS.open("/");
     Serial.println();
     Serial.println("Diretorio do LittleFS:");
     Serial.println();
     printDirectory(dir);
   }
   else if (str == "2") {
     delay(500);
     File dir = LittleFS.open("/");
     Serial.println();
     Serial.println("Diretorio do LittleFS:");
     Serial.println();
     printDirectory(dir);
     Serial.println();
     Serial.println("Nome do arquivo que será excluido: ");
     while(Serial.available() == 0) {
     }
     str = Serial.readString();
     excluirArquivo(str);
   }
   else if (str == "3") {
     Serial.println("Nome do arquivo Vazio que será criado: ");
     while(Serial.available() == 0) {
     }
     str = Serial.readString();
     criaArquivoVazio(str);
     delay(500);
     File dir = LittleFS.open("/");
     Serial.println();
     Serial.println("Diretorio do LittleFS:");
     Serial.println();
     printDirectory(dir);
     Serial.println();
   }
   else if (str == "4") {
     delay(500);
     File dir = LittleFS.open("/");
     Serial.println();
     Serial.println("Diretorio do LittleFS:");
     Serial.println();
     printDirectory(dir);
     Serial.println();
     Serial.println("Nome do arquivo que será impresso: ");
     while(Serial.available() == 0) {
     }
     str = Serial.readString();
     imprimeArquivo(str);
   }
   else if (str == "5") {
     delay(500);
     File dir = LittleFS.open("/");
     Serial.println();
     Serial.println("Diretorio do LittleFS:");
     Serial.println();
     printDirectory(dir);
     Serial.println();
     Serial.println("Nome do arquivo que será escrito: ");
     while(Serial.available() == 0) {
     }
     str = Serial.readString();
     Serial.println("O que será escrito: ");
     while(Serial.available() == 0) {
     }
     String str2 = Serial.readString();
     escreveArquivo(str, str2, 0);
     imprimeArquivo(str);
   }
   else if (str == "6") {
     delay(500);
     File dir = LittleFS.open("/");
     Serial.println();
     Serial.println("Diretorio do LittleFS:");
     Serial.println();
     printDirectory(dir);
     Serial.println();
     Serial.println("Nome do arquivo que será escrito: ");
     while(Serial.available() == 0) {
     }
     str = Serial.readString();
     Serial.println("O que será escrito: ");
     while(Serial.available() == 0) {
     }
     String str2 = Serial.readString();
     escreveArquivo(str, str2, 1);
     imprimeArquivo(str);
   }
   
  Serial.println();
  Serial.println("Digite Algo para continuar");
  while(Serial.available() == 0) {
   }
  str = Serial.readString();
  int i = 0;
  while(i < 30){
    Serial.println();
    i++;
  }
}
 
void printDirectory(File dir) {
  while (true) {
 
    File entry =  dir.openNextFile();
    if (! entry) {
      break;
    }

    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry);
    } else {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void excluirArquivo(String fileName) {
  fileName = "/" + fileName + ".txt";
  if (LittleFS.remove(fileName)){
    Serial.println();
    Serial.print(fileName);
    Serial.println(" foi excluido com sucesso");
  }
  else {
    Serial.println();
    Serial.print(fileName);
    Serial.println(" falhou na exclusão");
  }
}

void criaArquivoVazio(String fileName) {
  fileName = "/" + fileName + ".txt";
  File createFile = LittleFS.open(fileName, "a");
  if (createFile){
    Serial.println();
    Serial.print("o arquivo vazio ");
    Serial.print(fileName);
    Serial.println(" foi criado com sucesso");
  }else{
    Serial.println();
    Serial.print("o arquivo vazio ");
    Serial.print(fileName);
    Serial.println(" teve um erro na sua criação");
  }
  createFile.close();
  
}

void imprimeArquivo(String fileName) {
  fileName = "/" + fileName + ".txt";
  File readFile = LittleFS.open(fileName, "r");
  if (readFile){
    Serial.println();
    Serial.print("conteudo do arquivo ");
    Serial.print(fileName);
    Serial.println(":");
    Serial.println();
    Serial.println(readFile.readString());
  }else{
    Serial.println("Houve um problema na impressão do arquivo");
  }
  readFile.close();
}

void escreveArquivo(String fileName, String conteudo, int tipo) {
  fileName = "/" + fileName + ".txt";
  File writeFile;
  if (tipo == 0){
      writeFile = LittleFS.open(fileName, "w");
  }
  else if (tipo == 1) {
      writeFile = LittleFS.open(fileName, "a");
  }
  if (writeFile){
    Serial.println();
    Serial.print("escrevendo no arquivo ");
    Serial.print(fileName);
    Serial.println("...");
    Serial.println();
    writeFile.println(conteudo);
  }else{
    Serial.println("Houve um problema na escrita do arquivo");
  }
  writeFile.close();
}
