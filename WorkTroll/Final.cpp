  /**********************************************************/
 /*			Created by Daniel(Lubini vitton && Kaligula)		   */
/**********************************************************/

#include "Final.hpp"

YOLO::YOLO():
	allPokemons(-1),trainers() {}

YOLO::~YOLO() {}

void YOLO::AddTrainer(int trainerID) {
	this->trainers.insert(Trainer(trainerID));
}

void YOLO::CatchPokemon(int pokemonID,int trainerID, int level) {
	Pokemon toCatch(pokemonID,trainerID,level);
	Trainer& temp = this->trainers.find(Trainer(trainerID));
	this->allPokemons.CatchPokemon(toCatch);
	temp.CatchPokemon(toCatch);
}

void YOLO::FreePokemon(int pokemonID) {
	int trainerID = allPokemons.FreePokemon(pokemonID);
	Trainer& temp = this->trainers.find(Trainer(trainerID));
	temp.FreePokemon(pokemonID);
}

void YOLO::LevelUp(int pokemonID, int levelIncrease) {
	int trainerID = this->allPokemons.LevelUp(pokemonID,levelIncrease);
	Trainer& temp = this->trainers.find(Trainer(trainerID));
	temp.LevelUp(pokemonID,levelIncrease);
}

void YOLO::GetTopPokemon(int trainerID, int* pokemonID) {
	if (trainerID<0)
		*pokemonID = allPokemons.GetTopPokemon();
	else {
		Trainer& temp = this->trainers.find(Trainer(trainerID));
		*pokemonID = temp.GetTopPokemon();
	}
}

void YOLO::GetAllPokemonsByLevel(int trainerID,
																 int** pokemons, int* numOfPokmemon) {

	if (trainerID<0) {
		*pokemons = allPokemons.GetAllPokemonsByLevel(numOfPokmemon);
	}
	else {
		Trainer& temp = this->trainers.find(Trainer(trainerID));
		*pokemons = temp.GetAllPokemonsByLevel(numOfPokmemon);
	}
}

void YOLO::EvolvePokemon(int pokemonID, int evolvedID) {
	int trainerID = this->allPokemons.EvolvePokemon(pokemonID,evolvedID);
	Trainer& temp = this->trainers.find(Trainer(trainerID));
	temp.EvolvePokemon(pokemonID,evolvedID);
}

void YOLO::UpdateLevels(int stoneCode,int stoneFactor) {
	allPokemons.UpdateLevels(stoneCode, stoneFactor);
	Trainer* trainersArr = this->trainers.inOrder();
	if (trainersArr == NULL)
		return;
	for (int i = 0; i < this->trainers.size(); ++i)
		trainersArr[i].UpdateLevels(stoneCode,stoneFactor);
	this->trainers.insertArrayToTree(trainersArr, this->trainers.size());
	delete[] trainersArr;
}

