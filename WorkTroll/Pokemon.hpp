  /******************************************************/
 /*			Created by Daniel(Lyubin && Krigel)		   */
/******************************************************/

#ifndef POKEMON_HPP_
#define POKEMON_HPP_

class Pokemon {
  int pokemonID;
  int level;
  int trainerID;
public:
  /**C'tors and D'tor**/
  Pokemon();
  Pokemon(int pokemonID,int level = -1 ,int trainerID = -2 );
  Pokemon(const Pokemon&);
  ~Pokemon();
  /**Sets and Gets**/
  const int& getID() const;
  const int& getLevel() const;
  const int& getTrainerID() const;
  void setID(const int&);
  void setLevel(const int&);
  /**Operator(s)**/
  Pokemon& operator=(const Pokemon&);
  bool operator==(const Pokemon&);
};

class PokemonsCompareByLevel {
public:
  bool operator()(const Pokemon&,const Pokemon&) const;
};
class PokemonsCompareById {
public:
  bool operator()(const Pokemon&,const Pokemon&) const;
};
#endif /*POKEMON_HPP_*/
