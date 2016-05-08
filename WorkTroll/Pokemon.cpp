  /******************************************************/
 /*			Created by Daniel(Lyubin && Krigel)		   */
/******************************************************/

#include "Pokemon.hpp"

  /*****************************************************/
 /*					C'tors and D'tor				  */
/*****************************************************/
Pokemon::Pokemon(): pokemonID(-1), level(-1), trainerID(-2) {}

Pokemon::Pokemon(int pokemonID,int trainerID,
				int level):
	pokemonID(pokemonID), level(level), trainerID(trainerID) {}

Pokemon::Pokemon(const Pokemon& pokemon):
	pokemonID(pokemon.pokemonID), level(pokemon.level), 
	trainerID(pokemon.trainerID) {}	

Pokemon::~Pokemon() {}

  /*****************************************************/
 /*					Sets and Gets					  */
/*****************************************************/

const int& Pokemon::getID() const{
	return this->pokemonID;
}

const int& Pokemon::getLevel() const{
	return this->level;
}

const int& Pokemon::getTrainerID() const{
	return this->trainerID;	
}


void Pokemon::setID(const int& id) {
	this->pokemonID=id;
}

void Pokemon::setLevel(const int& level) {
	this->level=level; 
};

  /*****************************************************/
 /*					 Operator(s)					  */
/*****************************************************/

Pokemon& Pokemon::operator=(const Pokemon& pokemon) {
	if (this==&pokemon)
		return *this;
	this->pokemonID = pokemon.pokemonID;
	this->level=pokemon.level;
	this->trainerID=pokemon.trainerID;
	return *this;
}

bool Pokemon::operator==(const Pokemon& pokemon) {
	return this->pokemonID == pokemon.pokemonID;
}

bool PokemonsCompareByLevel::operator()(const Pokemon& pok1,
					const Pokemon& pok2) const {
  if (pok1.getLevel() > pok2.getLevel()) 
    return true;
  else
    if (pok1.getLevel() == pok2.getLevel())
      if (pok1.getID() < pok2.getID())
				return true;
  return false;
}


bool PokemonsCompareById::operator()(const Pokemon& pok1,
				     const Pokemon& pok2) const {
	return pok1.getID() < pok2.getID();
}

  /*****************************************************/
 /*					 Peace Out.						  */
/*****************************************************/
