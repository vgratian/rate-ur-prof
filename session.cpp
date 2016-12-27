/*
This is a class that provides an interface for the user, allowing them
to login, logout, register, check rating/reviews of professors and add new reviews
*/

class Session {
private:
  // member variables:
  Students* uni;
  std::string m_email;
  std::string m_password;
  bool loggedin;
  // member functions:
  void start();
  void login();
  void logout();
  void registr();
  void browse();
  void rate();
  void get_login_details();
  std::string get_hash_value(std::string raw_password);
  bool is_valid_email(std::string email);

public:
  Session();
};

Session::Session() {
  uni = new Students;
  loggedin = false;
  start();
}

void Session::start() {
  int choice;
  std::cout << "\n**Welcome to Rate Professor**\n";
  std::cout << "Currently " << uni->get_size() << " students are registered\n"; // This line is only for testing
  std::cout << "Choose your option:\n";
  // Menu for logged in user
  if(loggedin) {
    std::cout << "1: Logout\n2: Rate\n3: Browse\n";
    std::cin >> choice;

    if(choice == 1) logout();
    else if(choice == 2) rate();
    else if(choice == 3) browse();
    else std::cout << "Please enter 1 or 2" << std::endl;
  }
  // Menu for not logged in or registered user
  else {
    std::cout << "1: Login\n2: Register\n3: Browse\n";
    std::cin >> choice;

    if(choice == 1) login();
    else if(choice == 2) registr();
    else if(choice == 3) browse();
    else std::cout << "Please enter 1 or 2" << std::endl;
  }
}

void Session::login() {
  // First make sure user is already not logged in
  if(loggedin) {
    std::cout << "already logged in\n";
    return start();
  }
  // Proceed with login
  else {
    get_login_details();
    std::cout << "mail: " << m_email << ", psw: " << m_password << "\n"; // TODO remove
    // Check if email and password are correct
    if(uni->is_registered(m_email)) {
      if(uni->check_password(m_email, m_password)) {
          std::cout << "log in succesful\n";
          loggedin = true;
          return start();
      }
      else {
        std::cout << "password incorrect\n";
        return login();
      }
    }
    else {
      std::cout << "email incorrect\n";
      return login();
    }
  }
}

void Session::logout() {
  m_email.clear();
  m_password.clear();
  loggedin = false;
  std::cout << "loggout succeful\n";
  return start();
}

void Session::registr() {
  std::cout << "\n**Registration page**\n";
  get_login_details();

  // Check if user is not already registered
  if(uni->is_registered(m_email)) {
    std::cout << "email already registered\n";
    return registr();
  }
  // Check if email is from university
  else if(!is_valid_email(m_email)) {
    std::cout << "invalid email, please choose email associated with your university.\n";
    return registr();
  }

  uni->insert(m_email, m_password);
  std::cout << "registration succesful\n";
  loggedin = true;
  return start();
}

void Session::rate() {
  ;
}

void Session::browse() {
  ;
}

void Session::get_login_details() {
  std::cout << "e-mail: ";
  std::cin >> m_email;
  std::cout << "password: ";
  std::cin >> m_password;
  m_password = get_hash_value(m_password);
}

std::string Session::get_hash_value(std::string raw_password) {
  size_t hash_value;
  std::hash <std::string> hashfn; // TODO Replace with safe(r) hash function?
  hash_value = hashfn(raw_password);
  std::stringstream ss;
  ss << hash_value;
  return ss.str();
}

bool Session::is_valid_email(std::string email) {
  std::string domain = email.substr(email.find("@") + 1);
  if(domain == "edu.aua.am")
    return true;
  return false;
}
