#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <typeinfo>

struct professor {
  unsigned int id;
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
  void insert_to_tree(std::string name, std::string students, std::string reviews, std::string ratings);
  void insert_deeper(professor* root, unsigned int id, std::string name, std::string students, std::string reviews, std::string ratings);
  void destroy_tree(professor* root);
  void update_rating();
  professor* find(professor* node, unsigned int);

public:
  Professors();
  ~Professors();
  int get_rating();
  int get_size();
  void get_score(std::string name);
  void get_profile(std::string name);
  void add_rating();
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
    std::string ratings = str;
    insert_to_tree(name, students, reviews, ratings);
   }
}

Professors::~Professors() {
  destroy_tree(m_root);
}

// Generates id by hashing name
unsigned int Professors::get_id(std::string name) {
  unsigned int id;
  std::hash <std::string> hashfoo;
  id = hashfoo(name);
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

// Prints all details about given professor
void Professors::get_profile(std::string name) {
  professor* node = find(m_root, get_id(name));
  if(node != NULL && node->name == name)
    std::cout << "Name: " << node->name << "\nReviews: " << node->reviews << "\nRatings: " << node->ratings << "\n\n";
  else
    std::cout << "No professor found with name " << name << "\n";
}

void Professors::get_score(std::string name) {
  ;
}

// Returns number of professors in the tree
int Professors::get_size() {
  return m_size;
}

// Deletes all nodes in the tree: TODO: Do we need this?
void Professors::destroy_tree(professor* node) {
  if(node != NULL){
    destroy_tree(node->left);
    destroy_tree(node->right);
    delete node;
  }
}
