
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int Toram_Common_Rooms_BossDifficultyLevelMethods_CheckDifficulty
              (int difficulty,undefined *methodInfo)

{
  if (difficulty < -1) {
    return 0;
  }
  if (3 < difficulty) {
    return 4;
  }
  return difficulty + 1;
}

