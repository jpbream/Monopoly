#pragma once

//used to backup and restore the state of the game.
// there is only one backup slot.
namespace Backup {

	//saves the state of the game, filling the backup slot. 
	//if a backup has already been made, nothing happens
	void MakeBackup();

	//restores the previously backed up game state, freeing the backup slot
	// if no backup was previously made, nothing happens
	void RestoreBackup();

}
