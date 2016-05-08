  /******************************************************/
 /*       Created by Daniel(Lubini Vitton && Krigel)   */
/******************************************************/

#include "Trainer.hpp"
#include <exception>
#include <iostream>
#include <stdlib.h>
using std::cout;
using std::endl;
using std::exception;

  /******************************************************/
 /*		      Aux. Functions		       */
/******************************************************/
Pokemon findBest(AvlTree<Pokemon,PokemonsCompareByLevel>& tree) {
	if (tree.size() == 0)
 			return Pokemon();
	return tree.findMin();
}

void updatePokemons(Pokemon*& pokemons, int stoneFactor, int size) {	
  for (int i = 0; i < size; ++i) {
    pokemons[i].setLevel(pokemons[i].getLevel()*stoneFactor);
  }
}
template<class CompareFunc>
void mergePokemons(Pokemon*& pokemonArr1,Pokemon*& pokemonArr2,
		   Pokemon*& toMerge, CompareFunc cmp,
		   int size1, int size2,int sizeMerged) {

  int i = 0,j = 0,k = 0;
  while (j < size1 && k < size2) {
    if (cmp(pokemonArr1[j],pokemonArr2[k]))
      toMerge[i] = pokemonArr1[j++];
    else
      toMerge[i] = pokemonArr2[k++];
    ++i;
  }
  
  while(j < size1) {
		toMerge[i++] = pokemonArr1[j++];
  }
  while(k < size2) {
		toMerge[i++] = pokemonArr2[k++];
  }
}

  /*****************************************************/
 /*		   				 	 C'tors and D'tor							      */
/*****************************************************/
Trainer::Trainer():
	trainerID(-2), bestPokemon(),pokeTreeLevel(), pokeTreeId() {}

Trainer::Trainer(int id):
	trainerID(id),bestPokemon(), pokeTreeLevel(), pokeTreeId() {}

Trainer::Trainer(const Trainer& t):
	trainerID(t.trainerID),bestPokemon(t.bestPokemon),
	pokeTreeLevel(t.pokeTreeLevel), pokeTreeId(t.pokeTreeId) {}


  /*****************************************************/
 /*	         	Functions		      */
/*****************************************************/
const int& Trainer::getID() const{
  return this->trainerID;
}

int Trainer::GetTopPokemon() {
  return (this->bestPokemon).getID();
}

void Trainer::CatchPokemon(Pokemon pokemon) {
  this->pokeTreeId.insert(pokemon);

  this->pokeTreeLevel.insert(pokemon);
	PokemonsCompareByLevel cmp;
  if(cmp(pokemon, (this->bestPokemon))){
    this->bestPokemon = pokemon;  
  }
}

/*This function returns the id of the trainer of the deleted pokemon
 *For future use.*/
int Trainer::FreePokemon(int pokemonID) {
  Pokemon temp(pokemonID);
  int trainer;
  temp = (this->pokeTreeId).find(temp);
	Pokemon temp2 = (this->pokeTreeLevel).find(temp);
  trainer = (temp).getTrainerID();
  (this->pokeTreeLevel).remove(temp2);
(this->pokeTreeId).remove(temp);

  if (temp == this->bestPokemon)
    this->bestPokemon = findBest(this->pokeTreeLevel);
  return trainer;
}

/*Same here.*/
int Trainer::LevelUp(int pokemonID, int levelIncrease) {
  Pokemon temp(pokemonID);
  int trainer;
  temp = (this->pokeTreeId).find(temp);
  trainer = temp.getTrainerID();
  this->FreePokemon(temp.getID());
  
  temp.setLevel(temp.getLevel()+levelIncrease);
  this->CatchPokemon(temp);
  return trainer;
}

int* Trainer::GetAllPokemonsByLevel(int* arrSize) {
  Pokemon* pokemonArr = (this->pokeTreeLevel).inOrder();
    *arrSize = (this->pokeTreeLevel).size();
	if (*arrSize == 0)
		return NULL;
  int* pokemonIds = (int*)malloc(sizeof(int)*(*arrSize));
  for (int i=0; i< *arrSize; ++i)
    pokemonIds[i] = pokemonArr[i].getID();
	delete[] pokemonArr;
  return pokemonIds;
}

