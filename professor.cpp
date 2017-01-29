/*
This is a binary tree that contains all the instructors from an institution
(eg. a university). Once initiated it loads instructors with their reviews and
ratings saved in the "professors.csv" file

Required libraries: iostream, fstream, sstream
*/

struct professor {
  unsigned int id;
  unsigned int score;
  std::string name;
  std::string students; //students that rated this professor (emails)
  std::string reviews;
  std::string ratings;
  professor* left;
  professor* right;
  professor* up;
};

class Professors {
private:
  professor* m_root;
  unsigned int m_size;
  unsigned int get_id(std::string name);
  unsigned int get_score(std::string ratings);
  void insert_to_tree(std::string name, std::string students, std::string reviews, std::string ratings);
  void insert_deeper(professor* root, unsigned int id, std::string name, std::string students, std::string reviews, std::string ratings);
  void destroy_tree(professor* root);
  void update_rating();
  void write_to_file();
  void write_inorder(professor* node);
  void write_line(std::string name, std::string students, std::string reviews, std::string ratings);
  professor* find(professor* node, unsigned int id);

public:
  Professors();
  ~Professors();
  int get_rating();
  int get_size();
  std::string get_profile(std::string name);
  std::string add_review(std::string name, std::string email, std::string review, unsigned int rating);
  bool check_name(std::string name);
};

Professors::Professors() {
  m_root = NULL;
  m_size = 0;

  // Loads all professors from database and inserts to tree
  std::ifstream file("professors.csv");
  std::string str;
  while (std::getline(file, str)) {
    std::string name = str.substr(0, str.find(";"));
    str.erase(0, name.length()+1);
    std::string students = str.substr(0, str.find(";"));
    str.erase(0, students.length()+1);
    std::string reviews = str.substr(0, str.find(";"));
    str.erase(0, reviews.length()+1);
    std::string ratings = str.substr(0, str.find(";"));
    insert_to_tree(name, students, reviews, ratings);
   }
}

Professors::~Professors() {
  write_to_file();
  destroy_tree(m_root);
}

void Professors::write_to_file() {
  std::ofstream file;
  file.open("professors.csv", std::ios::trunc);
  file.close();
  write_inorder(m_root);
  }

void Professors::write_inorder(professor* node) {
  if(node != NULL) {
    write_inorder(node->left);
    write_line(node->name, node->students, node->reviews, node->ratings);
    write_inorder(node->right);
  }
}

void Professors::write_line(std::string name, std::string students, std::string reviews, std::string ratings) {
  std::string fulldata;
  std::stringstream ss;
  ss << name << ";" << students << ";" << reviews << ";" << ratings << "\n";
  fulldata = ss.str();

  std::ofstream file;
  file.open("professors.csv", std::ios::app);
  file << fulldata;
  file.close();
}

// Deletes all nodes in the tree: TODO: Do we need this?
void Professors::destroy_tree(professor* node) {
  if(node != NULL){
    destroy_tree(node->left);
    destroy_tree(node->right);
    delete node;
    //m_size--;
  }
}
// Generates id by hashing name
unsigned int Professors::get_id(std::string name) {
  std::hash <std::string> hashfoo;
  unsigned int  id = hashfoo(name);
  return id;
}

void Professors::insert_to_tree(std::string name, std::string students, std::string reviews, std::string ratings) {
  unsigned int id = get_id(name);
  if(m_root == NULL) {
    m_root = new professor;   // creating the root if it's empty
    m_root->id = id;
    m_root->name = name;
    m_root->students = students;
    m_root->reviews = reviews;
    m_root->ratings = ratings;
    m_root->score = get_score(ratings);
    m_root->left = NULL;
    m_root->right = NULL;
    m_root->up = NULL;
    m_size = 1;
  }
  else {
    insert_deeper(m_root, id, name, students, reviews, ratings);
  }
}

void Professors::insert_deeper(professor* parent, unsigned int id, std::string name, std::string students, std::string reviews, std::string ratings) {
  if(id < parent->id) {
    if(parent->left == NULL) {
      parent->left = new professor;
      parent->left->id = id;
      parent->left->name = name;
      parent->left->students = students;
      parent->left->reviews = reviews;
      parent->left->ratings = ratings;
      parent->left->score = get_score(ratings);
      parent->left->left = NULL;
      parent->left->right = NULL;
      parent->left->up = parent;
      m_size++;
    }
    else
      insert_deeper(parent->left, id, name, students, reviews, ratings);
  }
  else if(id >= parent->id) {
    if(parent->right == NULL) {
      parent->right = new professor;
      parent->right->id = id;
      parent->right->name = name;
      parent->right->students = students;
      parent->right->reviews = reviews;
      parent->right->ratings = ratings;
      parent->right->score = get_score(ratings);
      parent->right->left = NULL;
      parent->right->right = NULL;
      parent->right->up = parent;
      m_size++;
    }
    else
      insert_deeper(parent->right, id, name, students, reviews, ratings);
  }
}

// Finds and returns professor with given id
professor* Professors::find(professor* node, unsigned int id) {
  if(node != NULL)
    if(id == node->id)
      return node;
    else if(id < node->id)
      find(node->left, id);
    else if(id > node->id)
      find(node->right, id);
  else // if not found
    return NULL;
}

// Prints profile of given professor
std::string Professors::get_profile(std::string name) {
  professor* node = find(m_root, get_id(name));
  if(node != NULL && node->name == name) {
    std::stringstream ss;
    ss << "name: " << node->name << "  Rating: " << node->score << "\nReviews:\n" << node->reviews << "\n";
    return ss.str();
  }
  else
    return "Oops, no professor found with name " + name + "\n";
}

std::string Professors::add_review(std::string name, std::string email, std::string review, unsigned int rating) {
  professor* node = find(m_root, get_id(name));
  if(node != NULL && node->name == name) {
    node->students += email += ",";
    node->reviews += "*";
    node->reviews += review += "*,";
    node->ratings += std::to_string(rating) += ",";
    node->score = get_score(node->ratings);
    return "You succesfully reviewed " + name + "!\n";
  }
  else {
    return "Oops, no professor found with name " + name + "\n";
  }
}

unsigned int Professors::get_score(std::string ratings) {
  if(ratings.length()) { // Exception handling for when ratings is empty
    unsigned int sum = 0;
    unsigned int amount = 0;
    std::string all_ratings = ratings; // Ratings in the form of a single string

    while(all_ratings.length()) {
      sum += std::stoi(all_ratings.substr(0, all_ratings.find(",")));
      all_ratings.erase(0,2);
      amount++;
    }
    return sum/amount;
  }
  else
    return 0;
}

// Returns number of professors in the tree
int Professors::get_size() {
  return m_size;
}

bool Professors::check_name(std::string name) {
  professor* node = find(m_root, get_id(name));
  if(node == NULL)
    return false;
  return true;
}
