// Get entity from Serial

/*
  Entity is a sequence of non-space characters.
*/

/*
  Author: Martin Eden
  Last mod.: 2024-05-17
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_SerialTokenizer
{
  using namespace me_BaseTypes;

  // Get entity from serial
  TBool GetEntity(
    TChar * Entity,
    TUint_2 * EntityLength,
    TUint_2 EntityCapacity
  );

  // Implementation

  TBool StreamIsEmpty();
  TBool StockPeek(TChar * Char);
  TBool PeekCharacter(TChar * Char);

  void PurgeCharacter();
  void PurgeSpaces();
  void PurgeEntity();
}

/*
  2024-05-08
  2024-05-13
*/
