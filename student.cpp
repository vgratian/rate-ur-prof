
/*
This is a binary tree that contains all the students from an institution
(eg. a university). Once initiated it loads login details of all students
saved in the "students.csv" file

Used libraries: iostream, fstream
*/

struct student {
  unsigned int id;
  std::string name;
  std::string email;
  std::string password;
  student* left;
  student* right;
  student* parent;
};

class Students {
private:
  student* m_root;
  unsigned int m_size;
  unsigned int get_id(std::string name);
  void insert_to_tree(std::string email, std::string password);
  void insert_deeper(student* parent, unsigned int id, std::string email, std::string password);
  void destroy_tree(student* node);
  student* find(student* node, unsigned int id);

public:
  Students();
  ~Students();
  void insert(std::string email, std::string password);
  void check_find(std::string name);
  int get_size();
  bool check_email(std::string email);
  bool check_password(std::string email, std::string password);
};

Students::Students() {
  m_root = NULL;
  m_size = 0;
  // Constructor will load all "saved" students and build tree
  std::ifstream file("students.csv");
  std::string str;
  while (std::getline(file, str)) {
    std::string email = str.substr(0, str.find(";"));
    std::string password = str.substr(str.find(";") + 1);
    // create new node in the tree
    insert_to_tree(email, password);
   }
}

Students::~Students() {
  destroy_tree(m_root);
}

void Students::insert(std::string email, std::string password) {
  // writes new data into file before adding to tree
  std::ofstream file;
  file.open("students.csv", std::ios_base::app);
  file << email << ";" << password << std::endl;
  insert_to_tree(email, password);
}

void Students::insert_to_tree(std::string email, std::string password) {
  unsigned int id = get_id(email);
  if(m_root == NULL) {
    m_root = new student;   // creating the root if it's empty
    m_root->id = id;
    m_root->email = email;
    m_root->password = password;
    m_root->left = NULL;
    m_root->right = NULL;
    m_root->parent = NULL;
    m_size = 1;
  }
  else {
    insert_deeper(m_root, id, email, password);
  }
}

void Students::insert_deeper(student* parent, unsigned int id, std::string email, std::string password) {
  if(id < parent->id) {
    if(parent->left != NULL)
      insert_deeper(parent->left, id, email, password);
    else {
      parent->left = new student;
      parent->left->id = id;
      parent->left->email = email;
      parent->left->password = password;
      parent->left->left = NULL;
      parent->left->right = NULL;
      parent->left->parent = parent;
      m_size++;
    }
  }
  else if(id >= parent->id) {
    if(parent->right != NULL)
      insert_deeper(parent->right, id, email, password);
    else {
      parent->right = new student;
      parent->right->id = id;
      parent->right->email = email;
      parent->right->password = password;
      parent->right->left = NULL;
      parent->right->right = NULL;
      parent->right->parent = parent;
      m_size++;
    }
  }
}

// Deletes all nodes in the tree
void Students::destroy_tree(student* node) {
  if(node != NULL){
    destroy_tree(node->left);
    destroy_tree(node->right);
    delete node;
  }
}

// Checks if tree has any student with given email
bool Students::check_email(std::string email) {
  student* node = find(m_root, get_id(email));
  if(node != NULL && node->email == email)
    return true;
  return false;
}

bool Students::check_password(std::string email, std::string password) {
  student* node = find(m_root, get_id(email));
  if(node != NULL && node->password == password)
    return true;
  return false;
}

// Returns student with email
student* Students::find(student* node, unsigned int id) {
  if(node != NULL) {
    if(id == node->id)
      return node;
    else if(id < node->id)
      find(node->left, id);
    else if(id > node->id)
      find(node->right, id);
  }
  else
    return NULL;
}

// returns number of students
int Students::get_size() {
  return m_size;
}

// Generates id by hashing email
unsigned int Students::get_id(std::string email) {
  std::hash <std::string> hashfoo;
  unsigned int id = hashfoo(email);
  return id;
}
