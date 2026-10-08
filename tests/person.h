#pragma once  


#include <string>
#include <vector>
#include <iostream>


namespace person  {
  
      class Person {
        public:
          Person(std::string name, int age) : name(name), age(age) {}
          std::string getName() const { return name; }
          int getAge() const { return age; }
        private:
          std::string name;
          int age;
      };
      
}