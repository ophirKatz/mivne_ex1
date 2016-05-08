  /**********************************************************/
 /*			Created by Daniel(Lubini vitton && Kaligula)		   */
/**********************************************************/

#include "Trainer.hpp"

class YOLO {
	Trainer allPokemons;
	AvlTree<Trainer,CompareTrainers> trainers;
public:
	YOLO();
	~YOLO();
	void AddTrainer(int trainerID);
	void CatchPokemon(int pokemonID,int trainerID,int level);
	void FreePokemon(int pokemonID);
	void LevelUp(int pokemonID,int levelIncrease);
	void GetTopPokemon(int trainerID, int* pokemonID);
	void GetAllPokemonsByLevel(int trainerID,
														 int** pokemons, int* numOfPokmemon);
	void EvolvePokemon(int pokemonID, int evolvedID);
	void UpdateLevels(int stoneCode,int stoneFactor);
};
