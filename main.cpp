#include <iostream>
#include <map>
#include <string>
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include "include/nlohmann/json.hpp"

const nlohmann::json & valueAt(const nlohmann::json & map, const std::string & key)
{
  return map[key];
}
const nlohmann::json & valueAt(const nlohmann::json::object_t & map, const std::string & key)
{
  return map.at(key);
}

const nlohmann::json::object_t & getObjectRef(const nlohmann::json & obj)
{
  return obj.get_ref<const nlohmann::json::object_t &>();
}

const nlohmann::json::string_t & getStringRef(const nlohmann::json & obj)
{
  return obj.get_ref<const nlohmann::json::string_t &>();
}

const nlohmann::json::object_t getObject(const nlohmann::json & obj)
{
  return obj.get<const nlohmann::json::object_t>();
}

const nlohmann::json::string_t getString(const nlohmann::json & obj)
{
  return obj.get<const nlohmann::json::string_t>();
}

int main()
{
  nlohmann::json j2 = {
    {"string", "foo"},
    {"object", {
      {"currency", "USD"},
      {"value", 42.99}
    }}
  };

  auto object = getObject(valueAt(j2, "object"));

  std::cout << "object" << '\n';
  std::cout << nlohmann::json(object) << '\n';

  auto nestedObject = getString(valueAt(object, "currency"));

  std::cout << "nestedObject" << '\n';
  // This works
  std::cout << nestedObject << '\n';

  // ------------------------------------------------------------------

  auto & objectRef = getObjectRef(valueAt(j2, "object"));

  std::cout << "objectRef" << '\n';
  std::cout << nlohmann::json(objectRef) << '\n';

  auto & nestedObjectRef  = getStringRef(valueAt(objectRef, "currency"));

  std::cout << "nestedObjectRef" << '\n';
  // Here `nestedObject` seems to be empty.
  std::cout << nestedObjectRef << '\n';
}