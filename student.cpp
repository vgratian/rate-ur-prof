/*
This is a binary tree that contains all the students from an institution
(eg. a university). Once initiated it loads login details of all students
saved in the "students.csv" file
*/

struct student {
  std::string name;
  std::string email;
  std::string password;
  student* left;
  student* right;
  student* parent;
  rating ratings[100];
  std::string courses[100];
};

class Students {
private:
  student* m_root;
  unsigned int m_size;
  void insert_data(std::string email, std::string password);
  void insert_deeper(student* parent, std::string email, std::string password);
  void destroy_tree(student* element);
  student* find(student* element, std::string email);

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

// Deletes all elements in the tree
void Students::destroy_tree(student* element) {
  if(element != NULL){
    destroy_tree(element->left);
    destroy_tree(element->right);
    delete element;
  }
}

// Checks if tree has any student with given email
bool Students::is_registered(std::string email) {
  student* element = find(m_root, email);
  if(element != NULL && element->email == email)
    return true;
  return false;
}

bool Students::check_password(std::string email, std::string password) {
  student* element = find(m_root, email);
  if(element != NULL && element->password == password)
    return true;
  return false;
}

// Returns student with email
student* Students::find(student* element, std::string  email) {
  if(element != NULL) {
    if(email == element->email)
      return element;
    else if(email < element->email)
      find(element->left, email);
    else if(email > element->email)
      find(element->right, email);
  }
  else
    return NULL;
}

// returns number of students
int Students::get_size() {
  return m_size;
}
