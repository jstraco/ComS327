#ifndef ITEM_H
# define ITEM_H

# include <stdint.h>
# undef swap
# include <vector>
# include <string>
# include "dice.h"
# include "descriptions.h"



class object{
 private:
  std::string name, description;
  object_type_t type;
  uint32_t color;
  dice damage;
  bool artifact;
  uint32_t rarity;
  uint32_t hit, dodge, defence, weight, speed, attribute, value;
 public:
  object() : name(),    description(), type(objtype_no_type),
                         color(0),  hit(),         damage(),
                         dodge(),   defence(),     weight(),
                         speed(),   attribute(),   value(),
                         artifact(false), rarity(0)
  {
  }
  void set(const std::string &name,
           const std::string &description,
           const object_type_t type,
           const uint32_t color,
           const uint32_t &hit,
           const dice &damage,
           const uint32_t &dodge,
           const uint32_t &defence,
           const uint32_t &weight,
           const uint32_t &speed,
           const uint32_t &attrubute,
           const uint32_t &value,
           const bool artifact,
           const uint32_t rarity);
  std::ostream &print(std::ostream &o);
  /* Need all these accessors because otherwise there is a *
   * circular dependancy that is difficult to get around.  */
  inline const std::string &get_name() const { return name; }
  inline const std::string &get_description() const { return description; }
  inline const object_type_t get_type() const { return type; }
  inline const uint32_t get_color() const { return color; }
  inline const uint32_t &get_hit() const { return hit; }
  inline const dice &get_damage() const { return damage; }
  inline const uint32_t &get_dodge() const { return dodge; }
  inline const uint32_t &get_defence() const { return defence; }
  inline const uint32_t &get_weight() const { return weight; }
  inline const uint32_t &get_speed() const { return speed; }
  inline const uint32_t &get_attribute() const { return attribute; }
  inline const uint32_t &get_value() const { return value; }
};

#endif