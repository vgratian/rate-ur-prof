/*
This is a class that provides an interface for the user, allowing them
to login, logout, register, check rating/reviews of professors and add new reviews
*/

class Session {
private:
  Students* allstudents;
  Professors* allprofessors;
  std::string m_email;
  std::string m_password;
  bool loggedin;
  bool is_valid_email(std::string email);
  void start();
  void login();
  void logout();
  void registr();
  void browse();
  void rate();
  void get_login_details();
  std::string get_hash_value(std::string raw_password);

public:
  Session();
  ~Session();
};

Session::Session() {
  allstudents = new Students;
  allprofessors = new Professors;
  loggedin = false;
  start();
}

Session::~Session() {
  delete allstudents;
  delete allprofessors;
}

void Session::start() {
  int choice;
  std::cout << "\n**Welcome to Rate Professor**\n";
  std::cout << "Currently " << allstudents->get_size() << " students are registered\n"; // This line is only for testing
  std::cout << "Choose your option:\n";
  // Menu for logged in user
  if(loggedin) {
    std::cout << "1: Logout\n2: Rate\n3: Browse reviews\n";
    std::cin >> choice;

    if(choice == 1) logout();
    else if(choice == 2) rate();
    else if(choice == 3) browse();
    else std::cout << "Please enter 1, 2 or 3" << std::endl;
  }
  // Menu for not logged in user
  else {
    std::cout << "1: Login\n2: Register\n3: Browse reviews\n";
    std::cin >> choice;

    if(choice == 1) login();
    else if(choice == 2) registr();
    else if(choice == 3) browse();
    else std::cout << "Please enter 1, 2 or 3" << std::endl;
  }
}

void Session::login() {
  // Make sure user is not already logged in
  if(loggedin) {
    std::cout << "already logged in\n";
    return start();
  }
  // Proceed with login
  else {
    startlogin:
    get_login_details();
    // Check if email and password are correct
    if(allstudents->check_email(m_email)) {
      if(allstudents->check_password(m_email, m_password)) {
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
  if(allstudents->check_email(m_email)) {
    std::cout << "email already registered\n";
    return registr();
  }
  // Check if email is from allstudents
  else if(!is_valid_email(m_email)) {
    std::cout << "invalid email, please choose email associated with your university.\n";
    return registr();
  }

  allstudents->insert(m_email, m_password);
  std::cout << "registration succesful\n";
  loggedin = true;
  return start();
}

void Session::rate() {
  std::string professor_name;
  std::string review;
  unsigned int rate;

  std::cout << "Please, enter Professor's full name: ";
  std::cin.clear();
  std::cin.ignore(1); // Without this getline doesn't work
  std::getline (std::cin,professor_name);

  // Check if professor with given name exists
  if(!allprofessors->check_name(professor_name)){
    std::cout << "Professor not found. Try again.";
    //return rate();
  }

  std::cout << "Rate this professor (number between 1 and 5): ";
  std::cin >> rate;

  std::cout << "Please give constructive feedback: ";
  std::cin.clear();
  std::cin.ignore(1); // Without this getline doesn't work
  std::getline (std::cin,review);

  allprofessors->add_review(professor_name, m_email, review, rate);
}

void Session::browse() {
  std::string professor_name;

  std::cout << "Please, enter Professor's full name: ";
  std::cin.clear();
  std::cin.ignore(1); // Without this getline doesn't work
  std::getline (std::cin,professor_name);

  allprofessors->get_profile(professor_name);
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
