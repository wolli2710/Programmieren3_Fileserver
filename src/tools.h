/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/
#pragma once

static enum ContentType{
  html,
  application
 };

static std::string getHtmlHeader(int contentType, unsigned int contentSize){
  std::stringstream header;
  header << "HTTP/1.0 200 OK\n";
	header << "Server: FileServer/0.0.1\n";
	header << "Content-Type: ";
  switch(contentType){
    case ContentType::html:
      header << "text/html";
      break;
    case ContentType::application: 
      header << "application/octet-stream";
      break;
  }  
  header << "\n";
	header << "Content-Length: " << contentSize << "\n\n";
  return header.str();
}