int Trainer::EvolvePokemon(int pokemonID, int evolvedID) {
  Pokemon temp(pokemonID);
  Pokemon tempEvolved(evolvedID);

  int trainer;
  temp = (this->pokeTreeId).find(temp);
  trainer = temp.getTrainerID();
	try {
  	(this->pokeTreeId).find(tempEvolved);
	} catch (NotFound& e) {}
	
		/*to throw exception in case
					 there is a pokemon with that ID*/
	temp.setID(evolvedID);

  this->CatchPokemon(temp);
	
  this->FreePokemon(pokemonID);
	
  return trainer;
}

void Trainer::UpdateLevels(int stoneCode, int stoneFactor) {
  Pokemon* pokemons = (this->pokeTreeLevel).inOrder();
  Pokemon* pokemonsById = (this->pokeTreeId).inOrder();
	if (pokemons == NULL)
		return;
  int sizeToChange=0;
  for (int i = 0; i < (this->pokeTreeLevel).size(); ++i) {
    if (pokemons[i].getID() % stoneCode == 0)
      ++sizeToChange;
  }
  Pokemon* pokesToChangeId = new Pokemon[sizeToChange];
  Pokemon* pokesNotToChangeId =
    new Pokemon[(this->pokeTreeLevel).size()-sizeToChange];
  Pokemon* pokesToChangeLevel = new Pokemon[sizeToChange];
  Pokemon* pokesNotToChangeLevel =
    new Pokemon[(this->pokeTreeLevel).size()-sizeToChange];
  int tc=0,ntc=0;//to change, not to change
  for (int i = 0; i < (this->pokeTreeLevel).size(); ++i) {
    if (pokemonsById[i].getID() % stoneCode == 0)
      pokesToChangeId[tc++] = pokemonsById[i];
    else
      pokesNotToChangeId[ntc++] = pokemonsById[i];
  }
  tc=0;ntc=0;//to change, not to change
  for (int i = 0; i < (this->pokeTreeLevel).size(); ++i) {
    if (pokemons[i].getID() % stoneCode == 0)
      pokesToChangeLevel[tc++] = pokemons[i];
    else
      pokesNotToChangeLevel[ntc++] = pokemons[i];
  }
  updatePokemons(pokesToChangeId,stoneFactor, sizeToChange);

  updatePokemons(pokesToChangeLevel,stoneFactor, sizeToChange);
  PokemonsCompareByLevel cmpbl;
  PokemonsCompareById cmpbi;
  mergePokemons(pokesToChangeLevel, pokesNotToChangeLevel,pokemons,
		cmpbl,
		sizeToChange,
		(this->pokeTreeLevel).size() - 
		sizeToChange,(this->pokeTreeLevel).size());
  
  mergePokemons(pokesToChangeId, pokesNotToChangeId, 
		pokemonsById,cmpbi, 
		sizeToChange,
		(this->pokeTreeId).size() - sizeToChange,
		(this->pokeTreeId).size());
  (this->pokeTreeLevel).insertArrayToTree(pokemons,
					  (this->pokeTreeLevel).size());
  (this->pokeTreeId).insertArrayToTree(pokemonsById,
				       (this->pokeTreeId).size());
	this->bestPokemon = pokemons[0];
  
  delete[] pokemons;
  delete[] pokemonsById;
  delete[] pokesToChangeId;
  delete[] pokesNotToChangeId;
  delete[] pokesToChangeLevel;
  delete[] pokesNotToChangeLevel;
}

Trainer& Trainer::operator=(const Trainer& t) {
	if (&t == this)
		return *this;
	this->pokeTreeLevel = t.pokeTreeLevel;
	this->pokeTreeId = t.pokeTreeId;
	this->bestPokemon = t.bestPokemon;
	return *this;
}

bool CompareTrainers::operator()(const Trainer& t1,
				 const Trainer& t2) const{
  return (t1.getID() < t2.getID());
}


