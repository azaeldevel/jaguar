#include "config.h"


#include <string>
#include <vector>

namespace jaguar
{


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
		struct Config
		{
			std::string name;
			std::string brief;

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
		
		enum Type
		{
			none,
			get,
			post
		};
		struct Config : public Sampler::Config
		{
			std::string comment;

			std::string server;
			std::string path;
				
			Type type;
			std::vector<Parameter> params;

			Config();
		};

		Http(const Config&);	
		
		virtual bool run()const;


	private:
		std::string efective_url;
	};
}
}