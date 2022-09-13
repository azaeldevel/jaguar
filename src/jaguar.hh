#include "config.h"


#include <string>
#include <vector>

namespace jaguar
{

	class Test
	{
	public:
		struct Config
		{
			std::string name;
			std::string brief;

			unsigned short threads;
			float prob;		
			
		};

		Test(const Config&);
		

	private:
		const Config* config;
	};


namespace sampler
{
	class Sampler
	{
	public:
		struct Parameter
		{
			std::string name;
			std::string value;
		};
		enum Type
		{
			none,
			get,
			post
		};
		struct Config
		{
			std::string name;
			std::string brief;

			std::string server;
			std::string path;
				
			Type type;
			std::vector<Parameter> params;
			FILE* response;
			bool display;

			Config();
		};

		
		
		virtual bool run() const = 0;

	protected:
		Sampler(const Config&);
		const Config* config;
	};


	class Http : public Sampler
	{
	public:
		Http(const Sampler::Config&);	
		
		virtual bool run()const;


	private:
		std::string efective_url;
	};
}
}