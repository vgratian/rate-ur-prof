/*
This is a binary tree that contains all the students from an institution
(eg. a university). Once initiated it loads login details of all students
saved in the "students.csv" file
*/

struct student {
  std::string name;
  std::string email;
  std::string password;
  std::string courses[50];
  rating ratings[50];
  student* left;
  student* right;
  student* parent;
};

class Students {
private:
  student* m_root;
  unsigned int m_size;
  void insert_data(std::string email, std::string password);
  void insert_deeper(student* parent, std::string email, std::string password);
  void destroy_tree(student* node);
  student* find(student* node, std::string email);

public:
  Students();
  ~Students();
  void insert(std::string email, std::string password);
  int get_size();
  bool is_registered(std::string email);
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
    insert_data(email, password);
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

  insert_data(email, password);
}

void Students::insert_data(std::string email, std::string password) {
  if(m_root == NULL) {
    m_root = new student;   // creating the root if it's empty
    m_root->email = email;
    m_root->password = password;
    m_root->left = NULL;
    m_root->right = NULL;
    m_root->parent = NULL;
    m_size = 1;
  }
  else {
    insert_deeper(m_root, email, password);
  }
}

void Students::insert_deeper(student* parent, std::string email, std::string password) {
  if(email < parent->email) {
    if(parent->left != NULL)
      insert_deeper(parent->left, email, password);
    else {
      parent->left = new student;
      parent->left->email = email;
      parent->left->password = password;
      parent->left->left = NULL;
      parent->left->right = NULL;
      parent->left->parent = parent;
      m_size++;
    }
  }
  else if(email >= parent->email) {
    if(parent->right != NULL)
      insert_deeper(parent->right, email, password);
    else {
      parent->right = new student;
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
bool Students::is_registered(std::string email) {
  student* node = find(m_root, email);
  if(node != NULL && node->email == email)
    return true;
  return false;
}

bool Students::check_password(std::string email, std::string password) {
  student* node = find(m_root, email);
  if(node != NULL && node->password == password)
    return true;
  return false;
}

// Returns student with email
student* Students::find(student* node, std::string  email) {
  if(node != NULL) {
    if(email == node->email)
      return node;
    else if(email < node->email)
      find(node->left, email);
    else if(email > node->email)
      find(node->right, email);
  }
  else
    return NULL;
}

// returns number of students
int Students::get_size() {
  return m_size;
}
