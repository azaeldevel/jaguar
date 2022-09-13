
#include <iostream>
#include <curl/curl.h>

#include "jaguar.hh"


int main(void)
{
	
	jaguar::sampler::Sampler::Config configHome;
	configHome.name = "Home";
	configHome.server = "localhost";
	configHome.response = fopen("home.html","w");
	//configHome.display = true;
	jaguar::sampler::Http httpHome(configHome);
	if(httpHome.run())
	{
		std::cout << "Test " << configHome.name << "(Pass)\n";
	}
	else		
	{
		std::cout << "Test " << configHome.name << "(Failure)\n";
	}
	
	std::cout << "\n\n";

	
	jaguar::sampler::Sampler::Config config;
	config.name = "Login";
	config.server = "localhost";
	config.path = "/login.cgi";
	config.type = jaguar::sampler::Sampler::Type::post;
	config.response = fopen("login.html","w");
	//config.display = true;
	config.params.resize(2);
	config.params[0].name = "user";
	config.params[0].value = "root";
	config.params[1].name = "psw";
	config.params[1].value = "123456";
	jaguar::sampler::Http http(config);

	if(http.run())
	{
		std::cout << "Test " << config.name << "(Pass)\n";
	}
	else		
	{
		std::cout << "Test " << config.name << "(Failure)\n";
	}


	std::cout << "\n\n";

	jaguar::sampler::Sampler::Config configLogout;
	configLogout.name = "Logout";
	configLogout.server = "localhost";
	configLogout.path = "/logout.cgi";
	configLogout.response = fopen("logout.html","w");
	jaguar::sampler::Http httpLogout(configLogout);
	if(httpLogout.run())
	{
		std::cout << "Test " << configLogout.name << "(Pass)\n";
	}
	else		
	{
		std::cout << "Test " << configLogout.name << "(Failure)\n";
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