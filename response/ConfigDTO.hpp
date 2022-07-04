#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <string>
#include <vector>

struct LocationConfig {
  std::string uri_;

  // Define a HTTP redirection.
  std::string root_;

  // Define a list of accepted HTTP methods for the route
  std::vector<std::string> allowed_methods_;

  // Set a default file to answer if the request is a directory.
  std::vector<std::string> indexes_;

  // Turn on or off directory listing.
  bool autoindex_;

  // Execute CGI based on certain file extension (for example .php).
  std::string cgi_path_;
};

// DTOクラス
class ConfigDTO
{
private:
	std::string _location;
	std::string _root;
	std::string _index;
public:
	LocationConfig _location_conf;
	ConfigDTO();
	ConfigDTO(std::string location, std::string _root, std::string _index);
	~ConfigDTO();
	ConfigDTO(const ConfigDTO &other);
	ConfigDTO &operator=(const ConfigDTO &other);
	void buildLocationConfDemo();
	const std::string &GetLocation() const;
	const std::string &GetRoot() const;
	const std::string &GetIndex() const;
};

#endif

