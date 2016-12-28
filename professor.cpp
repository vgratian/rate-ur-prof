
struct rating {
  Professor* professor;
  unsigned int value;
};

class Professors {
private:
  std::string name;
  std::string courses[50];
  int rating;
  void update_rating();

public:
  Professor();
  int get_rating();
  std::string get_name();

};
