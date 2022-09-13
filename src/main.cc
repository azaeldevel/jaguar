
#include <iostream>
#include <curl/curl.h>

#include "jaguar.hh"


int main(void)
{
	jaguar::sampler::Sampler::Config config;
	config.server = "localhost";
	config.path = "/login.cgi";
	config.type = jaguar::sampler::Sampler::Type::post;
	config.params.resize(2);
	//config.response = fopen("response-1.html","w");
	config.display = true;
	config.params[0].name = "user";
	config.params[0].value = "root";
	config.params[1].name = "psw";
	config.params[1].value = "123456";
	jaguar::sampler::Http http(config);

	if(http.run())
	{
		std::cout << "Prueba pasada..\n";
	}
	else		
	{
		std::cout << "Prueba no pasada..\n";
	}
  
  	return EXIT_SUCCESS;
}

/*
#include <stdio.h>
#include <curl/curl.h>
 
int main(void)
{
  CURL *curl;
  CURLcode res;
 
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "localhost/login.cgi");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "user=root&psw=123456");
 
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}*/