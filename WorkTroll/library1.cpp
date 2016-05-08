#include "library1.h"
#include "Final.hpp"
#include <new>
#include <iostream>
void* Init() {
	YOLO* DS = new YOLO();
	return (void*)DS;
}

StatusType AddTroll(void *DS, int trollID) {
	if (DS == NULL || trollID <= 0)
	  return INVALID_INPUT;
	try {
	  ((YOLO*)DS)->AddTrainer(trollID);
	}
	catch (std::bad_alloc& ba) {
	  return ALLOCATION_ERROR;
	}
	catch (AlreadyExists& ae) {
	  return FAILURE;
	}
	return SUCCESS;
}

StatusType PublishPost(void *DS, int postID,int trollID, int likesCount) {
	if (DS == NULL || postID <= 0 || trollID <= 0 || likesCount < 0)
		return INVALID_INPUT;
	
	try {
		((YOLO*)DS)->CatchPokemon(postID,trollID,likesCount);
	}
	catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	catch (AlreadyExists& ae) {
		return FAILURE;
	}
	catch (NotFound& nf) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType DeletePost(void *DS, int postID) {
	if (DS == NULL || postID <= 0)
		return INVALID_INPUT;
	try {
		((YOLO*)DS)->FreePokemon(postID);
	}
	catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	catch (NotFound& nf) {
		return FAILURE;
	}
	return SUCCESS;
} 

StatusType FeedTroll(void *DS, int postID,int likesIncrease) {
	if (DS == NULL || postID <= 0 || likesIncrease <= 0)
		return INVALID_INPUT;
	try {
		((YOLO*)DS)->LevelUp(postID,likesIncrease);
	}
	catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	catch (NotFound& nf) {
		return FAILURE;
	}
	return SUCCESS;
}
/*
StatusType EvolvePokemon(void *DS, int pokemonID, int evolvedID) {
	if (DS == NULL || pokemonID <= 0 || evolvedID <= 0)
		return INVALID_INPUT;
	try {
		((YOLO*)DS)->EvolvePokemon(pokemonID, evolvedID);
	}
	catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	catch (AlreadyExists& ae) {
		return FAILURE;
	}
	catch (NotFound& nf) {
		return FAILURE;
	}
	return SUCCESS;
	}*/

StatusType GetTopPost(void *DS, int trollID, int *postID) {
	if (DS == NULL || trollID == 0 || postID == NULL)
		return INVALID_INPUT;
	try {
		((YOLO*)DS)->GetTopPokemon(trollID, postID);
	}
	catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	catch (NotFound& nf) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType GetAllPostsByLikes(void *DS, int trollID, int **posts, int *numOfPost) {
	if (DS == NULL || posts == NULL || numOfPost == NULL || trollID == 0)
		return INVALID_INPUT;
	try {
		((YOLO*)DS)->GetAllPokemonsByLevel(trollID, posts, numOfPost);
	}
	catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	catch (NotFound& nf) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType UpdateLikes(void *DS, int postsCode, int postsFactor) {
	if (DS == NULL || postsCode < 1 || postsFactor < 1)
		return INVALID_INPUT;
	try {
		((YOLO*)DS)->UpdateLevels(postsCode, postsFactor);
	}
	catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

void Quit(void **DS) {
		delete (YOLO*)*DS;
		*DS = NULL;
}
