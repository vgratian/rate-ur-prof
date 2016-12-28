
struct review {
  std::string student_email;
  std::string review;
  unsigned int rating;
};

struct professor {
  std::string name;
  std::string courses[50];
  std::string reviews[50];
  int score;
  professor* left;
  professor* right;
  professor* up;
};

class Professors {
private:
  professor* m_root;
  unsigned int m_size;
  void insert_data(std::string name);
  void insert_deeper(professor* parent, std::string name);
  void destroy_tree(professor* element);
  professor* find(professor* element, std::string name);
  void update_rating();

public:
  Professor();
  ~Professor();
  void add_rating();
  int get_rating(); // int?
  int get_size();
};

Professor::Professor() {

  m_root = NULL;
  m_size = 0;

  // Constructor will load all "saved" professors and build tree
  std::ifstream file("professors.csv");
  std::string str;
  while (std::getline(file, str)) {
    std::string name = str.substr(0, str.find(";"));
    str.erase(0, name.length()+1);
    std::string reviews = str.substr(0, str.find(";"));
    str.erase(0, reviews.length()+1);
    std::string ratings = str;
    // create new node in the tree
    insert_data(email, password);
   }
}

Students::~Students() {
  destroy_tree(m_root);
}
