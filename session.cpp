/*
This is a class that is designed to serve as an interface that can be easily
linked to any web service or application. It allows the user to login, logout,
register, check rating/reviews of professors and add new reviews
*/

class Session {
private:
  Students* allstudents;
  Professors* allprofessors;
  std::string email;
  std::string professor;
  std::string review;
  std::string browse(std::string professor_name);
  std::string login(std::string user_input);
  std::string logout(std::string user_input);
  std::string get_hash_value(std::string tmp_psw);
  std::string rate(std::string user_input);
  std::string registr(std::string user_input);
  bool email_is_valid(std::string email);
  bool loggedin;
  unsigned int location;
  unsigned int rating;
  const char* welcometext[2] = {
    "\nChoose your option:\n2: Register\n3: Login\n5: Browse reviews\nOr: exit\n",
    "\nChoose your option:\n4: Logout\n6: Rate\n5: Browse reviews\nOr: exit\n"};
public:
  Session();
  ~Session();
  const char* welcome(const char* query);
};

Session::Session() {
  allstudents = new Students;
  allprofessors = new Professors;
  loggedin = false;
  location = 0;
  email = "";
  professor = "";
  review = "";
  rating = 0;
};

Session::~Session() {
  delete allstudents;
  delete allprofessors;
}

const char* Session::welcome(const char* query) { /*
  This function serves as a tunnel with
  */
  std::cout << "QUERY IN WELCOME: "<< query << "\n";
  if(location == 0) { // when user enters program for the first time location is 0
    location = 1; // location is set to 1 because menu is printed (below)
    return welcometext[loggedin];
  }
  else if(location == 1) { // set location according to user input and call function again
    if(strcmp(query, "2") == 0) location = 2;
    else if(strcmp(query, "3") == 0) location = 3;
    else if(strcmp(query, "4") == 0) location = 4;
    else if(strcmp(query, "5") == 0) location = 5;
    else if(strcmp(query, "6") == 0) location = 6;
    else location = 0;
    std::cout << "new location: " << location << "\n";
    return welcome("NONE");
  }

  else {
    std::string str_query(query);
    std::string str_response;

    if(location == 2) str_response = registr(str_query);
    if(location == 3) str_response = login(str_query);
    if(location == 4) str_response = logout(str_query);
    if(location == 5) str_response = browse(str_query);
    if(location == 6) str_response = rate(str_query);

    char* chr_response = new char[str_response.length()+1];
    strcpy(chr_response, str_response.c_str());
    return chr_response;
  }
}

std::string Session::browse(std::string professor_name) {
  if(professor_name.compare("NONE") == 0)
    return "Please, enter Professor's full name: ";
  else {
    location = 0;
    return allprofessors->get_profile(professor_name) + welcometext[loggedin];
  }
}

std::string Session::login(std::string user_input) {
  // Make sure user is not already logged in
  if(loggedin) {
    location = 0;
    return "already logged in\n";
  }

  // Ask for user creditentials
  else if(user_input == "NONE"){
    if(email == "")
      return "e-mail: ";
    return "password: ";
    }

  // Check and accept creditentials
  else if(user_input != "NONE") {
    if(email == "") {
      if(allstudents->check_email(user_input)) {
        email = user_input;
        return welcome("NONE");
      }
      else
        return "email incorrect\n";
    }
    else {
      std::string tmp_psw = get_hash_value(user_input);
      if(allstudents->check_password(email, tmp_psw)) {
          loggedin = true;
          location = 0;
          return "log in succesful\n";
        }
      else
        return "password incorrect\n";
      }
    }
}

std::string Session::logout(std::string user_input) {
  email.clear();
  loggedin = false;
  location = 0;
  return "loggout succesful\n";
}

std::string Session::registr(std::string user_input) {
  // Make sure user is not already logged in
  if(loggedin) {
    location = 0;
    return "already logged in\n";
  }
  // Ask for user creditentials
  else if(user_input == "NONE" && email == "")
    return "e-mail: ";
  // Check and accept creditentials
  else {
    if(email == "") { // user_input is email
      if(allstudents->check_email(user_input))
        return "email already registered\n";
      else if(!email_is_valid(email))
        return "invalid email, please choose email associated with your university.\n";
      else {
        email = user_input;
        return "password: ";
      }
    }
    else { // user_input is password
      std::string tmp_psw = get_hash_value(user_input);
      allstudents->insert(email, tmp_psw);
      loggedin = true;
      location = 0;
      return "registration succesful\n";
    }
  }
}

std::string Session::rate(std::string user_input) {
  // Ask for professors name
  if(user_input == "NONE" && professor == "")
    return "Please, enter Professor's full name: ";
  else {
    if(professor == "") {
      if(allprofessors->check_name(user_input)){
        professor = user_input;
        return "Rate this professor (number between 1 and 5): ";
      }
      else
        "Professor not found. Try again.\n";
    }
    else if(rating == 0) {
      if(stoi(user_input) > 0 && stoi(user_input) < 6) {
        rating = stoi(user_input);
        return "Please give constructive feedback: ";
      }
      else
        return "Invalid number\n";
    }
    else if(review == "") {
      std::string reply = allprofessors->add_review(professor, email, user_input, rating);
      professor.clear();
      review.clear();
      rating = 0;
      location = 0;
      return reply;
    }
  }
}

std::string Session::get_hash_value(std::string raw_password) {
  size_t hash_value;
  std::hash <std::string> hashfn; // TODO Replace with safe(r) hash function?
  hash_value = hashfn(raw_password);
  std::stringstream ss;
  ss << hash_value;
  return ss.str();
}

bool Session::email_is_valid(std::string email) {
  std::string domain = email.substr(email.find("@") + 1);
  if(domain == "edu.aua.am")
    return true;
  return false;
}
