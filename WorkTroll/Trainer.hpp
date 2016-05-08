  /******************************************************/
 /*			Created by Daniel(Lyubin && Krigel)		   			 */
/******************************************************/

#ifndef TRAINER_HPP_
#define TRAINER_HPP_
#include "Pokemon.hpp"
#include "AvlTree.hpp"

class Trainer {
  int trainerID;
  Pokemon bestPokemon;
  AvlTree<Pokemon,PokemonsCompareByLevel> pokeTreeLevel;
  AvlTree<Pokemon,PokemonsCompareById> pokeTreeId;
public:
  Trainer(int);
  Trainer(const Trainer&);
  Trainer();
  const int& getID() const;
  int GetTopPokemon();
  void CatchPokemon(Pokemon pokemon);
  int FreePokemon(int pokemonID);
  int LevelUp(int pokemonID, int levelIncrease);
  int* GetAllPokemonsByLevel(int* arrSize);
  int EvolvePokemon(int pokemonID,int evolvedID);
  void UpdateLevels(int stoneCode,int stoneFactor);
	Trainer& operator=(const Trainer& t);
};


class CompareTrainers {
public:
  bool operator()(const Trainer& t1, const Trainer& t2) const;
};
/*****************************************************/
/*					 Hasta la Vista.				  */
/*****************************************************/
  
#endif /*TRAINER_HPP_*/
