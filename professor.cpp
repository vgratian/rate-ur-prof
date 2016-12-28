
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
  void destroy_tree(professor* node);
  professor* find(professor* node, std::string name);
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

Professors::~Professors() {
  destroy_tree(m_root);
}

void Professors::insert_data(std::string name) {
  if(m_root == NULL) {
    m_root = new professor;   // creating the root if it's empty
    m_root->name = name;
    m_root->left = NULL;
    m_root->right = NULL;
    m_root->parent = NULL;
    m_size = 1;
  }
  else {
    insert_deeper(m_root, name);
  }
}

void Professors::insert_deeper(professor* parent, std::string name) {
  if(name < parent->name) {
    if(parent->left != NULL)
      insert_deeper(parent->left, name);
    else {
      parent->left = new professor;
      parent->left->name = name;
      parent->left->left = NULL;
      parent->left->right = NULL;
      parent->left->parent = parent;
      m_size++;
    }
  }
  else if(name >= parent->name) {
    if(parent->right != NULL)
      insert_deeper(parent->right, name);
    else {
      parent->right = new professor;
      parent->right->name = name;
      parent->right->left = NULL;
      parent->right->right = NULL;
      parent->right->parent = parent;
      m_size++;
    }
  }
}

// Deletes all nodes in the tree
void Professor::destroy_tree(professor* node) {
  if(node != NULL){
    destroy_tree(node->left);
    destroy_tree(node->right);
    delete node;
  }
}

// Returns professor with name
professor* Professors::find(professor* node, std::string  name) {
  if(node != NULL) {
    if(name == node->name)
      return node;
    else if(name < node->name)
      find(node->left, name);
    else if(name > node->name)
      find(node->right, name);
  }
  else
    return NULL;
}

// returns number of professors in the tree
int Professors::get_size() {
  return m_size;
}
